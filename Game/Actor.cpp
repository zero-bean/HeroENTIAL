#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor()
{

}

Actor::~Actor()
{

}

void Actor::BeginPlay()
{
	for (const auto& component : _components)
		component->BeginPlay();
}

void Actor::Tick()
{
	for (const auto& component : _components)
		component->TickComponent();
}

void Actor::Render(HDC hdc)
{
	for (const auto& component : _components)
		component->Render(hdc);
}

void Actor::AddComponent(shared_ptr<Component> component)
{
    if (!component)
        return;

    component->SetOwner(weak_from_this());
    _components.push_back(component);
}

void Actor::RemoveComponent(shared_ptr<Component> component)
{
    auto findIt = std::find(_components.begin(), _components.end(), component);
    if (findIt == _components.end())
        return;

    _components.erase(findIt);
}
