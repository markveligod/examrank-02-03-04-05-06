#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title)
{
    this->name = name;
    this->title = title;
    std::cout << this->name << ": This looks like another boring day.\n";
}

Warlock::~Warlock()
{
    std::cout << this->name << ": My job here is done!\n";
    std::vector<ASpell *>::iterator it_begin = this->spells.begin();
    std::vector<ASpell *>::iterator it_end = this->spells.end();
    while (it_begin != it_end)
    {
        delete *it_begin;
        ++it_begin;
    }
}

std::string const &Warlock::getName() const
{
    return (this->name);
}

std::string const &Warlock::getTitle() const
{
    return (this->title);
}

void Warlock::setTitle(std::string const &title)
{
    this->title = title;
}

void Warlock::introduce() const
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void Warlock::learnSpell(ASpell *spell)
{
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

void Warlock::forgetSpell(std::string const &spellName)
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

void Warlock::launchSpell(std::string const &spellName, ATarget const &target)
{
    std::vector<ASpell *>::iterator it_begin = this->spells.begin();
    std::vector<ASpell *>::iterator it_end = this->spells.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == spellName)
        {
            (*it_begin)->launch(target);
            return;
        }
        ++it_begin;
    }
}
