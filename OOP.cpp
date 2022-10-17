#include <iostream>
#include <string>
#include<vector>

class vector
{
    public:
    //Функция, имеющая имя класса называется конструктор
    //Она инициализирует поля объекта
    vector(size_t size = 0)
    {
        size_ = size;
        pData_ = new int [size_];
    }

    //А давайте теперь создадим еще одну версию нашего конструктора -- заполняющий конструктор
    //Для этого воспользуемся еще одним способом инициализировать поля класса

    vector(size_t size, int element): size_(size), pData_(new int [size_]) {
        for(int i = 0; i < size; i++)
            pData_[i] = element;
    }

    //Данный конструктор создает копию переданного ему вектора -- конструктор копирования
    vector(const vector& vec_to_copy): size_(vec_to_copy.size_), pData_(new int [size_])
    {
        for(size_t i = 0; i < size_; i++)
            pData_[i] = vec_to_copy.pData_[i];
    }

    //Данный конструктор пермещает все данные в новый создаваемый вектор
    //Такой конструктор называется перемещающим
    vector(vector&& vec_to_move) : size_(vec_to_move.size_), pData_(vec_to_move.pData_)
    {
        vec_to_move.size_ = 0;
        vec_to_move.pData_ = nullptr;
    }

    //Если выделили память, то нужно ее осовободить. Когда программа выходит за область видимости объекта
    //происходит вызов специального метода -- деструктора, в него мы и пропишем удаление памяти
    ~vector()
    {
        delete [] pData_;
        pData_ = nullptr;
        size_ = 0;
        // И сразу две хорошие новости:
        //1 -- теперь память автоматически будет освобождаться
        // при выходе из области видимости объекта (вызове деструктора)
        // 2 -- в нашем курсе вам не понадобится использовать new/delete
        // и вообще работать с такими с-style массивами
        // Ведь всегда можно использовать vector, который сам освободит память!!!
    }

    vector& operator+=(const vector& rhs);
    int& operator[](size_t index);
    int operator[](size_t index) const;
    vector operator=(const vector& rha);
    vector operator=(vector&& rha);
    size_t size() const;

    //Если мы хотим чтобы какая-то сторонняя функция (или метод другого класса)
    //Имели доступ к полям класса, то можно их "подружить" :)
    friend std::ostream& operator<<(std::ostream& os, const vector& to_print);

    private:
    size_t size_;
    int* pData_;
};

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
vector operator+(const vector& lha, const vector& rha)
{
    vector result(lha);
    result += rha;
    return result;
}
bool operator==(const vector& lha, const vector& rha)
{
    if(rha.size() != lha.size())
        return false;
    for(size_t i = 0; i < lha.size(); i++)
        if(lha[i] != rha[i])
            return false;

    return true;
}
vector vector::operator=(const vector& rha)
{
    if(this != &rha)
    {
        this->~vector();
        pData_ = new int [rha.size_];
        for(size_t i = 0; i < rha.size_; i++)
            pData_[i] = rha[i];
        size_ = rha.size_;
    }
    return *this;
}
int& vector::operator[](size_t index)
{
    return *(pData_ + index);
}
int vector::operator[](size_t index) const
{
    return pData_[index];
}
vector vector::operator=(vector&& rha)
{
    std::swap(this->size_, rha.size_);
    std::swap(this->pData_, rha.pData_);
    return *this;
}
size_t vector::size() const
{
    return size_;
}

std::ostream& operator<<(std::ostream& os, const vector& to_print)
{
    //Точно также можно перегузить оператор ввода >>
    for(size_t i = 0; i < to_print.size(); i++)
        os << to_print.pData_[i] << " ";
    return os;
}

int main()
{
    //Объектно ориентированный подход -- программа стоит из взаимодействующих сущностей - объектов
    //Все объекты принадлежат к какому-то классу. Объекты одного класса устроены одинаково 
    //Объекты чем-то напоминают структуры -- они также хранят набор данных, состоящий из стандартных типов/других объектов
    //Отличие заключается в том, что объекты как правило не предоставлют доступ к хранимым данным напрямую(к в С-style структах),
    //Но предоставляют доступ к ним через интерфес: функции, которые имеют доступ к этим данным
    //Такие функции называются методами. Подобная регламентация доступа является реализацией прицнипа инскапсуляции
    //Подобный подход позволяет нам не заботиться о том, как объекты реализованны внутри
    //Все, что нам нужно знать, какой интерфейс он предоставляет

    // Объектно ориентрированный подход хорошо себе зарекомендовал как в работе с объектами из реальной жизни
    // (Такой пример мы рассмотрим на следующей паре)
    //В нашем курсе (да и в реальной работе физика) нам нечасто приходится создовать классы,
    //соответсвующие предметам реальной жизни
    //однако часто приходится работать с математическими абстракциями - системами уравнений, векторными полями и т.д.
    //Давайте в качестве примера реализуем класс вектор, который реализует структуру данных вектор
    //ДИСКЛЕЙМЕР: пока не реализует в полной мере -- у вектора памяти больше, чем требуется для хранения данных
    //Создаем векторы заполнением
    vector arr(1, 3);
    vector arr2(2,4);

    //Создаем вектор с помощью копирования
    vector arr3(arr);
    //Проверяем на равенство
    bool is_arr3_eq_arr = (arr == arr3);

    //Операция + здесь определена как конкатенация
    vector vec_new = arr + arr2;

    //Выводим получившийся вектор
    std::cout << vec_new << std::endl;

    vector to_move(std::move(vec_new));

    //Заметим, что мы так реализовали интерфейс класса,
    //что работа с ним мало чем отличается от работы с встроенными типами!
    return 0;
}