#pragma once
#include <iostream>
#include <algorithm>

template <typename KeyType, typename ValueType>
class AVLTree {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* left;
        Node* right;
        int height;

        Node(KeyType k, ValueType v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    size_t size = 0;

    int height(Node* node) const { // высота дерева в данной ноде
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const { // проверка баланса дерева между соседними нодами
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) { // после вставки или удаления обновляем высоту, затем балансировка
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        if (!node) return nullptr;

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bf < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* insert(Node* node, KeyType key, ValueType value, bool replace) {
        if (!node) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value, replace);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value, replace);
        }
        else {
            // Ключ уже существует
            if (replace) {
                node->value = value;
            }
            else {
                std::cerr << "Ошибка: повтор ключа: " << key << ", его значение: " << value << "\n";
            }
            return node; // Возвращаем неизмененный узел
        }

        return balance(node);
    }

    Node* findMin(Node* node) const {
        return node->left ? findMin(node->left) : node;
    }

    Node* remove(Node* node, KeyType key, ValueType*& removedValue) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key, removedValue);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key, removedValue);
        }
        else {
            // Сохраняем значение перед удалением
            removedValue = &node->value;

            // Узел с одним или без детей
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    delete node;
                    return nullptr;
                }
                else {
                    *node = *temp; // Копируем содержимое
                    delete temp;
                }
            }
            else {
                // Узел с двумя детьми
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key, removedValue);
            }
        }

        return balance(node);
    }

    const Node* search(const Node* node, KeyType key) const {
        if (!node) return nullptr;
        if (node->key == key) {
            return node;
        }
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void print_all(Node* node) {
        if (node) {
            std::cout << "Ключ: " << node->key << " Значение: " << node->value << std::endl;
            print_all(node->left);
            print_all(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    size_t& return_size() { return size; }

    void print_all() {
        print_all(root);
    }

    ValueType* remove(KeyType key) {
        ValueType* removedValue = nullptr;
        root = remove(root, key, removedValue);
        if (!search(key)) size--;
        return removedValue;
    }

    ValueType* search(KeyType key) {
        Node* node = const_cast<Node*>(search(root, key));
        return node ? &node->value : nullptr;
    }

    ValueType* insert(KeyType key, ValueType value, bool replace = true) {
        root = insert(root, key, value, replace);
        if (search(key)) size++;
        return search(key);
    }

    const ValueType* search(KeyType key) const {
        const Node* node = search(root, key);
        return node ? &node->value : nullptr;
    }

    bool contains(KeyType key) const {
        return search(root, key) != nullptr;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }


};