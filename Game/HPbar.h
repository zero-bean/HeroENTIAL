#pragma once

#include "UI.h"

class Creature;

class HPbar : public UI
{
public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

public:
    void SetOwner(shared_ptr<Creature> owner) { _owner = owner; }
	shared_ptr<Creature> GetOwner() { return _owner.lock(); }

private:
    weak_ptr<Creature> _owner;
};

