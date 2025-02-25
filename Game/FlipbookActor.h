#pragma once

#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetFlipbook(shared_ptr<Flipbook> flipbook);

	void SetScale(const __int32 scale) { _scale = scale; }
	__int32 GetScale() const { return _scale; }

	void Reset();
	bool IsAnimationEnded();

protected:
	shared_ptr<Flipbook> _flipbook = nullptr;
	float _sumTime = 0.f;
	__int32 _idx = 0;
	__int32 _scale = 1;
};

