#pragma once
#include <vector>
#include "../Utils/Property.h"
#include "../Utils/CMath.h"
#include "../Graphic/Animation.h"

using namespace::std;

class GameObject
{
public: 
	GameObject(Animation* animation);
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void Translate(float x, float y);
	virtual void Translate(VECTOR2D vec);

	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);

	VECTOR2D GetWorldPosition();

#pragma region Properties
	PROPERTY(VECTOR2D, position);
	GET(position) { return this->_position; }
	SET(position) { Translate(value); }
#pragma endregion

protected:
	Animation* _animation;
	GameObject* _parent;
	vector<GameObject*> _child;
#pragma region Transform
	VECTOR2D _position;
	MATRIX _worldMatrix;
	MATRIX _translationMatrix;
	bool _isTransformChanged;

	virtual void OnTransformChanged();

	void CalculateWorldMatrix();
	void CalculateWorldMatrix(MATRIX* matrixOut);
#pragma endregion
};

