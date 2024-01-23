# Решение демо 

<br>

## Задача 1 - Основы (5 баллов max)
Дан следующий фрагмент кода:

```cpp
class S {

private:
    int x, y;

public:
    S() : x(0), y(0) {}

    S(int a) : x(a), y(a) {}

    S(int x0, int y0) : x(x0), y(y0) {}

    // прототипы перегруженного оператора сложения
};

int main()
{
    S a1, a2, a3;

    int k;

    a1 = a2 + a3;

    a1 = k + a3;

    a1 = a2 + k;

    return 1;
}

```

Руководствуясь приведенным кодом функции `main()`, укажите, какое минимальное количество прототипов перегруженного оператора сложения должно быть включено в определение класса `S`. Приведите необходимые прототипы. Ответ обоснуйте.

<br><br><br><br><br><br><br><br>

## Задача 2 - Шаблоны (10 баллов max)
Одной из типовых задач при работе с контейнерами данных является преобразование контейнера путем
наложения на каждый его элемент некоторой функции преобразования.
Условно эта операция может быть представлена следующим образом:
`container<T> + func -> container<R>`, где func - некоторая функция преобразования `T -> R`, которая выполняется для каждого элемента контейнера.

Необходимо реализовать функцию `convert`, осуществляющую такое преобразование для контейнера `std::vector<T>`.
Функция `convert` принимает в качестве аргументов исходный контейнер source элементов типа `T` и функцию func преобразования элементов `T->R`.
В качестве результата функция должна возвращать сформированный контейнер элементов типа `R`, по размеру совпадающий с исходным.
Тип `Т` и тип `R` любые и могут отличаться или совпадать. Модификация исходного контейнера запрещена. Избегайте излишнего копирования
Напишите функцию convert и пример её использования в функции main в двух тестах (см. ниже).

```cpp
#include <functional>
#include <iostream>
#include <vector>

/*
тут должна быть функция convert
*/

int main()
{
    //Тестовые данные 1:
    std::vector<std::string> v1;
    v1.push_back("aaa");
    v1.push_back("bb");
    v1.push_back("cccc");

    //функция преобразования, принимающая строку и возвращающая длину
    auto func1 = [](const std::string& s) -> size_t { return s.size(); };

    std::vector<size_t> v1_result = convert(v1, func1);

    for (const auto& i : v1_result) {
        std::cout << i << std::endl;
    }
    /*
    корректный результат:
    3
    2
    4
    */

    //Тестовые данные 2:
    struct User {
        std::string name;
        std::string secondName;
    };
    std::vector<User> v2 = { User { "Ivan", "Ivanov" }, User { "Petya", "Petrov" } };

    // func2 - функция, принимающая пользователя и возвращающая строку
    // "фамилия-имя", напишите её
    std::vector<std::string> v2_result = convert(v2, func2);

    for (const auto& i : v2_result) {
        std::cout << i << std::endl;
    }
    /*
    корректный результат:
    Ivanov-Ivan
    Petrov-Petya
    */
}
```

<br><br><br><br><br><br><br><br>

## Задача 3 - Иерархия классов (20 баллов max)
Вовочку взял на работу Павел Дуров. Он будет участвовать в разработке нового мессенджера – «Телега». Вовочке необходимо разработать библиотеку для работы нового мессенджера.
Мессенджер представляет собой набор чатов. Чаты характеризуются описателем контакта собеседника (уникальный id, логин, номер телефона) и списком сообщений. Сообщения могут быть трех типов: текстовое сообщение (содержит id отправителя, время отправки, статус (прочитано или нет), текст сообщения), фотографии (содержит id отправителя, время отправки, статус (прочитано или нет), числовой идентификатор файла на сервере), аудиосообщения (содержит id отправителя, время отправки, числовой идентификатор файла на сервере,статус (прочитано или нет), текст сообщения).

Для сообщений определена функция функция `void print(ostream &)`, которая для текстовых сообщений выводит текст сообщение, для изображений — ссылку вида :

