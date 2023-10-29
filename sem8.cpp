#include <iostream>
#include <string>
#include <vector>
#include "my_temvec.hpp"
template<typename T>
T sum(T left, T right)
{
    return left + right;
}

/*
// Иногда нужно переопределить поведение шаблонной функции для какого-то типа данных
// Это можно сделать через специализацию 
template<> bool sum<bool> (bool left, bool right)
{
    return left & right;
}
*/

/*
// Также можно просто перегрузить функцию:
std::string sum(char left, char right)
{
    return  std::string(1, left) +  std::string(1, right);
}
*/

/*void printf(const char* str)
{
    while(*str)
        std::cout<<*str++;
}*/

template<typename T, typename... Args>
void printf(const char* str, T value, Args... args)
{
    //Обычно такие функции задействуют все аргументы 
    //посредстовом рекурсии  
    while(*str)
    {
        if(*str == '%' && *(++str) != '%')
        {
            std::cout << value;
            printf(str+1, args...);
            return;
        }
        std::cout << *str++;
            
    }
}

int main()
{
    // Очень часто при разработке программ мы сталкиваемся с тем, 
    // что приходится реализовывать один и тот же алгоритм для разных типов данных
    // Пример: сортировка
    // В языке С, например, нам пришлось бы писать несколько функций с разными наваниями,
    // которые будут совпадать с точностью до названия типа данных
    // В C++ это можно реализовать через перегрузку 
    // (при этом все еще нужно будет реализовать несколько функций, пусть и с одним именем)

    //Еще один способ реализовать один алгоритм для разных типов данных - это шаблоны

    int res_i = sum<int>(1, 1);
    double res_d = sum<double>(0.5, 2);
    std::string res_s = sum(std::string("Hello, "), std::string("world!"));

    //Какой результат будет для bool?
    bool res = sum(true, false);
    
    //А какой результат будет для char?
    char res_c = sum('n', 'o');


    //Также можно сделать шаблонный класс: 
    vector<int> my_vec(10);
    for(int i = 0; i < my_vec.size(); i++)
        my_vec[i] = i*i;
    
    vector<int> copied = my_vec;

    //Вариативные шаблоны
    //Можно делать функции с переменным числом аргументов
    printf("Hello, it's int: %i, it's double %d, it's char %c", 6, 5.5, 'c');

    return 0;
}