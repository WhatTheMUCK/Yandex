# Notifications

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Вам даны функции `SendSms` и `SendEmail`, которые «умеют» отправлять сообщения:

```cpp
#include <iostream>
#include <string>

void SendSms(const std::string& number, const std::string& message) {
    std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
    std::cout << "Send '" << message << "' to e-mail "  << email << std::endl;
}
```

Ваш код будет вставлен в указанное место:

```cpp
// Ваш код будет вставлен здесь:
#include "your_solution.h"
```

Реализуйте в вашем решении классы `NotifierBase`, `SmsNotifier` и `EmailNotifier`, чтобы следующий код заработал как ожидается:

```cpp
void Notify(const NotifierBase& notifier, const std::string& message) {
    notifier.Notify(message);
}

int main() {
    SmsNotifier sms("+7-495-777-77-77");
    EmailNotifier email("na-derevnyu@dedushke.ru");

    Notify(sms, "Hello! How are you?");
    Notify(email, "Let's learn C++!");
    return 0;
}
```

### Требования
- Напишите классы `SmsNotifier` и `EmailNotifier`, унаследованные от базового класса `NotifierBase`.
- Каждый из них должен переопределять виртуальную функцию `Notify`, чтобы вызывать соответствующую функцию:  
  - `SmsNotifier` → `SendSms`  
  - `EmailNotifier` → `SendEmail`
- Сдайте **только код классов** без функции `main` и без уже написанных функций `SendSms`/`SendEmail`.
- Подключите все необходимые заголовочные файлы в вашем решении.