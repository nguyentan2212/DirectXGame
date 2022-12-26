#include "ObjectPool.h"

ObjectPool* ObjectPool::_instance = nullptr;

ObjectPool::ObjectPool()
{

}

ObjectPool* ObjectPool::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new ObjectPool();
    }
    return _instance;
}

GameObject* ObjectPool::GetGameObjectWithName(string name)
{
    for (GameObject* obj : this->_objs)
    {
        if (obj->name == name)
        {
            return obj;
        }
    }
    return nullptr;
}

vector<GameObject*> ObjectPool::GetAllGameObject()
{
    return this->_objs;
}

vector<GameObject*> ObjectPool::GetAllGameObjectWithQuadtree(GameObject* obj)
{
    if (this->_quadtree == nullptr)
    {
        return vector<GameObject*>();
    }
    return this->_quadtree->Retrieve(obj);
}

vector<GameObject*> ObjectPool::GetAllGameObjectWithQuadtree()
{
    if (this->_quadtree == nullptr)
    {
        return vector<GameObject*>();
    }
    return this->_quadtree->GetAllGameObject();
}

void ObjectPool::AddGameObject(GameObject* obj)
{
    this->_objs.push_back(obj);
}

void ObjectPool::Clear()
{
    this->_objs.clear();
}

void ObjectPool::SetQuadtree(Quadtree* quadtree)
{
    this->_quadtree = quadtree;
    for (GameObject* obj : this->_objs)
    {
        this->_quadtree->Insert(obj);
    }
}

ObjectPool::~ObjectPool()
{
}
