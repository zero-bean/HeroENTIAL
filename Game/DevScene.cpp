#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"

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


	ResourceManager::GET_SINGLE()->CreateSprite(L"Coin", ResourceManager::GET_SINGLE()->GetTexture(L"Coin"), 0, 0, 128, 16);

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	// TODO
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}
