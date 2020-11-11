#pragma once

#include <iostream>

class ATarget;

class ASpell
{
    protected:
        std::string name;
        std::string effects;

    public:
        ASpell();
        ASpell(std::string const &name, std::string const &effects);
        ASpell(ASpell const &other);
        virtual ~ASpell();
        
        ASpell &operator=(ASpell const &other);

        std::string const &getName() const;
        std::string const &getEffects() const;

        void launch(ATarget const &target) const;

        virtual ASpell *clone() const = 0;

};

#include "ATarget.hpp"