#include "pch.h"
#include "BattleScene.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "Tilemap.h"
#include "TilemapActor.h"
#include "Player.h"
#include "Monster.h"
#include "Goblin.h"
#include "Item.h"
#include "Bullet.h"
#include "Inventory.h"
#include "GameEndPanel.h"
#include "InventoryPanel.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	Super::Init();
}

void BattleScene::Update()
{
	Super::Update();
}

void BattleScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void BattleScene::InitObjects()
{
	shared_ptr<Tilemap> tilemap = _tilemapActor->GetTilemap();
	const Vec2Int mapSize = tilemap->GetMapSize();

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			Tile tile = tilemap->GetTileAt({ x,y });
			SpawnObjectFromTile({ x,y }, tile.type, tile.metadata);
			tile.metadata = {};
		}
	}
}

void BattleScene::NotifyPlayerOnDied()
{
	// 예외 처리 - 현재 구조상 반드시 인벤토리 패널부터 제거
	if (auto panel = UIManager::GET_SINGLE()->GetUI<InventoryPanel>())
		UIManager::GET_SINGLE()->RemoveUI(panel);

	// 현재는 오브젝트 타입만 제거해도 무방
	_actors[LAYER_OBJECT].clear();

	if (shared_ptr<GameEndPanel> panel = UIManager::GET_SINGLE()->GetUI<GameEndPanel>())
		panel->SetVisible(true);
}

void BattleScene::NotifyMonsterOnDied()
{
	_monsterCount -= 1;

	if (_monsterCount <= 0)
	{
		if (shared_ptr<GameEndPanel> panel = UIManager::GET_SINGLE()->GetUI<GameEndPanel>())
		{
			panel->SetOutputContent(L"Clear!");
			panel->SetVisible(true);
		}
	}
}

ObjectConfig BattleScene::ParseObjectConfig(const wstring& meta)
{
	ObjectConfig config;
	wstringstream ss(meta);
	wstring pair;

	while (getline(ss, pair, L';'))
	{
		size_t eqPos = pair.find(L'=');
		if (eqPos != std::wstring::npos)
		{
			std::wstring key = pair.substr(0, eqPos);
			std::wstring val = pair.substr(eqPos + 1);

			if (key == L"class")
				config.className = val;
			else
				config.properties[key] = val;
		}
	}

	return config;
}

Rank BattleScene::ParseRank(const wstring& rankStr)
{
	if (rankStr == L"Rare")
		return Rank::Rare;
	if (rankStr == L"Elite")
		return Rank::Elite;
	if (rankStr == L"Boss")
		return Rank::Boss;

	return Rank::Common;
}

void BattleScene::SpawnObjectFromTile(const Vec2Int& pos, TILE_TYPE type, const wstring& meta)
{
	ObjectConfig config = ParseObjectConfig(meta);

	switch (type)
	{
	case TILE_TYPE::MONSTER:
		SpawnMonster(pos, config);
		break;
	case TILE_TYPE::NPC:
		///SpawnPortal(pos, config);
		break;
	case TILE_TYPE::PLAYER:
		//SpawnPlayer(pos, config);
		break;
	case TILE_TYPE::OBJECT:
		//SpawnNPC(pos, config);
		break;
	case TILE_TYPE::ITEM:
		//SpawnItem(pos, config);
		break;
	default:
		break;
	}
}

void BattleScene::SpawnMonster(const Vec2Int pos, const ObjectConfig& config)
{
	shared_ptr<Monster> monster;

	if (config.className == L"Goblin")
	{
		shared_ptr<Goblin> goblin = std::make_shared<Goblin>();

		if (config.properties.count(L"type"))
		{
			wstring type = config.properties.at(L"type");
			goblin->SetGoblinType(type == L"BOW" ? GoblinType::Bow : GoblinType::Axe);
		}

		if (config.properties.count(L"rank"))
			goblin->SetRank(ParseRank(config.properties.at(L"rank")));

		monster = goblin;
	}

	if (monster)
	{
		monster->SetCellPos(pos, true);
		monster->SetScale(4);
		AddActor(monster);
	}
}

