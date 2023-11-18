#include <iostream>
#include <vector>
#include <cstring>
const int SIZE = 8;

using namespace std;

struct dict_word {

    char eng_word[100] = {};
    char rus_word[100] = {};

    dict_word() {}
    dict_word(char eng_word[100], char rus_word[100]) {
        strcpy_s(this->eng_word, eng_word);
        strcpy_s(this->rus_word, rus_word);
    }
    /*dict_word(string eng_word, string rus_word) {
        for (int i = 0; i < eng_word.size() && i < 100; i++) {
            this->eng_word[i] = eng_word[i];
        }
        for (int i = 0; i < rus_word.size() && i < 100; i++) {
            this->rus_word[i] = rus_word[i];
        }
    }*/
};



struct HashTable {
    int capacity;
    int size;
    dict_word** tableElements;

    HashTable(int capacity);
    ~HashTable();
    void print();
    //void insert(char eng_word[100], char rus_word[100]);
    //dict_word* search(char eng_word[100]);
    void deleteElement(char eng_word[100]);
    int hashFunction(char key[100]);
};

int HashTable::hashFunction(char key[100]) {
    int hash = 0;
    for (int i = 0; i < 100; i++) {
        hash = hash + key[i];
    }
    hash = hash % capacity;
    return hash;
}

HashTable::~HashTable() {
    delete[] tableElements;
}

HashTable::HashTable(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->tableElements = new dict_word*[capacity];
    for (int i = 0; i < capacity; i++) {
        tableElements[i] = nullptr;
    }
}

void HashTable::print() {
    for (int i = 0; i < this->capacity; i++) {
        if (tableElements[i] != nullptr) {
            cout << tableElements[i]->eng_word << " " << tableElements[i]->rus_word << endl;
        }
    }
}

void insert(HashTable*, char[100], char[100]);

void rehash(HashTable* hashTable) {

    HashTable* newTable = new HashTable(hashTable->capacity * 2);
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->tableElements[i] != nullptr) {
            insert(newTable, hashTable->tableElements[i]->eng_word, hashTable->tableElements[i]->rus_word);
        }
    }
    delete hashTable;
    *hashTable = *newTable;

}


void insert(HashTable* hashTable, char eng_word[100], char rus_word[100]) {
    if (hashTable->capacity == hashTable->size) {
        rehash(hashTable);
    }
    int index = hashTable->hashFunction(eng_word);
    while (hashTable->tableElements[index] != nullptr) {
        index = (index + 1) % hashTable->capacity;
    }
    hashTable->tableElements[index] = new dict_word(eng_word, rus_word);
    hashTable->size++;
}

dict_word* search(HashTable* hashTable, char eng_word[100]) {
    int index = hashTable->hashFunction(eng_word);

    for (int iterations = 0; iterations < hashTable->capacity; iterations++) {
        if (hashTable->tableElements[index] != nullptr && strcmp(hashTable->tableElements[index]->eng_word, eng_word) == 0) {
            return hashTable->tableElements[index];
        }
        index = (index + 1) % hashTable->capacity;
    }
    return nullptr;

}

void deleteElement(HashTable* hashTable, char eng_word[100]) {

    int index = hashTable->hashFunction(eng_word);

    for (int iterations = 0; iterations < hashTable->capacity; iterations++) {
        if (hashTable->tableElements[index] != nullptr && strcmp(hashTable->tableElements[index]->eng_word, eng_word) == 0) {
            delete hashTable->tableElements[index];
            hashTable->tableElements[index] = nullptr;
            hashTable->size--;
            return;
        }
        index = (index + 1) % hashTable->capacity;
    }
    
}








//class HashTable { //linear probing
//private:
//    vector<dict_word> table;
//    int capacity;
//    int size;
//public:
//    HashTable(int capasity);
//    int hash(char key[100]);
//    void insert(char key[100], char rus_word[100]);
//    dict_word search();
//};



