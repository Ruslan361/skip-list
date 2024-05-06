#include <iostream>
#include <limits>
#include <cstdlib> // Для использования rand()

using namespace std;

// Node structure for Skip List
template <typename T>
struct Node {
    T key;
    Node** forward;

    Node(const T& key, int level) : key(key) {
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }

    ~Node() {
        delete[] forward; // Освобождение памяти для массива forward
    }
};

template <typename T>
class SkipList {
private:
    int maxLevel;
    float p; // Probability for increasing level
    Node<T>* header;
    
    int randomLevel() {
        int lvl = 1;
        while (rand() % 100 < p * 100 && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList(int maxLevel = 16, float p = 0.5) : maxLevel(maxLevel), p(p) {
        header = new Node<T>(numeric_limits<T>::min(), maxLevel); 
    }

    ~SkipList() {
        Node<T>* current = header->forward[0]; // Начинаем с первого элемента, так как header не нужно удалять
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->forward[0];
            delete temp;
        }
        delete header; // Освобождаем память для header
    }

    // Insert a new node into the Skip List
    void insert(const T& key) {
        Node<T>* current = header;
        Node<T>* update[maxLevel + 1];
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        // If key already exists, do nothing
        if (current != nullptr && current->key == key) {
            return;
        }

        int level = randomLevel();
        if (level > maxLevel) {
            for (int i = maxLevel + 1; i <= level; i++) {
                update[i] = header;
            }
            maxLevel = level;
        }

        Node<T>* newNode = new Node<T>(key, level);
        for (int i = 0; i <= level; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    // Search for a key in the Skip List
    bool search(const T& key) {
        Node<T>* current = header;
        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return current != nullptr && current->key == key;
    }

    // Erase a node from the Skip List
    void erase(const T& key) {
        Node<T>* current = header;
        Node<T>* update[maxLevel + 1];

        for (int i = maxLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->key == key) {
            for (int i = 0; i <= maxLevel; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            // Check if the maximum level needs to be updated
            while (maxLevel > 0 && header->forward[maxLevel] == nullptr) {
                maxLevel--;
            }
        }
    }

    // Print the Skip List (for debugging)
    void print() {
        for (int i = maxLevel; i >= 0; i--) {
            Node<T>* current = header->forward[i];
            cout << "Level " << i << ": ";
            while (current != nullptr) {
                cout << current->key << " ";
                current = current->forward[i];
            }
            cout << endl;
        }
    }

    size_t size() const {
        size_t count = 0;
        Node<T>* current = header->forward[0];
        while (current != nullptr) {
            count++;
            current = current->forward[0];
        }
        return count;
    }

    bool empty() const {
        return size() == 0;
    }
};