Vec2Int BattleScene::GetRandomEmptyCellPos()
{
	Vec2Int ret = { -1, -1 };
	int cnt = 1;

	if (_tilemapActor == nullptr)
		return ret;

	shared_ptr<Tilemap> tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	Vec2Int size = tm->GetMapSize();

	while (cnt <= 36)
	{
		__int32 x = rand() % size.x;
		__int32 y = rand() % size.y;
		Vec2Int cellPos{ x, y };

		if (CanGo(cellPos))
			return cellPos;

		cnt++;
	}

	return ret;
}

shared_ptr<Player> BattleScene::FindClosestPlayer(Vec2Int pos)
{
	float best = FLT_MAX;
	shared_ptr<Player> res = nullptr;

	for (shared_ptr<Actor> actor : _actors[LAYER_OBJECT])
	{
		if (shared_ptr<Player> player = dynamic_pointer_cast<Player>(actor))
		{
			Vec2Int dir = pos - player->GetCellPos();
			float dist = dir.LengthSquared();

			if (dist < best)
			{
				dist = best;
				res = player;
			}
		}
	}

	return res;
}

bool BattleScene::FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, __int32 maxDepth)
{
	// F = G + H
		// F = 최종 점수(작을 수록 좋음)
		// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용
		// H = 목적지에서 해당 좌표까지 이동하는데 드는 비용
	__int32 depth = abs(src.y - dest.y) + abs(src.x - dest.x);
	if (depth >= maxDepth)
		return false;

	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	map<Vec2Int, __int32> best;
	map<Vec2Int, Vec2Int> parent;

	// 초기값
	{
		__int32 cost = abs(dest.y - src.y) + abs(dest.x - src.x);

		pq.push(PQNode(cost, src));
		best[src] = cost;
		parent[src] = src;
	}

	Vec2Int front[4] =
	{
		{0, -1},
		{0, 1},
		{-1, 0},
		{1, 0},
	};

	bool found = false;

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		PQNode node = pq.top();
		pq.pop();

		// 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[node.pos] < node.cost)
			continue;

		// 목적지에 도착했으면 바로 종료
		if ((Vec2Int)node.pos == (Vec2Int)dest)
		{
			found = true;
			break;
		}

		// 방문
		for (__int32 dir = 0; dir < 4; dir++)
		{
			Vec2Int nextPos = node.pos + front[dir];

			if (CanGo(nextPos) == false)
				continue;

			__int32 depth = abs(src.y - nextPos.y) + abs(src.x - nextPos.x);
			if (depth >= maxDepth)
				continue;

			__int32 cost = abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x);
			__int32 bestValue = best[nextPos];
			if (bestValue != 0)
			{
				// 다른 경로에서 더 빠른 길을 찾았으면 스킵
				if (bestValue <= cost)
					continue;
			}

			// 예약 진행
			best[nextPos] = cost;
			pq.push(PQNode(cost, nextPos));
			parent[nextPos] = node.pos;
		}
	}

	if (found == false)
	{
		float bestScore = FLT_MAX;

		for (auto& item : best)
		{
			Vec2Int pos = item.first;
			__int32 score = item.second;

			// 동점이라면, 최초 위치에서 가장 덜 이동하는 쪽으로
			if (bestScore == score)
			{
				__int32 dist1 = abs(dest.x - src.x) + abs(dest.y - src.y);
				__int32 dist2 = abs(pos.x - src.x) + abs(pos.y - src.y);
				if (dist1 > dist2)
					dest = pos;
			}
			else if (bestScore > score)
			{
				dest = pos;
				bestScore = score;
			}
		}
	}

	path.clear();
	Vec2Int pos = dest;

	while (true)
	{
		path.push_back(pos);

		// 시작점
		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(path.begin(), path.end());
	return true;
}
