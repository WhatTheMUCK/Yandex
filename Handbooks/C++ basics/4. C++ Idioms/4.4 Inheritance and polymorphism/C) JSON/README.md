# JSON

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Данные часто нужно сериализовывать, то есть превращать в строку. Это нужно для сохранения на диске, для отправки по сети, для передачи другому процессу. Часто для этого используются несколько общепринятых форматов данных, таких как JSON, YAML, XML. Поскольку на этапе компиляции не всегда известно, в каком именно формате надо сериализовывать данные, часто приходится прибегать к наследованию.

Вам необходимо реализовать класс `Serializer` с чисто виртуальными методами:

```cpp
void BeginArray()
void AddArrayItem(const std::string &)
void EndArray()
```

После этого унаследуйте от него класс `JsonSerializer`, определив все эти методы.

`JsonSerializer` должен печатать упрощённую версию JSON (см. [официальное описание](https://ru.wikipedia.org/wiki/JSON)), состоящую **только из массивов и строк**:
- Массив начинается с квадратной скобки `[`.
- После каждого элемента, кроме последнего, должна стоять запятая.
- Массив заканчивается квадратной скобкой `]`.
- Все строки должны быть взяты в двойные кавычки `"..."`.
- Гарантируется, что все строки состоят только из латинских символов и пробелов, поэтому **экранировать их не нужно**.

### Требования
- Сдайте **только код классов**, без функции `main`.
- **Не определяйте** `operator<<` для вашего класса.
- Печать должна происходить **внутри указанных методов**.
- Мы будем использовать ваш класс полиморфно через указатель на `Serializer`, поэтому **обязательно добавьте виртуальный деструктор** в базовый класс.

## Примеры

### Пример 1
**Ввод**
```text
BeginArray
EndArray
```

**Вывод**
```text
[]
```

### Пример 2
**Ввод**
```text
BeginArray
AddArrayItem string
EndArray
```

**Вывод**
```text
["string"]
```

### Пример 3
**Ввод**
```text
BeginArray
AddArrayItem first
AddArrayItem second
EndArray
```

**Вывод**
```text
["first","second"]
```

### Пример 4
**Ввод**
```text
BeginArray
BeginArray
EndArray
EndArray
```

**Вывод**
```text
[[]]
```
## Решение

main.cpp
```cpp
#include <iostream>

class Serializer {
public:
    virtual void BeginArray() = 0;
    virtual void AddArrayItem(const std::string &) = 0;
    virtual void EndArray() = 0;
    virtual ~Serializer() {}
};

class JsonSerializer : public Serializer {
public:
    void BeginArray() override {
        if (hasElements) {
            std::cout << ',';
        }
        std::cout << '[';

        hasElements = false;
    }

    void AddArrayItem(const std::string & item) override {
        if (hasElements) {
            std::cout << ',';
        }
        std::cout << '"' << item << '"';
        hasElements = true;
    }

    void EndArray() override {
        std::cout << ']';
        hasElements = true;
    }

private:
    bool hasElements = false;
};

void Test1(Serializer & serializer) {
    serializer.BeginArray();
    serializer.EndArray();
}

void Test2(Serializer & serializer) {
    serializer.BeginArray();
    serializer.AddArrayItem("string");
    serializer.EndArray();
}

void Test3(Serializer & serializer){
    serializer.BeginArray();
    serializer.AddArrayItem("first");
    serializer.AddArrayItem("second");
    serializer.EndArray();
}

void Test4(Serializer & serializer){
    serializer.BeginArray();
    serializer.BeginArray();
    serializer.EndArray();
    serializer.EndArray();
}

void Test5(Serializer & serializer){
    serializer.BeginArray();
    serializer.BeginArray();
    serializer.EndArray();
    serializer.AddArrayItem("first");
    serializer.AddArrayItem("second");
    serializer.EndArray();
}

int main() {
    JsonSerializer tmp;
    Test5(tmp);
    return 0;
}
```
