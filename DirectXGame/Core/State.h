#pragma once
#include <string>
#include "../Utils/Property.h"
#include "../Physic/CollisionEvent.h"
#include "../Utils/Debug.h"

using namespace::std;

class GameObject;

class State
{
public:
	State() { this->_context = nullptr; this->_name = "default"; }
	~State() {};

	virtual void OnTransition() {};
	virtual void Update(float deltaTime) {};

	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void OnCollision(CollisionEvent colEvent) {};

	PROPERTY(string, name);
	GET(name) { return this->_name; }
	SET(name) { this->_name = value; }

	W_PROPERTY(GameObject*, context);
	SET(context) { this->_context = value; }

protected:
	GameObject* _context;
	string _name;
};