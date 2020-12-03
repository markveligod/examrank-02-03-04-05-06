#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{}

TargetGenerator::TargetGenerator(TargetGenerator const &other)
{
    *this = other;
}

TargetGenerator &TargetGenerator::operator=(TargetGenerator const &other)
{
    this->arr_target = other.arr_target;
    return (*this);
}

TargetGenerator::~TargetGenerator()
{
    std::vector<ATarget *>::iterator it_begin = this->arr_target.begin();
    std::vector<ATarget *>::iterator it_end = this->arr_target.end();
    while (it_begin != it_end)
    {
        delete *it_begin;
        ++it_begin;
    }
    this->arr_target.clear();
}

void TargetGenerator::learnTargetType(ATarget *target_ptr)
{
    std::vector<ATarget *>::iterator it_begin = this->arr_target.begin();
    std::vector<ATarget *>::iterator it_end = this->arr_target.end();
    if (target_ptr)
    {
        while (it_begin != it_end)
        {
            if ((*it_begin)->getType() == target_ptr->getType())
                return ;
            ++it_begin;
        }
        this->arr_target.push_back(target_ptr->clone());
    }
}

void TargetGenerator::forgetTargetType(std::string const &name)
{
    std::vector<ATarget *>::iterator it_begin = this->arr_target.begin();
    std::vector<ATarget *>::iterator it_end = this->arr_target.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getType() == name)
        {
            delete *it_begin;
            this->arr_target.erase(it_begin);
            return ;
        }
        ++it_begin;
    }
}

ATarget* TargetGenerator::createTarget(std::string const &name)
{
    std::vector<ATarget *>::iterator it_begin = this->arr_target.begin();
    std::vector<ATarget *>::iterator it_end = this->arr_target.end();
    while (it_begin != it_end)
    {
        if ((*it_begin)->getType() == name)
            return (*it_begin);
        ++it_begin;
    }
    return (NULL);
}
