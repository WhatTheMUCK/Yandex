# Рисование прямоугольников - 2

**Ограничение времени:** 4 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

На рабочем столе расположены $k$ окон открытых приложений. Некоторые из окон могут перекрываться, а для некоторых даже невозможно определить точное положение: либо полностью закрыты другими окнами, либо некоторая часть границы полностью перекрывается окнами других приложений.

По видимой части окон определите общее количество последовательностей открытия окон, каждая из которых приводит к данной конфигурации рабочего стола.

## Модельное описание условия

Задана матрица $n \times m$, состоящая из $n$ строк и $m$ столбцов, и два числа $k$ и $s$. Матрица задаёт области рабочего стола:

- Если в определённой части рабочего стола нет ни одного открытого окна приложений, то эта область задаётся символом `.`.
- Если самым верхним окном в области является окно приложения с номером $i$, то эта область описывается цифрой $i$.

Для удобства будем считать, что запущено не более девяти программ. Окно каждой из запущенных программ задаётся квадратом $s \times s$.

Для автоматизации тестирования необходимо составить тестовый сценарий открытия окон:

- Определить, в каком порядке программы будут запускаться.
- Для каждой программы определить левую верхнюю позицию на рабочем столе для размещения нового окна. Окно новой запущенной программы может перекрывать ранее открытые окна.

Требуется определить **общее число подходящих тестовых сценариев**, которые после выполнения образуют заданную конфигурацию рабочего стола.  
Сценарии различаются как порядком открытия приложений, так и позициями их окон.

## Формат ввода

- В первой строке содержится целое число $t$ — количество тестовых примеров.
- Описание каждого тестового примера начинается со строки, содержащей четыре числа $n$, $m$, $k$, $s$.
- Далее следует описание рабочего стола: $n$ строк по $m$ символов.

**Гарантируется:**

- Каждое окно имеет размер $s \times s$ и полностью помещается на рабочем столе.
- Для каждого приложения $i \in \{1, \dots, k\}$ в матрице присутствует хотя бы одна клетка с цифрой $i$ (окно частично видимо).
- Существует хотя бы одно корректное размещение окон, соответствующее заданной матрице.

## Формат вывода

Для каждого тестового примера выведите единственное число — количество возможных тестовых сценариев.

## Примеры

### Пример 1

**Ввод**  
```
3
5 5 5 1
12345
.....
.....
.....
.....
5 5 5 2
.11..
411..
44522
.3322
.33..
5 5 5 2
..11.
4411.
44522
.3322
.33..
```

**Вывод**  
```
120
55
160
```

### Пример 2

**Ввод**  
```
1
2 6 5 2
112345
112345
```

**Вывод**  
```
1
```

### Пример 3

**Ввод**  
```
2
8 10 9 5
133377777.
266677777.
288888777.
289999977.
289999977.
28999994..
.8999994..
.599999...
10 9 9 5
..9999922
.39999922
.39999922
.39999922
.39999944
778888844
777776544
777776544
777776444
7777761..
```

**Вывод**  
```
70
12
```

## Ограничения

- $1 \leq t \leq 100$
- $2 \leq n, m \leq 10$
- $1 \leq k \leq 9$
- $1 \leq s \leq 5$
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <queue>


template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

template <typename T>
std::istream & operator>>(std::istream & is, matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j){
            is >> rhs[i][j];
        }
    }
    return is;
}

template <typename T>
std::ostream & operator<<(std::ostream & os, const matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j){
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

template <typename T, typename V>
std::ostream & operator<<(std::ostream & os, const std::pair<T, V> rhs) {
    return os << '{' << rhs.first << ", " << rhs.second << "} ";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int test = 0; test < t; ++test) {
        int n, m, k, s;
        std::cin >> n >> m >> k >> s;

        matrix<char> window(n + 1, row<char>(m + 1, '.'));
        std::vector<matrix<int>> helper(k, matrix<int>(n + 1, row<int>(m + 1, 0)));

        std::vector<int> amount(k);
        std::vector<std::vector<std::pair<int, int>>> possibleAngle(k);
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                char symbol;
                std::cin >> symbol;
                
                window[i][j] = symbol;
                if (symbol == '.') {
                    continue;
                }

                ++amount[symbol - '1'];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                char symbol = window[i][j];
                if (symbol == '.') {
                    continue;
                }

                ++helper[symbol - '1'][i][j];

                if (i == 0 && j == 0) {
                    continue;
                }
                for (int index = 0; index < k; ++index) {
                    if (i == 0) {
                        helper[index][i][j] += helper[index][i][j - 1];
                        continue;
                    }

                    if (j == 0) {
                        helper[index][i][j] += helper[index][i - 1][j];
                        continue;
                    }

                    helper[index][i][j] += helper[index][i][j - 1] + helper[index][i - 1][j] - helper[index][i - 1][j - 1];

                    if (i >= s && j >= s) {
                        int amountInArea = helper[index][i][j] - (helper[index][i - s][j] + helper[index][i][j - s] - helper[index][i - s][j - s]);
                        if (amountInArea == amount[index])
                        possibleAngle[index].push_back({i + 1 - s, j + 1 - s});
                    }
                }
            }
        }

        std::stack<int> DFS;
        int startMask = 0;
        matrix<char> startWindow(n + 1, row<char>(m + 1, '.'));
        DFS.push(startMask);
        long long answer = 0;
        while (!DFS.empty()) {
            auto mask = DFS.top();
            DFS.pop();
            for (int i = 0; i < k; ++i) {
                int curMask = mask;
                if ((curMask & (1 << i)) != 0) {
                    continue;
                }
                curMask |= (1 << i);
                for (size_t j = 0; j < possibleAngle[i].size(); ++j) {
                    auto [leftUpI, leftUpj] = possibleAngle[i][j];
                    bool canBeAnswer = true; 
                    for (int offsetI = 0; offsetI < s && canBeAnswer; ++offsetI) {
                        for (int offsetJ = 0; offsetJ < s && canBeAnswer; ++offsetJ) {
                            int curI = leftUpI + offsetI, curJ = leftUpj + offsetJ;
                            if (!(0 < curI && curI <= n) || !(0 < curJ && curJ <= m)) {
                                continue;
                            }

                            if (window[curI][curJ] != i + '1') {
                                if (window[curI][curJ] == '.') {
                                    canBeAnswer = false;
                                    continue;
                                }

                                if ((curMask & (1 << (window[curI][curJ] - '1'))) != 0) {
                                    canBeAnswer = false;
                                    continue;
                                }
                            }
                        }
                    }

                    if (!canBeAnswer) {
                        continue;
                    }

                    if (curMask == ((1 << k) - 1)) {
                        ++answer;
                        continue;
                    }

                    DFS.push(curMask);
                }
            }
        }

        std::cout << answer << '\n';
    }

    return 0;
}
```
