#include <cassert>
#include <iostream>
#include "lru.hpp"

void testAddAndRetrieveEntry() {
    LRUCache<std::string, std::string> cache(3, 1024);

    assert(cache.put("key1", "value1"));

    auto value = cache.get("key1");
    assert(value.has_value());
    assert(value.value() == "value1");
}

void testOverwriteEntry() {
    LRUCache<std::string, std::string> cache(3, 1024);

    assert(cache.put("key1", "value1"));

    assert(cache.put("key1", "new_value"));

    auto value = cache.get("key1");
    assert(value.has_value());
    assert(value.value() == "new_value");
}

void testEvictionBySize() {
    LRUCache<std::string, std::string> cache(3, 1024); 
    assert(cache.put("key1", "value1"));
    assert(cache.put("key2", "value2"));
    assert(cache.put("key3", "value3"));

    assert(cache.put("key4", "large_value_exceeding_limit"));

    assert(!cache.get("key1").has_value());
    assert(cache.get("key2").has_value());
    assert(cache.get("key3").has_value());
    assert(cache.get("key4").has_value());
}

void testEvictionByEntries() {
    LRUCache<std::string, std::string> cache(2, 1024);

    assert(cache.put("key1", "value1"));
    assert(cache.put("key2", "value2"));

    assert(cache.put("key3", "value3"));

    assert(!cache.get("key1").has_value());
    assert(cache.get("key2").has_value());
    assert(cache.get("key3").has_value());
}

void testClear() {
    LRUCache<std::string, std::string> cache(3, 1024);

    assert(cache.put("key1", "value1"));
    assert(cache.put("key2", "value2"));

    cache.clear();

    assert(!cache.get("key1").has_value());
    assert(!cache.get("key2").has_value());
    assert(cache.size() == 0);
    assert(cache.size_bytes() == 0);
}

int main() {
    testAddAndRetrieveEntry();
    testOverwriteEntry();
    testEvictionBySize();
    testEvictionByEntries();
    testClear();

    std::cout << "All tests passed!\n";
    return 0;
}
