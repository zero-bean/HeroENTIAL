#include "pch.h"
#include "LobbyScene.h"
#include "Actor.h"
#include "TilemapActor.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Tilemap.h"
#include "Player.h"
#include "NPC.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "UI.h"
#include "DungeonEnterPanel.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "UIManager.h"

LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
	LoadMap();
	LoadTileMap();
	shared_ptr<Player> player = LoadPlayer();
	LoadUI();
	LoadNPC();

	ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont64", L"Font\\DungeonFont.ttf", L"DungeonFont", 64);

	Super::Init();
}

void LobbyScene::Update()
{
	Super::Update();

	// TODO
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
}

void LobbyScene::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void LobbyScene::LoadMap()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-Lobby", L"Sprite\\Map\\Lobby.bmp");
	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-Lobby", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-Lobby"));
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
	// TilemapActor - TickPicking에 사용
	ResourceManager::GET_SINGLE()->LoadTexture(L"Tile_CanMove", L"Sprite\\Map\\Tile-CanMove.bmp");
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);

	shared_ptr<TilemapActor> actor = make_shared<TilemapActor>();
	AddActor(actor);

	_tilemapActor = actor;
	{
		shared_ptr<Tilemap> tilemap = ResourceManager::GET_SINGLE()->CreateTilemap(L"Tilemap_LOBBY");
		tilemap->SetMapSize({ 132, 92 });
		tilemap->SetTileSize(16);
		tilemap->SetScale(3);

		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_LOBBY", L"Tilemap\\Tilemap_LOBBY.txt");

		_tilemapActor->SetTilemap(tilemap);
		_tilemapActor->SetShowDebug(false);
	}
}

shared_ptr<Player> LobbyScene::LoadPlayer()
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

	shared_ptr<Player> player = make_shared<Player>();
	player->SetCellPos({ 21,12 }, true);
	AddActor(player);

	shared_ptr<CameraComponent> camera = make_shared<CameraComponent>();
	camera->SetBackGroundRange({ 2112, 1472 });
	player->AddComponent(camera);

	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_NPC);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	player->AddComponent(collider);

	return player;
}

void LobbyScene::LoadNPC()
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

	/* 소환 */
	shared_ptr<NPC> npc_Quest = make_shared<NPC>();
	npc_Quest->AddCollider({ 128,128 });
	npc_Quest->SetCellPos({ 8,10 }, true);
	AddActor(npc_Quest);

	shared_ptr<NPC> npc_Dungeon = make_shared<NPC>();
	npc_Dungeon->AddCollider({ 128,128 });
	npc_Dungeon->SetCellPos({ 21,6 }, true);
	npc_Dungeon->SetOnActivate([]() {
		auto dungeonPanel = UIManager::GET_SINGLE()->GetUI<DungeonEnterPanel>();
		dungeonPanel->SetIsActivated(true);
		});
	npc_Dungeon->SetOnDeActivate([]() {
		auto dungeonPanel = UIManager::GET_SINGLE()->GetUI<DungeonEnterPanel>();
		dungeonPanel->SetIsActivated(false);
		});
	AddActor(npc_Dungeon);

	shared_ptr<NPC> npc_Shop = make_shared<NPC>();
	npc_Shop->AddCollider({ 128,128 });
	npc_Shop->SetCellPos({ 33,10 }, true);
	AddActor(npc_Shop);
}

void LobbyScene::LoadUI()
{
	// Dungeon 입장 패널 - 패널 커버
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Banner_Dungeon", L"Sprite\\UI\\Banners\\Banner_Dungeon.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Banner_Dungeon", ResourceManager::GET_SINGLE()->GetTexture(L"Banner_Dungeon"), 0, 0, 192, 192);
	}
	// Dungeon 입장 패널 - 스테이지 1 입장 버튼
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage1_Regular", L"Sprite\\UI\\Buttons\\Stage1_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage1_Pressed", L"Sprite\\UI\\Buttons\\Stage1_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage1_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage1_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage1_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage1_Pressed"), 0, 0, 64, 64);
	}
	// Dungeon 입장 패널 - 스테이지 2 입장 버튼
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage2_Regular", L"Sprite\\UI\\Buttons\\Stage2_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage2_Pressed", L"Sprite\\UI\\Buttons\\Stage2_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage2_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage2_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage2_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage2_Pressed"), 0, 0, 64, 64);
	}
	// Dungeon 입장 패널 - 스테이지 3 입장 버튼
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage3_Regular", L"Sprite\\UI\\Buttons\\Stage3_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage3_Pressed", L"Sprite\\UI\\Buttons\\Stage3_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage3_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage3_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage3_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage3_Pressed"), 0, 0, 64, 64);
	}
	// Dungeon 입장 패널 - 스테이지 4 입장 버튼
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage4_Regular", L"Sprite\\UI\\Buttons\\Stage4_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage4_Pressed", L"Sprite\\UI\\Buttons\\Stage4_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage4_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage4_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage4_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage4_Pressed"), 0, 0, 64, 64);
	}
	// Dungeon 입장 패널 - 스테이지 5 입장 버튼
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage5_Regular", L"Sprite\\UI\\Buttons\\Stage5_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage5_Pressed", L"Sprite\\UI\\Buttons\\Stage5_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage5_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage5_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage5_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage5_Pressed"), 0, 0, 64, 64);
	}
	// Dungeon 입장 패널 - 스테이지 6 입장 버튼
	{
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage6_Regular", L"Sprite\\UI\\Buttons\\Stage6_Regular.bmp");
		ResourceManager::GET_SINGLE()->LoadTexture(L"Button_Stage6_Pressed", L"Sprite\\UI\\Buttons\\Stage6_Pressed.bmp");
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage6_Regular", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage6_Regular"), 0, 0, 64, 64);
		ResourceManager::GET_SINGLE()->CreateSprite(L"Button_Stage6_Pressed", ResourceManager::GET_SINGLE()->GetTexture(L"Button_Stage6_Pressed"), 0, 0, 64, 64);
	}

	shared_ptr<DungeonEnterPanel> dungeonPanel = make_shared<DungeonEnterPanel>();
	UIManager::GET_SINGLE()->AddUI(dungeonPanel);
}
