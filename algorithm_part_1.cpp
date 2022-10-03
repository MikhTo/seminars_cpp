#include <iostream>
#include <algorithm> //Подключаем алгоритмы стандартной библиотеки
#include <vector>
using namespace std;
bool comparator(int left, int right)
{
    return left > right;
}
int main()
{
    vector<int> sorted_vec{0, 9, 1, 8, 2, 7, 3, 6, 4, 5};
    // Алгоритмы сортировки: первые два аргумента -- итераторы на начало и конец сортируемой последовательност (т.е. можно сортировать не весь вектор)
    sort(sorted_vec.begin(), sorted_vec.end()); // по умолчанию сортировка идет по возрастанию

    // При желании можно передать третим аргументом компоратор: функцию от двух аргументов, возращающую bool
    // т.о. можно сказать, что третий аргумент по умолчанию -- оператор меньше ( < )
    sort(sorted_vec.begin(), sorted_vec.end(), comparator); 

    // Чтобы не плодить именованные сущности сверх меры, можно воспользоваться т.н. лямбда-выражением
    sort(sorted_vec.begin(), sorted_vec.end(), [](int left, int right){return left < right;});

    //Краткое введение в лямбда-выражения в С++
    //Место для туториала:)
    
    vector<int> test_vec(10);
    // Алгоритм for_each() -- в некоторых случаях удобная замена циклу for
    // Первые два аргумента -- итераторы, ограничивающие последовательность, последний элемент -- функция от одного аргумента,
    // принимающая в себя элемент последовательности и проводящая с ним некоторые преобразования
    for_each(test_vec.begin(), test_vec.end(), [](int& element){cin >> element;}); // Если хотим менять --- значение передается по ссылке
    for_each(test_vec.begin(), test_vec.end(), [](int& element){element *= element;});
    for_each(test_vec.begin(), test_vec.end(), [](int element){cout << element << " ";}); // Если не хотим  --- по значению/константной ссылке

    // Если хотим не менять наш исходный вектор, а записывать результат в другой, то используем transform()

    vector<int> destination(10);
    transform(test_vec.begin(), test_vec.end(), destination.begin(), [](int element){return element*element;}); 

    // Алгоритмы поиска:
    // Алгоритм find -- возращает итератор на первый элемент равный значению, переденному функции в качестве аргумента
    // Всего три аргумента итераторы на начало и конец подпоследовательности (искать можно и не во всем контейнере (а можно и во всем))
    // и искомое значение
    auto it = find(test_vec.begin(), test_vec.end(), 16);

    //Алгоритм find_if -- возращает первый элемент, для которого переданный выражение вернет true (вместо искомого значение передается функциональный объект)
    //т.о. find_if(begin, end, [some_value](int element){return element == some_value}) --- это тоже самое что и find(begin, end, some_value)
    int a = 25;
    it = find_if(test_vec.begin(), test_vec.end(), [a](int element){return element >= a;});

    //Также можно посчитать сколько элементов в последовательности равны определенному значению,
    // или удовлетворяют какому-то условию с помощью функций count  и count_if соответсвенно 

    size_t counted = count(test_vec.begin(), test_vec.end(), 4);
    size_t counted = count_if(test_vec.begin(), test_vec.end(), [](int element){return element > 0;});

    //Иногда нужно проверить, удовлетворяют ли все элементы (или хотя бы один из) какому либо условием
    //Для подобных задач есть функции all_of, any_of, none_of
    bool is_all_positive = all_of(test_vec.begin(), test_vec.end(), [](int element){return element > 0;});
    bool at_least_one_positive = any_of(test_vec.begin(), test_vec.end(), [](int element){return element > 0;});
    bool is_all_negative = none_of(test_vec.begin(), test_vec.end(), [](int element){return element > 0;});
    return 0;
}

