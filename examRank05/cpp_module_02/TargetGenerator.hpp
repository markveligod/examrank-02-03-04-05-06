#pragma once

#include "ATarget.hpp"
#include <vector>

class TargetGenerator
{
    private:
        std::vector<ATarget *> arr_target;

    public:
        TargetGenerator();
        TargetGenerator(TargetGenerator const &other);
        TargetGenerator &operator=(TargetGenerator const &other);
        ~TargetGenerator();

        void learnTargetType(ATarget *target_ptr);
        void forgetTargetType(std::string const &name);
        ATarget* createTarget(std::string const &name);
};