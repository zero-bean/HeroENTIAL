#include "pch.h"
#include "Minotaur.h"
#include "Player.h"
#include "BattleScene.h"
#include "SmashAttack.h"
#include "SwingStormSkill.h"

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
	_swing[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_SkillB");
	_swing[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_SkillB");
	_prepare[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Right_Prepare");
	_prepare[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Minotaur_Left_Prepare");
}

Minotaur::~Minotaur()
{
}

void Minotaur::BeginPlay()
{
	Super::BeginPlay();

	// 스텟
	SetStat(Stat(500, 500, 30, 5, 200));

	// 보스 패턴 순서 설정
	AddSequence(ObjectState::Attack);
	AddSequence(ObjectState::Attack);
	AddSequence(ObjectState::Skill);

	// 패턴 로직 추가
	AddPattern(L"Smash", make_shared<SmashAttack>(static_pointer_cast<BossMonster>(shared_from_this())));
	AddPattern(L"Swing", make_shared<SwingStormSkill>(static_pointer_cast<BossMonster>(shared_from_this())));

	// 시작
	SetState(ObjectState::Idle);
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
	else if (name == L"Prepare")
		SetFlipbook(_prepare[_animDir]);
}

void Minotaur::TickIdle()
{
	Super::TickIdle();
}

void Minotaur::TickMove()
{

	shared_ptr<Scene> scene = SceneManager::GET_SINGLE()->GetCurrentScene();
	if (!scene)
		return;

	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
	const float speed = GetStat().speed;
	const Vec2 dir = (_destPos - _pos);

	if (dir.Length() < 5.f)
	{
		_pos = _destPos;
		SetState(ObjectState::Idle);
	}
	else
	{
		bool horizontal = abs(dir.x) > abs(dir.y);

		if (horizontal)
			SetDir(dir.x < 0 ? DIR_LEFT : DIR_RIGHT);
		else
			SetDir(dir.y < 0 ? DIR_UP : DIR_DOWN);

		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= speed * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += speed * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= speed * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += speed * deltaTime;
			break;
		}

		// 움직이고 나서 Cell 좌표 갱신 요청
		scene->UpdateCellPos(dynamic_pointer_cast<GameObject>(shared_from_this()));
	}
}

void Minotaur::TickAttack() 
{
	// 현재 패턴을 진행 중이라면 무시
	if (_currentPattern)
		return;

	//const vector<wstring> attackPool = { L"Smash", L"Stab" };
	const vector<wstring> attackPool = { L"Smash" };
	const int idx = rand() % attackPool.size();
	_currentPattern = _patterns[attackPool[idx]];
	_currentPattern->Begin();
}

void Minotaur::TickSkill()
{
	// 현재 패턴을 진행 중이라면 무시
	if (_currentPattern)
		return;

	const vector<wstring> skillPool = { L"Swing" };
	const int idx = rand() % skillPool.size();
	_currentPattern = _patterns[skillPool[idx]];
	_currentPattern->Begin();
}

void Minotaur::TickDeath()
{
	Super::TickDeath();

	// 내용 추가해야 함 - 드랍, 연출, 삭제 등
}

