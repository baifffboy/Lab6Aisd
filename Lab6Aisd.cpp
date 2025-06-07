//#include <iostream>
//#include "TUnorderedTable.h"
//#include "Unordered_Table_on_forward_list.h"
//#include "Ordered_Table.h"
//#include "Hash_Table.h"
//#include "AVLTree.h"
//#include "RedBlackTree.h"
//
//int main()
//{
//    setlocale(LC_ALL, "Russian");
//
//    //TUnorderedTableTest
//    std::cout << "TUnorderedTableTest" << std::endl;
//    TUnorderedTable<int, std::string> table("Порядковый номер", "Строка");
//    table.create_record(1, "first",1);
//    table.create_record(2, "fdvs", 1);
//    table.create_record(2, "sdvs", 0);
//    table.create_record(4, "sdv", 1);
//
//    int* m = table.delete_value(3); // Ключ найден
//    if (m != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    int* k = table.delete_value(10); // Ключ не найден
//    if (k != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    std::string* r = table.search_of_value(3); // Значение не найдено
//    if (r != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::string* l = table.search_of_value(4); // Значение найдено
//    if (l != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::cout << "-------------------------------------------------------" << std::endl;
//
//    std::cout << "UnorderedTableonforwardlistTest" << std::endl;
//    //UnorderedTableonforwardlistTest
//    Unordered_Table_on_forward_list<int, std::string> table2("Порядковый номер", "Строка");
//    table2.create_last_node(1, "first", 1, false);
//    table2.create_last_node(2, "hjdbcjds", 1, false);
//    table2.create_last_node(3, "sbc", 1, false);
//    table2.create_last_node(4, "asmcnm mna", 1, false);
//
//    int* mm = table2.delete_value(3); // Ключ найден
//    if (mm != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    int* km = table2.delete_value(10); // Ключ не найден
//    if (km != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    std::string* rm = table2.search_of_value(3); // Значение не найдено
//    if (rm != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::string* lm = table2.search_of_value(4); // Значение найдено
//    if (lm != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::cout << "-------------------------------------------------------" << std::endl;
//
//    //OrderedTableTest
//    std::cout << "OrderedTableTest" << std::endl;
//    Ordered_Table<int, std::string> table3("Порядковый номер", "Строка");
//    table3.create_last_node(4, "first", 1, false);
//    table3.create_last_node(1, "hjdbcjds", 1, false);
//    //table3.print();
//    table3.create_last_node(3, "sbc", 1, false);
//    table3.print();
//    table3.create_last_node(2, "asmcnm mna", 1, false);
//    table3.print();
//
//    int* mmm = table2.delete_value(3); // Ключ найден
//    if (mmm != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    int* kmm = table2.delete_value(10); // Ключ не найден
//    if (kmm != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    std::string* rmm = table2.search_of_value(3); // Значение не найдено
//    if (rmm != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::string* lmm = table2.search_of_value(4); // Значение найдено
//    if (lmm != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::cout << "-------------------------------------------------------" << std::endl;
//
//    //HashTableTest
//    std::cout << "HashTableTest" << std::endl;
//    Hash_Table<std::string> table4("Порядковый номер", "Строка", 1, 5000);
//    table4.create_record("first");
//    table4.create_record("hjdbcjds");
//    //table3.print();
//    table4.create_record("sbc");
//    //table4.print();
//    table4.create_record("asmcnm mna");
//    //table4.print();
//
//    std::string* mmmn = table4.delete_value("first"); // Ключ найден
//    if (mmmn != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    std::string* kmmn = table4.delete_value("cdmnvhdjcnlks"); // Ключ не найден
//    if (kmmn != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    std::string* rmmn = table4.search_of_value("first"); // Значение не найдено
//    if (rmmn != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::string* lmmn = table4.search_of_value("sbc"); // Значение найдено
//    if (lmmn != nullptr) { std::cout << "Значение найдено" << std::endl; }
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::cout << "-------------------------------------------------------" << std::endl;
//
//    //AVLTreeTest
//    std::cout << "AVLTreeTest" << std::endl;
//    AVLTree<int, std::string> tr;
//    tr.insert(10, "10", 1);
//    tr.insert(20, "20", 1);
//    tr.insert(30, "30", 1);
//    tr.insert(15, "15", 1);
//    tr.insert(20, "20", 0);
//    tr.insert(5, "5", 1);
//    tr.insert(17, "17", 1);
//
//    std::string* value = tr.search(20); // Ключ найден
//    if (value != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    std::string* value1 = tr.search(2111110); //Ключ не найден
//    if (value1 != nullptr) { std::cout << "Ключ найден" << std::endl; }
//    else { std::cout << "Ключ не найден" << std::endl; }
//
//    if (tr.remove(20) != nullptr) { std::cout << "Значение найдено" << std::endl; } // Значение найдено
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    if (tr.remove(150000) != nullptr) { std::cout << "Значение найдено" << std::endl; } // Значение не найдено
//    else { std::cout << "Значение не найдено" << std::endl; }
//
//    std::cout << "-------------------------------------------------------" << std::endl;
//
//    //RedBlackTreeTest
//
//    std::cout << "RedBlackTreeTest" << std::endl;
//    RedBlackTree<int, std::string> tr1;
//    tr1.insert(10, "10", 1);
//    tr1.insert(20, "20", 1);
//    tr1.insert(30, "30", 1);
//    tr1.insert(15, "15", 1);
//    tr1.insert(20, "2034", 0);
//    tr1.insert(5, "5", 1);
//    tr1.insert(17, "17", 1);
//    tr1.insert(45, "45", 1);
//    tr1.insert(6, "6", 1);
//    tr1.insert(12, "12", 1);
//    tr1.insert(28, "28", 1);
//    tr1.insert(4, "4", 1);
//    tr1.insert(1, "1", 1);
//    tr1.insert(7, "7", 1);
//    tr1.insert(8, "8", 1);
//    tr1.insert(13, "13", 1);
//    
//    std::string value3 = tr1.search(20) ? tr1.search(20)->value : "Ключ не найден"; // Ключ найден
//    std::cout << value3 << std::endl;
//
//    std::string value31 = tr1.search(203254)? tr1.search(203254)->value : "Ключ не найден"; // Ключ не найден
//    std::cout << value31 << std::endl;
//
//    tr1.remove(20);
//    tr1.remove(5);
//    std::cout << "-------------------------------------------------------" << std::endl;
//}
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "TUnorderedTable.h"
#include "Unordered_Table_on_forward_list.h"
#include "Ordered_Table.h"
#include "Hash_Table.h"
#include "AVLTree.h"
#include "RedBlackTree.h"

