#pragma once
#include <string>
#include "../Graphic/Animation.h"
#include "../Utils/Property.h"

using namespace::std;

class GameObject;
class ObjectState
{
public:
	ObjectState() { this->_context = nullptr; this->_animation = nullptr; }
	~ObjectState();

	/// <summary>
	/// Updates object's state based on this state.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void Update(float deltaTime) = 0;

	/// <summary>
	/// Gets the animation.
	/// </summary>
	/// <returns></returns>
	virtual Animation* GetAnimation() = 0;

	W_PROPERTY(GameObject*, context);
	SET(context) { this->_context = value; }

#pragma region Commands
	virtual void Idle() {}
	virtual void Run() {}
	virtual void Jump() {}
	virtual void Fire() {}
	virtual void Sit() {}
	virtual void Hit() {}
	virtual void Death() {}
#pragma endregion

protected:
	GameObject* _context;
	Animation* _animation;
};

