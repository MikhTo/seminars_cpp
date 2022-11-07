#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include "my_temvec.hpp"

//Часто, реализую функцию или класс, нам необходимо, чтобы он работал с различными типами данных
//Для функций эту проблему можно решить с помощью перегрузки (см. конец файла algorithm_part_2)
//Однако при этом происходит повторное написание одного и того же кода (см. конец файла algorithm_part_2)
//Также эту проблему можно решить с помощью шаблонов, о чем мы сегодня и поговорим

//Для создания шаблонной функции используется ключевое слово template

template<typename T> //typename означает, что T в дальнейшем будет использоваться, как имя типа
T square(T x)
{
    //Ура!!! Не надо писать отдельные функции для double и float!
    //Однако, если мы передадим в функцию значения, для типа которых
    //Не определена операция умножения, то произойдет ...
    return x*x;
}

//помните, у нас была особая реализация функции square для типа char?
//Что если мы хотим, чтобы для какого-то типа шаблонная функция вела себя иначе?
//Это можно сделать с помощью специализации щаблонов:

template <> std::string square<std::string>(std::string str)
{
    size_t size = str.size() - 1;
    if (str.size() > 0)
        for (size_t i = 0; i < size; i++)
            str+=str;
    return str;
}



int main()
{
    // Если в каком-то месте кода мы вызываем шаблрнную функцию, то необходимо указывать
    // Шаблонные параметры в угловых скобках

    int result = square<int>(5);

    //Но копилятор может и сам понять

    result = square(result);

    double doubleres = square(1.22);

    //Помним, что для char у нас спецификация

    auto squared_str = square<std::string>("Hey");

    //А темеперь посмотрим на наш шаблонный вектор -- он стал почти как из std!!!

    vector<int> our_vec_int(10, 10);
    vector<double> our_vec_double(10);
    vector<std::string> our_vec_string(10, "10");
    vector<std::vector<int>>our_vec_stdvec;
    our_vec_stdvec.push_back(std::vector<int>(10,1));


    std::for_each(our_vec_stdvec[0].begin(), our_vec_stdvec[0].end(), [](int a){std::cout << a << " ";});


    return 0;
}