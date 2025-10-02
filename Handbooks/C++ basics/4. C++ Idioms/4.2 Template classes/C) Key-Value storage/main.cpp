#include <unordered_map>
#include <algorithm>

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

template <typename Key, typename Value>
bool KeyValueStorage<Key, Value>::Find(const Key& key, Value* const value) const {
    auto it = data.find(key); // std::find(data.begin(), data.end(), key);
    if (it == data.end()) {
        return false;
    }

    Value val = it->second;
    if (value != nullptr)
        *value = val;
    return true;
}

// Ваша реализация функции KeyValueStorage::find будет вставлена сюда:

#include <iostream>
#include <string>

int main() {
    KeyValueStorage<std::string, int> kv;
    kv.Insert("hello", 42);
    kv.Insert("bye", -13);
    int value = 123;
    std::cout << std::boolalpha << kv.Find("wrong", &value) << ' ' << value;  // должно вернуться false, а value не должен меняться
    std::cout << '\n' << kv.Find("bye", &value) << ' ' << value;  // должно вернуться true, в value должно быть -13
    std::cout << '\n' << kv.Find("hello", nullptr);  // должно вернуться true
    std::cout << '\n';
}