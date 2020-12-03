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
    std::vector<ASpell *>::iterator it_begin = this->arr.begin();
    std::vector<ASpell *>::iterator it_end = this->arr.end();
    while (it_begin != it_end)
    {
        delete *it_begin;
        ++it_begin;
    }
    this->arr.clear();
}

std::string const &Warlock::getName() const { return (this->name);}
std::string const &Warlock::getTitle() const { return (this->title);}

void Warlock::setTitle(std::string const &title) { this->title = title;}

void Warlock::introduce() const { std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";}

void Warlock::learnSpell(ASpell *aspell_ptr)
{
    std::vector<ASpell *>::iterator it_begin = this->arr.begin();
    std::vector<ASpell *>::iterator it_end = this->arr.end();
    if (aspell_ptr)
    {
        while (it_begin != it_end)
        {
            if ((*it_begin)->getName() == aspell_ptr->getName())
                return ;
            ++it_begin;
        }
        this->arr.push_back(aspell_ptr->clone());
    }
}

void Warlock::forgetSpell(std::string name)
{
    std::vector<ASpell *>::iterator it_begin = this->arr.begin();
    std::vector<ASpell *>::iterator it_end = this->arr.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == name)
        {
            delete *it_begin;
            this->arr.erase(it_begin);
            return ;
        }
        ++it_begin;
    }
}

void Warlock::launchSpell(std::string name, ATarget const &atarget_ref)
{
    std::vector<ASpell *>::iterator it_begin = this->arr.begin();
    std::vector<ASpell *>::iterator it_end = this->arr.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getName() == name)
        {
            (*it_begin)->launch(atarget_ref);
            return ;
        }
        ++it_begin;
    }
}
