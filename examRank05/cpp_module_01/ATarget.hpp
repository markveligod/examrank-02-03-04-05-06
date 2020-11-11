#pragma once

#include <iostream>

class ASpell;

class ATarget
{
    protected:
        std::string type;

    public:
        ATarget();
        ATarget(std::string const &type);
        ATarget(ATarget const &other);
        virtual ~ATarget();

        ATarget &operator=(ATarget const &other);

        std::string const &getType() const;

        void getHitBySpell(ASpell const &spell) const;

        virtual ATarget *clone() const = 0;
};

#include "ASpell.hpp"
