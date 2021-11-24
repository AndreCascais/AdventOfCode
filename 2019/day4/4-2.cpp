#include <iostream>
#include <string>

bool isValidPassword(int pw) {
    auto str = std::to_string(pw);

    if (str.size() != 6) {
        return false;
    }

    bool repeat = false;
    for (int i = 0; i < str.size() - 1; i++) {
        if (static_cast<int>(str[i]) > static_cast<int>(str[i + 1])) {
            return false;
        }
    }

    int chainSize = 0;

    for (int i = 0; i < str.size() -1; i++) {
        if (str[i] == str[i + 1] && chainSize == 0) {
            chainSize = 2;
        }
        else if (str[i] == str[i + 1]) {
            chainSize++;
        }
        else if (str[i] != str[i + 1] && chainSize == 2) {
            return true;
        }
        else {
            chainSize = 0;
        }
    }

    return chainSize == 2;
}

int numberOfValidPasswords(int start, int end) {

    int n = 0;

    for (int i = start; i < end + 1; i++) {
        if (isValidPassword(i)) {
            n++;
        }
    }
    return n;
}

int main() {
    int start, end;
    std::cin >> start >> end;
    std::cout << numberOfValidPasswords(start, end) << '\n';
}