#include <iostream>
//Последовательные контейнеры
#include <vector> // Подключаем нужный заголовочный файл - по названию используемого контейнера 
// Также есть array, list, forward_list, deque, stack и т.п.

// Ассоциативные
#include <set> // множество - набор уникальных однородных элементов
#include <map> // а также: multiset, multimap и т.п.

using namespace std;

int main()
{
    //Создадим vector - вероятно самый популярный контейнер
    //vector - динамический массив с автоматическим перевыделением памяти 
    vector<int> vect_i; // Пустой вектор с элементами типа int
    vector<vector<double>> vect_vect(10); // Вектор векторов с элементами типа double размером 10 

    vector<string> vect_str(10, "element"); // Вектор c элементами типа string, размером 10, каждая строка = "element"
    vector<float> vector_f = {1., 1.1, 1.2, 1.3, 1.4, 1.5}; // С помощью списка инициализации
    vector<float> new_vector_f(vector_f.begin(), vector_f.end() - 2); // С помощью итераторов!

    //Обращение к элементу также как в string: [] или .at():

    vect_str.at(9) = "last_one_element";

    //Полезные методы контейнера vector
    //Можно добавлять элементы с помощью различных методов:
    vect_str.push_back("pushed_back_one");

    vector<string> another_vec_str = {"inserted","by the insert method"};
    vect_str.insert(vect_str.end(), another_vec_str.begin(), another_vec_str.end());

    //Память выделяется также как в string -- с запасом

    cout << "Размер: " << vect_str.size() << ", емкость: " << vect_str.capacity() << endl;

    //Можно изменять размер:
    vect_vect.resize(20);


    for(string str: vect_str)
    {
        cout << str << ' ';
        str = "already printed"; // А внесутся ли изменения?
    }


    //Не особо

    for(string& str : vect_str) // Ссылки!
    {
        str = "already printed";
    }

    vect_str.clear();

    //Теперь к ассоциативным контейнерам
    //Множество -- набор уникальных однотипных элементов
    set<int> our_set{5, 5, 4, 3, 2, 1};

    our_set.insert(6);
    our_set.insert(1);

    // our_set[1] -- так нельзя!

    // приходится перебирать циклом: 
    for(int el: our_set) // & - нельзя
    {
        cout << el << " ";
        //el+=1; 
    }

    //Ищем элемент
    set<int>::iterator it = our_set.find(2); 
    if (it == our_set.end()) 
    {
        cout << "Not found\n";
    }
    else 
    {
        int val = *it;
        cout << "Found " << val << endl;
    }
    
    //Ищем элемент меньше трех
    if (auto it2 = our_set.lower_bound(3); it2 != our_set.end()) 
    {
        cout << "Lower bound is " << *it2 << endl; 
    }    
    
    map<string, int> our_map{{"one", 1}, {"two", 2}, {"three", 3}};
    //Хранит набор пар: ключ-значение, ключи должны быть уникальные
    //каждая пара хранится в специальном типе pair<type, type> --
    // -- это структура c двумя полями first -- для ключа, second -- для значения

    our_map["one"] = 2; // изменит значение на 2
    our_map["four"] = 4; // если ключа нет -- создает его
    our_map["four"] += 4; // добавит к four 4
    our_map["five"] += 5; // создаст "five" и инициализирует 5, а если бы ключ был, то прибавил бы 5
    //our_map.at("+100500"); -- ошибка!


    if(auto it = our_map.find("two"); it != our_map.end()) // перечисление условий == &&
    {
        it->second = 2*2;
        cout << "Ключ: " << it->first<< ", Значение: " << it->second << endl;
    }

    return 0;
}

