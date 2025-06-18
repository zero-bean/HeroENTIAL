#include "pch.h"
#include "Minotaur.h"
#include "Player.h"
#include "SmashAttack.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Minotaur::Minotaur()
{
	_idle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Idle");
	_idle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Idle");
	_move[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Move");
	_move[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Move");
	_birth[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Idle");
	_birth[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Idle");
	_attacked[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Attacked");
	_attacked[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Attacked");
	_death[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Death");
	_death[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Death");
	_stunned[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Stunned");
	_stunned[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Stunned");

	_smash[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_AttackA");
	_smash[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_AttackA");
	_stab[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_AttackB");
	_stab[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_AttackB");
	_swing[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_SkillC");
	_swing[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_SkillC");
	_shake[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_SkillB");
	_shake[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_SkillB");
	_drag[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_SkillA");
	_drag[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_SkillA");
}

Minotaur::~Minotaur()
{
}

void Minotaur::BeginPlay()
{
	Super::BeginPlay();

	// 보스 패턴 순서 설정
	AddSequence(ObjectState::Attack);
	AddSequence(ObjectState::Attack);
	AddSequence(ObjectState::Skill);
	AddSequence(ObjectState::Attack);
	AddSequence(ObjectState::Attack);
	AddSequence(ObjectState::Skill);

	// 패턴 로직 추가
	AddPattern(L"Smash", make_shared<SmashAttack>(shared_from_this()));


	// ...
}

void Minotaur::Tick()
{
	Super::Tick();

}

void Minotaur::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Minotaur::SetPatternAnimation(const wstring& name)
{
	if (name == L"Smash")
		SetFlipbook(_smash[_animDir]);
	else if (name == L"Stab")
		SetFlipbook(_stab[_animDir]);
	else if (name == L"Swing")
		SetFlipbook(_swing[_animDir]);
	else if (name == L"Shake")
		SetFlipbook(_shake[_animDir]);
	else if (name == L"Drag")
		SetFlipbook(_drag[_animDir]);
}

void Minotaur::TickIdle()
{
	Super::TickIdle();
}

void Minotaur::TickAttack() {
	// 현재 패턴을 진행 중이라면 무시
	if (_currentPattern)
		return;

	const vector<wstring> attackPool = { L"Smash", L"Stab", L"Punch" };
	const int idx = rand() % attackPool.size();
	_currentPattern = _patterns[attackPool[idx]];
	_currentPattern->Begin();
}

void Minotaur::TickSkill()
{
	// 현재 패턴을 진행 중이라면 무시
	if (_currentPattern)
		return;

	if (_skillCount >= 2)
	{
		_currentPattern = _patterns[L"SkillC"];
	}
	else
	{
		const vector<wstring> skillPool = { L"SkillA", L"SkillB" };
		const int idx = rand() % skillPool.size();
		_currentPattern = _patterns[skillPool[idx]];
	}

	_skillCount = (_skillCount + 1) % 3;
	_currentPattern->Begin();
}

