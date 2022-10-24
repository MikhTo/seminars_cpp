#include "my_vec.h"


//Метод, называющийся как класс -- конструктор
//Она инициализирует поля объекта
vector::vector(size_t size)
{
    size_ = size;
    capacity_ = size_ + 1;
    pData_ = new int [capacity_];
}

//А давайте теперь создадим еще одну версию нашего конструктора -- заполняющий конструктор
//Для этого воспользуемся еще одним способом инициализировать поля класса

vector::vector(size_t size, int element): size_(size), capacity_(size), pData_(new int [capacity_]) 
{
    for(int i = 0; i < size; i++)
        pData_[i] = element;
}

//Данный конструктор создает копию переданного ему вектора -- конструктор копирования
vector::vector(const vector& vec_to_copy): size_(vec_to_copy.size_), capacity_(vec_to_copy.capacity_) ,pData_(new int [capacity_])
{
    for(size_t i = 0; i < size_; i++)
        pData_[i] = vec_to_copy.pData_[i];
}

//Данный конструктор пермещает все данные в новый создаваемый вектор
//Такой конструктор называется перемещающим
vector::vector(vector&& vec_to_move) : size_(vec_to_move.size_), capacity_(vec_to_move.capacity_), pData_(vec_to_move.pData_)
{
    vec_to_move.size_ = 0;
    vec_to_move.capacity_ = 0;
    vec_to_move.pData_ = nullptr;
}

//Если выделили память, то нужно ее осовободить. Когда программа выходит за область видимости объекта
//происходит вызов специального метода -- деструктора, в него мы и пропишем удаление памяти
vector::~vector()
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
vector& vector::operator+=(const vector& rhs) 
{
    int presize = size_;
    size_ += rhs.size_;
    for(int i = presize; i < size_; i++)
    {
        pData_[i] = rhs[i - presize]; 
    }
    return *this;
}

//Оператор равно по суть копирует вектор справа в вектор слева
vector vector::operator=(const vector& rha)
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
int& vector::operator[](size_t index)
{
    return *(pData_ + index);
}

//Возвращает значение i-го элемента
//При этом нельзя менять значение данных класса
int vector::operator[](size_t index) const
{
    return pData_[index];
}

//Перемещающее равенство
vector vector::operator=(vector&& rha)
{
    std::swap(this->size_, rha.size_);
    std::swap(this->capacity_, rha.capacity_);
    std::swap(this->pData_, rha.pData_);
    return *this;
}
// Позволяет узнать размер вектора 
size_t vector::size() const
{
    return size_;
}

//Оператор вывод в поток (не является членом класса, но является другом)
//Хотя можно было и не дружиться с классом, просто воспользоваться оператором [] для нашего вектора
std::ostream& operator<<(std::ostream& os, const vector& to_print)
{
    //Точно также можно перегузить оператор ввода >>
    for(size_t i = 0; i < to_print.size(); i++)
        os << to_print.pData_[i] << " ";
    return os;
}

// Оператор сложения
vector operator+(const vector& lha, const vector& rha)
{
    vector result(lha);
    result += rha;
    return result;
}

// Реализует поэлементное сравнение
bool operator==(const vector& lha, const vector& rha)
{
    if(rha.size() != lha.size())
        return false;
    for(size_t i = 0; i < lha.size(); i++)
        if(lha[i] != rha[i])
            return false;

    return true;
}

// Увеличивает емкость нашего вектора в 2 раза не меняя содержимое
void vector::increase_buffer()
{
    int* new_buf = new int [capacity_ * 2];
    for(size_t i = 0; i < size_; i++)
        *(new_buf + i) = *(pData_ + i);

    delete [] pData_;
    pData_ = new_buf;
    capacity_ *= 2;  
}

//Метод, позволяющий узнать размер памяти, которым владет наш вектор
size_t vector::capacity() const
{
    return capacity_;
}

// Добавляет элемент в конец
void vector::push_back(int element)
{
    //Перед тем, как добавлять элемент, нужно проверить, хватает ли нам памяти
    if(capacity_ <= size_)
        increase_buffer();
    
    pData_[size_++] = element; 
}