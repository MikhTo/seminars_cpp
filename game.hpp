#pragma once
#include <string>
#include <random>
class Unit
{
    protected:
    double health_;
    double damage_;
    public:
    
    Unit (double, double);

    //Таким образом создается чистый виртуальный (абстрактный метод)
    //Класс тоже становится абстактным: нельзя создавать объекты этого класса,
    //но можно наследоваться
    virtual double attack() = 0;
    virtual std::string get_status() = 0;

    //А этот метод будет просто наследоваться
    bool is_alive();

    //Можно создавать функции, которые будут иметь доступ к закрытым полям класса
    //Такие функции называются функции -- друзья класса
    friend void fight(Unit*, Unit*);
};

void fight(Unit*, Unit*);

class Swordsman: public Unit
{
    private:
    double stamina_;
    public:
    Swordsman(double, double, double);
    double attack();
    std::string get_status();
};

class Archer: public Unit
{
    private:
    double accuracy_;
    public:
    Archer(double, double, double);
    double attack();
    std::string get_status();
};

class Wizard: public Unit
{
    private:
    double mana_;
    public:
    Wizard(double, double, double);
    double attack();
    std::string get_status();
};