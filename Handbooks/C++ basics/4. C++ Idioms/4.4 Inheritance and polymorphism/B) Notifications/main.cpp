#include <iostream>
#include <string>

void SendSms(const std::string& number, const std::string& message) {
    std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
    std::cout << "Send '" << message << "' to e-mail "  << email << std::endl;
}

// Ваш код будет вставлен здесь:
class NotifierBase {
public:
    virtual void Notify(const std::string& message) const = 0;
    virtual ~NotifierBase() {};
};

class SmsNotifier  : public NotifierBase {
public:
    SmsNotifier(const std::string& number) : number_(number) {}

    void Notify(const std::string& message) const override {
        SendSms(number_, message);
        return;
    }

private:
    const std::string number_;
};

class EmailNotifier  : public NotifierBase {
public:
    EmailNotifier(const std::string& email) : email_(email) {}

    void Notify(const std::string& message) const override {
        SendEmail(email_, message);
        return;
    }

private:
    const std::string email_;
};

// Реализуйте в вашем решении классы NotifierBase, SmsNotifier и EmailNotifier,
// чтобы следующий код заработал как ожидается:

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