#pragma once
#include "ResourceBase.h"

class Sound : public ResourceBase
{
public:
	Sound();
	virtual ~Sound();

public:
	bool LoadWave(fs::path fullPath);
	void Play(bool loop = false);
	void Stop(bool reset = false);

public:
	LPDIRECTSOUNDBUFFER CloneBuffer();
	LPDIRECTSOUNDBUFFER GetBuffer() const { return _soundBuffer; }

private:
	virtual void LoadFile(const wstring& path) {}
	virtual void SaveFile(const wstring& path) {}

private:
	LPDIRECTSOUNDBUFFER _soundBuffer = nullptr;
	DSBUFFERDESC _bufferDesc = {};
};