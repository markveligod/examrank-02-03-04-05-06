#include "ATarget.hpp"

ATarget::ATarget()
{}

ATarget::ATarget(std::string const &type)
{
    this->type = type;
}

ATarget::ATarget(ATarget const &other)
{
    *this = other;
}

ATarget::~ATarget()
{}

ATarget &ATarget::operator=(ATarget const &other)
{
    this->type = other.type;
    return (*this);
}

std::string const &ATarget::getType() const
{
    return (this->type);
}

void ATarget::getHitBySpell(ASpell const &spell) const
{
    std::cout << this->type << " has been " << spell.getEffects() << "!\n";
}
