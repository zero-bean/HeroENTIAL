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
	void Clear();

	void AddCollider(shared_ptr<Collider> collider);
	void RemoveCollider(shared_ptr<Collider> collider);

private:
	void ProcessAddCollider();
	void ProcessRemoveCollider();

private:
	vector<shared_ptr<Collider>> _colliders;
	queue<shared_ptr<Collider>> _addQueue;
	queue<shared_ptr<Collider>> _removeQueue;

};



