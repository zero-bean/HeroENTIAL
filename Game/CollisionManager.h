#pragma once

class Collider;

class CollisionManager
{
public:
	static CollisionManager* GET_SINGLE()
	{
		static CollisionManager instance;
		return &instance;
	}

private:
	CollisionManager() {}
	~CollisionManager() {}

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager operator=(const CollisionManager&) = delete;

public:
	void Init();
	void Update();

	void AddCollider(shared_ptr<Collider> collider);
	void RemoveCollider(shared_ptr<Collider> collider);

private:
	vector<shared_ptr<Collider>> _colliders;
};



