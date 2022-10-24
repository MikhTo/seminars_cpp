#include <iostream>
#include <string>
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
        return "Hello, i am" + name_ + surname_;
    }
    std::string get_info() const
    {
        return "name: " + name_ + " surname: " + surname_;
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
        return this->Person::get_info() + std::to_string(year_);
    }

    void get_next_year()
    {
        year_++;
    }

    private:
    int year_;
};


int main()
{
    Person some_person("Ivan", "Ivanov");
    Student some_student("Petr","Petrov", 2);

    //Приветствия (унаследованный метод)
    std::cout << some_person.greetings() << '\t' << some_student.greetings() << '\n';
    
    //Информация об (измененный метод)

    std::cout << some_person.get_info() << '\t' << some_student.get_info() << '\n';

    //Ссылка на родительский класс может ссылаться на класс наследник

    Person& tricky_ref = some_student;

    //Однако из такой ссылки мы не можем вызвать методы класса наследника!
    std::cout << tricky_ref.get_info();
    //Как видите, вызвался метод из класса Person

    //Возможность вызывать методы дочерних классов (т.е. классов наследников) была бы удобна
    //Если бы у нас было множество классов наследников с методом имеющим одно название и разную реализацию
    // и мы хотели вызвать такой метод у всех этот

    //Как это сделать и зачем это нужно обсудим на следущем занятии!



}