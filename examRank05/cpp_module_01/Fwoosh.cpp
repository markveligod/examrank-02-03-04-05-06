#include "Fwoosh.hpp"

Fwoosh::Fwoosh(): ASpell("Fwoosh", "fwooshed") 
{}

Fwoosh::~Fwoosh() {}

ASpell *Fwoosh::clone(void) const 
{
	return (new Fwoosh(*this));
}
