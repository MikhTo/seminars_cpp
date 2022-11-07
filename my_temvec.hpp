#pragma once
#include <iostream> 
template<typename T> 
class vector
{
    private:
    size_t size_;
    size_t capacity_;
    T* pData_; //а было int* pData_

    void increase_buffer();

    public:

    //Конструкторы и деструктор
    vector(size_t size = 0);
    vector(const vector& vec_to_copy);
    vector(vector&& vec_to_move);
    vector(size_t size, T element);
    ~vector();

    //Перегруженные операторы
    vector& operator+=(const vector& rhs);
    T& operator[](size_t index);
    T operator[](size_t index) const;
    vector operator=(const vector& rha);
    vector operator=(vector&& rha);

    //Другие методы
    size_t size() const;
    size_t capacity() const;
    void push_back(T element);


};
template<typename T>
bool operator==(const vector<T>& lha, const vector<T>& rha);
template<typename T>
vector<T> operator+(const vector<T>& lha, const vector<T>& rha);

//Метод, называющийся как класс -- конструктор
//Она инициализирует поля объекта
template<typename T>
vector<T>::vector(size_t size)
{
    size_ = size;
    capacity_ = size_ + 1;
    pData_ = new T [capacity_];
}

//А давайте теперь создадим еще одну версию нашего конструктора -- заполняющий конструктор
//Для этого воспользуемся еще одним способом инициализировать поля класса
template<typename T>
vector<T>::vector(size_t size, T element): size_(size), capacity_(size), pData_(new T [capacity_]) 
{
    for(int i = 0; i < size; i++)
        pData_[i] = element;
}

//Данный конструктор создает копию переданного ему вектора -- конструктор копирования
template<typename T>
vector<T>::vector(const vector<T>& vec_to_copy): size_(vec_to_copy.size_), capacity_(vec_to_copy.capacity_) ,pData_(new T [capacity_])
{
    for(size_t i = 0; i < size_; i++)
        pData_[i] = vec_to_copy.pData_[i];
}

//Данный конструктор пермещает все данные в новый создаваемый вектор
//Такой конструктор называется перемещающим
template<typename T>
vector<T>::vector(vector<T>&& vec_to_move) : size_(vec_to_move.size_), capacity_(vec_to_move.capacity_), pData_(vec_to_move.pData_)
{
    vec_to_move.size_ = 0;
    vec_to_move.capacity_ = 0;
    vec_to_move.pData_ = nullptr;
}

//Если выделили память, то нужно ее осовободить. Когда программа выходит за область видимости объекта
//происходит вызов специального метода -- деструктора, в него мы и пропишем удаление памяти
template<typename T>
vector<T>::~vector()
{
        delete [] pData_;
        pData_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        // И сразу две хорошие новости:
        //1 -- теперь память автоматически будет освобождаться
        // при выходе из области видимости объекта (вызове деструктора)
        // 2 -- в нашем курсе вам не понадобится использовать new/delete
        // и вообще работать с такими с-style массивами
        // Ведь всегда можно использовать vector, который сам освободит память!!!
}

//Прибавлет вектору слева вектор справа
//Сложение у нас == конкатенция
//Если мы включили оператор в класс (как в нашем случае)
//То можно рассматривать его, как метод класса
//т.е. можно в реализации образщаться к данным (pData_, size_ и т.д.)
//просто по имени, при этом мы обращаемся к полям ЛЕВОГО объекта вектора (left):
// left += some_vector_on_the_right
template<typename T>
vector<T>& vector<T>::operator+=(const vector<T>& rhs) 
{
    size_t presize = size_;
    size_ += rhs.size_;
    for(int i = presize; i < size_; i++)
    {
        pData_[i] = rhs[i - presize]; 
    }
    return *this;
}

//Оператор равно по суть копирует вектор справа в вектор слева
template<typename T>
vector<T> vector<T>::operator=(const vector<T>& rha)
{
    //Эта проверка нужна, чтобы при попытке приравнять элемент самому себе
    // не происходило удаление памяти (удаление происходит в ~vector())
    //this - указатель на текущий объект
    //т.е. тот, что находится слева
    if(this != &rha)
    {
        this->~vector();
        pData_ = new int [rha.capacity_];
        for(size_t i = 0; i < rha.size_; i++)
            pData_[i] = rha[i];
        size_ = rha.size_;
        capacity_ = rha.capacity_;
    }
    return *this;
}

//Возвращает ССЫЛКУ на i-ый элемент
//Что позволяет менять его значения
template<typename T>
T& vector<T>::operator[](size_t index)
{
    return *(pData_ + index);
}

//Возвращает значение i-го элемента
//При этом нельзя менять значение данных класса
template<typename T>
T vector<T>::operator[](size_t index) const
{
    return pData_[index];
}

//Перемещающее равенство
template<typename T>
vector<T> vector<T>::operator=(vector<T>&& rha)
{
    std::swap(this->size_, rha.size_);
    std::swap(this->capacity_, rha.capacity_);
    std::swap(this->pData_, rha.pData_);
    return *this;
}
// Позволяет узнать размер вектора 
template<typename T>
size_t vector<T>::size() const
{
    return size_;
}

//Оператор вывод в поток (не является членом класса, но является другом)
//Хотя можно было и не дружиться с классом, просто воспользоваться оператором [] для нашего вектора
template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& to_print)
{
    //Точно также можно перегузить оператор ввода >>
    for(size_t i = 0; i < to_print.size(); i++)
        os << to_print.pData_[i] << " ";
    return os;
}

// Оператор сложения
template<typename T>
vector<T> operator+(const vector<T>& lha, const vector<T>& rha)
{
    vector<T> result(lha);
    result += rha;
    return result;
}

// Реализует поэлементное сравнение
template<typename T>
bool operator==(const vector<T>& lha, const vector<T>& rha)
{
    if(rha.size() != lha.size())
        return false;
    for(size_t i = 0; i < lha.size(); i++)
        if(lha[i] != rha[i])
            return false;

    return true;
}

// Увеличивает емкость нашего вектора в 2 раза не меняя содержимое
template<typename T>
void vector<T>::increase_buffer()
{
    T* new_buf = new T [capacity_ * 2];
    for(size_t i = 0; i < size_; i++)
        *(new_buf + i) = *(pData_ + i);

    delete [] pData_;
    pData_ = new_buf;
    capacity_ *= 2;  
}

//Метод, позволяющий узнать размер памяти, которым владет наш вектор
template<typename T>
size_t vector<T>::capacity() const
{
    return capacity_;
}

// Добавляет элемент в конец
template<typename T>
void vector<T>::push_back(T element)
{
    //Перед тем, как добавлять элемент, нужно проверить, хватает ли нам памяти
    if(capacity_ <= size_)
        increase_buffer();
    
    pData_[size_++] = element; 
}