/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - inherits from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    vector< list< pair<K,V> > > hashtable;
    int m_size{0};
    int m_bucket_count;
public:
    ChainingHash(int n = 11) {
        m_bucket_count = findNextPrime(n);
        hashtable.resize(m_bucket_count);
    }

    ~ChainingHash() {
        this->clear();
    }



    bool empty() {
      return m_size == 0;
    }

    int size() {
        return m_size;
    }

    V& at(const K& key) {
        int index = hash(key);
        auto entry = hashtable[index];
        for(auto &val : entry){
            if(val.first == key)
                return val.second;
        }
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) {
        return this->at(key);
    }

    int count(const K& key) {
        int count = 0;
        int index = hash(key);
        auto entry = hashtable[index];
        for(auto & val : entry){
            if(val.first == key)
                return 1;
        }
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
        auto& entry = hashtable[index];
        if(count(key)){
            for(auto it = entry.begin(); it != entry.end(); it++){
                if(it->first == key){
                    *it = pair;
                    return;
                }
            }
        }
        else{
            entry.push_back(pair);
            m_size++;
        }
    }

    void erase(const K& key) {
        if(this->empty()) return;
        int index = hash(key);
        auto &entry = hashtable[index];
        bool flag = false;
        for(auto itr = entry.begin(); itr != entry.end(); itr++){
            if(itr->first == key){
                entry.erase(itr);
                m_size--;
                flag = true;
            }
        }
        if (!flag){
            throw std::out_of_range("Key not in hash");
        }
    }

    void clear() {
        hashtable.clear();
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
        auto entry = hashtable[n];
        return entry.size();
    }

    int bucket(const K& key) {
        int index = hash(key);
        auto entry = hashtable[index];
        for(auto &val : entry){
            if(val.first == key)
                return index;
        }
        throw std::out_of_range("Key not in hash");
    }

    float load_factor() {
        float f = (float)m_size;
        f = f/(float)m_bucket_count;
        return f;
    }

    void rehash() {
        // int new_bucket_size = findNextPrime(m_bucket_count + 1);
        rehash(m_bucket_count + 1);
    }

    void rehash(int n) {
        auto temp = hashtable;
        clear();
        m_bucket_count = findNextPrime(n);
        hashtable.resize(m_bucket_count);
        for(uint i = 0; i < temp.size(); i++){
            auto entry = temp[i];
            for(auto val : entry){
                this->insert(val);
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
        return 0;       // This technicall works, but is very very bad
    }

};

#endif //__CHAINING_HASH_H
