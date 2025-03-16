#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
    std::vector<std::shared_ptr<Collider>> toRemove;
    // µð¹ö±ë
    {
        int sz = colliders.size();
        int cy = colliders.capacity();
    }

    for (__int32 i = 0; i < colliders.size(); i++)
    {
        if (colliders[i].use_count() == 1) 
            toRemove.push_back(colliders[i]); 

        for (__int32 j = i + 1; j < colliders.size(); j++)
        {
            shared_ptr<Collider> src = colliders[i];
            shared_ptr<Collider> dest = colliders[j];

            if (src->GetOwner() == nullptr || dest->GetOwner() == nullptr)
                continue;

            if (src->CheckCollision(dest))
            {
                if (src->_collisionMap.contains(dest) == false)
                {
                    src->GetOwner()->OnComponentBeginOverlap(src, dest);
                    dest->GetOwner()->OnComponentBeginOverlap(dest, src);
                    src->_collisionMap.insert(dest);
                    dest->_collisionMap.insert(src);
                }
            }
            else
            {
                if (src->_collisionMap.contains(dest))
                {
                    src->GetOwner()->OnComponentEndOverlap(src, dest);
                    dest->GetOwner()->OnComponentEndOverlap(dest, src);
                    src->_collisionMap.erase(dest);
                    dest->_collisionMap.erase(src);
                }
            }
        }
    }

    for (auto& collider : toRemove)
    {
        auto it = std::find(colliders.begin(), colliders.end(), collider);

        if (it != colliders.end())
            colliders.erase(it);
    }
}

void CollisionManager::AddCollider(shared_ptr<Collider> collider)
{
	colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(shared_ptr<Collider> collider)
{
	if (collider == nullptr)
		return;

	auto it = std::find(colliders.begin(), colliders.end(), collider);
	if (it == colliders.end())
		return;

	colliders.erase(it);
}