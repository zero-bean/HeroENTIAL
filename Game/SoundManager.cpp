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
	auto sound = ResourceManager::GET_SINGLE()->GetSound(key);
	if (!sound)
		return;

	auto buffer = sound->CloneBuffer();
	if (!buffer)
		return;

	LONG dsVolume = CalculateDSVolume(_sfxVolume);
	buffer->SetVolume(dsVolume);

	buffer->SetCurrentPosition(0);
	buffer->Play(0, 0, loop ? DSBPLAY_LOOPING : 0);

	if (!loop)
		_SFXBuffers.push_back(buffer);
}


void SoundManager::PlayBGM(const wstring& key, bool loop)
{
	if (_currentBGM)
	{
		_currentBGM->Stop(true);
		_currentBGM = nullptr;
	}

	_currentBGM = ResourceManager::GET_SINGLE()->GetSound(key);

	if (_currentBGM)
	{
		SetBGMVolume(_bgmVolume);
		_currentBGM->Play(loop);
	}
}

void SoundManager::SetBGMVolume(float volume)
{
	_bgmVolume = clamp(volume, 0.0f, 1.0f);  
	if (_currentBGM)
	{
		LONG dsVolume = CalculateDSVolume(_bgmVolume);
		_currentBGM->GetBuffer()->SetVolume(dsVolume);
	}
}

void SoundManager::SetSFXVolume(float volume)
{
	_sfxVolume = clamp(volume, 0.0f, 1.0f); 
	LONG dsVolume = CalculateDSVolume(_sfxVolume);

	for (auto& buffer : _SFXBuffers)
	{
		if (buffer)
			buffer->SetVolume(dsVolume);
	}
}

LONG SoundManager::CalculateDSVolume(float volume)
{
	if (volume <= 0.0001f)
		return DSBVOLUME_MIN;

	float db = 20.0f * log10(volume);       
	LONG dsVolume = static_cast<LONG>(db * 100.0f); 

	return clamp((int)dsVolume, DSBVOLUME_MIN, DSBVOLUME_MAX);
}
