#pragma once
#include <string>
#include "../Graphic/Animation.h"
#include "../Utils/Property.h"
#include "../Utils/Debug.h"
#include "../Utils/CMath.h"

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

	/// <summary>
	/// Gets the bounding box.
	/// </summary>
	/// <returns></returns>
	virtual Box GetBoundingBox();

	W_PROPERTY(GameObject*, context);
	SET(context) { this->_context = value; }

#pragma region Commands
	virtual void Idle() {}
	/// <summary>
	/// Runs the specified speed.
	/// </summary>
	/// <param name="speed">speed smaller than 0 => run to left, greater than 0 => run to right</param>
	virtual void Run(float speed) {}
	/// <summary>
	/// Jumps the specified speed.
	/// </summary>
	/// <param name="speed">speed greater than 0 => go up</param>
	virtual void Jump(float speed) {}
	virtual void Fire() {}
	virtual void Sit() {}
	virtual void Hit() {}
	virtual void Death() {}
#pragma endregion

protected:
	GameObject* _context;
	Animation* _animation;
	float _width = 0.0f;
	float _height = 0.0f;
};

