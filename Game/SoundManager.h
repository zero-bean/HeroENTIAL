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
	void Update();
	void Clear();

public:
	void Play(const wstring& key, bool loop = false);      // 효과음
	void PlayBGM(const wstring& key, bool loop = true);    // 배경음

	void SetBGMVolume(int volume); 
	void SetSFXVolume(int volume);    

	LPDIRECTSOUND GetSoundDevice() { return _soundDevice; }

private:
	LPDIRECTSOUND _soundDevice = nullptr; // 사운드 카드
	vector<LPDIRECTSOUNDBUFFER> _SFXBuffers;
	shared_ptr<Sound> _currentBGM;
	int _bgmVolume = 100;
	int _sfxVolume = 100;
};

