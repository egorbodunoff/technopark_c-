#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
    struct Entry {
        Key key;
        Value value;
        bool occupied = false;

        Entry() : key(), value() {}
        Entry(const Key& k, const Value& v, bool valid)
            : key(k), value(v), occupied(valid) {}
    };

   public:
    explicit HashTable(size_t capacity = 16) : buckets_(capacity), hash_fn_(), size_(0) {}

    bool empty() const { return size_ == 0; }

    size_t size() const { return size_; }

    void clear() {
        buckets_.clear();
        buckets_.resize(16);
        size_ = 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > buckets_.size()) {
            resize(new_capacity);
        }
    }

    double load_factor() const { return static_cast<double>(size_) / buckets_.size(); }

    double max_load_factor() const { return max_load_factor_; }

    std::optional<Value> find(const Key& key) const {
        size_t index = find_index(key);
        if (index != npos && buckets_[index].occupied) {
            return buckets_[index].value;
        }
        return std::nullopt;
    }

    size_t count(const Key& key) const { return find_index(key) != npos ? 1 : 0; }

    bool insert(const Key& key, const Value& value) {
        if (size_ >= buckets_.size() * max_load_factor_) {
            resize(buckets_.size() * 2);
        }
        size_t index = find_or_empty(key);
        if (buckets_[index].occupied) {
            buckets_[index].value = value;
            return false;
        }
        buckets_[index] = Entry(key, value, true);
        ++size_;
        return true;
    }

    void erase(const Key& key) {
        size_t index = find_index(key);
        if (index != npos && buckets_[index].occupied) {
            buckets_[index].occupied = false;
            --size_;
        }
    }

    Value& operator[](const Key& key) {
        size_t index = find_or_empty(key);
        if (!buckets_[index].occupied) {
            buckets_[index] = Entry(key, Value(), true);
            // buckets_[index] = {key, Value(), true};
            ++size_;
        }
        return buckets_[index].value;
    }

   private:
    static constexpr size_t npos = size_t(-1);
    size_t find_index(const Key& key) const {
        size_t index = hash_fn_(key) % buckets_.size();
        for (size_t i = 0; i < buckets_.size(); ++i) {
            if (!buckets_[index].occupied) return npos;
            if (buckets_[index].key == key) return index;
            index = (index + 1) % buckets_.size();
        }
        return npos;
    }

    size_t find_or_empty(const Key& key) const {
        size_t index = hash_fn_(key) % buckets_.size();
        for (size_t i = 0; i < buckets_.size(); ++i) {
            if (!buckets_[index].occupied || buckets_[index].key == key) {
                return index;
            }
            index = (index + 1) % buckets_.size();
        }
        
        return npos;
    }

    void resize(size_t new_capacity) {
        std::vector<Entry> new_buckets(new_capacity);
        for (const auto& entry : buckets_) {
            if (entry.occupied) {
                size_t index = hash_fn_(entry.key) % new_capacity;
                while (new_buckets[index].occupied) {
                    index = (index + 1) % new_capacity;
                }
                new_buckets[index] = entry;
            }
        }
        buckets_.swap(new_buckets);
    }

    std::vector<Entry> buckets_;
    Hash hash_fn_;
    size_t size_;
    static constexpr double max_load_factor_ = 0.75;
};

#endif
