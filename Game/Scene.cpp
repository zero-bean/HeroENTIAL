#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "TilemapActor.h"
#include "Creature.h"
#include "Tilemap.h"

Scene::Scene()
{

}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->BeginPlay();
}

void Scene::Update()
{
	for (const vector<shared_ptr<Actor>> actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->Render(hdc);
}

void Scene::AddActor(shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;
	
	vector<shared_ptr<Actor>>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

bool Scene::CanGo(Vec2Int cellPos, bool checkItem)
{
	if (_tilemapActor == nullptr)
		return false;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return false;

	Tile& tile = tileMap->GetTileAt(cellPos);
	if (tile.value == 1)
		return false;

	if (checkItem && tile.hasItem)
		return false;

	return true;
}

Vec2 Scene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	if (_tilemapActor == nullptr)
		return ret;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return ret;

	__int32 size = tileMap->GetTileSize() * tileMap->GetScale();
	Vec2 pos = _tilemapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + (size / 2);
	ret.y = pos.y + cellPos.y * size + (size / 2);

	return ret;
}

shared_ptr<Creature> Scene::GetCreatureAt(Vec2Int cellPos)
{
	for (const shared_ptr<Actor>& actor : _actors[LAYER_OBJECT])
	{
		// GameObjectType
		shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(actor);
		if (creature && (Vec2Int)creature->GetCellPos() == cellPos)
			return creature;
	}

	return nullptr;
}

