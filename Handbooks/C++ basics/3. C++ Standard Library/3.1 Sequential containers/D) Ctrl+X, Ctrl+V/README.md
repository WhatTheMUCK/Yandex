# Ctrl+X, Ctrl+V

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Петя решил написать свой собственный текстовый редактор и просит вас помочь протестировать его прототип.  
На текущей стадии разработки в редакторе есть только возможность загрузить файл и выполнять с ним такие действия:

- `Down` — переместить курсор на строчку **вниз**
- `Up` — переместить курсор на строчку **вверх**
- `Ctrl+X` — **вырезать** текущую строку в буфер обмена
- `Ctrl+V` — **вставить** строку из буфера **перед** текущей строкой

---

## Правила

- Изначально курсор находится на **первой строке**.
- Операции `Down` на последней строке и `Up` на первой строке — **игнорируются**.
- Любой файл **заканчивается пустой строкой** (последняя строка всегда пустая).
- Операция `Ctrl+X` на **пустой строке** — **ничего не делает**.
- Изначально **буфер пустой**.
- `Ctrl+X` **перезаписывает** буфер, если в нём уже что-то было.
- `Ctrl+V` **не очищает буфер** — можно вставлять много раз подряд.
- `Ctrl+V` при **пустом буфере** — **ничего не делает**.

---

## Формат ввода

- На вход подаются строки текстового файла (длина каждой ≤ 3000 символов).
- **Последняя строка — всегда пустая** → это сигнал окончания ввода файла.
- После пустой строки — команды: `Down`, `Up`, `Ctrl+X`, `Ctrl+V` (по одной в строке, до конца ввода).

> 💡 Используйте `std::getline` для чтения строк.

---

## Формат вывода

Выведите получившийся файл **построчно** — включая финальную пустую строку, если она осталась.

---

## Пример 1

**Ввод:**
```text
program
is awesome
My
is awful

Down
Down
Down
Ctrl+X
Up
Ctrl+X
Up
Up
Ctrl+V
```

**Вывод:**
```text
My
program
is awesome

```

---

## Пример 2

**Ввод:**
```text
copy
paste

Ctrl+X
Ctrl+V
Ctrl+V
Ctrl+V
Ctrl+X
Ctrl+V
Ctrl+V
Ctrl+V
```

**Вывод:**
```text
copy
copy
copy
paste
paste
paste

```

---

## Примечание

Если условие кажется запутанным — попробуйте воспроизвести пример в настоящем редакторе (например, Sublime Text). Поведение должно совпасть.

❗ **Используйте `std::getline` для чтения строк.**

---

## Требования к реализации

Напишите **полную программу**, читающую из `std::cin` и пишущую в `std::cout`.  
Функция `main` должна быть включена — в этом задании предполагается полная реализация.
## Решение

main.cpp
```cpp
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



```
