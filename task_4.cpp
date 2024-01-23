// #include <bits/stdc++.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <memory>
#include <list>
#include <map>
#include <functional>


// Перечисляемый тип факультетов
enum Faculty {
    graphfinder, czerin, configrun, pythondui, unknown
};

// Класс студента (реализация не важна для текущей задачи)
class Student {
public:
    size_t id;
};

// Функция, записывающая студента на заданный факультет
void assignFaculty(Student student, Faculty faculty) {
    static std::mutex mut;
    std::unique_lock<std::mutex> gg(mut);
    std::cout << "assigned " << student.id << " to " << faculty << std::endl;
}

// Функция, отправляющая запрос распределяющей сети под номером N
// Возвращает самый подходящий факультет для переданного студента
// Если сервер перегрелся, возвращает значение unknown
Faculty runNN(const Student &student, int N) {
    return (Faculty)(rand() % 5);
}

constexpr size_t thread_count = 26;

class Distributor /* huh o_- */ {
public:
    const std::vector<Student> &students;

    std::vector<bool> is_NN_disabled;
    size_t max_nn;

    size_t max_per_faculty;
    std::vector<size_t> per_faculty_count;

    std::list<size_t> to_do;
    size_t next_nn = 0;

    Distributor(const std::vector<Student>  &students) : students(students), is_NN_disabled(thread_count, false), per_faculty_count(unknown, 0) {
        max_nn = thread_count;
        max_per_faculty = students.size() / 3;

        for (size_t i = 0; i < students.size(); ++i) {
            to_do.push_back(i);
        }
        size_t next_nn = 0;
    }
    
    void distribute(size_t tid) {
        static std::mutex mut;

        while (1) {
            size_t i;
            size_t nn_index;
            {
                std::unique_lock<std::mutex> gg(mut);

                if (!to_do.size()) break;

                i = to_do.front();
                to_do.pop_front();

                nn_index = next_nn;
                next_nn += 1;
                for (size_t i = 0; i < max_nn; ++i) {
                    if (!is_NN_disabled[nn_index]) break;
                    nn_index = (nn_index + 1) % max_nn;
                }
                std::cout << "working on " << i << " using " << nn_index << " from " << tid << std::endl;
            }

            auto result = runNN(students[i], nn_index);

            if (result != unknown) {
                std::unique_lock<std::mutex> gg(mut);
                if (per_faculty_count[result] < max_per_faculty) {
                    per_faculty_count[result] += 1;
                    assignFaculty(students[i], result);
                } else {
                    size_t min_index = std::distance(per_faculty_count.begin(), std::min_element(per_faculty_count.begin(), per_faculty_count.end()));
                    per_faculty_count[min_index] += 1;
                    assignFaculty(students[i], (Faculty)min_index);
                }
            } else {
                std::unique_lock<std::mutex> gg(mut);
                std::cout << "working failed on " << i << " using " << nn_index << " from " << tid << std::endl;
                to_do.push_back(i);
                is_NN_disabled[nn_index] = true;
            }
        }
    }
};

// Функция для распределения вектора студентов по факультетам
void distribute(const std::vector<Student>& students) {
    std::vector<std::thread> threads(thread_count);
    Distributor dist(students);

    for (size_t tid = 0; tid < thread_count; ++tid) {
        threads[tid] = std::thread(&Distributor::distribute, &dist, tid);
    }

    for (size_t i = 0; i < thread_count; ++i) {
        threads[i].join();
    }
}

int main(void) {
    std::vector<Student> studs(1704);
    for (size_t i = 0; i < studs.size(); ++i) {
        studs[i].id = i;
    }

    std::cout << "Hello sailor!" << std::endl;
    distribute(studs);
    std::cout << "Hello sailor!" << std::endl;

    return 0;    
}

/*

шаблон для простого решения - только первый пункт

void handle_thread(size_t tid, const std::vector<Student>& students) {
    size_t start_i = tid * students.size() / thread_count;
    size_t end_i = (tid + 1) * students.size() / thread_count;
    for (size_t i = start_i; i < end_i; ++i) {
        Faculty result = runNN(students[i], tid);
        assignFaculty(students[i], result);
    }
}


// Функция для распределения вектора студентов по факультетам
void distribute(const std::vector<Student>& students) {
    std::vector<std::thread> threads(thread_count);

    for (size_t tid = 0; tid < thread_count; ++tid) {
        threads[tid] = std::thread(handle_thread, tid, students);
    }

    for (size_t i = 0; i < thread_count; ++i) {
        threads[i].join();
    }
}

*/


// -std=c++17 -fsanitize=thread -g
