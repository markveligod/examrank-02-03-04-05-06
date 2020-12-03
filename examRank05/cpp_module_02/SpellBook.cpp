#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::SpellBook(SpellBook const &other) { *this = other;}
SpellBook &SpellBook::operator=(SpellBook const &other)
{
    this->arr_spell = other.arr_spell;
    return (*this);
}

SpellBook::~SpellBook()
{
    std::vector<ASpell *>::iterator it_begin = this->arr_spell.begin();
    std::vector<ASpell *>::iterator it_end = this->arr_spell.end();
    while (it_begin != it_end)
    {
        delete *it_begin;
        ++it_begin;
    }
    this->arr_spell.clear();
}

void SpellBook::learnSpell(ASpell *aspell_ptr)
{
    std::vector<ASpell *>::iterator it_begin = this->arr_spell.begin();
    std::vector<ASpell *>::iterator it_end = this->arr_spell.end();
    if (aspell_ptr)
    {
        while (it_begin != it_end)
        {
            if ((*it_begin)->getName() == aspell_ptr->getName())
                return ;
            ++it_begin;
        }
        this->arr_spell.push_back(aspell_ptr->clone());
    }
}

void SpellBook::forgetSpell(std::string const &name)
{
    std::vector<ASpell *>::iterator it_begin = this->arr_spell.begin();
    std::vector<ASpell *>::iterator it_end = this->arr_spell.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == name)
        {
            delete *it_begin;
            this->arr_spell.erase(it_begin);
            return ;
        }
        ++it_begin;
    }
}

ASpell* SpellBook::createSpell(std::string const &name)
{
    std::vector<ASpell *>::iterator it_begin = this->arr_spell.begin();
    std::vector<ASpell *>::iterator it_end = this->arr_spell.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == name)
            return (*it_begin);
        ++it_begin;
    }
    return (NULL);
}

        