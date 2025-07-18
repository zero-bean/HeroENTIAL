#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"

GameManager::GameManager()
{
	_questSystem = make_shared<QuestSystem>();
	_inventory = make_shared<Inventory>();
}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	_questSystem->Init();
	_inventory->BeginPlay();
}

void GameManager::Update()
{
	_inventory->TickComponent();
}

shared_ptr<QuestSystem> GameManager::GetQuestSystem() const
{
	return _questSystem;
}

shared_ptr<Inventory> GameManager::GetInventory() const
{
	return _inventory;
}