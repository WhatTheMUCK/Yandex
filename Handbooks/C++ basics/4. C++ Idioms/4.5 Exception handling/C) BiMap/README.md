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
## Решение

bimap.h
```cpp
#include <stdexcept>
#include <optional>
#include <map>

template <typename Key1, typename Key2, typename Value>
class BiMap {
public:
    // Вставить значение, указав один или оба ключа.
    // Генерирует исключение std::invalid_argument("some text") в случае,
    // если оба ключа пусты, либо один из ключей уже имеется в хранилище.
    void Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2, const Value& value) {
        std::pair<std::optional<Key1>, std::optional<Key2>> valueInfo = {key1, key2};
        std::pair<std::optional<Key1>, std::optional<Key2>> nullValue = {std::nullopt, std::nullopt};
        if (valueInfo == nullValue) {
            throw std::invalid_argument("some text");
        }

        // Проверка: key1 уже существует
        if (key1.has_value() && key1ToKey2.contains(key1)) {
            throw std::invalid_argument("some text");
        }

        // Проверка: key2 уже существует
        if (key2.has_value() && key2ToKey1.contains(key2)) {
            throw std::invalid_argument("some text");
        }

        mp[valueInfo] = value;
        key1ToKey2[key1] = key2;
        key2ToKey1[key2] = key1;
    }

    // Получить значение по ключу первого типа.
    // Генерирует исключение std::out_of_range("some text")
    // в случае отсутствия ключа (как и функция at в std::map).
    Value& GetByPrimaryKey(const Key1& key) {
        if (!key1ToKey2.contains(std::optional<Key1>(key))) {
            throw std::out_of_range("some text");
        }

        return mp[{key, key1ToKey2[key]}];
    }
    const Value& GetByPrimaryKey(const Key1& key) const {
        if (!key1ToKey2.contains(std::optional<Key1>(key))) {
            throw std::out_of_range("some text");
        }

        return mp[{key, key1ToKey2[key]}];
    }

    // Аналогичная функция для ключа второго типа.
    Value& GetBySecondaryKey(const Key2& key) {
        if (!key2ToKey1.contains(std::optional<Key2>(key))) {
            throw std::out_of_range("some text");
        }

        return mp[{key2ToKey1[key], key}];
    }
    const Value& GetBySecondaryKey(const Key2& key) const {
        if (!key2ToKey1.contains(std::optional<Key2>(key))) {
            throw std::out_of_range("some text");
        }

        return mp[{key2ToKey1[key], key}];
    }

private:
    // Для поиска значений
    std::map<std::pair<std::optional<Key1>, std::optional<Key2>>, Value> mp;
    
    // Для поиска соответствия
    std::map<std::optional<Key1>, std::optional<Key2>> key1ToKey2;
    std::map<std::optional<Key2>, std::optional<Key1>> key2ToKey1;
};
```

main.cpp
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
    BiMap<int, string, Student> bimap;  // студента можно определить либо по номеру, либо по логину
    bimap.Insert(42, {}, {"Ivanov", "Ivan"});
    bimap.Insert({}, "cshse-ami-512", {"Petrov", "Petr"});
    bimap.Insert(13, "cshse-ami-999", {"Fedorov", "Fedor"});

    cout << bimap.GetByPrimaryKey(42) << "\n";  // Ivanov Ivan

    cout << bimap.GetBySecondaryKey("cshse-ami-512") << "\n";  // Petrov Petr

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Fedor
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Fedor

    // меняем значение по первичному ключу - по вторичному оно тоже должно измениться
    bimap.GetByPrimaryKey(13).Name = "Oleg";

    cout << bimap.GetByPrimaryKey(13) << "\n";  // Fedorov Oleg
    cout << bimap.GetBySecondaryKey("cshse-ami-999") << "\n";  // Fedorov Oleg
    return 0;
}
```
