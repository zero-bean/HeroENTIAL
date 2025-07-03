#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "TilemapActor.h"
#include "Creature.h"
#include "Item.h"
#include "Player.h"
#include "Inventory.h"
#include "Tilemap.h"

Scene::Scene()
{
	_isLayerUpdateEnabled.resize(LAYER_MAXCOUNT, true);
}

Scene::~Scene()
{
	_addQueue = {};
	_removeQueue = {};
	for (auto& actors : _actors)
		actors.clear();
	_tilemapActor = nullptr;
}

void Scene::Init()
{
	// 1. 요청된 객체 추가 작업을 처리 후,
	ProcessAddActor();

	// 2. Scene 내에서 초기화
	for (vector<shared_ptr<Actor>>& actors : _actors)
		for (shared_ptr<Actor>& actor : actors)
			actor->BeginPlay();

	// 3. 그 뒤, UI 초기화를 진행
	UIManager::GET_SINGLE()->BeginPlay();
}

void Scene::Update()
{
	// 1. 요청된 객체 삭제
	ProcessRemoveActor();

	// 2. 업데이트
	for (int layer = 0; layer < LAYER_MAXCOUNT; ++layer)
	{
		if (!_isLayerUpdateEnabled[layer])
			continue;

		// 복사함으로써 Tick 동안 생명 주기 보장함
		vector<shared_ptr<Actor>> actors = _actors[layer];
		for (const auto& actor : actors)
			actor->Tick();
	}
	UIManager::GET_SINGLE()->Update();

	// 3. 요청된 객체 추가
	ProcessAddActor();
}

void Scene::Render(HDC hdc)
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->Render(hdc);

	UIManager::GET_SINGLE()->Render(hdc);
}

void Scene::AddActor(shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	// Actor 추가를 예약
	_addQueue.push(actor);
}

void Scene::RemoveActor(shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;
	
	// Actor 삭제를 예약
	_removeQueue.push(actor);
}

