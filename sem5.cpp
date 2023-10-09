//Семинар 5: ООП и с чем его едят
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

// Описание класса начинается с ключевого слова class
// и имени класса (у нас это Cat) 
class Cat
{
    //Поля класса могут быть открытими и закрытыми
    //Зачастую (но далеко не всегда), 
    // закрытые поля -- это хранимые данные, а открытые -- методы
    private:
    std::string name;
    int age;
    double weight;
    double daily_colorage = 500; //?


    public:
    //У классов есть набор особых методов
    //Один из них -- конструктор, метод, который вызывается при создании нового объекта
    //Ниже реализован конструктор класса Cat - он принимает имя, вес и возраст кота
    //Обратите внимание, что у cat_age есть значение по умолчанию
    Cat(std::string cat_name, double cat_weight, int cat_age = 0)
    {
        //Здесь просто инициализируем поля аргументами функции
        name = cat_name;
        weight = cat_weight;
        age = cat_age;
    }

    //Метод bark позволяет нашему коту мяукать
    void bark()
    {
        std::cout << "Meow!!!" << std::endl;
    }

    //метод eat позволяет кормить нашего кота
    //при этом вес кота может измениться
    void eat(double calories)
    {
        if(calories > daily_colorage)
            weight+=0.050*calories/daily_colorage;
    }

    //Можео определить првила для сравнения котов:
    bool operator>(Cat left_cat)
    {
        if(left_cat.age != age)
            return weight > left_cat.weight;
        return age > left_cat.age;
    }
    //Конечно, данный класс еще есть куда дорабатывать
};



class ComplexNumber
{
    //Заметьте, что нет privare:
    double real_;
    double img_;
    
    public:
    //Еще один способ создать конструктор:
    ComplexNumber(double r = 0, double i = 0): real_(r), img_(i) {};
    //Конструктор копирования реализуется для копирования объектов
    ComplexNumber(const ComplexNumber& to_copy) //Он принимает ссылку на объект
    {
        //Внутри определения класса нам доступен this -- указатель на сам объет
        this->real_ = to_copy.real_;
        this->img_ = to_copy.img_;
        //Следующая запись тоже сработала бы
        //real_ = to_copy.real_;
        //img_ = to_copy.img_;
        //я прописываю явно this только для удобочитаемости
    }
    //Деструктор вызывается при удалении объекта (здесь он максимально прост)
    //На следующей паре рассмотрим примеры, где надо его реально реализовывать
    ~ComplexNumber(){} //Объявление деструктора: ~имя_класса()

    //Заметьте, что real и img -- перегружены
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
    
    //Оперция сопряжения
    void conj()
    {
        img_*=-1;
    }
    //Переопределяем операторы
    ComplexNumber operator=(const ComplexNumber& rightNumb)
    {
        this->real_ = rightNumb.real_;
        this->img_ = rightNumb.img_;
        return *this;
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

std::istream& operator>>(std::istream& is, ComplexNumber& cn) {
    std::string sign, i;
    is >> cn.real() >> sign >> cn.img() >> i;
    if(sign == "-")
        cn.img()*=-1;
    return is;
}

//Добавить унарные операции
int main()
{
    // Сегодня начнем знакомиться с ООП
    // Отличие этого подхода от того, что было ранее в том, что появляется новая сущность
    // Объекты -- создаваемые программистом сущности, 
    // они обладают ПОЛЯМИ для хранения данных
    // и МЕТОДАМИ для работы с ними (где мы еще слышали про методы?)
    // Каждый объект принадлежит к какому-то классу (именно класс и описывает разработчик)
    // Функционал разных может быть разным (это зависит от того, какие задачи класс решает), 
    // его можно довести до того, что работа с объектами
    // (по факту с переменными с пользовательским типом данных)
    // будет ничем не отличаться от встроенных типов данных
    // 
    // Основные принципы ООП: абстракция, инкапсуляция, наследование и полиморфизм
    // Мы будем знакомиться с ними на ближайших трех занятиях 

    //Обычно говорится, что ООП было придумано для более удобного описания РЕАЛЬНЫХ вещей
    //Поэтому обычно в качестве вводных примеров используют кошечек и собачек
    //Не будем оригинальными:
    Cat Mozart("Mozart", 2, 1);
    Cat Valera("Valera", 3);

    //Можно кормить котов:
    Mozart.eat(300);
    Valera.eat(900);

    //Можно заставить их мяукать:
    Mozart.bark();
    Valera.bark();

    std::cout << "Сравниваем котов: " << (Mozart > Valera) << std::endl;

    //Коты - это, конечно, хорошо
    //Но как физики мы чаще имеем дело с различными физическими/математическими абстракциями
    //И они тоже прекрасно описываются объектно-ориентированным подходом

    //Давайте создадим класс комплексных чисел (есть готовый класс в библиотеке complex)
    ComplexNumber c1; //Наш конструктор позволяет создавать комплексный числа по разному
    ComplexNumber c2(1);
    ComplexNumber c3(4, -4);

    //Можно создавать путем копирования
    ComplexNumber copied(c3);
    //Что будет, если приравняем int?
    ComplexNumber from_int = 10;

    //Реализовали разные методы
    //Сопряжение
    c3.conj();
    
    std::cout << "Реальная часть: " << c3.real() << ", мнимая часть: " << c3.img() << std::endl;
    //Модуль и фаза
    std::cout<< "Модуль: " << c3.abs()  << ", Фаза: " << c3.arg() << std::endl;

    //Переопределили для нашего класса арифметические операторы
    ComplexNumber sum = c2 + c3;
    sum *= c2 - c3;

    //Для комплексных чисел определена оперция сравнения на равенство
    //Мы тоже ее определили:
    bool is_equal = (c2 == sum);

    //Можно определить правила, по которым вводится из/выводятся в стандартный поток
    //наши комплексные числа 
    std::cin >> c1;
    std::cout << c1; 

    //Объекты ComplexNumber можно хранить в vector
    std::vector<ComplexNumber> cvec = {{-5, 10}, c1, c2, c3};
    //т.о. мы таким образом определили наш класс, что работать с ним также удобно,
    // как и со встроенными типами
    return 0;
}