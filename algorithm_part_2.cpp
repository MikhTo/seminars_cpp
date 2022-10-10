#include <algorithm> // Добъем некторые алгоритмы здесь
#include <numeric> // Затем посмотрим следющие
#include <random>
#include <iostream>
#include <vector>
#include <string>
int square (int x)
{
    return x*x;
}
double square (double x)
{
    return x*x;
}
std::string square(char symb)
{
    return std::string(symb, symb);
}
int pow(int x, int exponent = 0)
{
    if (exponent == 0)
        return 1;
    else
        return x*pow(x, --exponent);
}

std::string operator+(const std::string& str, int some_val)
{
    return str + std::to_string(some_val);
}

int main()
{
    // В прошлый раз забыли про lower/upper bound, исправляемся:
    // Представленные ниже алгоритмы работают для отсортированных контейнеров
    
    // Создадим вектор строк, в которые прописаны цифры от 1 до 10
    std::vector<std::string> snumb{"one", "two", "three", "four", "five", "six"};
    // Отсортируем -- порядок, очевидно, изменится
    std::sort(snumb.begin(), snumb.end());

    // Теперь можем рассмотреть алгоритмы
    auto lower_re = std::lower_bound(snumb.begin(), snumb.end(), "five"); // Возращает итератор нп элемент >= третьему аргументу
    auto upper_res = std::upper_bound(snumb.begin(), snumb.end(), "five"); // Возращает итератор на элемент > третьего аргумента
    auto binary_res = std::binary_search(snumb.begin(), snumb.end(), "five"); // Возращает true, если в последовательности есть третий аргумент

    // Ещё две функции, которые пригодятся в рещении задач:

    // std::lexicographical_compare
    auto comp = std::lexicographical_compare(snumb.begin(), snumb.end(), snumb.rbegin(), snumb.rend(), [](std::string left, std::string right){
        return (left.length() < right.length()) ;});

    // функция для перебора перестановок: next_permutation()
    do
    {
        std::for_each(snumb.begin(), snumb.end(), [](const std::string& element){std::cout << element << ' ';});
        std::cout << std::endl;
    }while(std::next_permutation(snumb.begin(), snumb.end()));

    // Рассмотрим библиотеку numeric

    // Алгоритм iota позволяет заполнить вектор числами от n до т + vector.size - 1
    // n - третий аргумент
    std::vector<int>  vec_to_fill(10);
    std::iota(vec_to_fill.begin(), vec_to_fill.end(), -5);
    std::iota(vec_to_fill.begin(), vec_to_fill.end(), 1);

    //Алгоритм accumulate позволяет посчитать сумму
    //Третий аргумент тоже включается суммируется
    int sum = std::accumulate(vec_to_fill.begin(), vec_to_fill.end(), 0);  

    //На самом деле можно передать в accumulate аргументом функцию, которая будет использоваться вместо суммирования
    //Например можно высчитать факториал:
    int factor = std::accumulate(vec_to_fill.begin(), vec_to_fill.end(), 1, [](int a, int b){return a * b;});  


    //Следующая тема введение в ООП, она очень объемная и чтобы снизить нагрузку на сл пару рассмотрим небольшой раздел сейчас:
    //Перегрузка функций
    // Я думаю, что вы уже заметили что многие функци можно вызывать о по одному имени с различным числом аргументов
    //Пример функция string.find(char some_symbol) и string.find(char some_symbol, size_t position)
    // Также различные контейнеры stl можно создавать разными способами:
    //vector(it_begin, it_end); vector(size_t size);vector(size_t size, element)
    //при этом очевидно, что реализация этих функция должна быть разная

    // Функции с разными наборами аргументов (сигнатурой) называются перегруженными

    int a = square(4);
    double d = square(0.4);
    std::string str = square('a');

    // Можно задать аргументам функции значения по умолчанию
    int cubic_v_cube = pow(3, 3);
    int just_one = pow(cubic_v_cube);
    // Перегружать также можно операторы

    std::string is_it_possible = std::string("Eleven is ") + 11;
    return 0;
}