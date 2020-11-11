#pragma once

#include "ASpell.hpp"

class Fireball: public ASpell
{
public:
	Fireball();
	virtual ~Fireball();

	virtual ASpell *clone(void) const;
};
