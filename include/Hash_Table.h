#pragma once
#include <iostream>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>

template <typename TValue>
class Hash_Table {
private:
    std::string name_of_first_column;
    std::string name_of_second_column;
    unsigned int formula;
    size_t capacity;
    size_t size;
    std::forward_list<TValue>* arr; // Array of forward_lists for chaining
    std::vector<size_t> hg; // Vector to store used hash keys

public:
    Hash_Table(std::string ke, std::string r, unsigned int t, size_t y)
        : name_of_first_column(ke), name_of_second_column(r), formula(t), capacity(y), size(0) {
        arr = new std::forward_list<TValue>[capacity];
    }

    ~Hash_Table() {
        delete[] arr;
    }

    size_t return_size() { return size; }

    class Record {
    private:
        TValue value;
    public:
        Record(TValue Value) : value(Value) {}

        size_t hash_string_djb2(const std::string& key, size_t table_size) const {
            unsigned long hash = 5381;
            for (char c : key) {
                hash = ((hash << 5) + hash) + c;
            }
            return hash % table_size;
        }

        size_t multiplicative_hash(int key, size_t table_size) const {
            const double A = 0.6180339887;
            double val = key * A;
            val -= static_cast<unsigned int>(val);
            return static_cast<unsigned int>(table_size * val);
        }

        size_t get_hash(unsigned int formula, size_t capacity) const {
            if (formula == 1) {
                return hash_string_djb2(value, capacity);
            }
            return multiplicative_hash(sizeof(value), capacity);
        }

        const TValue& get_value() const { return value; }
    };

    unsigned int return_formula() const {
        return formula;
    }

    size_t return_capacity() const {
        return capacity;
    }

    void create_record(TValue Values) {
        Record record(Values);
        size_t hash = record.get_hash(formula, capacity);

        // Check if this hash is new
        bool is_new_hash = std::find(hg.begin(), hg.end(), hash) == hg.end();

        // Add the value to the appropriate bucket
        arr[hash].push_front(Values);
        size++;

        // If this is a new hash, add it to hg
        if (is_new_hash) {
            hg.push_back(hash);
        }
    }

    TValue* search_of_value(TValue Values) {
        Record record(Values);
        size_t hash = record.get_hash(formula, capacity);

        // Check if the hash exists
        if (std::find(hg.begin(), hg.end(), hash) == hg.end()) {
            return nullptr;
        }

        // Search in the bucket
        for (auto& val : arr[hash]) {
            if (val == Values) {
                return &val;
            }
        }
        return nullptr;
    }

    bool delete_value(TValue Values) {
        Record record(Values);
        size_t hash = record.get_hash(formula, capacity);

        // Check if the hash exists
        if (std::find(hg.begin(), hg.end(), hash) == hg.end()) {
            return false;
        }

        auto& bucket = arr[hash];
        auto prev = bucket.before_begin();
        for (auto it = bucket.begin(); it != bucket.end(); ) {
            if (*it == Values) {
                it = bucket.erase_after(prev);
                size--;

                // If bucket is empty, remove the hash from hg
                if (bucket.empty()) {
                    auto hg_it = std::find(hg.begin(), hg.end(), hash);
                    if (hg_it != hg.end()) {
                        hg.erase(hg_it);
                    }
                }
                return true;
            }
            prev = it;
            ++it;
        }
        return false;
    }

    void print_all() const {
        for (size_t hash : hg) {
            std::cout << "Ключ: " << hash << " Значение: ";
            for (const auto& val : arr[hash]) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};