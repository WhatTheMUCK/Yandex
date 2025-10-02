# Key-Value storage

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вася разрабатывает свою структуру — базу данных «ключ-значение». Эта структура данных должна хранить значение, ассоциированное с ключом, и она будет делать это суперэффективно. Пока для простоты Вася выбрал за основу `std::unordered_map`, но потом он это переделает.

Какие операции должно поддерживать такое хранилище? Правильно: вставка элемента, удаление элемента и поиск элемента. Вася написал прототипы функций `Insert`, `Remove` и `Find`, но функция `Find` почему-то не работает. Помогите Васе её исправить. Вот код Васи:

```cpp
#include <unordered_map>

template <typename Key, typename Value>
class KeyValueStorage {
private:
      std::unordered_map<Key, Value> data;

public:
    void Insert(const Key& key, const Value& value) {
        data[key] = value;
    }

    void Remove(const Key& key) {
        data.erase(key);
    }

    bool Find(const Key& key, Value* const value = nullptr) const;
};


// Почему-то не работает...
//
// template <typename Key, typename Value>
// bool KeyValueStorage<Key, Value>::Find(const Key& key, Value* const value) const {
//     auto it = std::find(data.begin(), data.end(), key);
//     auto val = *it;
//     if (value != nullptr)
//         value = &val;
//     return it != data.end();
// }

// Ваша реализация функции KeyValueStorage::find будет вставлена сюда:
#include "your_version_of_find.h"
```

Ваша версия функции `Find` будет вставлена в конце этого кода. Её заголовок должен быть таким же, как в закомментированной части.

---

### Требования к функции `Find`:

Функция `Find` по задумке должна:

- Возвращать `true`, если ключ был найден, и `false` в противном случае.
- Если второй аргумент (`value`) отличен от `nullptr` и ключ найден — записать **найденное значение** в объект, на который ссылается `value`.
- Предполагается, что структура быстро определяет наличие ключа, но извлечение значения происходит только при необходимости.

---

### Пример использования:

```cpp
#include "key_value_storage.h"
#include <string>

int main() {
    KeyValueStorage<std::string, int> kv;
    kv.Insert("hello", 42);
    kv.Insert("bye", -13);
    int value = 123;
    auto res = kv.Find("wrong", &value);  // должно вернуть false, value не меняется
    res = kv.Find("bye", &value);         // должно вернуть true, value = -13
    res = kv.Find("hello", nullptr);      // должно вернуть true
}
```