#include "pch.h"
#include "Potion.h"
#include "Player.h"
#include "DevScene.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Inventory.h"

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

void Potion::UpdateAnimation()
{
	switch (_type)
	{
	case PotionType::Sandwitch:
		SetFlipbook(ResourceManager::GET_SINGLE()->GetFlipbook(L"Sandwitch"));
		SetItemContent({ L"샌드위치",
			L"공방일체, 완벽한 밸런스와 건강까지 한 번에 잡았다!",
			L"플레이어의 체력을 30% 회복한다." });
		SetObjectID(110);
		break;
	case PotionType::Burger:
		SetFlipbook(ResourceManager::GET_SINGLE()->GetFlipbook(L"Burger"));
		SetItemContent({ L"햄버거",
			L"무슨 말이 필요할까." L" JUST EAT IT!",
			L"플레이어의 체력을 50% 회복한다." });
		SetObjectID(111);
		break;
	case PotionType::Steak:
		SetFlipbook(ResourceManager::GET_SINGLE()->GetFlipbook(L"Steak"));
		SetItemContent({ L"스테이크",
			L"육즙이 흘러 넘친다. " 
			L"질기지도 않고 느끼하지도 않아서, 육식파에게 사랑받는 음식이다!",
			L"플레이어의 체력을 70% 회복한다." });
		SetObjectID(112);
		break;
	}
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
	Super::OnComponentBeginOverlap(collider, other);
}

void Potion::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	Super::OnComponentEndOverlap(collider, other);
}

void Potion::TickIdle()
{
}

void Potion::SetPotionType(PotionType type)
{
	if (_type == type)
		return;

	_type = type;
	UpdateAnimation();
}
