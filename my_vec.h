#pragma once
#include <iostream> 
class vector
{
    private:
    size_t size_;
    size_t capacity_;
    int* pData_;

    void increase_buffer();

    public:

    //Конструкторы и деструктор
    vector(size_t size = 0);
    vector(const vector& vec_to_copy);
    vector(vector&& vec_to_move);
    vector(size_t size, int element);
    ~vector();

    //Перегруженные операторы
    vector& operator+=(const vector& rhs);
    int& operator[](size_t index);
    int operator[](size_t index) const;
    vector operator=(const vector& rha);
    vector operator=(vector&& rha);

    //Другие методы
    size_t size() const;
    size_t capacity() const;
    void push_back(int element);


    //Если мы хотим чтобы какая-то сторонняя функция (или метод другого класса)
    //Имели доступ к полям класса, то можно их "подружить" :)
    friend std::ostream& operator<<(std::ostream& os, const vector& to_print);
};

bool operator==(const vector& lha, const vector& rha);
vector operator+(const vector& lha, const vector& rha);