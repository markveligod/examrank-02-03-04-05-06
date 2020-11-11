#pragma once

#include "ASpell.hpp"

class Fwoosh: public ASpell
{
    public:
	    Fwoosh();
	    virtual ~Fwoosh();

	    virtual ASpell *clone(void) const;
};
