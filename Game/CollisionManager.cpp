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
    // 1. ��û�� Collider �߰� �۾��� �����ϰ�, 
    ProcessAddCollider();

    // 2. �浹 �˻縦 �����Ѵ�
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

    // 3. ���������� ��û�� Collider ���� �۾��� �����Ѵ�
    ProcessRemoveCollider();
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

        // ������ ����� ã��,
        auto it = find(_colliders.begin(), _colliders.end(), target);
        // �߰��ߴٸ�,
        if (it != _colliders.end())
        {
            // �� �ڷ� ������ ���� : O(1), ����X�� ����
            iter_swap(it, prev(_colliders.end()));
            _colliders.pop_back();
        }
    }
}
