# Шаблонный Print

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Вам надо написать **шаблонную функцию `Print`**, которая умеет печатать в поток `std::cout` элементы переданного контейнера через указанную строку-разделитель.

### Требования:
- Первый аргумент — **контейнер**.  
  Гарантируется, что по нему можно пройтись с помощью **range-based for**, и что его элементы можно вывести через `operator<<` в `std::cout`.
- Второй аргумент — **строка-разделитель**, которую нужно печатать **между элементами**.
- После последнего элемента **не должно быть разделителя**.
- В конце вывода — обязательно напечатать **перевод строки `\n`**.

---

## Пример вызова:

```cpp
int main() {
    std::vector<int> data = {1, 2, 3, 4};
    Print(data, ", ");  // Вывод: 1, 2, 3, 4\n
}
```

---

## Примечание

- В вашем решении должен быть **только код функции `Print`** — без `main`.
- Подключите все необходимые заголовочные файлы.
- Используйте **константные ссылки** для параметров и при итерации, чтобы избежать лишних копирований.  
  ❗ *Если этого не сделать — программа не скомпилируется.*

---

## Ожидаемый интерфейс:

```cpp
template <typename Container>
void Print(const Container& container, const std::string& delimiter);
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <list>

template <typename Container>
void Print(const Container & data, const std::string & delimiter) {
    std::string answer;
    for (auto cur = std::begin(data); cur != std::end(data); ++cur) {
        std::cout << *cur;
        if (std::next(cur) == std::end(data)) {
            std::cout << '\n';
            break;
        }
        std::cout << delimiter;
    }
    return;
}

int main() {
    // std::vector<int> data = {1, 2, 3, 4};
    // double data[] = {1.2, 2., 3.7, 4.5};
    std::list<int> data = {90, 1, 2, 3};
    Print(data, ", ");  // 1, 2, 3, 4
    return 0;
}
```
