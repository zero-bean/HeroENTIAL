#include "pch.h"
#include "GameObject.h"
#include "Scene.h"
#include "Flipbook.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);
}

void GameObject::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case ObjectState::Idle:
		TickIdle();
		break;
	case ObjectState::Move:
		TickMove();
		break;
	}
}

void GameObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

void GameObject::SetState(ObjectState state)
{
	if (_state == state)
		return;
	if (state == ObjectState::Attacked)
		_destPos = _pos;
	_state = state;
	UpdateAnimation();
}

void GameObject::SetDir(Dir dir)
{
	_dir = dir;

	if (dir == DIR_RIGHT)
		_animDir = DIR_RIGHT;
	else if (dir == DIR_LEFT)
		_animDir = DIR_LEFT;

	UpdateAnimation();
}

bool GameObject::HasReachedDest()
{
	Vec2 dir = (_destPos - _pos);
	return (dir.Length() < 5.f);
}

bool GameObject::CanGo(Vec2Int cellPos)
{
	shared_ptr<Scene> scene = SceneManager::GET_SINGLE()->GetCurrentScene();
	if (scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

Dir GameObject::GetLookAtDir(Vec2Int cellPos)
{
	Vec2Int dir = cellPos - GetCellPos();

	if (dir.x > 0)
		return DIR_RIGHT;
	else if (dir.x < 0)
		return DIR_LEFT;
	else if (dir.y > 0)
		return DIR_DOWN;
	else
		return DIR_UP;
}

void GameObject::SetCellPos(Vec2Int cellPos, bool teleport)
{
	Vec2Int oldPos = _cellPos;
	_cellPos = cellPos;

	if (shared_ptr<Scene> scene = SceneManager::GET_SINGLE()->GetCurrentScene())
	{
		_destPos = scene->ConvertPos(cellPos);
		scene->NotifyObjectMoved(static_pointer_cast<GameObject>(shared_from_this()), oldPos, _cellPos);

		if (teleport)
			_pos = _destPos;
	}
}

Vec2Int GameObject::GetFrontCellPos()
{
	switch (_dir)
	{
	case DIR_RIGHT:
		return _cellPos + Vec2Int{ 1, 0 };
	case DIR_LEFT:
		return _cellPos + Vec2Int{ -1, 0 };
	case DIR_UP:
		return _cellPos + Vec2Int{ 0, -1 };
	case DIR_DOWN:
		return _cellPos + Vec2Int{ 0, 1 };
	}

	return _cellPos;
}
