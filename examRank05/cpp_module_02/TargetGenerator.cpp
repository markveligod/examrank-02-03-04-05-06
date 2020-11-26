#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() 
{
	std::vector<ATarget *>::iterator it_begin = this->targets.begin();
    std::vector<ATarget *>::iterator it_end = this->targets.end();
    while (it_begin != it_end)
    {
        delete *it_begin;
        ++it_begin;
    }
    this->targets.clear();
}

void TargetGenerator::learnTargetType(ATarget *target)
{
	if (target)
	{
		std::vector<ATarget *>::iterator it_begin = this->targets.begin();
        std::vector<ATarget *>::iterator it_end = this->targets.end();
        while (it_begin != it_end)
        {
            if ((*it_begin)->getType() == target->getType())
                return ;
            ++it_begin;
        }
        this->targets.push_back(target->clone());
	}
}

void TargetGenerator::forgetTargetType(std::string const &name) 
{
    std::vector<ATarget *>::iterator it_begin = this->targets.begin();
    std::vector<ATarget *>::iterator it_end = this->targets.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getType() == name)
        {
            delete *it_begin;
            this->targets.erase(it_begin);
            return ;
        }
        ++it_begin;
    }
}

ATarget *TargetGenerator::createTarget(std::string const &name) 
{
	std::vector<ATarget *>::iterator it_begin = this->targets.begin();
    std::vector<ATarget *>::iterator it_end = this->targets.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getType() == name)
            return (*it_begin);
        ++it_begin;
    }
    return (NULL);
}
