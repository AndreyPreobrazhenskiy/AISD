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

void solve_hanoi(int n, LinkedList<int>& source, LinkedList<int>& target, LinkedList<int>& auxiliary) {
    if (n == 1) {
        int disk = source[source.get_size() - 1];
        source.pop_tail();
        target.push_tail(disk);
        std::cout << "Moved disk " << disk << " from Source to Target\n";
        return;
    }
    solve_hanoi(n - 1, source, auxiliary, target);
    int disk = source[source.get_size() - 1];
    source.pop_tail();
    target.push_tail(disk);
    std::cout << "Moved disk " << disk << " from Source to Target\n";
    solve_hanoi(n - 1, auxiliary, target, source);
}
