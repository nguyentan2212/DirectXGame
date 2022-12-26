#pragma once
#include "GameObject.h"
#include "../Utils/Property.h"
#include "../Utils/CMath.h"

class Camera
{
public:
	void Update(float deltaTime);
	void Render();

	static Camera* GetInstance();
	void Init(float width, float height);
	void Follow(GameObject* obj, VECTOR2D vec = VECTOR2D(0.0f, 0.0f));
	Box GetBoundingBox();
	bool IsDrawable(Box box);

	PROPERTY(VECTOR2D, position);
	GET(position) { return this->_position; }
	SET(position) { this->_position = value; }

	PROPERTY(float, width);
	GET(width) { return this->_width; }
	SET(width) { this->_width = value; }

	PROPERTY(float, height);
	GET(height) { return this->_height; }
	SET(height) { this->_height = value; }

	PROPERTY(VECTOR2D, bottomLeft);
	GET(bottomLeft) { return this->_bottomLeft; }
	SET(bottomLeft) { this->_bottomLeft = value; }

	PROPERTY(VECTOR2D, topRight);
	GET(topRight) { return this->_topRight; }
	SET(topRight) { this->_topRight = value; }
private:
	Camera();
	~Camera();

	GameObject* _followedObj;
	VECTOR2D _translateVector;
	VECTOR2D _position;
	float _width, _height;
	VECTOR2D _bottomLeft;
	VECTOR2D _topRight;

	VECTOR2D GetFollowObjPosition();

	static Camera* _instance;
};

