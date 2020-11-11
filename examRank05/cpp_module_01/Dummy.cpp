#include "Dummy.hpp"

Dummy::Dummy(): ATarget("Dummy Practice") {}

Dummy::~Dummy() {}

ATarget *Dummy::clone() const 
{
	return (new Dummy(*this));
}
