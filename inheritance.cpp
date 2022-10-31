#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include <memory>
#include <exception>
// А теперь давайте обсудим наследование классов в C++
// Часто бывает, что хочется перенести уже имеюшийся функционал одного класса в другой
// При это не меняя исходный класс. Это можно проделать с помощью наследования
// Давайте создадим два класса с простейшим функционалом, чтобы показать как это работает:


class Person
{
    public:
    Person(std::string name, std::string surname): name_(name), surname_(surname) {}
    std::string greetings()
    {
        return "Hi, i am " + name_ + " " + surname_ + '\n';
    }
    std::string get_info() const
    {
        return "name: " + name_ + " surname: " + surname_ ;
    }
    
    std::string get_name()
    {
        return name_;
    }

    std::string get_surname()
    {
        return surname_;
    }
    private:
    std::string name_;
    std::string surname_;

};

// Отнаследуем класс от Person
// Такой класс называется классом-наследником Person, 
// a сам класс Person - родительским классом

class Student: public Person
{
    public:
    Student(std::string name, std::string surname, int year): Person(name, surname), year_(year) {}
    std::string get_info() const 
    {
        //Если хоти обратиться к методу родительского класса прописываем его имя:
        return Person::get_info() + " year: " + std::to_string(year_) + '\n';
    }

    std::string greetings()
    {
        return "Hi, i am " + get_name() + " " + get_surname() + "\n";
    }

    void get_next_year()
    {
        year_++;
    }

    private:
    int year_;
};

class Professor: public  Person 
{
    public:
    Professor(std::string name, std::string surname) : Person(name, surname) {}
    std::string greetings()
    {
        return "Hello, i am Dr. " + get_surname() + '\n';
    }
};


std::unique_ptr<int> pow(std::unique_ptr<int> base, std::unique_ptr<int> exponent)
{
    std::unique_ptr<int> result(new int(std::pow(*base, *exponent)));
    return std::move(result);
}

int main()
{
    //Сперва рассмотрим две побочные темы: "умные указатели" и обработку исключений

    //умные указатели

    // Как вы помните, при работе с динамической памятью у нас может возникнуть проблема утечки памяти, если мы забываем ее освободить
    // В стандартной библиотеке есть набор т.н. умных указателей: unique_ptr, shared_ptr и т.д., 
    // в которых этой проблемы нет -- они сами позаботятся об удалении памяти в нужный момент!!!
    // Но тут нет никакой магии
    // На самом деле умный указатель -- это класс, в полем которого является обычный указатель, 
    // его конструктор принимает в себя этот обычный указатель, а в деструкторе происходит освобождение памяти  
    // т.к. деструктор в любом случае будет вызан (или вручную, или автоматически после выхода из области видимости объекта)
    // то память освободится в любом случае
    
    
    // Мы с вами рассмотрим работу только с одним таким указателем -- unique_ptr
    // Для работы с ними подключем #include <memory>

    //При создании такого указателя передаем в конструктор обычный указатель
    std::unique_ptr<int> smart_p(new int (5));

    //Можно создать с помощью функции make_unique

    std::unique_ptr<int> smart_p1 = std::make_unique<int>(10);

    // Для класса unique_ptr переопределен оператор разыменовывания -- можно работать как с обычными указателями:
    bool is_true = (*smart_p == *smart_p1 / 2);

    // Указатель уникальный -- нет конструктора копирования!!!
    //std::unique_ptr<int> smart_p2(smart_p); // --- выдаст ошибку!!!
    //Возникает вопрос -- а как тогда передавать его в функцию, если копировать нельзя?

    //Ответ:








    //Перемещаем с помощью std::move
    smart_p1 = pow(std::move(smart_p1), std::move(smart_p));

    //Используйте умные указатели, если это возможно -- это сэкономит вам множество времени

    // Теперь давайте обсудим исключения
    // Часто во время работы программы могут возникать ошибки:
    // Попытки открыть несуществующий файл, выход за границы контейнера, деление на ноль и т.д.
    // Раньше это приводило к тому, что программа прекращала работу
    // В C++ ошибки можно очень удобно обрабатывать
    // Для этого используется блок try-catch
    //Для аботы с исключениями подключаем #include <exception>
    auto test_div = [](int x, int y){
        if (y == 0)
            throw std::invalid_argument("denominator must be nonzero\n"); //Бросаем исключение, на этом моменте выполенение функции завершается
        return x/y;
        };



    int test_int = 0;
    try
    {
        test_int = test_div(1, 0);
    }
    catch(std::invalid_argument e) // пишем, какое исключение хотим поймать 
    {
        std::cout << e.what();
    }


    //В текущем блоке заданий от вас будут периодически просить выбрасывать исключения
    //Имеется ввиду делать throw ... -- обрабатывать (catch) их не надо -- это сделает внешний код

      
    Person some_person("Ivan", "Ivanov");
    Student some_student("Petr","Petrov", 2);
    Professor some_professor("Charles", "Xavier");

    //Приветствия 
    std::cout << some_person.greetings() << '\n' << some_student.greetings() << '\n' << some_professor.greetings() << '\n';

    //Информация об 

    std::cout << some_person.get_info() << '\n' << some_student.get_info() << '\n' << some_professor.get_info() << '\n';

    //Ссылка на родительский класс может ссылаться на класс наследник

    Person& tricky_ref = some_student;

    //Однако из такой ссылки мы не можем вызвать методы класса наследника!
    std::cout << tricky_ref.get_info() << std::endl;

    //Как видите, вызвался метод из класса Person

    //Возможность вызывать методы дочерних классов (т.е. классов наследников) была бы удобна
    //Если бы у нас было множество классов наследников с методом имеющим одно название и разную реализацию
    // и мы хотели вызвать такой метод у всех этот

    // Так, если бы у нас был массив, хранящий указатели/ссылки на объекты родительского класса Person, 
    // Мы могли бы сделать так, чтобы они указывали на объекты дочерних классов Student и Professor
    // И попросить их, например, поздороваться (метод greetings) используя цикл

    Student NikIv("Nikita", "Ivanov", 2); 
    Student IvNik("Ivan", "Nikitin", 2); 
    Professor AlEin("Albert", "Einstein");
    std::vector<Person*> university{&NikIv, &IvNik, &AlEin};

    std::for_each(university.begin(), university.end(), [](Person* member){std::cout << member->greetings();});


}