#pragma once
#include "ObjectState.h"

class EmptyObjectState: public ObjectState
{
public:
	EmptyObjectState(float width, float height);
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;
};

