//Семинар 5: ООП и с чем его едят
#include <string>
#include <iostream>
#include <cmath>

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
    double real() const
    {
        return real_;
    }
    double img() const
    {
        return img_;
    }

    double& real()
    {
        return real_;
    }
    double& img()
    {
        return img_;
    }
    
    void conj()
    {
        img_*=-1;
    }
    ComplexNumber operator=(const ComplexNumber& rightNumb)
    {

    }
    ComplexNumber operator+(const ComplexNumber& rightNumb) const
    {
        return {this->real_+rightNumb.real_, this->img_+rightNumb.img_};
    }
    ComplexNumber operator-(const ComplexNumber& rightNumb) const
    {
        return {this->real_-rightNumb.real_, this->img_-rightNumb.img_};
    }
    ComplexNumber operator*(const ComplexNumber& rightNumb) const
    {
        return {this->real_*rightNumb.real_ - this->img_*rightNumb.img_, 
            this->img_*rightNumb.real_ + this->real_*rightNumb.img_};
    }
    ComplexNumber operator+=(const ComplexNumber& rightNumb) 
    {
        this->real_ += rightNumb.real_;
        this->img_ += rightNumb.img_;
        return *this;
    }
    ComplexNumber operator-=(const ComplexNumber& rightNumb)
    {
        this->real_ -= rightNumb.real_;
        this->img_ -= rightNumb.img_;
        return *this;
    }
    ComplexNumber operator*=(const ComplexNumber& rightNumb)
    {
        this->real_ *= rightNumb.real_;
        this->img_ *= rightNumb.img_;
        return *this;
    }
    
    double abs()
    {
        ComplexNumber res = (*this)*(*this);
        return sqrt(res.real_);
    }
    double arg()
    {
        //Потенциально деление на 0!
        return atan(this->img_/this->real_);
    }

    //Операторы сравнения
    //Для комплексных чисел их немного:
    bool operator==(ComplexNumber& rightArg)
    {
        return (this->real_ == rightArg.real_) && (this->img_ == rightArg.img_);
    }

};

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn) {
    os << cn.real() << " + " << cn.img() << "i";
    return os;
}

std::istream& operator<<(std::istream& is, ComplexNumber& cn) {
    std::string sign;
    is >> cn.real() >> sign >> cn.img();
    if(sign == "-")
        cn.img()*=-1;
    return is;
}

//Добавить унарные операции
int main()
{
    return 0;
}