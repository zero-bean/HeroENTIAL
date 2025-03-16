#include "pch.h"
#include "Potion.h"
#include "Player.h"
#include "DevScene.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"

unordered_map<PotionType, function<void(shared_ptr<Player>&)>> Potion::_effect = {
	{PotionType::Sandwitch,  [](std::shared_ptr<Player>& player) {
		Stat& stat = player->GetStat();
		__int32 heal = stat.hp + static_cast<__int32>(stat.maxHp * 0.3);
		stat.hp = clamp(heal, 0, stat.maxHp); }
	},
	{PotionType::Burger,  [](std::shared_ptr<Player>& player) {
		Stat& stat = player->GetStat();
		__int32 heal = stat.hp + static_cast<__int32>(stat.maxHp * 0.5);
		stat.hp = clamp(heal, 0, stat.maxHp); }
	},
	{PotionType::Steak,  [](std::shared_ptr<Player>& player) {
		Stat& stat = player->GetStat();
		__int32 heal = stat.hp + static_cast<__int32>(stat.maxHp * 0.7);
		stat.hp = clamp(heal, 0, stat.maxHp); }
	},
};

Potion::Potion()
{
	switch (_type)
	{
	case PotionType::Burger:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"Burger");
			break;
	case PotionType::Steak:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"Steak");
		break;
	case PotionType::Sandwitch:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"Sandwitch");
		break;
	}
}

Potion::~Potion()
{
}

void Potion::BeginPlay()
{
	Super::BeginPlay();


}

void Potion::Tick()
{
	Super::Tick();


}

void Potion::Render(HDC hdc)
{
	Super::Render(hdc);


}

void Potion::Use()
{
	shared_ptr<Player> player = dynamic_pointer_cast<Player>(GetOwner());
	if (player == nullptr)
		return;

	_effect[_type](player);
}

void Potion::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	shared_ptr<BoxCollider> b1 = dynamic_pointer_cast<BoxCollider>(collider);
	shared_ptr<BoxCollider> b2 = dynamic_pointer_cast<BoxCollider>(other);

	auto player = static_pointer_cast<Player>(b2->GetOwner());
	if (player)
	{
		// 인벤토리에 귀속 //
		_effect[_type](player);
		CollisionManager::GET_SINGLE()->RemoveCollider(b1);

		shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());

		if (scene == nullptr)
			return;

		scene->RemoveActor(static_pointer_cast<Actor>(shared_from_this()));
		//
		return;
	}
}

void Potion::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
}

void Potion::TickIdle()
{
}
