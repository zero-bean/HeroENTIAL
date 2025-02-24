#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "TilemapActor.h"
#include "Player.h"
#include "CameraComponent.h"


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

	ResourceManager::GET_SINGLE()->CreateSprite(L"Coin", ResourceManager::GET_SINGLE()->GetTexture(L"Coin"), 0, 0, 128, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-T01", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-T01"));
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);
	
	LoadMap();
	LoadPlayer();
	LoadTileMap();

	{
		shared_ptr<Player> player = make_shared<Player>();
		player->SetCellPos({400, 400}, true);
		AddActor(player);

		shared_ptr<CameraComponent> camera = make_shared<CameraComponent>();
		camera->SetBackGroundRange({ 832, 832 });
		player->AddComponent(camera);

		player->BeginPlay();
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	// TODO
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	{
		if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::F))
			ResourceManager::GET_SINGLE()->SaveTilemap(L"Tilemap_TEST_01", L"Tilemap\\Tilemap_TEST_01.txt");
		if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::G))
			ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_TEST_01", L"Tilemap\\Tilemap_TEST_01.txt");
	}
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
		_tilemapActor->SetShowDebug(true);
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
		fb->SetInfo({ texture, L"Player_AttackRight1", {192, 192}, 0, 5, 4, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackRight2");
		fb->SetInfo({ texture, L"Player_AttackRight2", {192, 192}, 0, 5, 5, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackLeft1");
		fb->SetInfo({ texture, L"Player_AttackLeft1", {192, 192}, 0, 5, 6, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackLeft2");
		fb->SetInfo({ texture, L"Player_AttackLeft2", {192, 192}, 0, 5, 7, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackDown1");
		fb->SetInfo({ texture, L"Player_AttackDown1", {192, 192}, 0, 5, 8, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackDown2");
		fb->SetInfo({ texture, L"Player_AttackDown2", {192, 192}, 0, 6, 9, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackUp1");
		fb->SetInfo({ texture, L"Player_AttackUp1", {192, 192}, 0, 6, 10, 0.5f });
	}
	{
		shared_ptr<Flipbook> fb = ResourceManager::GET_SINGLE()->CreateFlipbook(L"Player_AttackUp2");
		fb->SetInfo({ texture, L"Player_AttackUp2", {192, 192}, 11, 6, 0, 0.5f });
	}
}

bool DevScene::CanGo(Vec2Int cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return false;

	Tile& tile = tileMap->GetTileAt(cellPos);
	return tile.value != 1;
}

Vec2 DevScene::ConvertPos(Vec2Int cellPos)
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
