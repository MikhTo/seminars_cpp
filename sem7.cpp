#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include <exception>

class Animal {

    private:
    std::string name_;
    int age_;
    double weight_;
    public:
    Animal(std::string name, double weight, int age)
    {
        this->name_ = name;
        this->weight_ = weight;
        this->age_ = age;
    }
    void bark() //virtual -- чтобы вызывался нужный метод работе с указателями на дочерние классы
    {
        std::cout << "???" << std::endl;
    }
};

// Отнаследуем класс Cat от класса Animal
// Класс Cat называется классом-наследником Animal, 
// a сам класс Animal - родительским классом
class Cat: public Animal
{
    private:
    std::string breed_;

    public:
    Cat(std::string name, double weight, int age, std::string breed): Animal(name, weight, age), breed_(breed){} 
    void bark()
    {
        std::cout << "Meow!" << std::endl;
    }
};

class Toad: public Animal
{
    public:
    Toad(std::string name, double weight, int age): Animal(name, weight, age){};
    void bark()
    {
        std::cout << "Ribbit-ribbit!" << std::endl;
    }
};

class Owl: public Animal
{
    public:
    Owl(std::string name, double weight, int age): Animal(name, weight, age){};
    void bark()
    {
        std::cout << "Twit-Twoo!" << std::endl;
    }
};
double calc(std::string operation, double x, double y)
{
    if(operation == "+")
        return x + y;
    else if(operation == "-") 
        return x - y;
    else if (operation == "*")
        return x * y;
    else if (operation == "/")
    {
        //Тут возможно деление на 0, в этом случае "бросаем" исключение
        if(y == 0)
             throw std::invalid_argument("denominator must be nonzero\n");
        //если исключение было брошено, то выполнение программы приостанавливается,
        //стэк функций сматывается до ближайшего подходящего catch
        return x/y;
    }
    else if (operation == "log")
    {
        //Давайте допишем исключение для логарифма:
        return log(x)/log(y);
    }            
    else
        throw std::invalid_argument("wrong operation\n");
}

double func()
{
    std::string operation;
    double x, y;
    std::cout << "Введите операцию из набора (+,-,*,/,log) и два числа:" << std::endl;
    std::cin >> operation >> x >> y;

    //Исключения, возникшие в блоке try будут обработаны в catch
    try
    {
        return calc(operation, x, y);
    }
    catch(std::invalid_argument e)
    {
        //Тут происходит обработка исключений
        std::cout << e.what(); //Метод what выводит текст исключения
        //в нем можно, например, сказать пользователю, в чем была проблема
        
        //Вызовем func() еще раз в надежде, что пользователь встанет на путь праведный
        return func();
    }
}

int main()
{
    // При выполнении программы могут возникать ошибки
    // При этом программа может быть написана правильно, 
    // а ошибки связаны с некорректными входными данными
    // например пользователь невверно вводит название файла, который нужно открыть,
    // или индекс для доступа к элементу массива, который выходит за границы 

    // Для обработки таких случаев в C++ ввели исключения
    // Чтобы подключить исключения: #include <exception> 

    //Чтобы разобраться, давайте рассмотрим пример
    //Мини-программку, которая вычисляет значение арифметических операций

    //double res = func();

    //Теперь поговорим о наследовании в С++
    //Наследование -- это возможность создавать новые классы из уже имеющихся
    //При этом методы и поля копируются

    Animal strange_beast("wth?!", 100500, 2000);
    Cat Gaw ("Gaw", 1, 47, "homeless");
    Toad Trevor("Trevor", 0.3, 3);
    Owl Hedwig ("Hedwig", 2, 600);

    //Давайте начнем обсуждение полиморфизма
    //Классы-наследники обладают очень полезным свойством: 
    //их можно хранить по указателю (или ссылке) на родительский класс

    //Таким образом можно унифицировать работу с ними: например сохранить в одном массиве
    //и работать уже с ним.

    std::vector<Animal*> zoo {&strange_beast, &Gaw, &Trevor, &Hedwig};
    std::for_each(zoo.begin(), zoo.end(), [](Animal* pet){pet->bark();});

    //Как видите, и работе с указателями вызывается метод родительского класса
    //Исправим это с помощью виртуальных методов

    //На самом деле способность создавать объекты класса Animal может показаться странным:
    //Действительно, если его дочерные классы описывают реальных животных,
    //то Animal -- это скорее заготовка, в которой прописаны общие для всех свойства

    //Чтобы решить эту проблемы можно воспользоваться абстрактными классами
    

    // Также если в какой-то момент времени указатель указывал на объект класса A1
    // Который был отнаследован от класса B, то ничто не мешает ему затем 
    // присвоить адрес объекта класса A2, также отнаследованного от B
    // Такое поведение называется динамическим полиморфизмом.


    
    }