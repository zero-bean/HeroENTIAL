#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
    // 1. Remove 刚历 贸府
    while (!_removeQueue.empty())
    {
        auto target = _removeQueue.front();
        _removeQueue.pop();

        auto it = std::find(colliders.begin(), colliders.end(), target);
        if (it != colliders.end())
            colliders.erase(it);
    }

    // 2. Add 贸府
    while (!_addQueue.empty())
    {
        auto target = _addQueue.front();
        _addQueue.pop();

        colliders.push_back(target);
    }

    // 3. 面倒 八荤 矫累
    for (__int32 i = 0; i < colliders.size(); i++)
    {
        shared_ptr<Collider> src = colliders[i];
        if (src == nullptr || src->GetOwner() == nullptr)
            continue;

        for (__int32 j = i + 1; j < colliders.size(); j++)
        {
            shared_ptr<Collider> dest = colliders[j];
            if (dest == nullptr || dest->GetOwner() == nullptr)
                continue;

            if (src->CheckCollision(dest))
            {
                if (!src->_collisionMap.contains(dest))
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
}


void CollisionManager::AddCollider(shared_ptr<Collider> collider)
{
    if (collider)
        _addQueue.push(collider);
}

void CollisionManager::RemoveCollider(shared_ptr<Collider> collider)
{
    if (collider)
        _removeQueue.push(collider);
}
