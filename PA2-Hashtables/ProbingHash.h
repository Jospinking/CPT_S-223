#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> {
private:
    vector< pair<K,V> > hashtable;
    vector<EntryState> statevec;
    int m_size{0};
    int m_bucket_count;
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion

public:
    ProbingHash(int n = 11) {
        m_bucket_count = findNextPrime(n);
        hashtable.resize(m_bucket_count);
        statevec.resize(m_bucket_count);
        for(int i = 0; i < m_bucket_count; i++ ){
            statevec[i] = EMPTY;
        }
    }

    ~ProbingHash() {
        this->clear();
        // Needs to actually free all table contents
    }

    bool empty() {
        return m_size == 0;
    }

    int size() {
        return m_size;
    }

    V& at(const K& key) {
        int index = hash(key);
        if(statevec[index] == VALID)
            return hashtable[index].second;

        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) {
        return this->at(key);
    }

    int count(const K& key) {
        int index = hash(key);
        if(statevec[index] == VALID)
            return 1;

        return 0;
    }

    void emplace(K key, V value) {
        while(load_factor() >= 1.0){
            rehash();
        }
        this->insert(std::make_pair(key,value));
    }

    void insert(const std::pair<K, V>& pair) {
        int key = pair.first;
        int index = hash(key);
        while(statevec[index] == VALID){
            if(hashtable[index].first == key){
                hashtable[index] = pair;
                return;
            }
            index = (index + 1) % m_bucket_count;
        }
        hashtable[index] = pair;
        statevec[index] = VALID;
        m_size++;
    }

    void erase(const K& key) {
        if(this->empty()) return;
        int index = hash(key);
        if(statevec[index] == VALID && hashtable[index].first == key){
            statevec[index] = DELETED;
            m_size--;
            return;
        }
        throw std::out_of_range("Key not in hash");
    }

    void clear() {
        hashtable.clear();
        statevec.clear();
        m_size = 0;
        m_bucket_count = 0;
    }

    int bucket_count() {
        return m_bucket_count;
    }

    int bucket_size(int n) {
        if(n>=m_bucket_count){
            throw std::out_of_range("Input Bucket count out of range");
        }
        if(statevec[n] == VALID)
            return 1;
        else
            return 0;

    }

    int bucket(const K& key) {
        int index = hash(key);
        if(count(key) < 1){
            throw std::out_of_range("Key not in hash");
        }
        else
            return index;
    }

    float load_factor() {
        float f = (float)m_size;
        f = f/(float)m_bucket_count;
        return f;
    }

    void rehash() {
        rehash(m_bucket_count + 1);
    }

    void rehash(int n) {
        auto temp = hashtable;
        auto temp_state = statevec;
        clear();
        m_bucket_count = findNextPrime(n);
        hashtable.resize(m_bucket_count);
        statevec.resize(m_bucket_count);
        for(int i = 0; i < m_bucket_count; i++ ){
            statevec[i] = EMPTY;
        }
        for(uint i = 0; i < temp.size(); i++){
            if(temp_state[i] == VALID){
                auto entry = temp[i];
                this->insert(entry);
            }

        }
        temp.clear();
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return key % m_bucket_count;
               // This technicall works, but is very very bad
    }

};

#endif //__PROBING_HASH_H
