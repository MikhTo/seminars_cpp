#include "game.hpp"

Unit::Unit(double health, double damage): health_(health), damage_(damage) {}
bool Unit::is_alive(){return health_ > 0;}

Swordsman::Swordsman(double health, double damage, double stamina): Unit(health, damage), stamina_(stamina){};
double Swordsman::attack()
{
    double strike = damage_*stamina_/100;
    stamina_ *= 0.5;
    return strike;
}
std::string Swordsman::get_status()
{
    return "Swordsmen:\nhealth: "+std::to_string(health_)+", stamina: " + std::to_string(stamina_);
}


Archer::Archer(double health, double damage, double accuracy): Unit(health, damage), accuracy_(accuracy){};
double Archer::attack()
{
    return damage_*accuracy_*(rand()%11);
}
std::string Archer::get_status()
{
    return "Archer:\nhealth: "+std::to_string(health_);
}

Wizard::Wizard(double health, double damage, double mana): Unit(health, damage), mana_(mana){};

double Wizard::attack()
{
    double strike = damage_*mana_/100;
    mana_ *= 0.75;
    return strike;
}
std::string Wizard::get_status()
{
    return "Wizard:\nhealth: "+std::to_string(health_)+", mana: " + std::to_string(mana_);
}


void fight(Unit* first, Unit* second) 
{
    first->health_ -= second->attack();
    second->health_ -= first->attack();
}
