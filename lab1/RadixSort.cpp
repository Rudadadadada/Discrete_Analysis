#include <iostream>
#include <vector>

struct memorizedKey {
    unsigned long long left_half;
    unsigned long long right_half;
};

unsigned long long toTen(std::string &s) {
    int size = 16;

    unsigned long long res = 0;
    for (char c: s) {
        if (isdigit(c)) {
            res = res * size + c - '0';
        }
        if (std::isalpha(c)) {
            res = res * size + c - 'a' + 10;
        }
    }
    return res;
}

std::string fromTen(unsigned long long num) {
    int size = 16;

    std::string alphabet = "0123456789abcdef";
    std::string res_rev;
    while (num > 0) {
        res_rev += alphabet[num % size];
        num /= size;
    }

    while (res_rev.size() != size) {
        res_rev.push_back('0');
    }

    std::string res;
    for (int i = (int) res_rev.size() - 1; i > -1; --i) {
        res.push_back(res_rev[i]);
    }
    return res;
}

memorizedKey toStructure(std::string &num) {
    std::string second_part, first_part;
    for (int i = 0; i < num.size(); ++i) {
        if (i < 16) {
            first_part += num[i];
        } else {
            second_part += num[i];
        }
    }
    return memorizedKey{toTen(first_part), toTen(second_part)};
}

void countSort(std::vector<std::pair<memorizedKey, int>> &arr, int &digit) {
    int number_system = 256;

    int n = (int) arr.size();
    std::vector<std::pair<memorizedKey, int>> output(n);
    std::vector<int> count(number_system, 0);

    for (int i = 0; i < n; ++i) {
        unsigned long long num;
        int index;
        if (digit < 8) {
            num = arr[i].first.right_half;
            index = (int) ((num >> (digit * 8)) % (1 << 8));
        } else {
            num = arr[i].first.left_half;
            index = (int) ((num >> ((digit - 8) * 8)) % (1 << 8));
        }
        ++count[index];
    }

    for (int i = 1; i < number_system; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i > -1; --i) {
        unsigned long long num;
        int index;
        if (digit < 8) {
            num = arr[i].first.right_half;
            index = (int) ((num >> (digit * 8)) % (1 << 8));
        } else {
            num = arr[i].first.left_half;
            index = (int) ((num >> ((digit - 8) * 8)) % (1 << 8));
        }
        output[count[index] - 1] = arr[i];
        --count[index];
    }

    arr = output;
}

void radixSort(std::vector<std::pair<memorizedKey, int>> &arr) {
    int max_digit = 16;

    for (int digit = 0; digit < max_digit; ++digit) {
        countSort(arr, digit);
    }
}

void print(std::vector<std::pair<memorizedKey, int>> &arr, std::vector<std::string> &values) {
    std::cout.tie(nullptr);
    for (std::pair<memorizedKey, int> &item: arr) {
        std::cout << fromTen(item.first.left_half) << fromTen(item.first.right_half) << '\t'
                  << values[item.second] << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<memorizedKey, int>> arr;
    std::string key, value;
    std::vector<std::string> values;

    int index = 0;
    while (std::cin >> key) {
        std::cin >> value;
        values.push_back(value);
        arr.emplace_back(toStructure(key), index);
        ++index;
    }

    radixSort(arr);
    print(arr, values);
    return 0;
}