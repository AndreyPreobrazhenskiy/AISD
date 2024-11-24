#include "list.h"


bool is_happy(int number) {
    std::unordered_set<int> seen;
    while (number != 1 && seen.find(number) == seen.end()) {
        seen.insert(number);
        int sum = 0;
        while (number > 0) {
            int digit = number % 10;
            sum += digit * digit;
            number /= 10;
        }
        number = sum;
    }
    return number == 1;
}