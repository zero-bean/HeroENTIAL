#include "pch.h"
#include "Bullet.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "BattleScene.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::BeginPlay()
{
	SetBulletType(_type);

	Super::BeginPlay();
}

void Bullet::Tick()
{
	Super::Tick();

}

void Bullet::Render(HDC hdc)
{
	Super::Render(hdc);


}

void Bullet::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{

	shared_ptr<BoxCollider> b1 = dynamic_pointer_cast<BoxCollider>(collider);
	shared_ptr<BoxCollider> b2 = dynamic_pointer_cast<BoxCollider>(other);

	auto creature = static_pointer_cast<Creature>(b2->GetOwner());
	if (b1->CheckCollision(b2) && creature)
	{
		creature->OnDamaged(static_pointer_cast<Projectile>(shared_from_this()));
		OnDestroyed();
		CollisionManager::GET_SINGLE()->RemoveCollider(b1);
		return;
	}
}

void Bullet::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{

}

void Bullet::AddCollider(const Vec2 size)
{
	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->SetSize(size);
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	AddComponent(collider);
}

void Bullet::TickIdle()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_timer -= deltaTime;
	_pos.y += 250 * DirVec.y * deltaTime;
	_pos.x += 250 * DirVec.x * deltaTime;

	if (_timer <= 0.f)
		OnDestroyed();
}

void Bullet::SetBulletType(BulletType type)
{
	_type = type;

	switch (type)
	{
	case BulletType::Basic:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"Bullet_Red_Basic");
		SetScale(2.f);
		AddCollider({ 32,32 });
		break;
	case BulletType::BladeStorm:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"BladeStorm_Red");
		SetScale(3.5f);
		shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
		collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_BULLET);
		collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
		collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
		collider->RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
		collider->SetSize({ 80, 80 });
		CollisionManager::GET_SINGLE()->AddCollider(collider);
		AddComponent(collider);
		break;
	}
}

void Bullet::SetDirVec(const Vec2 sp, const Vec2 lp)
{
	DirVec = lp - sp;
	DirVec.Normalize();
}


void Bullet::OnDestroyed()
{
	if (shared_ptr<BattleScene> scene
		= static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
		scene->RemoveActor(static_pointer_cast<Actor>(shared_from_this()));
}
