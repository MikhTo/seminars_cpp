#include <iostream>
#include <vector>
#include <set>
#include <forward_list>

using namespace std;

int main()
{

    // Итератор - это объект, использующийся для получения доступа к элементам контейнеров 
    // Говоря иначе, это объект который указывает на какой-то элемент контейнера
    // Тут могут возникнуть вопросы:
    // Зачем он нужен, если можно обратиться по индексу/ключу?
    // Ответ: не для всех контейнеров это возможно -- например для set, list, forward_list и т.д.
    
    // А чем это отличается от указателя?
    // На самом деле они похожи: и целью использования, и их также можно разыменовывать -- операторы * и ->
    // Отличие заключается в том, что указатели работают как итераторы только для массивов
    // В массивах элементы идут друг за другом в памяти, что позволяет быстро получать доступ к произвольному элементу,
    // Зная лишь адрес первого
    // Если мы используем, например, список, 
    // то следующая ячейка памяти наврядли хранит следющий элемент списка (возможно, у нас даже нет доступа к этой ячейке!)  
    // т.о. итераторы позволяют получать доступ к элементам, используя интерфейс указателей!

    // В зависимости от возможностей итераторы делят на:

    // Random acces iterator:
    vector<int>::iterator it_vi; // он же для array, deque
    // Доступны операторы ++, --, арифметика (it_vi + some_int), операции сравнения (<, > и т.д.)

    // Bidirectional iterator
    set<int>::iterator it_si; // также для map, list
    // Доступны операторы ++, --

    // Forward iterator
    forward_list<int> it_fli; // также для unordered map и unordered set
    // Доступен лишь ++

    // Есть и другие: Input/Output iterator, но за рамками нашего курса

    // Теперь посмотрим, как ими орудовать: 

    set<int> test_set{1, 2, 3, 4, 5, 6}; // Вектор для тестов

    auto two_it = test_set.find(2);
    //Также для перемещения есть методы std::next(it), std::prev(it), std::advance(it, int_move)

    cout << "Найденное значение: " << *two_it ;
    advance(two_it, 3);
    cout << " , перемещаемся на три методом advance на 3: " << *two_it;
    next(two_it);
    cout << ", смещаем вперед на элемент методом next: " << *two_it;
    prev(two_it);
    cout << ", возращаем методом prev: " << *two_it << endl;

    // Reverse iterator
    // Позволяет перебрать элементы в обратном порядке/инвертировать контейнер

    
    for (auto it = test_set.rbegin(); it != test_set.rend(); it++)
    {
        cout << *it << ' ';
    }
    vector<int> r_set(test_set.rbegin(), test_set.rend());
    //set<int> r_set(test_set.rbegin(), test_set.rend()); // А что будет если так?
    
    // Инвалидация итераторов:
    //
    return 0;
    }