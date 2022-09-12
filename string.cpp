#include <iostream>
#include <string> // Подключаем нужный класс!!!


int main()
{
    std::string first, second, third(6, 't'), fourth("fourth"); // создание строки

    std::cin >> first >> second; // Можно считывать строки из стандартного потока

    std::cout << "Содержание первых двух строк, полученное из консоли: " << first << '\t' << second << std::endl; //Можно отправлять в стандартный поток

    std::cout << "Содержимое третьей и четвертой строк, инициализированных при создании: " << third << '\t' << fourth << std::endl;


    //обращаться к элементам строки можно через [] или через .at()
    std::cout << "Обращаемся к элементам по индексу: " << third[3] << " " << fourth.at(4) << std::endl;
    
    fourth += fourth;  // +. +=, .append() - операция конкатенации -- сравнения строк
    std::cout << "Конкатенация: " << fourth << " " << first + second << " " << fourth.append("the end!") << std::endl;

    //Строки можно сравнивать лексикографически
    std::cout << "Результат third > fourth: " << (third > fourth) << std::endl; //доступны <, >, <=, >=, ==, !=

    std::string a("abcd");
    std::cout << "Новая строка, с которой будем работать: " << a << std::endl;
    std::cout << "Узнать размер можно с помощью .size() или .length(): " << a.size() << std::endl;

    std::cout <<"Однако места в памяти требуется больше, чем на строку: "<< a.capacity() << std::endl; //  Почему так? Чтобы можно было добавлять символ в конец без перезаписи
    a.push_back('e');
    std::cout << "Добавили \'e\' с помощью .push_back(): " << a << std::endl;
    //А убрать можно с помощью pop_back();
    a.pop_back();
    std::cout<< "А теперь убрали при помощи pop_back(): " << a << std::endl;

    //Полезный метод find() -- ищет первое вхождение
    std::string phrase("NSU is the novosibirsk State University");
    std::cout << "Новая строка для работы: " << phrase << std::endl;
    std::cout << "Позиция \"si\", найденная с помощью метода find: " << phrase.find("si") << std::endl;
    std::cout << "Позиция второго вхождения \"si\" при передаче методу find в качестве второго аргумента индекс"
    " первого вхождения: " << phrase.find("si", phrase.find("si") + 1) << std::endl; // Второй параметр -- точка старта поиска

    phrase.at(phrase.find("novo")) = std::toupper(phrase[phrase.find("novo")]); // А вот так можно менять регистр (для понижения функция tolower)

    std::cout << "Повышаем регистр у буквы n в слове \'novosibirsk\': " << phrase << std::endl;
    return 0;
}