#pragma once

enum class KeyType
{
	LEFT_MOUSE = VK_LBUTTON,
	RIGHT_MOUSE = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',

	Q = 'Q',
	W = 'W',
	E = 'E',
	R = 'R',
	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F',
	G = 'G',
	I = 'I',
};

enum class KeyState
{
	None,
	Press,
	Down,
	Up,

	End
};

enum
{
	KEY_TYPE_COUNT = static_cast<__int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<__int32>(KeyState::End)
};

class InputManager
{
public:
	static InputManager* GET_SINGLE() 
	{
		static InputManager instance;
		return &instance;
	}

private:
	InputManager() {}
	~InputManager() {}

	InputManager(const InputManager&) = delete;
	InputManager operator=(const InputManager&) = delete;

public:
	void Init(HWND hwnd);
	void Update();

public:
	// 누르고 있을 때
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }

	// 맨 처음 눌렀을 때
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// 맨 처음 눌렀다가 땔 때
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<unsigned __int8>(key)]; }

private:
	HWND _hwnd = 0;
	vector<KeyState> _states = {};
	POINT _mousePos = {};
};

