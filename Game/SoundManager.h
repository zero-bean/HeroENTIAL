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

	void SetBGMVolume(float volume); 
	float GetBgmVolume() const { return _bgmVolume; }

	void SetSFXVolume(float volume);    
	float GetSFXVolume() const { return _sfxVolume; }

	LPDIRECTSOUND GetSoundDevice() { return _soundDevice; }

private:
	LONG CalculateDSVolume(float volume);

private:
	LPDIRECTSOUND _soundDevice = nullptr; // 사운드 카드
	vector<LPDIRECTSOUNDBUFFER> _SFXBuffers;
	shared_ptr<Sound> _currentBGM;
	float _bgmVolume = 1.f;
	float _sfxVolume = 1.f;
};

