#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename TKey, typename TValue>
class Ordered_Table {
private:
	std::string name_of_first_column;
	std::string name_of_second_column;
	class node { //класс node
	public:
		node* ptr = nullptr; // указатель следующей ноды
		bool is_delete;
		TKey Keys;
		bool with_repeat_replacement;
		TValue Values;

		node(TKey Key, TValue Value, bool with_repeat_replacementt, bool is_delet) { // реализация конструктора node
			Keys = Key;
			Values = Value;
			with_repeat_replacement = with_repeat_replacementt;
			is_delete = is_delet;
		}
		~node() {}
		TKey return_Keys() {
			return Keys;
		}
		bool return_with_repeat_replacement() {
			return with_repeat_replacement;
		}
		bool return_is_delete() {
			return is_delete;
		}
		TValue* return_Values() {
			return &Values;
		}
		void Set_Value(TValue k) { Values = k; }
		void Set_is_delete(bool k) { is_delete = k; }
	};
	node* first_ptr; // указатель на первую ноду односвязного списка
	unsigned size = 0; // размер форвард листа
public:
	node* get_first_ptr() { return first_ptr; }
	unsigned return_size() { return size; }
	TKey del_value[10];
	unsigned del = 0;

	class iterator {
	public:
		node* PTR;
		iterator() { PTR = nullptr; }
		iterator(node* m) {
			PTR = m;
		}
		~iterator() {}
		void operator ++() {
			if (PTR != nullptr) {
				PTR = PTR->ptr;
			}
			else { std::cout << "Введите позицию итератора" << std::endl; }
		}
		bool operator ==(node* m) const {
			return PTR == m;
		}
		bool operator !=(node* m) const {
			if (PTR != m) return true;
			else return false;
		}
		node* operator +=(int m) {
			for (int i = 0; i < m; i++) {
				PTR = PTR->ptr;
			}
			return PTR;
		}
		node* operator +(int m) {
			iterator ptr2(this->PTR);
			for (int i = 0; i < m; i++) {
				ptr2.PTR = ptr2.PTR->ptr;
			}
			return ptr2.PTR;
		}
	};

	Ordered_Table(std::string k, std::string r) {
		name_of_first_column = k;
		name_of_second_column = r;
	}

	~Ordered_Table() {}

	node* begin() {
		return first_ptr;
	}

	node* end() {
		iterator m(begin());
		m += size - 1;
		/*node* m = first_ptr->ptr;
		for (int i = 0; i < size; i++) {
			m = m->ptr;
		}*/
		return m.PTR;
	}

	std::string return_name_of_first_column() {
		return name_of_first_column;
	}

	std::string return_name_of_second_column() {
		return name_of_first_column;
	}

	bool create_last_node(TKey Key, TValue Value, bool with_repeat_replacementt, bool is_delete) {
		iterator l(begin());
		for (int i = 0; i < size; i++) {
			if ((l.PTR->return_Keys() == Key) && (with_repeat_replacementt == false)) { std::cerr << "Ошибка: повтор ключа\n"; return false; }
			if ((l.PTR->return_Keys() == Key) && (with_repeat_replacementt == true)) { l.PTR->Set_Value(Value); l.PTR->Set_is_delete(false);  return true; } // делаем пометку об удалении
			l += 1;
		}
		node* Node = new node(Key, Value, with_repeat_replacementt, is_delete);
		iterator m(begin());
		if (size == 0) { size++; first_ptr = Node; }
		else {
			m += size - 1;
			m.PTR->ptr = Node;
			size++;
		}
		this->to_order();
	}

	void to_order() {
		std::vector<TKey> vec;
		iterator l(begin());
		for (int i = 0; i < size; i++) {
			vec.push_back(l.PTR->Keys);
			l += 1;
		}
		std::sort(vec.begin(), vec.end()); // сортировка ключей в массиве
		TKey Key; 
		TValue Value; 
		bool with_repeat_replacementtt; 
		bool is_deleted;
		iterator r(begin());
		for (int i = 0; i < size; i++) {
			if (vec[i] != r.PTR->return_Keys()) {
				Key = r.PTR->return_Keys();
				Value = *r.PTR->return_Values();
				with_repeat_replacementtt = r.PTR->return_with_repeat_replacement();
				is_deleted = r.PTR->return_is_delete();
				iterator s(begin());
				s += i + 1;
				for (int t = i+1; t < size; t++) {
					if (vec[i] == s.PTR->return_Keys()) {
						r.PTR->Keys = s.PTR->return_Keys();
						r.PTR->Values = *s.PTR->return_Values();
						r.PTR->with_repeat_replacement = s.PTR->return_with_repeat_replacement();
						r.PTR->is_delete = s.PTR->return_is_delete();
						s.PTR->Keys = Key;
						s.PTR->Values = Value;
						s.PTR->with_repeat_replacement = with_repeat_replacementtt;
						s.PTR->is_delete = is_deleted;
						break;
					}
					else s += 1;
				}
			}
			r += 1;
		}
	}

