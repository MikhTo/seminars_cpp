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
    //Однако, стоит передавать те типы, для которых определена операция умножения
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


//Параметром может быть не только имя типа, но и целое число,
//А шаблонными могут быть не только функции, но и классы

template<typename T, int N>
class NVector
{
    T* pData;

    public:
    NVector(std::array<T,N> coord): pData(new T [N]) { 
        for(size_t i = 0; i < N; i++)
            pData[i] = coord[i];
    }
    ~NVector(){delete [] pData;}
    //Дальше можно реализовывать методы для работы с этим вектором
    //P.S. А еще, разумней было бы использовать указателя на T соответсвующий std::array
};







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


    NVector<double, 3> unit_vec3D({1, 0, 0});


    //А темеперь посмотрим на наш шаблонный вектор -- он стал почти как из std!!!

    vector<int> our_vec_int(10, 10);
    vector<double> our_vec_double(10);
    vector<std::string> our_vec_string(10, "10");
    vector<std::vector<int>>our_vec_stdvec;
    our_vec_stdvec.push_back(std::vector<int>(10,1));


    std::for_each(our_vec_stdvec[0].begin(), our_vec_stdvec[0].end(), [](int a){std::cout << a << " ";});


    return 0;
}