#pragma once

//1. Каждая вершина является либо красной, либо черной и имеет двух потомков
//2. Корень дерева является черным
//3. Каждый лист не содержит данные и является черным
//4. У каждой вершины оба потомка черные
//5. Любой путь до потомков-листьев от любой вершины содержит одинаковое число черных вершин

#include <iostream>
#include <string>
#include <vector>
template <typename KeyType, typename ValueType>
class RedBlackTree {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* left;
        Node* right;
        Node* predok;
        std::string color;

        Node(KeyType k, ValueType v, std::string y) : key(k), value(v), left(nullptr), right(nullptr), predok(nullptr), color(y) {}

        void operator =(Node* r) {
            this->height = r->height;
            this->key = r->key;
            this->value = r->value;
        }
    };

    std::vector <Node*> storage_of_values;
    Node* root = nullptr;
    size_t size = 0;

    bool Red_love_Black(Node* Node) { //проверка оба ли потомка у красной вершины черные 
        return ((Node->left->color == "B") || (Node->right->color == "B")) ? true : false;
    }

    bool root_is_black() { return (root->color == "B") ? true : false; }

    void swap_Node(Node* node1, Node* node2) {
        Node* t = new Node(node1->key, node1->value, node1->color);
        t = node1;
        node1 = node2;
        node2 = t;
    }

    bool checkRedProperty(Node* node) const {
        if (!node) return true;

        if (node->color == "R") {
            if (node->left && node->left->color != "B") return false;
            if (node->right && node->right->color != "B") return false;
        }

        return checkRedProperty(node->left) && checkRedProperty(node->right);
    }

    bool checkBlackCount(Node* node, int currentCount, int& pathBlackCount) const {
        if (!node) {
            // Достигли листа (NIL узла)
            if (pathBlackCount == -1) {
                pathBlackCount = currentCount;
            }
            else if (currentCount != pathBlackCount) {
                return false;
            }
            return true;
        }

        if (node->color == "B") {
            currentCount++;
        }

        return checkBlackCount(node->left, currentCount, pathBlackCount) &&
            checkBlackCount(node->right, currentCount, pathBlackCount);
    }

    Node* restore_properties(Node* node) {

        if (!node || node == root || !node->predok) {
            return node;
        }

        if (node->predok == root) {
            return node->predok;
        }
        
        if (node->predok->color == "R") { // первая ситуация, когда вставка красного элемента под красным 

            if (node->predok->predok->left && node->predok->predok->right) {
                if ((node == node->predok->left) && (node->predok->predok->right->color == "R") && (node->predok->predok->left == node->predok)) {// нарушение исправляем перекраской предка и брата предка
                    node->predok->color = "B";
                    node->predok->predok->color = "R";
                    node->predok->predok->right->color = "B";
                    return node->predok;
                }
                if ((node == node->predok->left) && (node->predok->predok->left->color == "R") && (node->predok->predok->right == node->predok)) {// нарушение исправляем перекраской предка и брата предка
                    node->predok->color = "B";
                    node->predok->predok->color = "R";
                    node->predok->predok->left->color = "B";
                    return node->predok;
                }
                if ((node == node->predok->right) && (node->predok->predok->left->color == "R") && (node->predok->predok->right == node->predok)) {
                    node->predok->color = "B";
                    node->predok->predok->color = "R";
                    node->predok->predok->left->color = "B";
                    return node->predok;
                }
                if ((node == node->predok->right) && (node->predok->predok->right->color == "R") && (node->predok->predok->left == node->predok)) {
                    node->predok->color = "B";
                    node->predok->predok->color = "R";
                    node->predok->predok->right->color = "B";
                    return node->predok;
                }
            }

            if ((!node->predok->predok->right) || (!node->predok->predok->left) || (node->predok->predok->right->color == "B") || (node->predok->predok->left->color == "B")) {
                // заходим сюда если дядя черный или дяди вообще нет
                if (((!node->predok->predok->right) || (node->predok->predok->right->color == "B")) && (node == node->predok->right)) { // вторая ситуация, похожа на первую, но брат предка теперь черный
                    swap_Node(node, node->predok);
                    Node* t = node->predok->left;
                    node->predok->left = node;
                    node->predok->right = t;
                    node->predok->color = "B";
                    node->predok->predok->color = "R";
                    return node->predok;
                }
                if (((!node->predok->predok->left) || (node->predok->predok->left->color == "B")) && (node == node->predok->left)) {
                    swap_Node(node, node->predok);
                    Node* t = node->predok->right;
                    node->predok->right = node;
                    node->predok->left = t;
                    node->predok->color = "B";
                    node->predok->predok->color = "R";
                    return node->predok;
                }

                if (((!node->predok->predok->right) || (node->predok->predok->right->color == "B")) && (node == node->predok->left)) {
                    Node* t = node->predok->right; // запоминаем T1
                    Node* r = node->predok->predok->predok; // запоминаем предка G
                    node->predok->predok->color = "R";
                    node->predok->right = node->predok->predok;
                    if (r) {
                        if (r->left == node->predok->predok) { r->left = node->predok; }
                        if (r->right == node->predok->predok) { r->right = node->predok; }
                    }
                    node->predok->predok = r;
                    node->predok->right->left = t;
                    node->predok->right->predok = node->predok;
                    node->predok->color = "B";
                    node->predok->right->color = "R";
                    return node->predok;
                }

                if ((((!node->predok->predok->left) || node->predok->predok->left->color == "B")) && (node == node->predok->right)) {
                    Node* t = node->predok->left; // запоминаем T1
                    Node* r = node->predok->predok->predok; // запоминаем предка G
                    node->predok->predok->color = "R";
                    node->predok->left = node->predok->predok;
                    if (r) {
                        if (r->left == node->predok->predok) { r->left = node->predok; }
                        if (r->right == node->predok->predok) { r->right = node->predok; }
                    }
                    node->predok->predok = r;
                    node->predok->left->right = t;
                    node->predok->left->predok = node->predok;
                    node->predok->color = "B";
                    node->predok->left->color = "R";
                    return node->predok;
                }
            }
        }
        return node->predok;
    }

    Node* search(Node* node, KeyType key) const { //наша закрытая private функция чтобы пользователь вводил только ключ интересуемый а мы уже сами подставим корневую ноду - root
        if (!node || node->key == key) {
            return node;
        }

        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    Node* insert(Node* node, KeyType key, ValueType value, bool r) {
        Node* h = nullptr;
        Node* k = nullptr;
        bool kr = false;
        if (!node) {
            Node* k = new Node(key, value, "R");
            k->left = nullptr;
            k->right = nullptr;
            return k;
        }

        if (key < node->key) {
                if (node->left) k = node->left->right;
                node->left = insert(node->left, key, value, r);
                h = node->left->predok;
                node->left->predok = node; // устанавливаем связь с предком при вставке
        }
        else if (key > node->key) {
                if (node->right) k = node->right->left;
                node->right = insert(node->right, key, value, r);
                h = node->right->predok;
                node->right->predok = node; // устанавливаем связь с предком при вставке
        }
        else {
            // Ключ уже существует, обновляем значение
            if (r) {
                node->value = value;
                return node;
            }
            else {
                std::cerr << "Ошибка: повтор ключа: " << key << ", его значение: " << value << "\n" << std::endl;
                return node;
            }
        }
        if (!node) {
            return nullptr;
        }

        Node* j = search(root, key);

        if (node->right) {
            if (node->predok == node->right) {
                node->right->predok = h;
                node->right = k;
                k = nullptr;
                h = nullptr;
                kr = true; //если поворот был
            }
        }
        if (node->left) {
            if (node->predok == node->left) {
                node->left->predok = h;
                node->left = k;
                k = nullptr;
                h = nullptr;
                kr = true; //если поворот был
            }
        }

        if (j->predok->color == "B") {
            if (node->predok) {
                if (node->color == "R" && node->predok->color == "R") {
                    restore_properties(node);
                    return node;
                }
            }
            if (j->predok->left && j->predok->left != j) {
                if (!kr /*j->predok->left != root*/) return node;
            }
            if (j->predok->right && j->predok->right != j) {
                if (!kr /*j->predok->right != root*/) return node;
            }
            if (!j->predok->right || !j->predok->left) {
                return node;
            }
            if (j->predok == root) 
                return node;
        }
        return restore_properties(j);
    }

    void leftRotate(Node* x) {
        if (!x || !x->right) return;
        Node* y = x->right;
        x->right = y->left;
        if (y->left) {
            y->left->predok = x;
        }
        y->predok = x->predok;
        if (!x->predok) {
            //root = y;  // Assuming you have a root member in your class
        }
        else if (x == x->predok->left) {
            x->predok->left = y;
        }
        else {
            x->predok->right = y;
        }
        y->left = x;
        x->predok = y;
    }

    void rightRotate(Node* y) {
        if (!y || !y->left) return;
        Node* x = y->left;
        y->left = x->right;
        if (x->right) {
            x->right->predok = y;
        }
        x->predok = y->predok;
        if (!y->predok) {
            //root = x; // Assuming you have a root member in your class
        }
        else if (y == y->predok->right) {
            y->predok->right = x;
        }
        else {
            y->predok->left = x;
        }
        x->right = y;
        y->predok = x;
    }

    void remove(Node* root, KeyType key) {
        Node* z = search(root, key);
        if (!z) return; // Узел не найден

        Node* y = z;
        Node* x = nullptr;
        std::string y_original_color = y->color;

        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->predok == z) {
                if (x) x->predok = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right) y->right->predok = y;
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left) y->left->predok = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == "B") {
            deleteFixup(x);
        }
    }

    Node* minimum(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void transplant(Node* u, Node* v) {
        if (!u->predok) {
            root = v;
        }
        else if (u == u->predok->left) {
            u->predok->left = v;
        }
        else {
            u->predok->right = v;
        }
        if (v) {
            v->predok = u->predok;
        }
    }

    void deleteFixup(Node* x) {
        while (x != root && (!x || x->color == "B")) {
            if (x == x->predok->left) {
                Node* w = x->predok->right;
                if (w && w->color == "R") {
                    w->color = "B";
                    x->predok->color = "R";
                    leftRotate(x->predok);
                    w = x->predok->right;
                }
                if ((!w->left || w->left->color == "B") &&
                    (!w->right || w->right->color == "B")) {
                    w->color = "R";
                    x = x->predok;
                }
                else {
                    if (!w->right || w->right->color == "B") {
                        if (w->left) w->left->color = "B";
                        w->color = "R";
                        rightRotate(w);
                        w = x->predok->right;
                    }
                    w->color = x->predok->color;
                    x->predok->color = "B";
                    if (w->right) w->right->color = "B";
                    leftRotate(x->predok);
                    x = root;
                }
            }
            else {
                // Симметричный случай
                Node* w = x->predok->left;
                if (w && w->color == "R") {
                    w->color = "B";
                    x->predok->color = "R";
                    rightRotate(x->predok);
                    w = x->predok->left;
                }
                if ((!w->right || w->right->color == "B") &&
                    (!w->left || w->left->color == "B")) {
                    w->color = "R";
                    x = x->predok;
                }
                else {
                    if (!w->left || w->left->color == "B") {
                        if (w->right) w->right->color = "B";
                        w->color = "R";
                        leftRotate(w);
                        w = x->predok->left;
                    }
                    w->color = x->predok->color;
                    x->predok->color = "B";
                    if (w->left) w->left->color = "B";
                    rightRotate(x->predok);
                    x = root;
                }
            }
        }
        if (x) x->color = "B";
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

    RedBlackTree() {}

    ~RedBlackTree() { clear(root); }

    size_t& return_size() { return size; }

    void print_all() {
        print_all(root);
    }

    Node* search(KeyType key) const {
        Node* node = search(root, key);
        return node ? node : nullptr;
    }

    Node* insert(KeyType key, ValueType value, bool r) {
        if (!root) {
            root = new Node(key, value, "B");  // Корень всегда чёрный
            size++;
            return root;
        }
        root = insert(root, key, value, r);
        root->color = "B"; // корень всегда черный
        if (search(key)) size++;
        return search(key);
    }

    Node* remove(KeyType key) {
        Node* nodeToRemove = search(key);
        if (!nodeToRemove) return nullptr;
        remove(root, key);
        if(!search(key)) size--;
        return search(key);
    }

    bool contains(KeyType key) const {
        return search(root, key) != nullptr;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool isRedBlackTreeValid() const {

        if (!root) return true;

        // Проверка что корень черный
        if (root->color != "B") {
            std::cerr << "Violation: Root is not black" << std::endl;
            return false;
        }

        // Проверка что у красных узлов только черные потомки
        if (!checkRedProperty(root)) {
            std::cerr << "Violation: Red node has red child" << std::endl;
            return false;
        }

        // Проверка одинакового количества черных узлов на всех путях
        int blackCount = -1;
        if (!checkBlackCount(root, 0, blackCount)) {
            std::cerr << "Violation: Black height differs" << std::endl;
            return false;
        }

        return true;
    }

};