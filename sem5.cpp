//Семинар 5: ООП и с чем его едят
#include <string>
#include <iostream>

class Cat
{
    private:
    std::string name;
    int age;
    double weight;
    double daily_colorage = 5000; //?


    public:
    Cat(std::string cat_name, double cat_weight, int cat_age = 0)
    {
        name = cat_name;
        weight = cat_weight;
        age = cat_age;
    }

    void bark()
    {
        std::cout << "Meow!!!" << std::endl;
    }

    void eat(double calories)
    {
        if(calories > daily_colorage)
            weight+=0.050*calories/daily_colorage;
    }

    bool operator>(Cat left_cat)
    {
        if(left_cat.age != age)
            return weight > left_cat.weight;
        return age > left_cat.age;
    }
    
};



class ComplexNumber
{
    private:
    double real_;
    double img_;
    public:
    
    ComplexNumber(double r = 0, double i = 0): real_(r), img_(i) {};
    double real_part()
    {
        return real_;
    }
    double img_part()
    {
        return img_;
    }
    
    void conj()
    {
        img_*=-1;
    }

    ComplexNumber operator+(const ComplexNumber rightNumb) const
    {
        return {this->real_+rightNumb.real_, this->img_+rightNumb.img_};
    }
};


int main()
{
    return 0;
}