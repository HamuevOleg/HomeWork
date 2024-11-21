#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <cassert>

class Stack {
private:
    std::vector<int> data;

public:
    // Конструкторы
    Stack() = default;

    explicit Stack(size_t size) : data(size, 0) {}

    Stack(int* arr, size_t size) : data(arr, arr + size) {}

    Stack(const Stack& other) : data(other.data) {}

    Stack(Stack&& other) noexcept : data(std::move(other.data)) {}

    template <typename Iterator>
    Stack(Iterator begin, Iterator end) : data(begin, end) {}

    // Операторы
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Методы
    void clear() {
        data.clear();
    }

    void push(int value) {
        data.push_back(value);
    }

    void push_range(const std::initializer_list<int>& values) {
        data.insert(data.end(), values.begin(), values.end());
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }

    int top() const {
        if (!data.empty()) {
            return data.back();
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }

    void swap(Stack& other) noexcept {
        data.swap(other.data);
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    int at(int index) const {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        int actual_index = index < 0 ? data.size() + index : index;
        if (actual_index < 0) {
            return data.front();
        } else if (actual_index >= static_cast<int>(data.size())) {
            return data.back();
        }
        return data[actual_index];
    }

    void resize(size_t newSize) {
        data.resize(newSize, 0);
    }

    void assign(size_t count, int value) {
        data.assign(count, value);
    }

    size_t length() const {
        return data.size();
    }

    void print() const {
        for (const int& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    bool operator==(const Stack& other) const {
        return data == other.data;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }

    static bool is_equal(const Stack& stack1, const Stack& stack2) {
        return stack1.data == stack2.data;
    }

    // Итераторы
    using iterator = typename std::vector<int>::iterator;
    using const_iterator = typename std::vector<int>::const_iterator;
    using reverse_iterator = typename std::vector<int>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<int>::const_reverse_iterator;

    iterator begin() {
        return data.begin();
    }

    iterator end() {
        return data.end();
    }

    reverse_iterator rbegin() {
        return data.rbegin();
    }

    reverse_iterator rend() {
        return data.rend();
    }

    const_iterator begin() const {
        return data.begin();
    }

    const_iterator end() const {
        return data.end();
    }

    const_reverse_iterator rbegin() const {
        return data.rbegin();
    }

    const_reverse_iterator rend() const {
        return data.rend();
    }
};

int main() {
    int array[] = {19, 47, 74, 91};

    // Создаем стек из массива
    Stack a(array, 4);
    for (auto it = a.begin(); it != a.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // Создаем стек с использованием конструктора с итераторами
    Stack b(a.begin(), a.end());
    assert(Stack::is_equal(a, b));

    // Выводим элементы стека с использованием диапазона for
    for (const auto& it : b)
        std::cout << it << " ";
    std::cout << std::endl;

    // Создаем еще один стек с использованием итераторов
    Stack c(b.begin(), b.end());
    assert(std::equal(c.begin(), c.end(), b.begin()));

    // Выводим элементы стека в обратном порядке
    for (auto it = c.rbegin(); it != c.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // Создаем стек из обратных итераторов
    Stack d(c.rbegin(), c.rend());
    for (const auto& it : d)
        std::cout << it << " ";
    std::cout << std::endl;

    return 0;
}
