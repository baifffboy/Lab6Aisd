#pragma once
#include <iostream>
#include <vector>

template <typename TKey, typename TValue>
class Unordered_Table_on_forward_list {
private:
	std::string name_of_first_column;
	std::string name_of_second_column;
	class node { //����� node
	private:
		TKey Keys;
		bool with_repeat_replacement;
		TValue Values;
	public:
		node* ptr = nullptr; // ��������� ��������� ����
		bool is_delete;

		node(TKey Key, TValue Value, bool with_repeat_replacementt, bool is_delet) { // ���������� ������������ node
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
	node* first_ptr; // ��������� �� ������ ���� ������������ ������
	unsigned size = 0; // ������ ������� �����
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
			else { std::cout << "������� ������� ���������" << std::endl; }
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

	Unordered_Table_on_forward_list(std::string k, std::string r) {
		name_of_first_column = k; 
		name_of_second_column = r;
	}

	~Unordered_Table_on_forward_list() {}

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
			if ((l.PTR->return_Keys() == Key) && (with_repeat_replacementt == false)) { std::cerr << "������: ������ �����\n"; return false; }
			if ((l.PTR->return_Keys() == Key) && (with_repeat_replacementt == true)) { l.PTR->Set_Value(Value); l.PTR->Set_is_delete(false);  return true; } // ������ ������� �� ��������
			l+=1;
		}
		node* Node = new node(Key, Value, with_repeat_replacementt, is_delete);
		iterator m(begin());
		if (size == 0) { size++; first_ptr = Node; }
		else {
			m += size - 1;
			m.PTR->ptr = Node;
			size++;
		}
		return true;
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

	TKey* delete_value(TKey Keys) {
		if (search_of_value(Keys) != nullptr) {
			for (int i = 0; i < (sizeof(del_value) / sizeof(del_value[0])); i++) {
				if (Keys == del_value[i]) { return &Keys; }
			}
			// ���� ��� ��� � del_value
			iterator f(begin());
			for (int i = 0; i < size; i++) {
				if (f.PTR->return_Keys() == Keys) { f.PTR->is_delete = true; } // ������ ������� �� ��������
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
				del_value[del % 10] = Keys; // ������� ��� � del_value
				del++;
				if (index != -1) return &Keys;
				else return nullptr;
			}
			else {
				del_value[del % 10] = Keys; // ������� ��� � del_value
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
			k+=1;
		}
		return nullptr;
	}

	Unordered_Table_on_forward_list reverse_list() {
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

	bool is_empty() {
		if (size == 0) return true; else return false;
	}

	void resize_list(unsigned m) {
		if (m > size) {
			for (int i = 0; i < size - m; i++) { create_last_node(); }
		}
	}
};
