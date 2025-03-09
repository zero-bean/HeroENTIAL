#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
	using Super = Collider;
public:
	BoxCollider();
	virtual ~BoxCollider() override;

public:
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(shared_ptr<Collider> other);

public:
	Vec2 GetSize() const { return _size; }
	void SetSize(Vec2 size) { _size = size; }

	RECT GetRect();

private:
	Vec2 _size = {};
};
