#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> textEditor;
    std::string curLine;
    while (std::getline(std::cin, curLine) && !curLine.empty()) {
        textEditor.push_back(curLine + '\n');
    }
    textEditor.push_back("");

    // Работа с командами тектового редактора
    int mouseLine = 0;
    std::string buffer;
    while (std::getline(std::cin, curLine)) {
        if (curLine == "Down") {
            mouseLine = std::min(mouseLine + 1, static_cast<int>(textEditor.size()));
        } else if (curLine == "Up") {
            mouseLine = std::max(mouseLine - 1, 0);
        } else if (curLine == "Ctrl+X" && !textEditor.empty() && !textEditor[mouseLine].empty()) {
            buffer = textEditor[mouseLine];
            textEditor.erase(textEditor.begin() + mouseLine);
        } else if (curLine == "Ctrl+V" && !buffer.empty()) {
            textEditor.insert(textEditor.begin() + mouseLine++, buffer);
        }
    }

    for (const std::string & line : textEditor) {
        std::cout << line;
    }

    return 0;
}


