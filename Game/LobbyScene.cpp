#include "pch.h"
#include "LobbyScene.h"
#include "EngineComponents.h"
#include "GameObjects.h"
#include "GameUI.h"

LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
	LoadResources();
	LoadMap();
	LoadTileMap();
	LoadPlayer();
	LoadNPC();
	LoadSound();
	LoadUI();

	Super::Init();
	
	LoadCamera();
}

void LobbyScene::Update()
{
	Super::Update();
	
	UIManager::GET_SINGLE()->HandleInputs();

	/*
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::F))
		ResourceManager::GET_SINGLE()->SaveTilemap(L"Tilemap_LOBBY", L"Tilemap\\Tilemap_LOBBY.txt");
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::G))
		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_LOBBY", L"Tilemap\\Tilemap_LOBBY.txt");
	*/
}

void LobbyScene::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void LobbyScene::LoadResources()
{
	// Font
	{
		ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont64", L"Font\\DungeonFont.ttf", L"DungeonFont", 64);
		ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont48", L"Font\\DungeonFont.ttf", L"DungeonFont", 48);
		ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont32", L"Font\\DungeonFont.ttf", L"DungeonFont", 32);
	}

	// DungeonEnterPanel
	{
		// 표지
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Dungeon", L"Sprite\\UI\\Banners\\Banner_Dungeon.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Dungeon", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Dungeon"), 0, 0, 192, 192);
		// 스테이지 1 입장 버튼
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage1_Regular", L"Sprite\\UI\\Buttons\\Stage1_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage1_Pressed", L"Sprite\\UI\\Buttons\\Stage1_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage1_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage1_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage1_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage1_Pressed"), 0, 0, 64, 64);
		// 스테이지 2 입장 버튼
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage2_Regular", L"Sprite\\UI\\Buttons\\Stage2_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage2_Pressed", L"Sprite\\UI\\Buttons\\Stage2_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage2_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage2_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage2_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage2_Pressed"), 0, 0, 64, 64);
		// 스테이지 3 입장 버튼
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage3_Regular", L"Sprite\\UI\\Buttons\\Stage3_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage3_Pressed", L"Sprite\\UI\\Buttons\\Stage3_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage3_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage3_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage3_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage3_Pressed"), 0, 0, 64, 64);
		// 스테이지 4 입장 버튼
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage4_Regular", L"Sprite\\UI\\Buttons\\Stage4_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage4_Pressed", L"Sprite\\UI\\Buttons\\Stage4_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage4_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage4_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage4_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage4_Pressed"), 0, 0, 64, 64);
		// 스테이지 5 입장 버튼
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage5_Regular", L"Sprite\\UI\\Buttons\\Stage5_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage5_Pressed", L"Sprite\\UI\\Buttons\\Stage5_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage5_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage5_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage5_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage5_Pressed"), 0, 0, 64, 64);
		// 스테이지 6 입장 버튼
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage6_Regular", L"Sprite\\UI\\Buttons\\Stage6_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage6_Pressed", L"Sprite\\UI\\Buttons\\Stage6_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage6_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage6_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage6_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage6_Pressed"), 0, 0, 64, 64);
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
	}

	// QuestPanel
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Arrow_Right", L"Sprite\\UI\\Buttons\\Button_Arrow_Right.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Arrow_Right_Pressed", L"Sprite\\UI\\Buttons\\Button_Arrow_Right_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Arrow_Left", L"Sprite\\UI\\Buttons\\Button_Arrow_Left.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Arrow_Left_Pressed", L"Sprite\\UI\\Buttons\\Button_Arrow_Left_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Accept", L"Sprite\\UI\\Buttons\\Button_Accept.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Accept_Pressed", L"Sprite\\UI\\Buttons\\Button_Accept_Pressed.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Cancle", L"Sprite\\UI\\Buttons\\Button_Cancle.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Cancle_Pressed", L"Sprite\\UI\\Buttons\\Button_Cancle_Pressed.bmp");

		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Arrow_Right", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Arrow_Right"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Arrow_Right_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Arrow_Right_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Arrow_Left", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Arrow_Left"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Arrow_Left_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Arrow_Left_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Accept", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Accept"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Accept_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Accept_Pressed"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Cancle", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Cancle"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Cancle_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Cancle_Pressed"), 0, 0, 64, 64);
	}

	// LobbyMap
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-Lobby", L"Sprite\\Map\\Lobby.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-Lobby", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-Lobby"));
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

	// NPC
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Pawn_Blue", L"Sprite\\NPC\\Pawn_Blue.bmp");
		shared_ptr<Texture> texture = ResourceManager::GET_SINGLE()->GetTexture(L"Pawn_Blue");
		// IDLE
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_IdleRight");
			fb->SetInfo({ texture, L"Pawn_IdleRight", {192, 192}, 0, 5, 0, 0.6f });
		}
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_IdleLeft");
			fb->SetInfo({ texture, L"Pawn_IdleLeft", {192, 192}, 0, 5, 6, 0.6f });
		}
		// Move
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_MoveRight");
			fb->SetInfo({ texture, L"Pawn_MoveRight", {192, 192}, 0, 5, 1, 0.6f });
		}
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_MoveLeft");
			fb->SetInfo({ texture, L"Pawn_MoveLeft", {192, 192}, 0, 5, 7, 0.6f });
		}
		// Axe
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_AxeRight");
			fb->SetInfo({ texture, L"Pawn_AxeRight", {192, 192}, 0, 5, 2, 0.6f });
		}
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_AxeLeft");
			fb->SetInfo({ texture, L"Pawn_AxeLeft", {192, 192}, 0, 5, 8, 0.6f });
		}
		// Hammer
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_HammerRight");
			fb->SetInfo({ texture, L"Pawn_HammerRight", {192, 192}, 0, 5, 3, 0.6f });
		}
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_HammerLeft");
			fb->SetInfo({ texture, L"Pawn_HammerLeft", {192, 192}, 0, 5, 9, 0.6f });
		}
		// IDLE - with holding
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_HoldIdleRight");
			fb->SetInfo({ texture, L"Pawn_HoldIdleRight", {192, 192}, 0, 5, 4, 0.6f });
		}
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_HoldIdleLeft");
			fb->SetInfo({ texture, L"Pawn_HoldIdleLeft", {192, 192}, 0, 5, 10, 0.6f });
		}
		// Move - with holding
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_HoldMoveRight");
			fb->SetInfo({ texture, L"Pawn_HoldMoveRight", {192, 192}, 0, 5, 5, 0.6f });
		}
		{
			shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Pawn_HoldMoveLeft");
			fb->SetInfo({ texture, L"Pawn_HoldMoveLeft", {192, 192}, 0, 5, 11, 0.6f });
		}
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

	// Sound
	{
		ResourceManager::GET_SINGLE()->LoadSound(L"BGM_LOBBY", L"Sound\\Sound_Lobby.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_PICK", L"Sound\\Sound_Pick.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_POP", L"Sound\\Sound_Pop.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_CLICK", L"Sound\\Sound_Click.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_FIRE1", L"Sound\\Sound_Fire1.wav");
		ResourceManager::GET_SINGLE()->LoadSound(L"SFX_QUESTCLEAR", L"Sound\\Sound_QuestClear.wav");
	}
}

