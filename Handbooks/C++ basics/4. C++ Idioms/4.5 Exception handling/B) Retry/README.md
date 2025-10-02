# Retry

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Иногда некоторые действия не удаётся выполнить с первого раза. Например, обращение по сети к стороннему сервису может завершиться неудачей из-за сетевых проблем или перегрузки. В таких случаях часто реализуют логику повторных попыток.

Вам нужно реализовать функцию `DoWithRetry` со следующим заголовком:

```cpp
#include <exception>
#include <functional>
#include <optional>

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(std::function<Result()> func,
                                  int retryCount, int sleepTime, bool throwLast);
```

### Параметры:
- `func` — функция без аргументов, возвращающая значение типа `Result`.
- `retryCount` — количество **дополнительных** попыток (всего вызовов будет до `retryCount + 1`).
- `sleepTime` — время ожидания между попытками (в миллисекундах или условных единицах — используется функция `Sleep(sleepTime)`).
- `throwLast` — флаг: если `true`, то при исключении на **последней** попытке оно должно быть **проброшено дальше**; если `false` — вернуть пустой `std::optional`.

### Поведение:
- Вызвать `func`.
- Если выброшено исключение **типа `Exception`**:
  - Если остались попытки → вызвать `Sleep(sleepTime)` и повторить.
  - Если это **последняя попытка**:
    - Если `throwLast == true` → **пробросить то же самое исключение**.
    - Иначе → вернуть `std::nullopt`.
- Если `func` завершилась успешно → обернуть результат в `std::optional` и вернуть.
- **Важно:** после **последней** попытки (даже неудачной) **не вызывать `Sleep`**.

### Примечания:
- Гарантируется, что функция `Sleep(int)` объявлена и доступна (не нужно её реализовывать).
- Исключения **других типов** (не `Exception`) должны **пробрасываться немедленно**, без повторных попыток.
- Про `std::optional` можно прочитать в [официальной документации](https://en.cppreference.com/w/cpp/utility/optional).
## Решение

main.cpp
```cpp
#include <exception>
#include <functional>
#include <optional>

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(std::function<Result()> func,
                                  int retryCount, int sleepTime, bool throwLast) 
{
    for (int i = 0; i < retryCount + 1; ++i) {
        try {
            return func();
        } catch (const Exception & e) {
            if (i == retryCount) {
                if (throwLast) {
                    throw e;
                } 
            } else {
                Sleep(sleepTime);
            }
        }
    }
    return {};
}
```
