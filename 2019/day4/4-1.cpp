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
        if (str[i] == str[i + 1]) {
            repeat = true;
        }
    }

    return repeat;
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
