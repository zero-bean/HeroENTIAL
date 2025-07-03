#include "pch.h"
#include "Stage1.h"
#include "EngineComponents.h"
#include "GameObjects.h"
#include "GameUI.h"

Stage1::Stage1()
{
	_monsterCount = 4;
}

Stage1::~Stage1()
{
}

void Stage1::Init()
{
	LoadResources();
	LoadMap();
	LoadTileMap();
	LoadPlayer();
	LoadUI();
	LoadSound();
	InitObjects();

	Super::Init();

	LoadCamera();
}

void Stage1::Update()
{
	Super::Update();

	UIManager::GET_SINGLE()->HandleInputs();

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

void Stage1::LoadResources()
{
	// LobbyMap
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-01", L"Sprite\\Map\\Stage-01.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-01", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-01"));
	}

	// TileMap
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Tile_CanMove", L"Sprite\\Map\\Tile-CanMove.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
		ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);
	}

	// Player
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
	}

	// Minimap
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Minimap", L"Sprite\\UI\\Banners\\Banner_Minimap.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Minimap", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Minimap"), 0, 0, 128, 128);
	}

	// Inventory
	{
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
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Dungeon", L"Sprite\\UI\\Banners\\Banner_Dungeon.bmp");

		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Dungeon", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Dungeon"), 0, 0, 192, 192);
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
	}

	// Item
	{
		// 햄버거
		{
			ResourceManager::GET_SINGLE()->LoadTexture(L"Burger", L"Sprite/Item/Food/burger.bmp");
			shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Burger");
			shared_ptr<Flipbook> flipbook = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Burger");
			flipbook->SetInfo({ texture, L"Burger", {32, 32}, 0, 0, 0 });
		}
		// 스테이크
		{
			ResourceManager::GET_SINGLE()->LoadTexture(L"Steak", L"Sprite/Item/Food/steak.bmp");
			shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Steak");
			shared_ptr<Flipbook> flipbook = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Steak");
			flipbook->SetInfo({ texture, L"Steak", {32, 32}, 0, 0, 0 });
		}
		// 샌드위치
		{
			ResourceManager::GET_SINGLE()->LoadTexture(L"Sandwitch", L"Sprite/Item/Food/sandwitch.bmp");
			shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Sandwitch");
			shared_ptr<Flipbook> flipbook = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Sandwitch");
			flipbook->SetInfo({ texture, L"Sandwitch", {32, 32}, 0, 0, 0 });
		}
	}

	// Monster
	{
		// Goblin
		{
			ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Bow_Right", L"Sprite/Monster/Goblin/Goblin_Common_Bow_Right.bmp");
			ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Bow_Left", L"Sprite/Monster/Goblin/Goblin_Common_Bow_Left.bmp");
			ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Axe_Right", L"Sprite/Monster/Goblin/Goblin_Common_Axe_Right.bmp");
			ResourceManager::GET_SINGLE()->LoadTexture(L"Goblin_Axe_Left", L"Sprite/Monster/Goblin/Goblin_Common_Axe_Left.bmp");
		
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
	}

	// Bullet
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Bullet_Red", L"Sprite\\Bullet\\red.bmp", RGB(0, 0, 0));
		{
			shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Bullet_Red");
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Bullet_Red_Basic");
			fb->SetInfo({ texture, L"Bullet_Red_Basic", {16, 17}, 0, 4, 1, 0.3f });
		}
	}

	// Effect
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Effect_Red", L"Sprite\\Effect\\red.bmp", RGB(0, 0, 0));
		{
			shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Effect_Red");
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"BladeStorm_Red");
			fb->SetInfo({ texture, L"BladeStorm_Red", {32, 32}, 6, 9, 0, 0.4f });
		}
		// 폰트
		ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont", L"Font\\DungeonFont.ttf", L"DungeonFont", 24);
	}

	// GameEndPanel
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Return", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Return_Pressed", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_GameEnd", L"Sprite\\UI\\Banners\\Banner_GameEnd.bmp");

		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Return", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Return"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Return_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Return_Pressed"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_GameEnd", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_GameEnd"), 0, 0, 683, 384);

		ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont64", L"Font\\DungeonFont.ttf", L"DungeonFont", 64);
	}

	// SettingsPanel
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Back", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Back.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Back_Pressed", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Back_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Quit", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Quit.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Quit_Pressed", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Quit_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Sound", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Sound.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Sound_Pressed", L"Sprite\\UI\\Buttons\\Button_Blue_3Slides_Sound_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Settings", L"Sprite\\UI\\Banners\\Banner_Settings.bmp");

		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Back", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Back"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Back_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Back_Pressed"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Quit", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Quit"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Quit_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Quit_Pressed"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Sound", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Sound"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Sound_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Sound_Pressed"), 0, 0, 192, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Settings", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Settings"), 0, 0, 683, 384);
		
		ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont48", L"Font\\DungeonFont.ttf", L"DungeonFont", 48);
	}

	// Sound
	{
		ResourceManager::GET_SINGLE()->LoadSound(L"BGM_STAGE", L"Sound\\Sound_Stage.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_PICK", L"Sound\\Sound_Pick.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_POP", L"Sound\\Sound_Pop.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_CLICK", L"Sound\\Sound_Click.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_FIRE1", L"Sound\\Sound_Fire1.wav");
	}
}

