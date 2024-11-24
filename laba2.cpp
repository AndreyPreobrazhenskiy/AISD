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

int main() {
    // Пример работы всех методов
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.push_head(0);
    std::cout << "List: " << list << std::endl;

    LinkedList<int> another_list(5, 10, 50);
    std::cout << "Another list: " << another_list << std::endl;

    list.push_tail(another_list);
    std::cout << "Merged list: " << list << std::endl;

    list.pop_head();
    list.pop_tail();
    std::cout << "After pops: " << list << std::endl;

    list.delete_node(2);
    std::cout << "After deleting 2s: " << list << std::endl;

    // Счастливые числа
    LinkedList<int> happy_list(20, 1, 100);
    std::cout << "---------------------------------------------";
    std::cout << "\nHappy numbers: ";
    for (size_t i = 0; i < happy_list.get_size(); ++i) {
        if (is_happy(happy_list[i])) {
            std::cout << happy_list[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "---------------------------------------------\n";

    // Ханойская башня
    LinkedList<int> tower1, tower2, tower3;
    for (int i = 3; i > 0; --i) {
        tower1.push_tail(i);
    }
    solve_hanoi(3, tower1, tower2, tower3);

    return 0;
}
