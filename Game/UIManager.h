#pragma once

class UI;
class Slot;

struct DragState
{
public:
	void BeginDrag(shared_ptr<Slot> slot)
	{
		active = true;
		this->slot = slot;
	}

	void EndDrag()
	{
		active = false;
		slot = nullptr;
	}

	bool IsDrag() const { return active; }

	shared_ptr<Slot> GetSlot() const { return slot; }

private:
	bool active = false;
	shared_ptr<Slot> slot = nullptr;
};

class UIManager
{
public:
    static UIManager* GET_SINGLE()
    {
        static UIManager instance;
        return &instance;
    }

private:
    UIManager() {}
    ~UIManager() {};

    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

public:
    void Init(HWND hwnd);
	void BeginPlay();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	DragState& GetDragState() { return _drag; }
	void SetDragState(DragState drag) { _drag = drag; }

	void AddUI(shared_ptr<UI> ui);
	void RemoveUI(shared_ptr<UI> ui);

	bool IsMouseInUIs();

public:
	template<typename T>
	shared_ptr<T> GetUI()
	{
		for (auto& ui : _uis) {
			if (auto casted = dynamic_pointer_cast<T>(ui)) 
				return casted;
		}

		return nullptr;
	}

private:
    HWND _hwnd = nullptr;
	DragState _drag = {};
	vector<shared_ptr<UI>> _uis;
	queue<shared_ptr<UI>> _addQueue;
	queue<shared_ptr<UI>> _removeQueue;
};