using namespace std;

// Функция для разделения строки на токены
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    for (char ch : s) {
        if (ch == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

// Функция для вывода всех структур
void printAllStructures(
    TUnorderedTable<int, string>& ut,
    Unordered_Table_on_forward_list<int, string>& utf,
    Ordered_Table<int, string>& ot,
    Hash_Table<string>& ht,
    AVLTree<int, string>& avl,
    RedBlackTree<int, string>& rbt) {

    cout << "\n=== TUnorderedTable ===" << endl;
    for (const auto& pair : ut.vec) {
        if (pair.second.second) {
            cout << "Ключ: " << pair.first << " Значение: " << pair.second.first << endl;
        }
    }

    cout << "\n=== Unordered_Table_on_forward_list ===" << endl;
    auto it = utf.begin();
    for (int i = 0; i < utf.return_size(); ++i) {
        if (!it->return_is_delete()) {
            cout << "Ключ: " << it->return_Keys() << " Значение: " << *it->return_Values() << endl;
        }
        it = it->ptr;
    }

    cout << "\n=== Ordered_Table ===" << endl;
    auto it2 = ot.begin();
    for (int i = 0; i < ot.return_size(); ++i) {
        if (!it2->return_is_delete()) {
            cout << "Ключ: " << it2->return_Keys() << " Значение: " << *it2->return_Values() << endl;
        }
        it2 = it2->ptr;
    }

    cout << "\n=== Hash_Table ===" << endl;
    ht.print_all();

    cout << "\n=== AVLTree ===" << endl;
    if (avl.return_size() > 0) avl.print_all();

    cout << "\n=== RedBlackTree ===" << endl;
    if (rbt.return_size() > 0) rbt.print_all();
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем по одному экземпляру каждой структуры
    TUnorderedTable<int, string> ut("Ключ", "Значение");
    Unordered_Table_on_forward_list<int, string> utf("Ключ", "Значение");
    Ordered_Table<int, string> ot("Ключ", "Значение");
    Hash_Table<string> ht("Ключ", "Значение", 1, 10);
    AVLTree<int, string> avl;
    RedBlackTree<int, string> rbt; // Начальный элемент

    cout << "Введите значение в формате: \"структура_операция_ключ\" (или \"exit\" для выхода)" << endl;
    cout << "Доступные структуры: ut, utf, ot, ht, avl, rbt" << endl;
    cout << "Операции: i (вставка), d (удаление), s (поиск)" << endl;
    cout << "Для вставки добавьте четвертый параметр: 1 (разрешить замену) или 0 (запретить замену)" << endl;

    string input;
    while (true) {
        cout << "\n> ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        vector<string> tokens = split(input, ' ');
        if (tokens.size() < 3) {
            cout << "Неверный формат ввода. Попробуйте снова." << endl;
            continue;
        }

        string structure = tokens[0];
        string operation = tokens[1];
        int key;
        std::string zamena = "";
        try {
            key = stoi(tokens[2]);
        }
        catch (...) {
            if (structure == "ht") { zamena = tokens[2]; }
            else { cout << "Неверный формат ключа. Используйте целые числа." << endl; continue;}     
        }

        bool replace = true;
        if (operation == "i" && tokens.size() >= 4) {
            replace = tokens[3] == "1";
        }
        string value;
        if (operation == "i") {
            
            cout << "Введите значение для вставки: ";
            getline(cin, value);

            if (structure == "ut") {
                bool success = ut.create_record(key, value, replace);
                if (!success) {
                    cout << "Вставка не выполнена: ключ уже существует и замена запрещена." << endl;
                }
            }
            else if (structure == "utf") {
                bool success = utf.create_last_node(key, value, replace, false);
                if (!success) {
                    cout << "Вставка не выполнена: ключ уже существует и замена запрещена." << endl;
                }
            }
            else if (structure == "ot") {
                bool success = ot.create_last_node(key, value, replace, false);
                if (!success) {
                    cout << "Вставка не выполнена: ключ уже существует и замена запрещена." << endl;
                }
            }
            else if (structure == "ht") {
                size_t y = ht.return_size();
                if (zamena == "") {
                    std::string h = std::to_string(key);
                    ht.create_record(h);
                }
                if (zamena != "") {
                    ht.create_record(zamena);
                    zamena = "";
                }
                if (y+1 != ht.return_size()) {
                    cout << "Вставка не выполнена: ключ уже существует и замена запрещена." << endl;
                }
                // Для Hash_Table ключ должен быть строкой
                cout << "Hash_Table требует строковые ключи. Операция пропущена." << endl;
            }
            else if (structure == "avl") {
                if(!avl.insert(key, value, replace)) cout << "Вставка не выполнена: ключ уже существует и замена запрещена." << endl;
            }
            else if (structure == "rbt") {
                if (!rbt.insert(key, value, replace)) cout << "Вставка не выполнена: ключ уже существует и замена запрещена." << endl;
            }
            else {
                cout << "Неизвестная структура: " << structure << endl;
            }

            // Выводим все структуры после вставки
            printAllStructures(ut, utf, ot, ht, avl, rbt);

        }
        else if (operation == "d") {
            if (structure == "ut") {
                int* result = ut.delete_value(key);
                if (result == nullptr) {
                    cout << "Ключ не найден." << endl;
                }
            }
            else if (structure == "utf") {
                int* result = utf.delete_value(key);
                if (result == nullptr) {
                    cout << "Ключ не найден." << endl;
                }
            }
            else if (structure == "ot") {
                int* result = ot.delete_value(key);
                if (result == nullptr) {
                    cout << "Ключ не найден." << endl;
                }
            }
            else if (structure == "ht") {
                bool k;
                if (zamena == "") {
                    std::string h = std::to_string(key);
                    k = ht.delete_value(h);
                }
                if (zamena != "") {
                    k = ht.delete_value(zamena);
                    zamena = "";
                }                
                if (k == false) {
                    cout << "Ключ не найден." << endl;
                }
            }
            else if (structure == "avl") {
                string* result = avl.remove(key);
                if (result == nullptr) {
                    cout << "Ключ не найден." << endl;
                }
            }
            else if (structure == "rbt") {
                if (!rbt.remove(key)) {
                    cout << "Ключ не найден." << endl;
                }
            }
            else {
                cout << "Неизвестная структура: " << structure << endl;
            }

            // Выводим все структуры после удаления
            printAllStructures(ut, utf, ot, ht, avl, rbt);

        }
        else if (operation == "s") {
            if (structure == "ut") {
                string* result = ut.search_of_value(key);
                if (result == nullptr) {
                    cout << "Значение не найдено." << endl;
                }
                else {
                    cout << "Значение: " << *result << endl;
                }
            }
            else if (structure == "utf") {
                string* result = utf.search_of_value(key);
                if (result == nullptr) {
                    cout << "Значение не найдено." << endl;
                }
                else {
                    cout << "Значение: " << *result << endl;
                }
            }
            else if (structure == "ot") {
                string* result = ot.search_of_value(key);
                if (result == nullptr) {
                    cout << "Значение не найдено." << endl;
                }
                else {
                    cout << "Значение: " << *result << endl;
                }
            }
            else if (structure == "ht") {
                std::string* result = nullptr;
                if (zamena == "") {
                    std::string h = std::to_string(key);
                    result = ht.search_of_value(h);
                }
                if (zamena != "") {
                    result = ht.search_of_value(zamena);
                    zamena = "";
                }
                if (result == nullptr) {
                    cout << "Значение не найдено." << endl;
                }
                else {
                    cout << "Значение: " << *result << endl;
                }
            }
            else if (structure == "avl") {
                string* result = avl.search(key);
                if (result == nullptr) {
                    cout << "Значение не найдено." << endl;
                }
                else {
                    cout << "Значение: " << *result << endl;
                }
            }
            else if (structure == "rbt") {
                if (rbt.search(key) == nullptr) {
                    cout << "Значение не найдено." << endl;
                }
                else {
                    cout << "Значение: " << rbt.search(key)->value << endl;
                }
            }
            else {
                cout << "Неизвестная структура: " << structure << endl;
            }
        }
        else {
            cout << "Неизвестная операция: " << operation << endl;
        }
    }

    return 0;
}