#include "CollisionManager.h"

CollisionManager* CollisionManager::_instance = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new CollisionManager();
    }
    return _instance;
}

DIRECTION CollisionManager::CalcAABB(GameObject* objA, GameObject* objB)
{
    return DIRECTION();
}

bool CollisionManager::IsCollision(Box boxA, Box boxB)
{
    float d1x = boxB.x - (boxA.x + boxA.width);
    float d1y = boxB.y - (boxA.y + boxA.height);
    float d2x = boxA.x - (boxB.x + boxB.width);
    float d2y = boxA.y - (boxB.y + boxB.height);

    if (d1x > 0.0f || d1y > 0.0f || d2x > 0.0f || d2y > 0.0f)
    {
        return false;
    }
    return true;
}

void CollisionManager::Processing()
{
    for (GameObject* root : this->_listeners)
    {
        for (GameObject* obj : this->_listeners)
        {
            if (root != obj)
            {
                DIRECTION direction = CalcAABB(root, obj);
                if (direction != DIRECTION::NONE)
                {
                    root->OnCollision(obj, direction);
                }
            }
        }
    }
}

void CollisionManager::AddListener(GameObject* listener)
{
    this->_listeners.push_back(listener);
}

void CollisionManager::RemoveListener(GameObject* listener)
{
    this->_listeners.remove(listener);
}
