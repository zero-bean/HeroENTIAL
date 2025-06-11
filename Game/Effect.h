#pragma once
#include "GameObject.h"

class Effect : public GameObject {
	using Super = GameObject;
public:
	Effect();
	virtual ~Effect() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetDuration(float time) { _duration = time; }
	void SetAutoDestroy(bool enable) { _autoDestroy = enable; }

protected:
	float _elapsed = 0.f;
	float _duration = 1.f;
	bool _autoDestroy = true;
};