`www.telega.org/img/<id файла>`, для аудио сообщений: ссылку вида : `www.telega.org/audio/<id файла>` и текст сообщения. 
Хранение чатов в мессенджере необходимо реализовать, используя один из стандартных контейнерных классов. Желательно, чтобы чаты были отсортированы по логину собеседника.

Помогите Вовочке не потерять работу!

1. Разработайте диаграмму классов в виде UML диаграммы (на экзаменационном листе) (6 баллов max)

2. Реализуйте объявление всех классов. Классы должны включать все необходимые методы, конструкторы, деструкторы, операторы присваивания. (6 баллов max)

3. Выполните реализацию всех методов классов «мессенджер» и «чат».
Для класса «мессенджер» необходимо перегрузить оператор вывода в поток `<<` для вывода списка чатов в отсортированном по логину порядке и оператор индексации `[ ]` ( в двух вариантах!) для получения чата по логину. Для класса «чат» необходимо реализовать функции добавления нового сообщения и вывода всех непрочитанных сообщений с изменением их статуса. (8 баллов max)

<br><br><br><br><br><br><br><br>

## Задача 4 - Многопоточность (15 баллов max)

В высшей школе программирования и машинного обучения "Прогвартс" студенты традиционно разделяются по четырем факультетам: "Граф-файндер", "С-зерин", "Конфигран" и "Пайтондуй".

Разделение студентов по факультетам в этом учебном заведении выполняется распределительной нейронной сетью на основании их способностей и предрасположенностей. В результате своей работы нейронная сеть возвращает самый подходящий  факультет для переданного ей студента.

Однако, используемая приемной комиссией нейронная сеть работает медленно, а количество мест на направления обучения постоянно растет, поэтому в этом году было принято решение обновить систему распределения студентов, и вместо одной  нейронной сети запустить сразу 24.

Ваша задача состоит в том, чтобы обеспечить равномерную и эффективную загрузку всех предоставленных нейросетей при распределении студентов.

1. Реализовать функцию распределения, выполняющую распределение студентов по факультетам в многопоточном режиме согласно условию (5 баллов max).

2. В связи с напряженной политической обстановкой, руководство "Прогвартс" обеспокоилось, что в этом году на факультет “С-зерин” будет распределено слишком много людей и их будет некому обучать.
В результате было поставлено новое условие - на один и тот же факультет не может поступить более чем 1/3 всего набора (например, если всего поступает 300 человек, то ни на каком факультете не должно оказаться больше 100 человек). Если нейронная сеть распределила студента на факультет, на котором не осталось свободных мест, необходимо вместо этого распределить его на тот факультет, на котором в данный момент меньше всего студентов.
Модифицируйте алгоритм согласно новым условиям (5 баллов max).

3. После тестового запуска системы оказалось, что используемые для нейронных сетей сервера могут иногда перегреваться и отказывать в выполнении запроса.
В этом случае, согласно регламенту, необходимо оставить нейронную без нагрузки на ближайшие 5 минут, а предназначенных для нее студентов распределить по остальным сетям. При этом, когда все студенты будут обработаны, необходимо завершить выполнение программы распределения не дожидаясь остывания серверов.
Модифицируйте алгоритм согласно новым условиям (5 баллов max).
Используемый фреймворк для решения вашей задачи может выглядеть следующим образом (либо можно предложить свой вариант):

```cpp
// Перечисляемый тип факультетов
enum Faculty {
    graphfinder, czerin, configrun, pythondui, unknown
};

// Класс студента (реализация не важна для текущей задачи)
class Student;

// Функция, записывающая студента на заданный факультет
void assignFaculty(Student student, Faculty faculty);

// Функция, отправляющая запрос распределяющей сети под номером N
// Возвращает самый подходящий факультет для переданного студента
// Если сервер перегрелся, возвращает значение unknown
Faculty runNN(const Student &student, int N);

// Функция для распределения вектора студентов по факультетам
// Вам необходимо реализовать эту функцию!
void distribute(const std::vector<Student>& students);
```

Примечание: все функции фреймворка являются потокобезопасными
