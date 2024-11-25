#include <cassert>
#include <iostream>

#include "hashtable.hpp"

struct CustomHash {
    size_t operator()(int key) const { return key % 4; }
};

void test_empty_and_size() {
    HashTable<int, int> ht;

    assert(ht.empty() == true);
    assert(ht.size() == 0);

    ht.insert(1, 10);
    assert(ht.empty() == false);
    assert(ht.size() == 1);
}

void test_insert_and_find() {
    HashTable<int, int> ht;

    ht.insert(1, 10);
    ht.insert(2, 20);

    auto value = ht.find(1);
    assert(value.has_value() && value.value() == 10);

    value = ht.find(2);
    assert(value.has_value() && value.value() == 20);

    value = ht.find(3);
    assert(!value.has_value());
}

void test_insert_with_existing_key() {
    HashTable<int, int> ht;

    ht.insert(1, 10);

    bool inserted = ht.insert(1, 20);
    assert(inserted == false);
    assert(ht[1] == 20);
}

void test_erase() {
    HashTable<int, int> ht;

    ht.insert(1, 10);
    ht.insert(2, 20);

    ht.erase(1);
    auto value = ht.find(1);
    assert(!value.has_value());

    value = ht.find(2);
    assert(value.has_value() && value.value() == 20);
}

void test_operator() {
    HashTable<int, int> ht;

    ht[1] = 10;
    ht[2] = 20;

    assert(ht[1] == 10);
    assert(ht[2] == 20);
}

void test_load_factor() {
    HashTable<int, int> ht(4);

    assert(ht.load_factor() == 0.0);

    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);

    assert(ht.load_factor() == 3.0 / 4);

    ht.insert(4, 40);

    assert(ht.load_factor() == 4.0 / 8);
}

void test_reserve() {
    HashTable<int, int> ht;

    ht.reserve(100);

    assert(ht.size() == 0);
}

void test_clear() {
    HashTable<int, int> ht;

    ht.insert(1, 10);
    ht.insert(2, 20);

    assert(ht.size() == 2);

    ht.clear();

    assert(ht.size() == 0);
    assert(ht.empty() == true);
}

void test_find_index() {
    HashTable<int, int> table(4);
    table.insert(1, 10);
    table.insert(5, 20);
    table.insert(9, 30);

    assert(!table.find(13));
}

void test_find_or_empty() {
    HashTable<int, int, CustomHash> table(4);
    table.insert(1, 10);
    table.insert(5, 20);

    table.erase(5);

    table.insert(9, 30);
    assert(table.find(9).value() == 30);
}

void test_resize_with_collisions() {
    HashTable<int, int, CustomHash> table(2);
    table.insert(1, 10);
    table.insert(5, 30);

    table.insert(2, 20);

    assert(table.find(1).value() == 10);
    assert(table.find(2).value() == 20);
    assert(table.find(5).value() == 30);
}

int main() {
    test_empty_and_size();
    test_insert_and_find();
    test_insert_with_existing_key();
    test_erase();
    test_operator();
    test_load_factor();
    test_reserve();
    test_clear();
    test_find_index();
    test_find_or_empty();

    return 0;
}
