#include "Warlock.hpp"

int main(void)
{
	std::cout << "--- Constructors:\n";
	// Warlock warlock; // Doesn't compile
	Warlock richard("Richard", "Master of the Universe");
	// Warlock warlock(richard); // Doesn't compile
	// Warlock warlock = richard; // Doesn't compile

	std::cout << "--- Introduce:\n";
	richard.introduce();

	std::cout << "--- New Title:\n";
	richard.setTitle("Master of the Earth");
	richard.introduce();

	std::cout << "--- Destructors:\n";
	return (0);
}