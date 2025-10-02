#include <iostream>
#include <vector>

template <typename T>
class Table {
public:
    Table() {}
    Table(size_t rows, size_t cols) {
        resize(rows, cols);
    }

    const std::vector<T> & operator[] (size_t i) const {
        return data[i];
    } 

    std::vector<T> & operator [] (size_t i) {
        return data[i];
    }

    void resize(size_t rows, size_t cols) {
        data.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            data[i].resize(cols);
        }
    }
    
    const std::pair<size_t, size_t> size() const {
        if (data.empty()) {
            return {0, 0};
        }

        return {data.size(), data[0].size()};
    }


private:
    std::vector<std::vector<T>> data;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Table<double> t(n, m);
    for (size_t i = 0; i < t.size().first; ++i) {
        for (size_t j = 0; j < t.size().second; ++j) {
            std::cin >> t[i][j];
        }
    }

    t.resize(n - 1, m - 1);
    t[0][0] = 100;
    
    for (size_t i = 0; i < t.size().first; ++i) {
        for (size_t j = 0; j < t.size().second; ++j) {
            if (j > 0) {
                std::cout << '\t';
            }
            std::cout << t[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}