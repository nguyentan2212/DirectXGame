#include "Mario.h"
#include "MarioRunState.h"
#include "MarioSitState.h"

Mario::Mario(): GameObject(new MarioRunState())
{
}
