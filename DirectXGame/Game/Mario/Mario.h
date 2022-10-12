#pragma once
#include <dinput.h>
#include "../../Core/GameObject.h"

#define SPEED 10
class Mario: public GameObject
{
public:
	Mario();

	void Update(float deltaTime) override;
	void Render() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