void Stage1::LoadMap()
{
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

void Stage1::LoadPlayer()
{
	shared_ptr<Player> player = make_shared<Player>();
	player->SetCellPos({ 11,29 }, true);
	AddActor(player);

	// 미니맵
	shared_ptr<Minimap> minimap = make_shared<Minimap>();
	minimap->SetTilemap(_tilemapActor->GetTilemap());
	player->AddComponent(minimap);

	// 인벤토리
	shared_ptr<Inventory> inventory = make_shared<Inventory>();
	player->AddComponent(inventory);

	// 퀵슬롯
	shared_ptr<QuickslotPanel> quickslotUI = make_shared<QuickslotPanel>();
	quickslotUI->SetSlotsOwnerPtr(inventory);
	UIManager::GET_SINGLE()->AddUI(quickslotUI);

	// 인벤토리 UI
	shared_ptr<InventoryPanel> invenUI = make_shared<InventoryPanel>();
	invenUI->SetInventory(inventory);
	UIManager::GET_SINGLE()->AddUI(invenUI);

	// 충돌
	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_BULLET);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	player->AddComponent(collider);
}

void Stage1::LoadUI()
{
	// 결과창 패널 추가
	shared_ptr<GameEndPanel> gameEndPanel = make_shared<GameEndPanel>();
	UIManager::GET_SINGLE()->AddUI(gameEndPanel);

	// Settings
	{
		shared_ptr<SettingsMainPanel> mp = make_shared<SettingsMainPanel>();
		mp->SetSoundBtnClick([mp]() {
			mp->SetEnabled(false);
			mp->SetVisible(false);
			if (auto panel = UIManager::GET_SINGLE()->FindUI<SettingsSoundPanel>())
			{
				panel->SetEnabled(true);
				panel->SetVisible(true);
			}});
			mp->SetBackBtnClick([mp]() {
				mp->SetEnabled(false);
				mp->SetVisible(false); });
			mp->SetQuitBtnClick([]() {SceneManager::GET_SINGLE()->RequestToChangeScene(SceneType::LobbyScene); });
			UIManager::GET_SINGLE()->AddUI(mp);

			shared_ptr<SettingsSoundPanel> sp = make_shared<SettingsSoundPanel>();
			sp->SetBtnClick([sp]() {
				if (auto panel = UIManager::GET_SINGLE()->FindUI<SettingsMainPanel>())
				{
					panel->SetEnabled(true);
					panel->SetVisible(true);
				}
				sp->SetEnabled(false);
				sp->SetVisible(false); });
			UIManager::GET_SINGLE()->AddUI(sp);
	}
}

void Stage1::LoadSound()
{
	SoundManager::GET_SINGLE()->PlayBGM(L"BGM_STAGE");
}

void Stage1::LoadCamera()
{
	// 카메라
	shared_ptr<CameraController> camera = make_shared<CameraController>();
	camera->SetBackGroundRange({ 1472, 1984 });
	AddActor(camera);
	camera->SetTarget(FindActor<Player>());
}
