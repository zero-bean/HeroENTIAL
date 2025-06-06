#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "TilemapActor.h"
#include "CameraComponent.h"
#include "Player.h"
#include "Goblin.h"
#include "Bullet.h"
#include "Item.h"
#include "Potion.h"
#include "BoxCollider.h"
#include "Inventory.h"
#include "InventoryPanel.h"
#include "QuickslotPanel.h"
#include "Font.h"

DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{
	// TODO
	ResourceManager::GET_SINGLE()->LoadTexture(L"Coin", L"Sprite\\Item\\coin_gold.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-T01", L"Sprite\\Map\\test-01.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Player_Blue", L"Sprite\\Player\\Warrior_Blue.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Tile_CanMove", L"Sprite\\Map\\Tile-CanMove.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Effect_Red", L"Sprite\\Effect\\red.bmp", RGB(0, 0, 0));
	ResourceManager::GET_SINGLE()->LoadTexture(L"Bullet_Red", L"Sprite\\Bullet\\red.bmp", RGB(0, 0, 0));
	
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Bow_Right", L"Sprite/Monster/Goblin/Goblin_Common_Bow_Right.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Bow_Left", L"Sprite/Monster/Goblin/Goblin_Common_Bow_Left.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Axe_Right", L"Sprite/Monster/Goblin/Goblin_Common_Axe_Right.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Axe_Left", L"Sprite/Monster/Goblin/Goblin_Common_Axe_Left.bmp");
	
	ResourceManager::GET_SINGLE()->LoadTexture(L"Button", L"Sprite\\UI\\Buttons\\Button_Blue.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Pressed", L"Sprite\\UI\\Buttons\\Button_Blue_Pressed.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Inventory_Slot", L"Sprite\\UI\\Banners\\Carved_Regular.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Inventory_UseSlot", L"Sprite\\UI\\Banners\\Carved_3Slides.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Inventory_AllSlot", L"Sprite\\UI\\Banners\\Carved_9Slides.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Vertical", L"Sprite\\UI\\Banners\\Banner_Vertical.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Horizontal", L"Sprite\\UI\\Banners\\Banner_Horizontal.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_1", L"Sprite\\UI\\Icons\\Regular_04.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_2", L"Sprite\\UI\\Icons\\Regular_05.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_3", L"Sprite\\UI\\Icons\\Regular_06.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_1_Pressed", L"Sprite\\UI\\Icons\\Pressed_04.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_2_Pressed", L"Sprite\\UI\\Icons\\Pressed_05.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_3_Pressed", L"Sprite\\UI\\Icons\\Pressed_06.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_1_Disabled", L"Sprite\\UI\\Icons\\Disable_04.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_2_Disabled", L"Sprite\\UI\\Icons\\Disable_05.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_3_Disabled", L"Sprite\\UI\\Icons\\Disable_06.bmp");


	ResourceManager::GET_SINGLE()->CreateSprite(L"Coin", ResourceManager::GET_SINGLE()->GetTexture(L"Coin"), 0, 0, 128, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-T01", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-T01"));
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);
	
	ResourceManager::GET_SINGLE()->CreateSprite(L"Button", ResourceManager::GET_SINGLE()->GetTexture(L"Button"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Pressed"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Inventory_Slot", ResourceManager::GET_SINGLE()->GetTexture(L"Inventory_Slot"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Inventory_UseSlot", ResourceManager::GET_SINGLE()->GetTexture(L"Inventory_UseSlot"), 0, 0, 192, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Inventory_AllSlot", ResourceManager::GET_SINGLE()->GetTexture(L"Inventory_AllSlot"), 0, 0, 192, 192);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Vertical", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Vertical"), 0, 0, 192, 192);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Horizontal", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Horizontal"), 0, 0, 192, 192);

	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_1", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_1"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_2", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_2"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_3", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_3"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_1_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_1_Pressed"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_2_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_2_Pressed"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_3_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_3_Pressed"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_1_Disabled", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_1_Disabled"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_2_Disabled", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_2_Disabled"), 0, 0, 64, 64);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_3_Disabled", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_3_Disabled"), 0, 0, 64, 64);

	ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont", L"Font\\DungeonFont.ttf", L"DungeonFont", 24);

	LoadMap();
	LoadTileMap();
	LoadPlayer();
	LoadMonster();
	LoadBullet();
	LoadEffect();
	LoadItem();


	shared_ptr<Player> player = make_shared<Player>();
	player->SetCellPos({ 7,7 }, true);
	AddActor(player);

	shared_ptr<CameraComponent> camera = make_shared<CameraComponent>();
	camera->SetBackGroundRange({ 832, 832 });
	player->AddComponent(camera);

	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	player->AddComponent(collider);

	shared_ptr<Inventory> inventory = make_shared<Inventory>();
	player->AddComponent(inventory);
	LoadUI(player);

	{
		shared_ptr<Goblin> goblin_axe = make_shared<Goblin>();
		goblin_axe->SetCellPos({ 12, 12 }, true);
		goblin_axe->SetScale(4);
		AddActor(goblin_axe);

		shared_ptr<Goblin> goblin_bow = make_shared<Goblin>();
		goblin_bow->SetCellPos({ 12, 6 }, true);
		goblin_bow->SetScale(4);
		AddActor(goblin_bow);
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	// TODO
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void DevScene::LoadMap()
{
	shared_ptr<Sprite> sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Stage-T01");

	shared_ptr<SpriteActor> background = make_shared<SpriteActor>();
	background->SetSprite(sprite);
	background->SetLayer(LAYER_BACKGROUND);
	const Vec2Int size = sprite->GetSize();
	background->SetPos(Vec2(size.x / 2, size.y / 2));

	AddActor(background);
}

void DevScene::LoadTileMap()
{
	shared_ptr<TilemapActor> actor = make_shared<TilemapActor>();
	AddActor(actor);

	_tilemapActor = actor;
	{
		shared_ptr<Tilemap> tilemap = ResourceManager::GET_SINGLE()->CreateTilemap(L"Tilemap_TEST_01");
		tilemap->SetMapSize({ 52, 52 });
		tilemap->SetTileSize(16);
		tilemap->SetScale(3);

		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_TEST_01", L"Tilemap\\Tilemap_TEST_01.txt");

		_tilemapActor->SetTilemap(tilemap);
		_tilemapActor->SetShowDebug(false);
	}
}

void DevScene::LoadPlayer()
{
	shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Player_Blue");

	// IDLE
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_IdleRight");
		fb->SetInfo({ texture, L"Player_IdleRight", {192, 192}, 0, 5, 0, 0.6f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_IdleLeft");
		fb->SetInfo({ texture, L"Player_IdleLeft", {192, 192}, 0, 5, 1, 0.6f });
	}
	// Move
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_MoveRight");
		fb->SetInfo({ texture, L"Player_MoveRight", {192, 192}, 0, 5, 2, 0.6f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_MoveLeft");
		fb->SetInfo({ texture, L"Player_MoveLeft", {192, 192}, 0, 5, 3, 0.6f });
	}
	// Attack
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackRight1");
		fb->SetInfo({ texture, L"Player_AttackRight1", {192, 192}, 0, 5, 4, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackRight2");
		fb->SetInfo({ texture, L"Player_AttackRight2", {192, 192}, 0, 5, 5, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackLeft1");
		fb->SetInfo({ texture, L"Player_AttackLeft1", {192, 192}, 0, 5, 6, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackLeft2");
		fb->SetInfo({ texture, L"Player_AttackLeft2", {192, 192}, 0, 5, 7, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackDown1");
		fb->SetInfo({ texture, L"Player_AttackDown1", {192, 192}, 0, 5, 8, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackDown2");
		fb->SetInfo({ texture, L"Player_AttackDown2", {192, 192}, 0, 5, 9, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackUp1");
		fb->SetInfo({ texture, L"Player_AttackUp1", {192, 192}, 0, 5, 10, 0.4f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackUp2");
		fb->SetInfo({ texture, L"Player_AttackUp2", {192, 192}, 0, 5, 11, 0.4f, false });
	}
}

void DevScene::LoadMonster()
{
	auto LoadGoblin = [](const wstring& name) {
		shared_ptr<Texture> tx_right = ResourceManager::GET_SINGLE()->GetTexture(name + L"_Right");
		shared_ptr<Texture> tx_left = ResourceManager::GET_SINGLE()->GetTexture(name + L"_Left");

		vector<tuple<wstring, int, int, float, bool>> animations = {
			{L"Idle", 5, 0, 0.6f, true},
			{L"Move", 4, 1, 0.5f, true},
			{L"Attack", 6, 2, 0.5f, false},
			{L"Attacked", 4, 3, 0.4f, false},
			{L"Death", 8, 4, 0.8f, false},
			{L"Birth", 5, 5, 0.4f, false}
		};

		for (auto& anim : animations) {
			wstring animName;
			int frameCount, index;
			float duration;
			bool loop;
			tie(animName, frameCount, index, duration, loop) = anim;

			shared_ptr<Flipbook> fb_right = ResourceManager::GET_SINGLE()->CreateFlipbook(name + L"_Right_" + animName);
			fb_right->SetInfo({ tx_right, name + L"_Right_" + animName, {32, 32}, 0, frameCount, index, duration, loop });

			shared_ptr<Flipbook> fb_left = ResourceManager::GET_SINGLE()->CreateFlipbook(name + L"_Left_" + animName);
			fb_left->SetInfo({ tx_left, name + L"_Left_" + animName, {32, 32}, 0, frameCount, index, duration, loop });
		}
	};

	LoadGoblin(L"Goblin_Bow");
	LoadGoblin(L"Goblin_Axe");
}

void DevScene::LoadBullet()
{
	shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Bullet_Red");

	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Bullet_Red_Basic");
		fb->SetInfo({ texture, L"Bullet_Red_Basic", {16, 17}, 0, 4, 1, 0.3f });
	}
}

void DevScene::LoadEffect()
{
	shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Effect_Red");

	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"BladeStorm_Red");
		fb->SetInfo({ texture, L"BladeStorm_Red", {32, 32}, 6, 9, 0, 0.4f });
	}
}

void DevScene::LoadItem()
{
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Burger", L"Sprite/Item/Food/burger.bmp");
		shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Burger");
		shared_ptr<Flipbook> flipbook = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Burger");
		flipbook->SetInfo({ texture, L"Burger", {32, 32}, 0, 0, 0 });
	}

	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Steak", L"Sprite/Item/Food/steak.bmp");
		shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Steak");
		shared_ptr<Flipbook> flipbook = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Steak");
		flipbook->SetInfo({ texture, L"Steak", {32, 32}, 0, 0, 0 });
	}

	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Sandwitch", L"Sprite/Item/Food/sandwitch.bmp");
		shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Sandwitch");
		shared_ptr<Flipbook> flipbook = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Sandwitch");
		flipbook->SetInfo({ texture, L"Sandwitch", {32, 32}, 0, 0, 0 });
	}
}

void DevScene::LoadUI(shared_ptr<Player> player)
{
	const shared_ptr<Inventory> inven = player->FindComponent<Inventory>();
	if (!inven)
		return;

	// 퀵슬롯 UI
	shared_ptr<QuickslotPanel> quickslotUI = make_shared<QuickslotPanel>();
	quickslotUI->SetSlotsOwnerPtr(inven);
	UIManager::GET_SINGLE()->AddUI(quickslotUI);

	// 인벤토리 UI
	shared_ptr<InventoryPanel> invenUI = make_shared<InventoryPanel>();
	invenUI->SetInventory(inven);
	UIManager::GET_SINGLE()->AddUI(invenUI);
}

void DevScene::MarkTileHasItem(const Vec2Int pos, const bool check)
{
	if (!_tilemapActor)
		return;

	shared_ptr<Tilemap> tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return;

	tm->GetTileAt(pos).hasItem = check;
}

void DevScene::PickUpItem(shared_ptr<Item> item, shared_ptr<Player> player)
{
	if (!item || !player)
		return;

	// 충돌체 제거
	shared_ptr<Collider> collider = item->GetCollider();
	if (collider)
		CollisionManager::GET_SINGLE()->RemoveCollider(collider);

	// 인벤토리 귀속
	auto inventory = player->FindComponent<Inventory>();
	if (inventory)
		inventory->AddItem(item);

	// 타일 정보 갱신 및 드랍
	MarkTileHasItem(item->GetCellPos(), false);
	RemoveActor(item);
}

void DevScene::DropItem(shared_ptr<Item> item, Vec2Int desiredPos)
{
	if (!item) return;

	// 실제 드랍 가능한 위치 계산
	Vec2Int dropPos = GetClosestEmptyCellPos(desiredPos);

	// 아이템 정보 초기화
	item->GetOwner().reset();
	item->SetCellPos(dropPos, true);
	item->SetScale(1);
	item->AddCollider({ 32, 32 });

	// 타일 정보 갱신 및 드랍
	MarkTileHasItem(dropPos, true);
	AddActor(item);
}

Vec2Int DevScene::GetRandomEmptyCellPos()
{
	Vec2Int ret = { -1, -1 };

	if (_tilemapActor == nullptr)
		return ret;

	shared_ptr<Tilemap> tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	Vec2Int size = tm->GetMapSize();

	while (true)
	{
		__int32 x = rand() % size.x;
		__int32 y = rand() % size.y;
		Vec2Int cellPos{ x, y };

		if (CanGo(cellPos))
			return cellPos;
	}
}

Vec2Int DevScene::GetClosestEmptyCellPos(const Vec2Int& center)
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

		if (CanGo(curr, true))
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

weak_ptr<Player> DevScene::FindClosestPlayer(Vec2Int pos)
{
	float best = FLT_MAX;
	shared_ptr<Player> res = nullptr;

	for (shared_ptr<Actor> actor : _actors[LAYER_OBJECT])
	{
		shared_ptr<Player> player = dynamic_pointer_cast<Player>(actor);

		if (player)
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

bool DevScene::FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, __int32 maxDepth)
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

