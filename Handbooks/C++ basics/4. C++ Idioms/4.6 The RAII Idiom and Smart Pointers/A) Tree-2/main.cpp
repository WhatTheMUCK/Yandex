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