#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() 
{
	std::vector<ASpell *>::iterator it_begin = this->spells.begin();
    std::vector<ASpell *>::iterator it_end = this->spells.end();
    while (it_begin != it_end)
    {
        delete *it_begin;
        ++it_begin;
    }
    this->spells.clear();
}

void SpellBook::learnSpell(ASpell *spell) {
	if (spell) 
    {
		std::vector<ASpell *>::iterator it_begin = this->spells.begin();
        std::vector<ASpell *>::iterator it_end = this->spells.end();

        while (it_begin != it_end)
        {
            if ((*it_begin)->getName() == spell->getName())
                return ;
            ++it_begin;
        }
        this->spells.push_back(spell->clone());
	}
}

void SpellBook::forgetSpell(std::string const &spellName) 
{
	std::vector<ASpell *>::iterator it_begin = this->spells.begin();
    std::vector<ASpell *>::iterator it_end = this->spells.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == spellName)
        {
            delete *it_begin;
            this->spells.erase(it_begin);
            return;
        }
        ++it_begin;
    }
}

ASpell *SpellBook::generateSpell(std::string const &spellName) 
{
	std::vector<ASpell *>::iterator it_begin = this->spells.begin();
    std::vector<ASpell *>::iterator it_end = this->spells.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == spellName)
            return(*it_begin);
        ++it_begin;
    }
    return (NULL);
}