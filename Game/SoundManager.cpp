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
	// ���� ����̽� ����
	if (FAILED(::DirectSoundCreate(NULL, &_soundDevice, NULL)))
	{
		::MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return;
	}

	// ���� ����̽� �������� ����
	if (FAILED(_soundDevice->SetCooperativeLevel(hwnd, DSSCL_PRIORITY)))
	{
		::MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return;
	}
}

void SoundManager::Play(const wstring& key, bool loop /*= false*/)
{
	shared_ptr<Sound> sound = ResourceManager::GET_SINGLE()->GetSound(key);
	if (sound == nullptr)
		return;

	sound->Play(loop);
}