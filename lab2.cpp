#include <iostream>


template<typename K, typename T>
struct Pair {
    K key;
    T value;
    bool is_occupied;
    bool is_deleted;

    Pair() : is_occupied(false), is_deleted(false) {}
};


template<typename K, typename T>
class UnorderedMap {
private:
    Pair<K, T>* table;
    int capacity;
    int size;

    int hash(K key) const {
        return key % capacity;
    }

public:
    UnorderedMap(int cap) : capacity(cap), size(0) {
        table = new Pair<K, T>[capacity];
    }

    UnorderedMap(int cap, int num_elements) : capacity(cap), size(0) {
        table = new Pair<K, T>[capacity];
        srand(time(0));
        for (int i = 0; i < num_elements; ++i) {
            K key = rand();
            T value = rand();
            insert(key, value);
        }
    }

    UnorderedMap(const UnorderedMap& other) {
        capacity = other.capacity;
        size = other.size;
        table = new Pair<K, T>[capacity];
        for (int i = 0; i < capacity; ++i)
            table[i] = other.table[i];
    }

    UnorderedMap& operator=(const UnorderedMap& other) {
        if (this != &other) {
            delete[] table;
            capacity = other.capacity;
            size = other.size;
            table = new Pair<K, T>[capacity];
            for (int i = 0; i < capacity; ++i)
                table[i] = other.table[i];
        }
        return *this;
    }

    ~UnorderedMap() {
        delete[] table;
    }

    void print() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].is_occupied && !table[i].is_deleted) {
                std::cout << "[" << i << "] Key: " << table[i].key << ", Value: " << table[i].value << "\n";
            }
        }
    }

    bool insert(K key, const T& value) {
        int index = hash(key);
        int original_index = index;
        while (table[index].is_occupied && !table[index].is_deleted) {
            if (table[index].key == key)
                return false;
            index = (index + 1) % capacity;
            if (index == original_index)
                return false;  // Table full
        }
        table[index].key = key;
        table[index].value = value;
        table[index].is_occupied = true;
        table[index].is_deleted = false;
        ++size;
        return true;
    }

    void insert_or_assign(K key, T& value) {
        int index = hash(key);
        int original_index = index;
        while (table[index].is_occupied && !table[index].is_deleted) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity;
            if (index == original_index)
                return;
        }
        table[index].key = key;
        table[index].value = value;
        table[index].is_occupied = true;
        table[index].is_deleted = false;
        ++size;
    }

    bool contains(const T& value) {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].is_occupied && !table[i].is_deleted && table[i].value == value)
                return true;
        }
        return false;
    }

    T* search(K key) {
        int index = hash(key);
        int original_index = index;
        while (table[index].is_occupied) {
            if (!table[index].is_deleted && table[index].key == key)
                return &table[index].value;
            index = (index + 1) % capacity;
            if (index == original_index)
                break;
        }
        return nullptr;
    }

    bool erase(K key) {
        int index = hash(key);
        int original_index = index;
        while (table[index].is_occupied) {
            if (!table[index].is_deleted && table[index].key == key) {
                table[index].is_deleted = true;
                --size;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == original_index)
                break;
        }
        return false;
    }

    int count(K key) {
        int index = hash(key);
        int collisions = 0;
        for (int i = 0; i < capacity; ++i) {
            if (table[i].is_occupied && hash(table[i].key) == index)
                ++collisions;
        }
        return collisions;
    }

    int getSize() const {
        return size;
    }

    int get_collision() const {
        int total_collisions = 0;
        for (int i = 0; i < capacity; ++i) {
            if (table[i].is_occupied && !table[i].is_deleted) {
                int ideal_pos = hash(table[i].key);
                if (ideal_pos != i) {
                    total_collisions++;
                }
            }
        }
        return total_collisions;
    }
};


template<typename K, typename T>
int find_and_print_optimal_size(int group_size) {
    printf("Size | Avg Collisions | Probability\n");
    printf("-----|----------------|------------\n");

    int optimal_size = -1;
    for (int size = 25; size <= 475; size += 50) {
        int total_collisions = 0;
        for (int exp = 0; exp < 100; ++exp) {
            UnorderedMap<K, T> map(size, group_size);
            total_collisions += map.get_collision();
        }

        double avg_collisions = (double)total_collisions / 100;
        double probability = avg_collisions / group_size * 100;

        printf("%4d | %14.2f | %9.2f%%\n", size, avg_collisions, probability);

        if (optimal_size == -1 && probability < 50.0) {
            optimal_size = size;
        }
    }

    return optimal_size;
}


int main() {
    srand(time(0));

    std::cout << "=== Constructor with specified capacity ===\n";
    UnorderedMap<int, int> map1(10);
    map1.insert(5, 100);
    map1.insert(15, 200); // Collision with key 5 (5 % 10 == 15 % 10 == 5)
    map1.print();

    std::cout << "\n=== Constructor with random values ===\n";
    UnorderedMap<int, int> map2(20, 5); // 5 random elements
    map2.print();

    std::cout << "\n=== Copy constructor ===\n";
    UnorderedMap<int, int> map3 = map1;
    map3.print();

    std::cout << "\n=== Assignment operator ===\n";
    UnorderedMap<int, int> map4(5);
    map4 = map2;
    map4.print();

    std::cout << "\n=== Method: search() ===\n";
    int* val = map1.search(5);
    if (val) std::cout << "Value found for key 5: " << *val << "\n";
    else std::cout << "Key 5 not found.\n";

    std::cout << "\n=== Method: contains() ===\n";
    int check_val = 100;
    if (map1.contains(check_val))
        std::cout << "Value 100 is present in the map.\n";
    else
        std::cout << "Value 100 is not found in the map.\n";

    std::cout << "\n=== Method: insert_or_assign() ===\n";
    int new_val = 999;
    std::cout << "Update value at key 5 -> 999\n";
    map1.insert_or_assign(5, new_val); // Update value at key 5
    map1.print();

    std::cout << "\n=== Method: erase() ===\n";
    if (map1.erase(15)) std::cout << "Key 15 erased successfully.\n";
    else std::cout << "Key 15 not found for deletion.\n";
    map1.print();

    std::cout << "\n=== Method: count() ===\n";
    int hash_index = 5 % 10;
    int count = map1.count(5);
    std::cout << "Number of elements with hash index " << hash_index << ": " << count << "\n";

    std::cout << "\n=== Collision demonstration ===\n";
    UnorderedMap<int, int> collision_test(5);
    collision_test.insert(0, 10);   // 0 % 5 = 0
    collision_test.insert(5, 20);   // 5 % 5 = 0 -> collision
    collision_test.insert(10, 30);  // 10 % 5 = 0 -> another collision
    collision_test.print();

    std::cout << "\n=== Collision analysis ===\n";
    int group_size = 19;
    int result = find_and_print_optimal_size<int, int>(group_size);

    if (result != -1) {
        printf("\nOptimal table size for %d elements: %d (collision probability < 50%%)\n",
            group_size, result);
    }
    else {
        printf("\nNo suitable table size found for %d elements (all probabilities >= 50%%)\n",
            group_size);
    }


    return 0;
}


