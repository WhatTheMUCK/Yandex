# Документы

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Вам дан класс `Document`, от которого унаследованы два класса (`PlainTextDocument` и `HTMLDocument`), определён тип `DocumentCollection`, и написаны две функции (`AddDocument` и `PrintCollection`):

```cpp
#include <iostream>
#include <string>
#include <vector>

class Document {
private:
    const std::string Content;
public:
    Document(const std::string& s): Content(s) {}
    void Save() const {
    }
};

class PlainTextDocument: public Document {
public:
    PlainTextDocument(const std::string& s): Document(s) {}
    virtual void Save() {
        std::cout << Content << "\n";
    }
};

class HTMLDocument: public Document {
public:
    HTMLDocument(const std::string& s): Document(s) {}
    virtual void Save() {
        std::cout << "<HTML><BODY>" << Content << "</BODY></HTML>\n";
    }
};

using DocumentCollection = std::vector<Document>;

void AddDocument(const std::string& content, const std::string& type, DocumentCollection& collection) {
    if (type == "plain") {
        collection.push_back(PlainTextDocument(content));
    } else if (type == "html") {
        collection.push_back(HTMLDocument(content));
    }
}

void PrintCollection(const DocumentCollection& collection) {
    for (const auto& doc : collection) {
        doc.Save();
    }
}
```

Однако этот код **не компилируется**, а если исправить ошибки компиляции, то работает **неправильно** (не полиморфно).

### Требования к исправленному коду:

- Иерархия классов должна сохраниться: `PlainTextDocument` и `HTMLDocument` — наследники `Document`.
- Функция `Save` в классе `Document` должна вести себя **полиморфно**.
- Тип `DocumentCollection` должен быть **вектором** (какого-то типа).
- Сигнатуры функций `AddDocument` и `PrintCollection` **должны остаться без изменений**.
  - Второй параметр `AddDocument` принимает значения `"plain"` или `"html"`.
- **Не должно быть утечек памяти**.

> Сдайте **полный исправленный код**, включая все необходимые `#include` и корректную реализацию классов и функций.
## Решение

main.cpp
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Document {
private:
    const std::string Content;
public:
    Document(const std::string& s): Content(s) {}

    const std::string & getContent() const {
        return Content;
    }

    virtual void Save() const {}
    virtual ~Document() {}
};

class PlainTextDocument: public Document {
public:
    PlainTextDocument(const std::string& s): Document(s) {}
    virtual void Save() const override {
        std::cout << getContent() << "\n";
    }
};

class HTMLDocument: public Document {
public:
    HTMLDocument(const std::string& s): Document(s) {}
    virtual void Save() const override{
        std::cout << "<HTML><BODY>" << getContent() << "</BODY></HTML>\n";
    }
};

using DocumentCollection = std::vector<std::unique_ptr<Document>>;

void AddDocument(const std::string& content, const std::string& type, DocumentCollection& collection) {
    if (type == "plain") {
        collection.push_back(std::make_unique<PlainTextDocument>(content));
    } else if (type == "html") {
        collection.push_back(std::make_unique<HTMLDocument>(content));
    }
}

void PrintCollection(const DocumentCollection& collection) {
    for (const auto& doc : collection) {
        doc->Save();
    }
}

int main() {
    {
        DocumentCollection docs;
        AddDocument("Ahahha", "html", docs);
        AddDocument("Ahahha2", "plain", docs);
        AddDocument("Ahahha3", "plain", docs);
        AddDocument("Ahahha4", "html", docs);
        PrintCollection(docs);
    }
    DocumentCollection docs;
    PrintCollection(docs);
    return 0;
}
```
