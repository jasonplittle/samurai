#pragma once

#include "Character.hpp"




class Player : public Character
{
public:
    void Jump() override final;
    void Attack() override final;

private:


};