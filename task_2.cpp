#include <functional>
#include <iostream>
#include <vector>

template <typename R, typename T, typename F>
std::vector<R> convert(const std::vector<T> &input, F func) {
    std::vector<R> result;
    result.reserve(result.size());
    for (const auto &it: input) {
        result.push_back(func(it));
    }
    return result;
}

int main() {
    //Тестовые данные 1:
    std::vector<std::string> v1;
    v1.push_back("aaa");
    v1.push_back("bb");
    v1.push_back("cccc");

    //функция преобразования, принимающая строку и возвращающая длину
    auto func1 = [](const std::string& s)-> size_t { return s.size(); };

    std::vector<size_t> v1_result = convert<size_t>(v1, func1);

    for (const auto& i : v1_result) {
        std::cout << i << std::endl;
    }
    /*корректный результат:
    3
    2
    4
    */

    //Тестовые данные 2:
    struct User { std::string name; std::string secondName; };
    std::vector<User> v2 = { User { "Ivan", "Ivanov" }, User { "Petya", "Petrov"} };
    
    //func2 - функция, принимающая пользователя и возвращающая строку "фамилия-имя"
    auto fun2 = [](const User &v) -> std::string { return v.secondName + "-" + v.name; };

    std::vector<std::string> v2_result = convert<std::string>(v2, fun2);

    for (const auto& i : v2_result) {
        std::cout << i << std::endl;
    }
    /*корректный результат:
    Ivanov-Ivan
    Petrov-Petya
    */
}
