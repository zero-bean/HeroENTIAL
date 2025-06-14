#include "pch.h"
#include "Stage1.h"
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
#include "Player.h"
#include "Monster.h"
#include "Goblin.h"
#include "Bullet.h"
#include "Item.h"
#include "Potion.h"
#include "CameraComponent.h"
#include "Inventory.h"
#include "Minimap.h"
#include "BoxCollider.h"
#include "InventoryPanel.h"
#include "QuickslotPanel.h"
#include "Font.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Init()
{
	LoadMap();
	LoadTileMap();
	shared_ptr<Player> player = LoadPlayer();
	LoadMonster();
	LoadBullet();
	LoadEffect();
	LoadItem();
	LoadUI(player);

	InitObjects();

	Super::Init();
}

void Stage1::Update()
{
	Super::Update();

	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	/*
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::F))
		ResourceManager::GET_SINGLE()->SaveTilemap(L"Tilemap_STAGE1", L"Tilemap\\Tilemap_STAGE1.txt");
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::G))
		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_STAGE1", L"Tilemap\\Tilemap_STAGE1.txt");
	*/
}

void Stage1::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Stage1::LoadMap()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-01", L"Sprite\\Map\\Stage-01.bmp");
	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-01", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-01"));
	shared_ptr<Sprite> sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Stage-01");
	shared_ptr<SpriteActor> background = make_shared<SpriteActor>();
	background->SetSprite(sprite);
	background->SetLayer(LAYER_BACKGROUND);
	const Vec2Int size = sprite->GetSize();
	background->SetPos(Vec2(size.x / 2, size.y / 2));
	AddActor(background);
}

void Stage1::LoadTileMap()
{
	// TilemapActor - TickPicking
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Tile_CanMove", L"Sprite\\Map\\Tile-CanMove.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
		ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);
	}

	shared_ptr<TilemapActor> actor = make_shared<TilemapActor>();
	AddActor(actor);

	_tilemapActor = actor;
	{
		shared_ptr<Tilemap> tilemap = ResourceManager::GET_SINGLE()->CreateTilemap(L"Tilemap_STAGE1");
		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_STAGE1", L"Tilemap\\Tilemap_STAGE1.txt");
		ResourceManager::GET_SINGLE()->LoadTilemapMetadata(L"Tilemap_STAGE1", L"Tilemap\\Tilemap_STAGE1_meta.txt");
		tilemap->SetTileSize(16);
		tilemap->SetScale(4);

		_tilemapActor->SetTilemap(tilemap);
		_tilemapActor->SetShowDebug(false);
	}
}

shared_ptr<Player> Stage1::LoadPlayer()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Player_Blue", L"Sprite\\Player\\Warrior_Blue.bmp");
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
	// Attacked
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackedRight");
		fb->SetInfo({ texture, L"Player_AttackedRight", {192, 192}, 0, 5, 12, 0.2f, false });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackedLeft");
		fb->SetInfo({ texture, L"Player_AttackedLeft", {192, 192}, 0, 5, 13, 0.2f, false });
	}
	// Minimap
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Minimap", L"Sprite\\UI\\Banners\\Banner_Minimap.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Minimap", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Minimap"), 0, 0, 128, 128);
	}
	shared_ptr<Player> player = make_shared<Player>();
	player->SetCellPos({ 11,29 }, true);
	AddActor(player);

	shared_ptr<Inventory> inventory = make_shared<Inventory>();
	player->AddComponent(inventory);

	shared_ptr<CameraComponent> camera = player->FindComponent<CameraComponent>();
	if (!camera)
	{
		camera = make_shared<CameraComponent>();
		player->AddComponent(camera);
	}
	camera->SetBackGroundRange({ 1472, 1984 });

	shared_ptr<Minimap> minimap = make_shared<Minimap>();
	minimap->SetTilemap(_tilemapActor->GetTilemap());
	player->AddComponent(minimap);

	shared_ptr<BoxCollider> collider = player->FindComponent<BoxCollider>();
	if (!collider)
	{
		collider = make_shared<BoxCollider>();
		player->AddComponent(collider);
	}
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_NPC);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	
	return player;
}

void Stage1::LoadMonster()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Bow_Right", L"Sprite/Monster/Goblin/Goblin_Common_Bow_Right.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Bow_Left", L"Sprite/Monster/Goblin/Goblin_Common_Bow_Left.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Axe_Right", L"Sprite/Monster/Goblin/Goblin_Common_Axe_Right.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Axe_Left", L"Sprite/Monster/Goblin/Goblin_Common_Axe_Left.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Minotaur", L"Sprite/Monster/Minotaur/Minotaur_Right.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Minotaur", L"Sprite/Monster/Minotaur/Minotaur_Left.bmp");

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

	auto LoadMinotaur = [](const wstring& name) {
		shared_ptr<Texture> tx_right = ResourceManager::GET_SINGLE()->GetTexture(name + L"_Right");
		shared_ptr<Texture> tx_left = ResourceManager::GET_SINGLE()->GetTexture(name + L"_Left");

		vector<tuple<wstring, int, int, float, bool>> animations = {
			{L"Idle", 4, 0, 0.5f, true},
			{L"Move", 7, 1, 0.5f, true},
			{L"SkillA", 4, 2, 0.5f, false},
			{L"AttackA", 8, 3, 0.7f, false},
			{L"AttackB", 4, 4, 0.3f, false},
			{L"SkillB", 5, 5, 0.5f, false},
			{L"SkillC", 8, 6, 0.5f, false},
			{L"Attacked", 2, 8, 0.1f, false},
			{L"Death", 5, 9, 0.4f, false},
		};

		for (auto& anim : animations) {
			wstring animName;
			int frameCount, index;
			float duration;
			bool loop;
			tie(animName, frameCount, index, duration, loop) = anim;

			shared_ptr<Flipbook> fb_right = ResourceManager::GET_SINGLE()->CreateFlipbook(name + L"_Right_" + animName);
			fb_right->SetInfo({ tx_right, name + L"_Right_" + animName, {96, 96}, 0, frameCount, index, duration, loop });

			shared_ptr<Flipbook> fb_left = ResourceManager::GET_SINGLE()->CreateFlipbook(name + L"_Left_" + animName);
			fb_left->SetInfo({ tx_left, name + L"_Left_" + animName, {96, 96}, 0, frameCount, index, duration, loop });
		}
		};

	LoadMinotaur(L"Minotaur");
}