void LobbyScene::LoadMap()
{
	shared_ptr<Sprite> sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Stage-Lobby");
	shared_ptr<SpriteActor> background = make_shared<SpriteActor>();
	background->SetSprite(sprite);
	background->SetLayer(LAYER_BACKGROUND);
	const Vec2Int size = sprite->GetSize();
	background->SetPos(Vec2(size.x / 2, size.y / 2));
	AddActor(background);
}

void LobbyScene::LoadTileMap()
{
	shared_ptr<TilemapActor> actor = make_shared<TilemapActor>();
	AddActor(actor);

	_tilemapActor = actor;
	{
		shared_ptr<Tilemap> tilemap = ResourceManager::GET_SINGLE()->CreateTilemap(L"Tilemap_LOBBY");
		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_LOBBY", L"Tilemap\\Tilemap_LOBBY.txt");
		tilemap->SetTileSize(16);
		tilemap->SetScale(4);

		_tilemapActor->SetTilemap(tilemap);
		_tilemapActor->SetShowDebug(false);
	}
}

void LobbyScene::LoadPlayer()
{
	shared_ptr<Player> player = make_shared<Player>();
	player->SetCellPos({ 16,9 }, true);
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
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_NPC);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	player->AddComponent(collider);
}

void LobbyScene::LoadNPC()
{
	// 던전 입장 패널 추가
	shared_ptr<DungeonEnterPanel> dungeonPanel = make_shared<DungeonEnterPanel>();
	UIManager::GET_SINGLE()->AddUI(dungeonPanel);

	// 퀘스트 패널 추가
	shared_ptr<QuestPanel> questPanel = make_shared<QuestPanel>();
	UIManager::GET_SINGLE()->AddUI(questPanel);

	/* 퀘스트 NPC */
	shared_ptr<NPC> npc_Quest = make_shared<NPC>();
	npc_Quest->AddCollider({ 128,128 });
	npc_Quest->SetCellPos({ 7,8 }, true);
	npc_Quest->SetRoleText(L"<Quest>");
	npc_Quest->SetOnActivate([]() {
		if (auto questPanel = UIManager::GET_SINGLE()->FindUI<QuestPanel>())
		{
			questPanel->SetVisible(true);
			questPanel->SetEnabled(true);
		}
		});
	npc_Quest->SetOnDeActivate([]() {
		if (auto questPanel = UIManager::GET_SINGLE()->FindUI<QuestPanel>())
		{
			questPanel->SetVisible(false);
			questPanel->SetEnabled(false);
		}
		});
	AddActor(npc_Quest);

	/* 던전 NPC */
	shared_ptr<NPC> npc_Dungeon = make_shared<NPC>();
	npc_Dungeon->AddCollider({ 128,128 });
	npc_Dungeon->SetCellPos({ 16,5 }, true);
	npc_Dungeon->SetRoleText(L"<Dungeon>");
	npc_Dungeon->SetOnActivate([]() {
		if (auto dungeonPanel = UIManager::GET_SINGLE()->FindUI<DungeonEnterPanel>())
		{
			dungeonPanel->SetVisible(true);
			dungeonPanel->SetEnabled(true);
		}
		});
	npc_Dungeon->SetOnDeActivate([]() {
		if (auto dungeonPanel = UIManager::GET_SINGLE()->FindUI<DungeonEnterPanel>())
		{
			dungeonPanel->SetVisible(false);
			dungeonPanel->SetEnabled(false);
		}
		});
	AddActor(npc_Dungeon);

	/* 상점 NPC */
	shared_ptr<NPC> npc_Shop = make_shared<NPC>();
	npc_Shop->SetRoleText(L"<Shop>");
	npc_Shop->AddCollider({ 128,128 });
	npc_Shop->SetCellPos({ 24,7 }, true);
	AddActor(npc_Shop);
}

void LobbyScene::LoadSound()
{
	SoundManager::GET_SINGLE()->PlayBGM(L"BGM_LOBBY");
}

void LobbyScene::LoadUI()
{
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
		mp->SetQuitBtnClick([]() {PostQuitMessage(0); });
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

void LobbyScene::LoadCamera()
{
	// 카메라
	shared_ptr<CameraController> camera = make_shared<CameraController>();
	camera->SetBackGroundRange({ 2112, 1472 });
	AddActor(camera);
	camera->SetTarget(FindActor<Player>());
}
