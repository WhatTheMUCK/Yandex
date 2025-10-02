# Table

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вам надо написать шаблонный класс `Table` для электронной таблицы. Для простоты будем считать, что все ячейки таблицы имеют один и тот же тип данных `T`. Таблица должна уметь менять свой размер по требованию пользователя. Вновь созданные ячейки должны заполняться значениями по умолчанию типа `T`.

---

### Требования к классу:

- Класс должен называться `Table`.
- У класса должен быть шаблонный параметр `T` — тип элемента в ячейке.
- У класса должен быть конструктор, получающий на входе два числа типа `size_t` — начальные размеры таблицы.
- У класса должны быть **константная и неконстантная версии оператора `[]`**, возвращающего нечто такое, к чему снова можно было бы применить оператор `[]`.  
  То есть, должны работать конструкции вида:  
  ```cpp
  std::cout << table[i][j];
  table[i][j] = value;
  ```  
  Проверять корректность индексов при этом **не нужно**.
- У класса должна быть функция `resize`, получающая на вход два параметра типа `size_t` и меняющая размер таблицы. Старые данные, умещающиеся в новый размер, должны при этом сохраниться.
- У класса должна быть функция `size`, возвращающая `std::pair<size_t, size_t>` — размер таблицы (в том же порядке, в котором эти аргументы передавались в конструктор).
## Решение

main.cpp
```cpp
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
```