	void create_first_node(TKey Key, TValue Value, bool with_repeat_replacementt, bool is_delete) {
		node* Node = new node(Key, Value, with_repeat_replacementt, is_delete);
		if (size == 0) { first_ptr = Node; size++; }
		else { Node->ptr = first_ptr; first_ptr = Node; size++; }
	}

	void delete_first_node() {
		node* m = first_ptr->ptr;
		first_ptr->~node();
		first_ptr = m;
		size--;
	}

	void delete_last_node() {
		iterator m(begin());
		m += size - 1;
		m.PTR->~node();
		size--;
	}

	void insert_node(unsigned index, TKey Key, TValue Value, bool with_repeat_replacementt, bool is_delete) {
		iterator m(begin());
		node* Node = new node(Key, Value, with_repeat_replacementt, is_delete);
		if (index == 0) { Node->ptr = first_ptr; first_ptr = Node; size++; }
		else {
			m += index - 1;
			Node->ptr = m.PTR;
			m.PTR->ptr = Node;
			size++;
		}
	}

	void pop(unsigned index) {
		if (index < size) {
			iterator m(begin());
			if (index != 0) m += index - 1;
			node* k = m + 1;
			if (index == 0) { first_ptr = k; m.PTR->~node(); }
			else
			{
				m.PTR->ptr = k->ptr;
				k->~node();
			}
			size--;
		}
	}

	TKey* delete_value(TKey Keys) {
		if (search_of_value(Keys) != nullptr) {
			for (int i = 0; i < (sizeof(del_value) / sizeof(del_value[0])); i++) {
				if (Keys == del_value[i]) { return &Keys; }
			}
			// если его нет в del_value
			iterator f(begin());
			for (int i = 0; i < size; i++) {
				if (f.PTR->return_Keys() == Keys) { f.PTR->is_delete = true; } // делаем пометку об удалении
				f += 1;
			}
			if (del > 10) {
				int index = -1;
				iterator z(begin());
				for (int i = 0; i < size; i++) {
					if (z.PTR->return_Keys() == del_value[del % 10]) { index = i; break; }
					z += 1;
				}
				iterator m(begin());
				if (index != 0) m += index - 1;
				iterator k = m + 1;
				if (Keys == first_ptr->return_Keys()) { first_ptr = k.PTR; m.PTR->~node(); }
				else
				{
					m.PTR->ptr = k.PTR->ptr;
					k.PTR->~node();
				}
				size--;
				del_value[del % 10] = Keys; // заносим его в del_value
				del++;
				if (index != -1) return &Keys;
				else return nullptr;
			}
			else {
				del_value[del % 10] = Keys; // заносим его в del_value
				del++;
			}
		}
		else return nullptr;
	}

	TValue* search_of_value(TKey Keys) {
		iterator k(begin());
		for (int i = 0; i < size; i++) {
			if (k.PTR->return_Keys() == Keys) {
				if (k.PTR->return_is_delete() == false) { return k.PTR->return_Values(); }
				else return nullptr;
			}
			k += 1;
		}
		return nullptr;
	}

	Ordered_Table reverse_list() {
		iterator m(begin());
		iterator k(begin());
		node* last_ptr = first_ptr;
		m += size - 1;
		first_ptr = m.PTR;
		m += 1;
		k += size - 2;
		int i = size;
		int r = size - 2;
		while (k.PTR != last_ptr) {
			m.PTR = k.PTR;
			m.PTR = last_ptr;
			i--;
			m += i;
			k.PTR = last_ptr;
			r--;
			k += r;
		}
		m.PTR->ptr = last_ptr;
		last_ptr->~node();
		return *this;
	}

	node* centre_of_list() {
		iterator m(begin());
		m += size / 2;
		return m.PTR;
	}

	void print() {
		iterator m(begin());
		for (int i = 0; i < size; i++) {
			std::cout << "Ключ: " << m.PTR->return_Keys() << " Значение: " << m.PTR->return_Values() << std::endl;
			m += 1;
		}
	}

	bool is_empty() {
		if (size == 0) return true; else return false;
	}

	void resize_list(unsigned m) {
		if (m > size) {
			for (int i = 0; i < size - m; i++) { create_last_node(); }
		}
	}
};
