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