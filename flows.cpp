#include <iostream> //стандартный ввод-вывод
#include <fstream> //ввод-вывод в файл
#include <string>

using namespace std; // Если без этой строки, то писать перед каждым вызовом функции стандартной библиотеки std::

int main()
{
    int i = 0;
    double d = 0.505;
    char c = 'a';
    cout << "Могу вывести корректно любой встроенный тип данных: " << "int: "<< i << ", double: " <<  d <<", char: " << c << endl;
    cout << "endl - означает конец строки"<< endl << "cin записывает из консоли -- опять же без указания типа" << endl;

    cin >> i >> d >> c;

    cout << "Новые значения: " << i << "\t" << d << "\t" << c << endl;

    cout << "Поток можно направить в файл / файл можно выгрузить в поток:" << endl;

    ifstream inputf("example.txt", ios::in); // ios::in - открываем файл только на чтение
    if(inputf.is_open())
    {
        inputf >> i >> d >> c;
    }
    inputf.close();

    cout << "Действительно обновилось " << i << " " << d << " " << c << endl;
    ofstream outputf("empty.txt", ios::out); // Чтобы не перезаписывать -- ios::app
    if(outputf.is_open())
    {
        outputf << i+i << " " << d*d << " " << "Hello!";
    }
    outputf.close();

    // Особенности работы со строками:
    string str;
    cin >> str;
    string str2;
    getline(cin, str2);
    return 0;
}