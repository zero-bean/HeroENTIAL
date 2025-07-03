#include "pch.h"
#include "DamageSkin.h"
#include "Font.h"
#include "Scene.h"

DamageSkin::DamageSkin()
{
}

DamageSkin::~DamageSkin()
{
}

void DamageSkin::Tick()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_timer -= deltaTime;
	_pos.y -= _floatSpeed * deltaTime;

	if (_timer <= 0)
		OnDestroyed();
}

void DamageSkin::Render(HDC hdc)
{
	if (_font == nullptr)
		return;

	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
	Vec2 renderPos = _pos - (cameraPos - Vec2(GWinSizeX / 2, GWinSizeY / 2));

	Utils::DrawTextColored(hdc, renderPos, _text, _font->GetHandle(), _color);
}

void DamageSkin::OnDestroyed()
{
	SceneManager::GET_SINGLE()->GetCurrentScene();
	shared_ptr<Scene> scene = SceneManager::GET_SINGLE()->GetCurrentScene();

	if (scene)
		scene->RemoveActor(shared_from_this());
}
