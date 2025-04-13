#pragma once
#include "Component.h"

class Collider;

class Actor : public enable_shared_from_this<Actor>
{
public: 
	Actor();
	virtual ~Actor();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void SetPos(const Vec2& pos) { _pos = pos; }
	Vec2 GetPos() const { return _pos; }

	void SetDestPos(const Vec2& pos) { _destPos = pos; }
	Vec2 GetDestPos() const { return _destPos; }

	void SetScale(const float scale) { _scale = scale; }
	float GetScale() const { return _scale; }

	void SetLayer(const LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() const { return _layer; }

public:
	void AddComponent(shared_ptr<Component> component);
	void RemoveComponent(shared_ptr<Component> component);

	template<typename T>
	shared_ptr<T> FindComponent()
	{
		for (auto& component : _components)
		{
			shared_ptr<T> casted = dynamic_pointer_cast<T>(component);
			
			if (casted)
				return casted;
		}

		return nullptr;
	}

	shared_ptr<Collider> GetCollider();

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) {}
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) {}

protected:
	Vec2 _pos = { 0,0 };
	Vec2 _destPos = { 0, 0 };
	float _scale = 1.f;
	LAYER_TYPE _layer = LAYER_TYPE::LAYER_OBJECT;
	vector<shared_ptr<Component>> _components;
};

