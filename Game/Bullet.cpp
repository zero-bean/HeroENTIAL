#include "pch.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "DevScene.h"

Bullet::Bullet(BulletType type)
{

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

void Bullet::TickIdle()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_timer -= deltaTime;
	_pos.y += 250 * DirVec.y * deltaTime;
	_pos.x += 250 * DirVec.x * deltaTime;

	if (_timer <= 0.f)
		OnDestroyed();
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

	scene->RemoveActor(shared_from_this());
}
