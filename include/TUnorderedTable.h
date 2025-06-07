#include <iostream>
#include <vector> 


template <typename TKey, typename TValue>
class TUnorderedTable {
private:
    std::string name_of_first_column;
    std::string name_of_second_column;
    unsigned del = 0;
    size_t size = 0;  
public:   
    TUnorderedTable(std::string k, std::string r) { name_of_first_column = k; name_of_second_column = r; }
    std::pair<TValue, bool> value;
    std::vector<std::pair<TKey, std::pair<TValue, bool>>> vec;
    std::vector<TKey> end;
    TKey del_value[10];
    class Record {
    private:
        TKey Keys;
        bool with_repeat_replacement;
        TValue Values;      
    public:
        std::pair<TValue, bool>* return_value() {
            return &value;
        }

        std::vector<std::pair<TKey, std::pair<TValue, bool>>>* return_vec() {
            return &vec;
        }

        Record(TKey Key, TValue Value, bool with_repeat_replacementt, std::pair<TValue, bool>& value, std::vector<std::pair<TKey, std::pair<TValue, bool>>>& vec, std::vector<TKey>& end, TKey(&del_value)[10]) {
            Keys = Key; 
            Values = Value;
            with_repeat_replacement = with_repeat_replacementt;
            //vec.push_back({Keys, {Values, with_repeat_replacement}});
            insert_record(Keys, Values, with_repeat_replacement, value, vec, end, del_value);
        }   

        bool insert_record(TKey Keys, TValue Values, bool with_repeat_replacement, std::pair<TValue, bool>& value, std::vector<std::pair<TKey, std::pair<TValue, bool>>>& vec, std::vector<TKey>& end, TKey(&del_value)[10]) {
            for (int i = 0; i < vec.size(); i++) { // если на вход поступает значение с уже существующим ключом то относительно предпочтения заменяем значение по этому ключу или нет
                if (vec[i].first == Keys) { // находим одинаковые ключи
                    if (with_repeat_replacement == true) {// если замена возможна будем заменять и искать где находится значение
                        for (int k = 0; k < (sizeof(del_value) / sizeof(del_value[0])); k++) {
                            if (del_value[k] == Keys) {
                                vec[i].second.second = true; // возврашаем значение из удаленных
                                del_value[k] = -9999;// ставим особый знак того что данное значение уже не должнно передаваться в end
                                return true;
                            }
                        }
                        auto it = std::find(end.begin(), end.end(), Keys);
                        if (it != end.end()) {
                            vec[i].second.second = true; // возврашаем значение из удаленных
                            end.erase(it); // удаляем из вектора чтобы на данный адрес не могли перезаписать другое значение
                            return true;
                        }
                        vec[i].second.first = Values; // если значения не было ни в del_value ни в end то мы просто заменяем значение и возможномть перезаписи актуальными
                        vec[i].second.second = with_repeat_replacement;
                        return true;
                    }
                    if (with_repeat_replacement == false) { //замена невозможна, будем выводить ошибку о нахождении уже такого ключа
                        std::cerr << "Ошибка: повтор ключа: " << Keys << ", его значение: " << Values <<  "\n" << std::endl;
                        return false;
                    } 
                }
            }
            if (end.size() != 0) {
                for (int i = 0; i < vec.size(); i++) {
                    if (vec[i].first == end[end.size() - 1]) {
                        vec[i].first = Keys;
                        vec[i].second.first = Values;
                        vec[i].second.second = with_repeat_replacement;
                        end.pop_back();
                        return true;
                    }
                }
            }
            else { vec.push_back({ Keys, {Values, with_repeat_replacement} }); return true; }
        }
    };

    bool create_record(TKey Keys, TValue Values, bool with_repeat_replacementt) {
        Record* m = new Record(Keys, Values, with_repeat_replacementt, value, vec, end, del_value);
        size++;
        if (search_of_value(Keys) == nullptr) return false;
        else return true;
    }

    TValue* search_of_value(TKey Keys) {
        for (int i = 0; i < vec.size(); i++) {
            if ((vec[i].first == Keys) && (vec[i].second.second == true)) {
                return &vec[i].second.first;
            }
        }
        return nullptr;
    }

    TKey* delete_value(TKey Keys) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].first == Keys) {
                vec[i].second.second = false;
                if ((del > 9) && (del_value[del % 10] != -9999)) {
                    end.push_back(del_value[del % 10]);
                }
                del_value[del % 10] = Keys;
                del++;
                size--;
                return &vec[i].first;
            }
        }
        return nullptr;
    }
};