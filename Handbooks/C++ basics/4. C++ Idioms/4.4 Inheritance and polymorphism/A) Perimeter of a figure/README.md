# Периметр фигуры

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Вам надо написать базовый класс `Figure` (геометрическая фигура) и унаследованные от него классы `Triangle` (треугольник) и `Rectangle` (прямоугольник).

- Класс `Triangle` должен иметь конструктор, принимающий на вход три числа типа `int` — стороны треугольника. Считайте, что треугольник с такими сторонами всегда существует.
- Класс `Rectangle` должен иметь конструктор, принимающий на вход два числа типа `int` — стороны прямоугольника.
- Класс `Figure` должен объявлять виртуальную функцию  
  ```cpp
  int Perimeter() const
  ```  
  возвращающую периметр фигуры.
- Классы-наследники должны переопределить эту функцию правильным образом.

Функцию `main` писать в вашем коде не надо: она будет в нашей проверяющей программе. Наша программа выглядит так:

```cpp
#include "figures.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<Figure*> figures;

    std::string type;

    while (std::cin >> type) {
        if (type == "Triangle") {
            int a, b, c;
            std::cin >> a >> b >> c;
            figures.push_back(new Triangle(a, b, c));
        } else if (type == "Rectangle") {
            int a, b;
            std::cin >> a >> b;
            figures.push_back(new Rectangle(a, b));
        }
    }

    for (Figure* f : figures) {
        std::cout << f->Perimeter() << "\n";
    }

    for (Figure* f : figures) {
        delete f;
    }
}
```