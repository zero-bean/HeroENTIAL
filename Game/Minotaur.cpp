#include "pch.h"
#include "Minotaur.h"

Minotaur::Minotaur()
{
}

Minotaur::~Minotaur()
{
}

void Minotaur::BeginPlay()
{
	Super::BeginPlay();

}

void Minotaur::Tick()
{
	Super::Tick();

}

void Minotaur::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Minotaur::TickIdle()
{
}

void Minotaur::TickMove()
{
}

void Minotaur::TickAttack()
{
}

void Minotaur::TickAttacked()
{
}

void Minotaur::TickBirth()
{
}

void Minotaur::TickSkill()
{
}

void Minotaur::UpdateAnimation()
{
	Super::UpdateAnimation();

	switch (_state)
	{
	case ObjectState::Skill:
		
		break;
	}
}

void Minotaur::DropItems()
{
}
