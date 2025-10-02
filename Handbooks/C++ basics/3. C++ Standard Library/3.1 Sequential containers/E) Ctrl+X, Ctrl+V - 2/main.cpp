#include <iostream>
#include <string>
#include <list>

int main() {
    std::list<std::string> textEditor;
    std::string curLine;

    while (std::getline(std::cin, curLine) && !curLine.empty()) {
        textEditor.push_back(curLine + '\n');
    }
    textEditor.push_back("");

    auto mouseLine = textEditor.begin();

    std::list<std::string> buffer;

    bool shiftPressed = false;
    int shiftOffset = 0;
    auto shift = textEditor.begin(); 

    std::string command;
    while (std::cin >> command) {
        if (command == "Up") {
            if (mouseLine == textEditor.begin()) {
                continue;
            }
            --mouseLine;
            if (!shiftPressed) {
                shift = mouseLine;
            } else {
                --shiftOffset;
            }
        } else if (command == "Down") {
            if (mouseLine == textEditor.end()) {
                continue;
            }
            ++mouseLine;
            if (!shiftPressed) {
                shift = mouseLine;
            } else {
                ++shiftOffset;
            }
        } else if (command == "Shift") {
            shiftPressed = true;
        } else if (command == "Ctrl+X") {
            if (shift == mouseLine && mouseLine == textEditor.end()) {
                continue;
            }

            buffer.clear();

            if (shift == mouseLine) {
                auto toSplice = mouseLine;
                mouseLine = std::next(mouseLine);
                buffer.splice(buffer.begin(), textEditor, toSplice);
            } else if (shiftOffset < 0) {
                buffer.splice(buffer.begin(), textEditor, mouseLine, shift);
                mouseLine = shift;
            } else {
                buffer.splice(buffer.begin(), textEditor, shift, mouseLine);
            }

            shiftPressed = false;
            shift = mouseLine;
            shiftOffset = 0;
        } else if (command == "Ctrl+V") {
            if (buffer.empty()) {
                continue;
            }

            if (shiftOffset < 0) {
                mouseLine = textEditor.erase(mouseLine, shift);
            } else if (shiftOffset > 0) {
                mouseLine = textEditor.erase(shift, mouseLine);
            }

            textEditor.insert(mouseLine, buffer.begin(), buffer.end());

            shiftPressed = false;
            shift = mouseLine;
            shiftOffset = 0;
        }
    }

    for (const std::string& line : textEditor) {
        std::cout << line;
    }

    return 0;
}