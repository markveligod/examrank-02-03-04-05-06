#pragma once

#include "ATarget.hpp"

class BrickWall: public ATarget
{
public:
	BrickWall();
	virtual ~BrickWall();

	virtual ATarget *clone(void) const;
};