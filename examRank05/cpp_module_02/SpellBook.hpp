#pragma once

#include "ASpell.hpp"
#include <vector>
#include <cstdlib>

class SpellBook
{
    private:
    	std::vector<ASpell*> spells;

	    SpellBook(SpellBook const &other);
	    SpellBook &operator=(SpellBook const &other);

    public:
	    SpellBook();
	    virtual ~SpellBook();

	    void learnSpell(ASpell *spell);
	    void forgetSpell(std::string const &spellName);
	    ASpell *generateSpell(std::string const &spellName);

};