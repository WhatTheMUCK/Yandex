#include <iostream>
#include <vector>

template <typename T>
class AdvancedVector : public std::vector<T> {
public:
    // Наследуем конструкторы от std::vector
    using std::vector<T>::vector;

    T & operator[](int index){
        int n = static_cast<int>(this->size());
        if (index >= n || -index > n) {
            throw std::out_of_range("index out of range");
        }

        if (0 <= index && index < n) {
            return this->at(index);
        }

        return this->at(n + index);
    }

    const T & operator[](int index) const {
        int n = static_cast<int>(this->size());
        if (index >= n || -index > n) {
            throw std::out_of_range("index out of range");
        }

        if (0 <= index && index < n) {
            return this->at(index);
        }

        return this->at(n + index);
    }
};

int main() {
    AdvancedVector<char> tmp({'a', 'b', 'c'});
    for (int i = 1; i <= 3; ++i) {
        std::cout << tmp[-i] << ' ';
    }
    std::cout << '\n';
    int n;
    std::cin >> n;
    AdvancedVector<double> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    // std::cout << vec[-1] << '\n';
    for (int i = 1; i <= n; ++i) {
        std::cout << vec[-i] << ' ';
    }
    std::cout << '\n';
    return 0;
}