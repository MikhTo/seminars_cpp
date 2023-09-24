#include <iostream>
//Сегодня мы познокомимся с:
//1. Контейнерами (самые базовые)
//2. Ссылками

//Последовательные контейнеры
#include <vector> // Подключаем нужный заголовочный файл - по названию используемого контейнера 
// Также есть array, list, forward_list, deque, stack и т.п.

// Ассоциативные
#include <set> // множество - набор уникальных однородных элементов
#include <map> // а также: multiset, multimap и т.п.


void print_vec_square(const std::vector<float>& vec)
{
    for (int element: vec)
        std::cout << element*element << " ";
}

int main()
{
    //В языке С для хранения множества элементов одного типа использовались МАССИВЫ
    //Статические:
    int mas [] = {1, 2, 3, 4, 5, 6};
    //И динамические:
    double* pMas = new double [6]; //new вместо malloc
    //А для работы с ними использовали for:
    for(int i = 0; i < 6; i++)
        *(pMas + i) = mas[i]*mas[i];
    delete[] pMas; //Освобождаем память

    //С какими проблемами вы сталкивались при работе с массивами (особенно динамическими)?
    
    //Стандартная библиотека C++ предоставляет большой набор контейнеров, 
    //которые позволяют удобно хранить и работать с наборами однотипных данных

    //Для работы с контейнерами надо включить одноименный заголовочный файл (см. #include)

    //Создадим vector - вероятно самый популярный контейнер
    //vector - динамический массив с автоматическим перевыделением памяти 

    std::vector<int> vect_i; // Пустой вектор с элементами типа int
    std::vector<std::vector<double>> vect_vect(10); // Вектор векторов с элементами типа double размером 10 

    std::vector<std::string> vect_str(10, "element"); // Вектор c элементами типа string, размером 10, каждая строка = "element"
    std::vector<float> vector_f = {1., 1.1, 1.2, 1.3, 1.4, 1.5}; // С помощью списка инициализации
    
    //Обращение к элементу также как в string: [] или .at():

    vect_str.at(9) = "last_one_element";

    //Полезные методы контейнера vector
    //Можно добавлять элементы  в конец с помощью метода pushed_back:
    vect_str.push_back("pushed_back_one");
    //Память выделяется также как в string -- с запасом

    std::cout << "Размер: " << vect_str.size() << ", емкость: " << vect_str.capacity() << std::endl;
    //можно узнать, какой максимальный размер может быть у вектора (работает с любым контейнером)
    std::cout << "Максимальный размер vector<float>: " << vector_f.max_size() << std::endl;
    //Можно изменять размер:
    vect_vect.resize(20);
    //Или удалить лишнюю память (сделать буфер равным размеру)
    vect_vect.shrink_to_fit();
    
    //В С++ цикл for может перебрать все элементы контейнера без использования индексов
    for(std::string str: vect_str)
    {
        std::cout << str << ' ';
        str = "already printed"; // А внесутся ли изменения?
    }


    //Не особо
    //Для этого можно воспользоваться ссылками
    //Можно сказать, что ссылка -- это создание перменной с памятью, которая уже принадлежит другой переменной
    //Таки образом, меняя данные в ссылке изменяется и исходная перменная (обратное утверждение тоже верно)
    //Ссылки были введены, как замена указателей (для некотрых целей), которая не страдает их "проблемами":
    //обращение к неинициализированной памяти, ошибки при работе с арфиметикой указателей и т.д. 
    //Давайте создадим ссылку:
    int a = 10;
    int& b = a; //тип_& имя_переменной
    b *= 2;
    std::cout << "Адрес а: " << &a << ", адрес b" << &b << std::endl;

    //Ссылки также используются для передачи больших объектов в функцию,
    //чтобы избежать копирования
    //При этом если передаваемый объект менять не планируется, 
    //то он передается в с модификатором const 
    print_vec_square(vector_f);
    
    //Возвращаемся к нашему циклу:

    for(std::string& str : vect_str)
    {
        str = "already printed";
    }
    //Теперь значения поменялись
    vect_str.clear(); //Можно удалить все значения


    //Теперь к ассоциативным контейнерам
    //Множество -- набор уникальных однотипных элементов
    //Вставка, удаление и поиск имеет сложность O(log(N)), т.к. значения упорядочены
    //Для савнения, у вектора поиск имеет сложность O(N), а обращение по индексу O(1)  
    std::set<int> our_set{5, 5, 4, 3, 2, 1};
    //Значения элементов НЕЛЬЗЯ менять, только удалять/добавлять новые элементы 

    our_set.insert(6);
    our_set.insert(1);
    our_set.erase(4);
    //нельзя обратиться по индексу к конкретному элементу
    //т.е. our_set[1] не скомилируется

    // приходится перебирать циклом: 
    for(int el: our_set) // & - нельзя
    {
        std::cout << el << " ";
        //el+=1; //что произойдет если снять комментарий? 
    }
    
    std::map<std::string, int> our_map{{"one", 1}, {"two", 2}, {"three", 3}};
    //Хранит набор пар: ключ-значение, ключи должны быть уникальные
    //каждая пара хранится в специальном типе pair<type, type> --
    // -- это структура c двумя полями first -- для ключа, second -- для значения

    our_map["one"] = 2; // изменит значение на 2
    our_map["four"] = 0; // если ключа нет -- создает его
    our_map["four"] += 4; // добавит к four 4
    our_map["five"] += 5; // создаст "five" и инициализирует 5, а если бы ключ был, то прибавил бы 5
    //our_map.at("+100500"); -- ошибка!
    //т.е. метод .at работает только с существующими ключами
    
    //Можно перебрать в цикле:
    for(std::pair<std::string, int> pair: our_map)
        std::cout << pair.first<< " and " << pair.second<< std::endl;

    //Но лучше этого не делать: про эффективный поиск поговорим на следующем занятии,
    //когда обсудим итераторы

    //Для map, как и для остальных контейнеров, реализованы операции сравнения (==, >, <  и т.д.)

    //Проверим: скопируем наш словарь (это еще одно название для map)
    std::map<std::string, int> another_map = our_map;
    std::cout << "Результат our_map == another_map: " << (our_map == another_map) << std::endl;
    //Давайте добавим в another_map еще одно значение
    another_map["six"] = 6;
    std::cout << "Результат our_map > another_map: " << (our_map < another_map) << std::endl;
    return 0;
}

