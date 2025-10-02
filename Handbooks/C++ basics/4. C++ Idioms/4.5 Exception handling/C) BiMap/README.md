# BiMap

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Все вы знаете контейнер `std::map`, который сопоставляет уникальным ключам значения. Представим теперь, что у данных может быть **два типа ключей**. Например, студента можно идентифицировать по номеру студенческого билета **или** по логину. При этом не обязательно заданы оба ключа.

Вам нужно реализовать шаблонный класс `BiMap`, позволяющий получать значение по **любому из двух ключей**.

### Интерфейс класса

```cpp
#include <stdexcept>
#include <optional>

template <typename Key1, typename Key2, typename Value>
class BiMap {
public:
    // Вставить значение, указав один или оба ключа.
    // Генерирует исключение std::invalid_argument("some text"), если:
    // - оба ключа пусты (nullopt),
    // - хотя бы один из переданных ключей уже существует в хранилище.
    void Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2, const Value& value);

    // Получить значение по первому типу ключа.
    // Ведёт себя как std::map::at: при отсутствии ключа бросает std::out_of_range.
    Value& GetByPrimaryKey(const Key1& key);
    const Value& GetByPrimaryKey(const Key1& key) const;

    // Аналогично для второго типа ключа.
    Value& GetBySecondaryKey(const Key2& key);
    const Value& GetBySecondaryKey(const Key2& key) const;
};
```

### Поведение методов

- **`Insert`**:
  - Принимает ключи через `std::optional`, так как один из них может отсутствовать.
  - Если **оба ключа `nullopt`** → бросить `std::invalid_argument`.
  - Если **хотя бы один из переданных ключей уже существует** в соответствующем индексе → бросить `std::invalid_argument`.
  - Иначе — сохранить значение и связать его с указанными ключами.

- **`GetByPrimaryKey` / `GetBySecondaryKey`**:
  - Возвращают ссылку на значение по соответствующему ключу.
  - Если ключ не найден → бросить `std::out_of_range`.

### Пример использования

```cpp
#include "bimap.h"
#include <iostream>
#include <string>

using namespace std;

struct Student {
    string Surname, Name;
};

ostream& operator << (ostream& out, const Student& s) {
    return out << s.Surname << " " << s.Name;
}

int main() {
    BiMap<int, string, Student> bimap;
    bimap.Insert(42, {}, {"Ivanov", "Ivan"});
    bimap.Insert({}, "cshse-ami-512", {"Petrov", "Petr"});
    bimap.Insert(13, "cshse-ami-999", {"Fedorov", "Fedor"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan
    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr
    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    // Изменение через один ключ влияет на оба представления
    bimap.GetByPrimaryKey(13).Name = "Oleg";

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg
    return 0;
}
```

### Требования
- Можно использовать `std::map` (предполагается, что на `Key1` и `Key2` определён `operator<`).
- Сдайте **только код класса `BiMap`**, без `main` и без дополнительных функций.
- Подключите все необходимые заголовочные файлы (`<map>`, `<optional>`, `<stdexcept>` и т.д.).