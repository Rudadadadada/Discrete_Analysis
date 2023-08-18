#include "vector"
#include "set"
#include <iostream>


std::vector<int> z_function(std::string &s) {
    int n = (int) s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

std::string remove_spaces(std::string &sequence) {
    std::string new_str;
    for (char i: sequence)
        if (i != ' ')
            new_str += i;
    return new_str;
}

void to_lower(std::string &sequence) {
    for (char &c: sequence)
        c = (char) tolower(c);
}

int main() {
    std::string pattern;
    std::getline(std::cin, pattern);
    to_lower(pattern);
    pattern = remove_spaces(pattern);
    int n = (int) pattern.size();
    std::string text;
    std::set <std::vector<int>> data;

    char c;
    int line = 1;
    int index = 0;
    int nWord = 0;
    std::string curWord;

    while ((c = (char) getchar()) != EOF) {
        if (c == '\n') {
            ++nWord;
            if (!curWord.empty()) {
                text += curWord;
                data.insert({index, line, nWord});
                curWord = "";
            }
            ++line;
            nWord = 0;
        } else if (c == ' ') {
            if (!curWord.empty()) {
                ++nWord;
                text += curWord;
                data.insert({index, line, nWord});
                curWord = "";
            }
        } else {
            curWord += (char) tolower(c);
            index += 1;
        }
    }

    std::string find_sub = pattern + '#' + text;
    std::vector<int> res = z_function(find_sub);

    std::set <std::pair<int, int>> realAns;

    for (int i = 0; i < (int) res.size(); ++i) {
        if (res[i] == n) {
            std::vector<int> ans = *data.lower_bound({i - n, 1, 1});
            realAns.insert({ans[1], ans[2]});
        }
    }
    for (auto &i: realAns)
        std::cout << i.first << ", " << i.second << '\n';
    return 0;
}