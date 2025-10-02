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