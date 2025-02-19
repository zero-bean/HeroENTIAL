#pragma once

class Actor;

class Component : public enable_shared_from_this<Component>
{
public:
	Component();
	virtual ~Component();

public:
	virtual void BeginPlay() {}
	virtual void TickComponent() {}
	virtual void Render(HDC hdc) { }

public:
	void SetOwner(shared_ptr<Actor> owner) { _owner = owner; }
	shared_ptr<Actor> GetOwner() { return _owner.lock(); }

protected:
	weak_ptr<Actor> _owner;
};

