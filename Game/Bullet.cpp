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
#include "DevScene.h"

Bullet::Bullet()
{
	_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"Bullet_Red_Basic");
}

Bullet::~Bullet()
{

}

void Bullet::BeginPlay()
{
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
	if (creature)
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
	if (_type == type)
		return;

	switch (type)
	{
	case BulletType::Basic:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"Bullet_Red_Basic");
		break;
	case BulletType::BladeStorm:
		_flipbook = ResourceManager::GET_SINGLE()->GetFlipbook(L"BladeStorm_Red");
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
	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());

	if (scene == nullptr)
		return;

	scene->RemoveActor(static_pointer_cast<Actor>(shared_from_this()));
}
