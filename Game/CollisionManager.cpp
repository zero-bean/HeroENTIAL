#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Actor.h"

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
    // 1. 요청된 Collider 추가 작업을 진행하고, 
    ProcessAddCollider();

    // 2. 충돌 검사를 진행한다
    for (__int32 i = 0; i < _colliders.size(); i++)
    {
        shared_ptr<BoxCollider> src = dynamic_pointer_cast<BoxCollider>(_colliders[i]);
        if (src == nullptr || src->GetOwner() == nullptr)
            continue;

        for (__int32 j = i + 1; j < _colliders.size(); j++)
        {
            shared_ptr<BoxCollider> dest = dynamic_pointer_cast<BoxCollider>(_colliders[j]);
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

    // 3. 마지막으로 요청된 Collider 삭제 작업을 진행한다
    ProcessRemoveCollider();
}

void CollisionManager::Clear()
{
    _colliders.clear();

    while (!_addQueue.empty()) 
        _addQueue.pop();

    while (!_removeQueue.empty()) 
        _removeQueue.pop();
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

void CollisionManager::ProcessAddCollider()
{
    while (!_addQueue.empty())
    {
        const shared_ptr<Collider> target = _addQueue.front();
        _addQueue.pop();

        if (target)
            _colliders.push_back(target);
    }
}

void CollisionManager::ProcessRemoveCollider()
{
    while (!_removeQueue.empty())
    {
        const shared_ptr<Collider> target = _removeQueue.front();
        _removeQueue.pop();

        // 삭제할 대상을 찾고,
        auto it = find(_colliders.begin(), _colliders.end(), target);
        // 발견했다면,
        if (it != _colliders.end())
        {
            // 마지막 요소의 소유권을 뺏고,
            *it = move(_colliders.back());
            // 비어있는 마지막 요소는 삭제
            _colliders.pop_back();
        }
    }
}
