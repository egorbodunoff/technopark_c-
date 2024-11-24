#ifndef LRU_HPP
#define LRU_HPP

#include "intrusive_list.hpp"
#include "hashtable.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <list>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class LRUCache {
    struct CacheEntry {
        Key key;
        Value value;
        size_t size_bytes;
        IntrusiveListHook<CacheEntry> hook;

        CacheEntry(const Key& key, const Value& value, size_t size_bytes)
            : key(key), value(value), size_bytes(size_bytes) {}
    };

    using ListType = IntrusiveList<CacheEntry, &CacheEntry::hook>;
    using MapType = HashTable<Key, typename ListType::Iterator, Hash>;

   public:
    LRUCache(size_t max_entries, size_t max_size_bytes)
        : max_entries_(max_entries), max_size_bytes_(max_size_bytes), current_size_bytes_(0) {}

    ~LRUCache() {
        clear(); 
    }

    bool put(const Key& key, const Value& value) {
        size_t entry_size = key.size() + sizeof(Value) + sizeof(CacheEntry);
        if (entry_size > max_size_bytes_ || max_entries_ == 0) {
            return false; 
        }

        auto it = map_.find(key);
        if (it) {
            list_.erase(**it);
            current_size_bytes_ -= (*it)->size_bytes;
            map_.erase(key);
        } else if (list_.size() >= max_entries_ || current_size_bytes_ + entry_size > max_size_bytes_) {
            evict(entry_size);
        }

        auto& new_entry = entries_.emplace_back(key, value, entry_size);
        list_.push_front(new_entry);
        map_.insert(key, list_.begin());
        current_size_bytes_ += entry_size;

        return true;
    }

    std::optional<Value> get(const Key& key) {
        auto it = map_.find(key);
        if (!it) return std::nullopt;

        auto& entry = **it;
        list_.erase(entry);
        list_.push_front(entry);

        return entry.value;
    }

    void clear() {
        list_.clear();
        map_.clear();
        entries_.clear();
        current_size_bytes_ = 0;
    }

    size_t size() const { return list_.size(); }

    size_t size_bytes() const { return current_size_bytes_; }

   private:
    void evict(size_t required_size) {
        while (!list_.empty() && (list_.size() >= max_entries_ || current_size_bytes_ + required_size > max_size_bytes_)) {
            auto& oldest = list_.back();
            current_size_bytes_ -= oldest.size_bytes;
            map_.erase(oldest.key);
            list_.pop_back();
        }
    }

    size_t max_entries_;
    size_t max_size_bytes_;
    size_t current_size_bytes_;
    ListType list_;
    MapType map_;
    std::list<CacheEntry> entries_;
};

#endif