void Stage1::LoadBullet()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Bullet_Red", L"Sprite\\Bullet\\red.bmp", RGB(0, 0, 0));

	shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Bullet_Red");

	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Bullet_Red_Basic");
		fb->SetInfo({ texture, L"Bullet_Red_Basic", {16, 17}, 0, 4, 1, 0.3f });
	}
}

void Stage1::LoadEffect()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Effect_Red", L"Sprite\\Effect\\red.bmp", RGB(0, 0, 0));

	shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Effect_Red");

	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"BladeStorm_Red");
		fb->SetInfo({ texture, L"BladeStorm_Red", {32, 32}, 6, 9, 0, 0.4f });
	}

	// 폰트
	ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont", L"Font\\DungeonFont.ttf", L"DungeonFont", 24);
}

void Stage1::LoadItem()
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

void Stage1::LoadUI(shared_ptr<Player> player)
{
	// 인벤토리 UI
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button", L"Sprite\\UI\\Buttons\\Button_Blue.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Pressed", L"Sprite\\UI\\Buttons\\Button_Blue_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Inventory_Slot", L"Sprite\\UI\\Banners\\Carved_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Inventory_UseSlot", L"Sprite\\UI\\Banners\\Carved_3Slides.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Inventory_AllSlot", L"Sprite\\UI\\Banners\\Carved_9Slides.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Vertical", L"Sprite\\UI\\Banners\\Banner_Vertical.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Horizontal", L"Sprite\\UI\\Banners\\Banner_Horizontal.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Dungeon", L"Sprite\\UI\\Banners\\Banner_Dungeon.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_1", L"Sprite\\UI\\Icons\\Regular_04.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_2", L"Sprite\\UI\\Icons\\Regular_05.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_3", L"Sprite\\UI\\Icons\\Regular_06.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_1_Pressed", L"Sprite\\UI\\Icons\\Pressed_04.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_2_Pressed", L"Sprite\\UI\\Icons\\Pressed_05.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_3_Pressed", L"Sprite\\UI\\Icons\\Pressed_06.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_1_Disabled", L"Sprite\\UI\\Icons\\Disable_04.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_2_Disabled", L"Sprite\\UI\\Icons\\Disable_05.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Icon_3_Disabled", L"Sprite\\UI\\Icons\\Disable_06.bmp");

		ResourceManager::GET_SINGLE()->CreateSprite(L"Button", ResourceManager::GET_SINGLE()->GetTexture(L"Button"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Inventory_Slot", ResourceManager::GET_SINGLE()->GetTexture(L"Inventory_Slot"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Inventory_UseSlot", ResourceManager::GET_SINGLE()->GetTexture(L"Inventory_UseSlot"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Inventory_AllSlot", ResourceManager::GET_SINGLE()->GetTexture(L"Inventory_AllSlot"), 0, 0, 192, 192);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Vertical", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Vertical"), 0, 0, 192, 192);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Horizontal", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Horizontal"), 0, 0, 192, 192);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Dungeon", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Dungeon"), 0, 0, 192, 192);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_1", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_1"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_2", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_2"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_3", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_3"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_1_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_1_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_2_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_2_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_3_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_3_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_1_Disabled", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_1_Disabled"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_2_Disabled", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_2_Disabled"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Icon_3_Disabled", ResourceManager::GET_SINGLE()->GetTexture(L"Icon_3_Disabled"), 0, 0, 64, 64);
	}

	// 인벤토리 패널 추가
	if (const shared_ptr<Inventory> inven = player->FindComponent<Inventory>())
	{
		// 퀵슬롯 UI
		shared_ptr<QuickslotPanel> quickslotUI = make_shared<QuickslotPanel>();
		quickslotUI->SetSlotsOwnerPtr(inven);
		UIManager::GET_SINGLE()->AddUI(quickslotUI);

		// 인벤토리 UI
		shared_ptr<InventoryPanel> invenUI = UIManager::GET_SINGLE()->GetUI<InventoryPanel>();
		if (!invenUI)
		{
			invenUI = make_shared<InventoryPanel>();
			invenUI->SetInventory(inven);
			UIManager::GET_SINGLE()->AddUI(invenUI);
		}
	}
}