bool Scene::CanGo(Vec2Int cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return false;

	if (!tileMap->IsPosInRange(cellPos))
		return false;

	Tile& tile = tileMap->GetTileAt(cellPos);
	if (tile.type != TILE_TYPE::EMPTY)
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

shared_ptr<GameObject> Scene::GetGameObjectAt(const Vec2Int cellPos)
{
	for (const shared_ptr<Actor>& actor : _actors[LAYER_OBJECT])
	{
		shared_ptr<GameObject> obj = dynamic_pointer_cast<GameObject>(actor);
		if (obj && (Vec2Int)obj->GetCellPos() == cellPos)
			return obj;
	}

	return nullptr;
}

Vec2Int Scene::GetClosestEmptyCellPos(const Vec2Int& center)
{
	Vec2Int ret = { -1, -1 };

	if (_tilemapActor == nullptr)
		return ret;

	shared_ptr<Tilemap> tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	Vec2Int size = tm->GetMapSize();
	queue<Vec2Int> q;
	set<Vec2Int> visited;

	q.push(center);
	visited.insert(center);

	const Vec2Int directions[4] = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	while (!q.empty())
	{
		Vec2Int curr = q.front();
		q.pop();

		if (CanGo(curr))
			return curr;

		for (const Vec2Int& dir : directions)
		{
			Vec2Int next = curr + dir;

			if (next.x < 0 || next.y < 0 || next.x >= size.x || next.y >= size.y)
				continue;

			if (visited.find(next) != visited.end())
				continue;

			q.push(next);
			visited.insert(next);
		}
	}

	return ret;
}

void Scene::NotifyObjectMoved(shared_ptr<GameObject> obj, const Vec2Int oldPos, const Vec2Int newPos)
{
	if (!obj->ShouldAffectTilemap())
		return;

	if (shared_ptr<Tilemap> tilemap = _tilemapActor->GetTilemap())
		tilemap->UpdateTileType(oldPos, newPos, obj->GetTileType());
}

void Scene::MarkTileType(const Vec2Int pos, const TILE_TYPE tileType)
{
	if (!_tilemapActor)
		return;

	if (shared_ptr<Tilemap> tm = _tilemapActor->GetTilemap())
		tm->GetTileAt(pos).type = tileType;
}

void Scene::PickUpItem(shared_ptr<Item> item, shared_ptr<Player> player)
{
	if (!item || !player)
		return;

	// 사운드 출력
	SoundManager::GET_SINGLE()->Play(L"SFX_PICK");

	// 인벤토리 귀속
	if (auto inventory = player->FindComponent<Inventory>())
	{
		// 소유주 갱신
		item->SetOwner(player);
		inventory->AddItem(item);

		// 타일 정보 갱신 및 아이템 획득
		MarkTileType(item->GetCellPos(), TILE_TYPE::EMPTY);
		RemoveActor(item);
	}
}

void Scene::DropItem(shared_ptr<Item> item, Vec2Int pos)
{
	if (!item)
		return;

	// 사운드 출력
	SoundManager::GET_SINGLE()->Play(L"SFX_POP");

	// 실제 드랍 가능한 위치 계산
	const Vec2Int dropPos = GetClosestEmptyCellPos(pos);
	if (dropPos == Vec2Int(-1, -1))
		return;

	// 아이템 정보 초기화
	item->GetOwner().reset();
	item->SetCellPos(dropPos, true);
	item->SetScale(1);

	// 타일 정보 갱신 및 드랍
	MarkTileType(dropPos, TILE_TYPE::ITEM);
	AddActor(item);
}

void Scene::TryPickUpItem(const Vec2Int center)
{
	shared_ptr<Tilemap> tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return;

	const int maxRange = 1;
	const Vec2Int size = tm->GetMapSize();
	queue<pair<Vec2Int, int>> q;
	auto cmp = [](const Vec2Int& a, const Vec2Int& b) {
		if (a.y != b.y) return a.y < b.y;
		return a.x < b.x;
		};
	set<Vec2Int, decltype(cmp)> visited(cmp);

	q.push({ center, 0 });
	visited.insert(center);

	const Vec2Int directions[4] = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	while (!q.empty())
	{
		auto [curr, dist] = q.front();
		q.pop();

		if (dist > maxRange)
			continue;

		if (shared_ptr<Item> item = dynamic_pointer_cast<Item>(GetGameObjectAt(curr)))
		{
			if (shared_ptr<Player> player = dynamic_pointer_cast<Player>(GetGameObjectAt(center)))
			{
				PickUpItem(item, player);
				break;
			}
		}

		for (const Vec2Int& dir : directions)
		{
			Vec2Int next = curr + dir;

			if (next.x < 0 || next.y < 0 || next.x >= size.x || next.y >= size.y)
				continue;

			if (visited.find(next) != visited.end())
				continue;

			visited.insert(next);
			q.push({ next, dist + 1 });
		}
	}
}

void Scene::UpdateCellPos(shared_ptr<GameObject> obj)
{
	if (_tilemapActor == nullptr || obj == nullptr)
		return;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return;

	int tileSize = tileMap->GetTileSize() * tileMap->GetScale();
	Vec2 tilemapPos = _tilemapActor->GetPos();

	Vec2 pos = obj->GetPos() - tilemapPos;

	Vec2Int newCellPos;
	newCellPos.x = static_cast<int>(pos.x) / tileSize;
	newCellPos.y = static_cast<int>(pos.y) / tileSize;

	if (obj->GetCellPos() != newCellPos)
		obj->SetCellPos(newCellPos);
}

void Scene::ProcessAddActor()
{
	while (!_addQueue.empty())
	{
		const shared_ptr<Actor> target = _addQueue.front();
		_addQueue.pop();

		if (target)
			_actors[target->GetLayer()].push_back(target);
	}
}

void Scene::ProcessRemoveActor()
{
	while (!_removeQueue.empty())
	{
		const shared_ptr<Actor> target = _removeQueue.front();
		_removeQueue.pop();
		vector<shared_ptr<Actor>>& v = _actors[target->GetLayer()];

		// 삭제할 대상을 찾고,
		auto it = find(v.begin(), v.end(), target);
		// 발견했다면,
		if (it != v.end())
		{
			// 마지막 요소의 소유권을 뺏고,
			*it = move(v.back());
			// 비어있는 마지막 요소는 삭제
			v.pop_back();
		}
	}
}
