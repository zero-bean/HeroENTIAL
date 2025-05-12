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
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"

LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-Lobby", L"Sprite\\Map\\Lobby.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Tile_CanMove", L"Sprite\\Map\\Tile-CanMove.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Player_Blue", L"Sprite\\Player\\Warrior_Blue.bmp");

	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-Lobby", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-Lobby"));
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);

	LoadMap();
	LoadTileMap();
	shared_ptr<Player> player = LoadPlayer();


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
	player->SetCellPos({ 12,9 }, true);
	AddActor(player);

	shared_ptr<CameraComponent> camera = make_shared<CameraComponent>();
	camera->SetBackGroundRange({ 2112, 1472 });
	player->AddComponent(camera);

	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	player->AddComponent(collider);

	return player;
}
