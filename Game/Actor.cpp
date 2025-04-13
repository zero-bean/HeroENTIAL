#include "pch.h"
#include "Actor.h"
#include "Collider.h"

Actor::Actor()
{

}

Actor::~Actor()
{
	for (shared_ptr<Component>& component : _components)
		RemoveComponent(component);
}

void Actor::BeginPlay()
{
	for (shared_ptr<Component>& component : _components)
		component->BeginPlay();
}

void Actor::Tick()
{
	for (shared_ptr<Component> component : _components)
		component->TickComponent();
}

void Actor::Render(HDC hdc)
{
	for (shared_ptr<Component>& component : _components)
		component->Render(hdc);
}

void Actor::AddComponent(shared_ptr<Component> component)
{
    if (!component)
        return;

    component->SetOwner(shared_from_this());
    _components.push_back(component);
}

void Actor::RemoveComponent(shared_ptr<Component> component)
{
	if (component == nullptr)
		return;

    auto findIt = std::find(_components.begin(), _components.end(), component);
    if (findIt == _components.end())
        return;

    _components.erase(findIt);
}

shared_ptr<Collider> Actor::GetCollider()
{
	for (shared_ptr<Component>& component : _components)
	{
		shared_ptr<Collider> collider = dynamic_pointer_cast<Collider>(component);
		if (collider)
			return collider;
	}

	return nullptr;
}
