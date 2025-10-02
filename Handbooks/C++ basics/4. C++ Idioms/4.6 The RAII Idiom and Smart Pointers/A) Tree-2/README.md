# Tree-2

**Ограничение времени**  
1 с  

**Ограничение памяти**  
64.0 Мб  

**Ввод**  
стандартный ввод или `input.txt`  

**Вывод**  
стандартный вывод или `output.txt`

Коля пишет класс «Дерево». Узел дерева может хранить целое число, а также знает о своём родителе и о своих потомках. У узла есть функция `AddChild` для добавления потомка с заданным числовым значением, а также функция `Print` для красивой печати поддерева начиная с этого узла.

Вот что получилось у Коли:

```cpp
#include <iostream>
#include <vector>

class TreeNode {
private:
    int value;
    TreeNode* root = nullptr;
    std::vector<TreeNode*> children;

public:
    TreeNode(int val): value(val) {
    }

    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    TreeNode* AddChild(int child_value) {
        auto node = new TreeNode(child_value);
        node->root = this;
        children.push_back(node);
        return node;
    }

    void Print(int depth = 0) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << "- " << value << "\n";
        for (const auto& child : children) {
            child->Print(depth + 1);
        }
    }
};
```

Использоваться этот класс будет примерно так:

```cpp
#include "tree.h"

int main() {
    TreeNode root(1);

    auto left_son = root.AddChild(10);
    auto middle_son = root.AddChild(20);
    auto right_son = root.AddChild(30);

    left_son->AddChild(100);
    left_son->AddChild(200);

    root.Print();
}
```

Однако эта работающая на первый взгляд тестовая программа падает, если её собрать с адресным санитайзером. Исправьте код класса `TreeNode`, чтобы решить эту проблему.

**Примечание**

Сдайте в систему только код класса `TreeNode` без функции `main`. Подключите все необходимые для вашей реализации библиотеки.
## Решение

tree.h
```cpp
#include <iostream>
#include <vector>
#include <memory>

class TreeNode {
private:
    int value;
    TreeNode* root = nullptr;
    std::vector<std::unique_ptr<TreeNode>> children;

public:
    TreeNode(int val): value(val) {
    }

    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    TreeNode * AddChild(int child_value) {
        children.push_back(std::make_unique<TreeNode>(child_value));
        children.back()->root = this;
        return children.back().get();
    }

    void Print(int depth = 0) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << "- " << value << "\n";
        for (const auto& child : children) {
            child->Print(depth + 1);
        }
    }
};
```

main.cpp
```cpp
#include "tree.h"

int main() {
    TreeNode root(1);

    auto left_son = root.AddChild(10);
    root.AddChild(20);
    root.AddChild(30);

    left_son->AddChild(100);
    left_son->AddChild(200);

    root.Print();
}
```
