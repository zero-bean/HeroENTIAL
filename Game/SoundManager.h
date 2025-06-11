#pragma once

class SoundManager
{
public:
	static SoundManager* GET_SINGLE()
	{
		static SoundManager instance;
		return &instance;
	}

private:
	SoundManager() {};
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

public:
	void Init(HWND hwnd);
	void Play(const wstring& key, bool loop = false);

	LPDIRECTSOUND GetSoundDevice() { return _soundDevice; }

private:
	LPDIRECTSOUND _soundDevice = nullptr; // 사운드 카드
};

