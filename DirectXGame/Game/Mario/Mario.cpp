#include "Mario.h"
#include "MarioRunState.h"
#include "MarioSitState.h"

Mario::Mario(): GameObject(new MarioRunState())
{
}

void Mario::Render()
{
	VECTOR2D worldPosition = GetWorldPosition();
	this->_state->GetAnimation()->Render(worldPosition.x, worldPosition.y, false);
}
