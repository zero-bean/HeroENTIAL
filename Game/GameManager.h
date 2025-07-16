#pragma once

class Inventory;
class QuestSystem;

class GameManager
{
public:
	static GameManager* GET_SINGLE()
	{
		static GameManager instance;
		return &instance;
	}

private:
	GameManager();
	~GameManager();

	GameManager(const GameManager&) = delete;
	GameManager operator=(const GameManager&) = delete;

public:
	void Init();
	void Update();

public:
	shared_ptr<QuestSystem> GetQuestSystem() const;
	
	shared_ptr<Inventory> GetInventory() const;

private:
	shared_ptr<QuestSystem> _questSystem = nullptr;
	shared_ptr<Inventory> _inventory = nullptr;
};
