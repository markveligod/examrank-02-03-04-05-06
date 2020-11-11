#include "BrickWall.hpp"

BrickWall::BrickWall(): ATarget("BrickWall Practice") {}

BrickWall::~BrickWall() {}

ATarget *BrickWall::clone(void) const
{
	return (new BrickWall(*this));
}
