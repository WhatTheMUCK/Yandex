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