#include "pch.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Sound.h"

SoundManager::~SoundManager()
{
	if (_soundDevice)
		_soundDevice->Release();
}

void SoundManager::Init(HWND hwnd)
{
	// 사운드 디바이스 생성
	if (FAILED(::DirectSoundCreate(NULL, &_soundDevice, NULL)))
	{
		::MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
		return;
	}

	// 사운드 디바이스 협조레벨 설정
	if (FAILED(_soundDevice->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
	{
		::MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
		return;
	}
}

void SoundManager::Update()
{
	auto it = _SFXBuffers.begin();
	while (it != _SFXBuffers.end())
	{
		DWORD status = 0;

		// 재생 실패했거나 완료된 버퍼라면
		if (FAILED((*it)->GetStatus(&status)) || ((status & DSBSTATUS_PLAYING) == 0))
		{
			// 버퍼 자원 해제 후, 마지막 버퍼를 가져옵니다
			(*it)->Release();
			*it = move(_SFXBuffers.back());
			
			// 마지막 순서라면, 제거하고 검사 종료
			if (it == prev(_SFXBuffers.end()))
			{
				_SFXBuffers.pop_back();
				break;
			}
			// 마지막 순서가 아니라면, 제거하고 검사 진행
			else
			{
				_SFXBuffers.pop_back();
				continue;
			}

		}

		++it; 
	}
}

void SoundManager::Clear()
{
	for (auto& buffer : _SFXBuffers)
	{
		if (buffer)
			buffer->Release();
	}
	_SFXBuffers.clear();

	if (_currentBGM)
	{
		_currentBGM->Stop(true);
		_currentBGM = nullptr;
	}
}

void SoundManager::Play(const wstring& key, bool loop)
{
	shared_ptr<Sound> sound = ResourceManager::GET_SINGLE()->GetSound(key);
	if (sound == nullptr)
		return;

	LPDIRECTSOUNDBUFFER buffer = sound->CloneBuffer();
	if (buffer == nullptr)
		return;

	int volume = _sfxVolume;
	LONG dsVolume = (volume == 0) ? DSBVOLUME_MIN : DSBVOLUME_MIN + (DSBVOLUME_MAX - DSBVOLUME_MIN) * volume / 100;
	buffer->SetVolume(dsVolume);

	buffer->SetCurrentPosition(0);
	buffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);

	if (!loop)
		_SFXBuffers.push_back(buffer);
}

void SoundManager::PlayBGM(const wstring& key, bool loop)
{
	// 1. 재생 중인 BGM이 있다면 중단 및 삭제
	if (_currentBGM)
	{
		_currentBGM->Stop(true);
		_currentBGM = nullptr;
	}

	if (_currentBGM = ResourceManager::GET_SINGLE()->GetSound(key))
	{
		_currentBGM->Play(loop);

		// 볼륨 설정
		if (LPDIRECTSOUNDBUFFER buffer = _currentBGM->CloneBuffer())
			SetBGMVolume(_bgmVolume);
	}
}

void SoundManager::SetBGMVolume(int volume)
{
	_bgmVolume = std::clamp(volume, 0, 100);

	if (_currentBGM)
	{
		LPDIRECTSOUNDBUFFER buffer = _currentBGM->CloneBuffer();
		if (buffer)
		{
			LONG dsVolume = (_bgmVolume == 0) ? DSBVOLUME_MIN : DSBVOLUME_MIN + (DSBVOLUME_MAX - DSBVOLUME_MIN) * _bgmVolume / 100;
			buffer->SetVolume(dsVolume);
			buffer->Release();
		}
	}
}

void SoundManager::SetSFXVolume(int volume)
{
	_sfxVolume = std::clamp(volume, 0, 100);
}
