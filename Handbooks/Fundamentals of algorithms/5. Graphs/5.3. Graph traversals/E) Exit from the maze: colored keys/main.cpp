#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>


template <typename T>
using row = std::vector<T>; 

template <typename T>
using matrix = std::vector<row<T>>; 

template <typename T>
std::ostream & operator<<(std::ostream & os, const matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

template <typename T, typename V>
std::pair<T, V> operator+=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> operator+(std::pair<T, V> lhs, const std::pair<T, V> & rhs) {
    return lhs += rhs;
}

template <typename T, typename V>
std::pair<T, V> operator-=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first -= rhs.first;
    lhs.second -= rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> operator-(std::pair<T, V> lhs, const std::pair<T, V> & rhs) {
    return lhs -= rhs;
}


std::vector<std::pair<int, int>> offsets = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
std::string directions = "0123"; // 0 - Up, 1 - Right, 2 - Down, 3 - Left 

std::unordered_map<char, char> reverseDirections = {{'0', '2'}, {'1', '3'}, {'2', '0'}, {'3', '1'}};
std::unordered_map<char, char> directionToLetter = {{'0', 'U'}, {'1', 'R'}, {'2', 'D'}, {'3', 'L'}, {'P', 'P'}};

long long pairToInt(const std::pair<int, int> & pos, int m) {
    auto & [i, j] = pos;
    return i * m + j;
}

std::pair<int, int> intToPair(long long index, int m) {
    return {index / m, index % m};
}

bool correct(const matrix<char> & maze, int i, int j, int mask, const std::unordered_map<char, char> & accordance) {
    int n = static_cast<int>(maze.size());
    int m = static_cast<int>(maze[0].size());
    if (!(0 <= i && i < n) || !(0 <= j && j < m)) {
        return false;
    }

    const char state = maze[i][j];
    if (state == '.' || state == 'F' || state == 'S' || state == 'K') {
        return true;
    }

    if (state == 'P') {
        return false;
    }


    if (directions.find(state) != std::string::npos) {
        return false;
    }

    if (('A' <= state && state <= 'Z')) {
        // std::cout << "state = " << state << " | " << accordance.at(state) << ' ' << (1 << (accordance.at(state) - 'a')) << '\n';
        return (mask & (1 << (accordance.at(state) - 'a'))) != 0;
    }

    if ('a' <= state && state <= 'z') {
        return true;
    }

    return false;
}

std::string binary(int x) {
    std::string answer;
    while (x > 0) {
        answer.push_back('0' + x%2);
        x /= 2;
    }
    std::reverse(answer.begin(), answer.end());

    if (answer.empty()) {
        answer = "0";
    }
    return answer;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    matrix<char> maze(n, row<char>(m));
    std::pair<int, int> start, finish, stopper = {-1, -1};
    start = finish = stopper;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> maze[i][j];
            
            if (maze[i][j] == 'S') {
                start = {i, j};
            } else if (maze[i][j] == 'F') {
                finish = {i, j};
            }
        }
    }

    int k;
    std::cin >> k;
    std::unordered_map<char, char> accordance;
    for (int i = 0; i < k; ++i) {
        char door, key;
        std::cin >> door >> key;
        accordance[door] = key;
    }

    if (start == stopper || finish == stopper) {
        std::cout << "-1\n";
        return 0;
    }

    std::unordered_map<int, matrix<char>> parents;
    
    std::queue<std::pair<long long, int>> BFS;
    int startMask = 0;
    parents[startMask] = maze;

    BFS.push({pairToInt(start, m), startMask});
    while (!BFS.empty()) {
        auto [posIndex, mask] = BFS.front();
        BFS.pop(); 

        std::pair<int, int> curPos = intToPair(posIndex, m);
        // auto [i1, j1] = curPos;
        // std::cout << "curPos: " << i1 << ' ' << j1 << ' ' << maze[i1][j1] << " | " << mask << ' ' << binary(mask) << '\n';
        for (int k = 0; k < 4; ++k) {
            std::pair<int, int> tempPos = curPos + offsets[k];
            auto & [i, j] = tempPos;
            // std::cout << std::boolalpha;
            // std::cout << "  tempPos: " << i << ' ' << j << ' ' << maze[i][j] << ' ' << correct(parents[mask], i, j, mask, accordance) << '\n';
            if (correct(parents[mask], i, j, mask, accordance)) {
                parents[mask][i][j] = directions[k];
                BFS.push({pairToInt(tempPos, m), mask});
                if ('a' <= maze[i][j] && maze[i][j] <= 'z') {
                    int newMask = mask | (1 << (maze[i][j] - 'a'));
                    if (newMask == mask) {
                        continue;
                    }

                    // std::cout << "  Create new mask:" << maze[i][j] << ' ' << newMask << '\n';
                    if (!parents.contains(newMask)) {
                        parents[newMask] = maze;
                    }
                    parents[newMask][i][j] = 'P';
                    BFS.push({pairToInt(tempPos, m), newMask});
                }

                if (maze[i][j] == 'F') {
                    std::string path;
                    while (tempPos != start || mask != 0) {
                        // std::cout << mask << ' ' << i << ' ' << j << ' ' << parents.at(mask)[i][j] << '\n';
                        path.push_back(directionToLetter[parents[mask][i][j]]);
                        if (parents[mask][i][j] == 'P') {
                            mask ^= (1 << (maze[i][j] - 'a'));
                            // std::cout << "  After deletion: " << mask << '\n';
                            continue;
                        } else {
                            char direction = reverseDirections[parents[mask][i][j]];
                            int offsetIndex = directions.find(direction);
                            tempPos += offsets[offsetIndex];
                        }
                    }
                    std::reverse(path.begin(), path.end());
                    std::cout << path.size() << '\n';
                    std::cout << path << '\n';
                    return 0;
            }
            }
        }
    }

    std::cout << "-1\n";
    return 0;
}