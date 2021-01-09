//
//  List.h
//  cpp_elections
//
//  Created by Yuval  Yakovskind  on 05/01/2021.
//  Copyright © 2021 Tamir Houri 205668627 & Yuval Yakovskind 316550524. All rights reserved.
//

#pragma once
#include <iostream>

namespace mySTL
{
	template <class T>
	struct Node {
		T data;
		Node* next = nullptr;
	};

	template <class T>
	class List
	{
		// Class to represent a template list
		// Restrictions: class T must have operator= , operator!= , operator==

	private:

		Node<T>* _head;
		Node<T>* _tail;
		int   _size;

	public:
		List() : _head(new Node<T>()), _tail(_head), _size(0) {}

		List(const List& other) : List() {
			*this = other;
		}

		~List() {
			clear();
			delete _head;
		}

		int size() const { return _size; }

		bool empty() const { return _head == _tail; }

		void clear() {
			Node<T>* curr = _head->next;
			Node<T>* temp;

			while (curr != nullptr) {
				temp = curr;
				curr = curr->next;
				delete temp;
			}
			_head->next = nullptr;
			_tail = _head;
			_size = 0;
		}

		void push_back(const T& val) {
			Node<T>* newnode = new Node<T>();
			newnode->data = val;

			_tail->next = newnode;
			_tail = newnode;
			_size++;
		}

		void pop_back() {

			if (!empty()) {
				Node<T> *curr;
				curr = _head;

				while (curr->next != _tail) {
					curr = curr->next;
				}
				curr->next = nullptr;
				delete _tail;
				_tail = curr;
			}
		}

		void push_front(const T& val) {
			Node<T>* newnode = new Node<T>();
			newnode->data = val;

			newnode->next = _head->next;
			_head->next = newnode;
			if (_head == _tail)
				_tail = newnode;

			_size++;
		}

		void pop_front() {
			if (!empty()) {
				Node<T>* tmp = _head->next;

				if (tmp == _tail)
					_tail = _head;

				_head->next = tmp->next;
				delete tmp;
				_size--;
			}
		}

		const T& front() const { return !empty() ? _head->next->data : nullptr; }
		T& front() { return !empty() ? _head->next->data : nullptr; }

		const T& back() const { return !empty() ? _tail->data : nullptr; }
		T& back() { return !empty() ? _tail->data : nullptr; }

		const List& operator=(const List& other) {
			if (this != &other) {
				clear();

				Node<T>* curr = other._head->next;
				while (curr != nullptr) {
					push_back(curr->data);
				}
			}
			return *this;
		}

		bool operator==(const List& other) const {
			Node<T> *curr1 = _head->next, *curr2 = other._head->next;

			while (curr1 != nullptr && curr2 != nullptr) {
				if (curr1->data != curr2->data)
					return false;
				curr1 = curr1->next;
				curr2 = curr2->next;
			}
			return !(curr1 && curr2);
		}


		class const_iterator;

		class iterator
		{
		private:
			Node<T>* _curr;
		public:
			using iterator_category = std::forward_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T * ;
			using reference = T & ;

			iterator(Node<T>* curr) : _curr(curr) {}
			iterator(const iterator& other) : _curr(other._curr) {}
			~iterator() {}

			friend class const_iterator;
			friend class List;

			const iterator& operator=(const iterator& other) {
				_curr = other._curr;
				return *this;
			}

			bool operator==(const iterator& other) const { return _curr == other._curr; }
			bool operator!=(const iterator& other) const { return !(*this == other); }
			bool operator==(const const_iterator& other) const { return _curr == other._curr; }
			bool operator!=(const const_iterator& other) const { return !(*this == other); }

			T& operator*() {
				return _curr->next->data;
			}
			const T& operator*() const {
				return _curr->next->data;
			}
			T* operator->() {
				return &_curr->next->data;
			}

			// increment iterator methods
			iterator& operator++() { // ++itr
				_curr = _curr->next;
				return *this;
			}
			iterator operator++(int) { // itr++
				iterator temp(*this);
				_curr = _curr->next;
				return temp;
			}

		};

		class const_iterator
		{
		private:
			const Node<T>* _curr;
		public:
			using iterator_category = std::forward_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T * ;
			using reference = T & ;

			const_iterator(const Node<T>& curr) : _curr(&curr) {}
			const_iterator(const iterator& other) : _curr(other._curr) {}
			const_iterator(const const_iterator& other) : _curr(other._curr) {}
			~const_iterator() {}


			const const_iterator& operator=(const iterator& other) {
				_curr = other._curr;
				return *this;
			}
			const const_iterator& operator=(const const_iterator& other) {
				_curr = other._curr;
				return *this;
			}

			friend class iterator;
			friend class List;

			bool operator==(const const_iterator& other) const { return _curr == other._curr; }
			bool operator!=(const const_iterator& other) const { return !(*this == other); }

			const T& operator*() {
				return _curr->next->data;
			}
			const T* operator->() {
				return &_curr->next->data;
			}

			// increment iterator methods
			const_iterator& operator++() { // ++itr
				_curr = _curr->next;
				return *this;
			}

			const_iterator operator++(int) { // itr++
				iterator temp(*this);
				_curr = _curr->next;
				return temp;
			}

		};

		iterator begin() const { return iterator(_head); }
		iterator end() const { return iterator(_tail); }
		const_iterator cbegin() const { return const_iterator(_head); }
		const_iterator cend() const { return const_iterator(_tail); }

		void insert(const iterator& pos, const T& val) {
			Node<T>* newnode = new Node<T>();
			newnode->data = val;
			newnode->next = pos._curr->next;

			if (pos._curr == _tail)
				_tail = newnode;

			pos._curr->next = newnode;
			_size++;
		}

		const iterator& erase(const iterator& iter) {
			Node<T> *toDelete = iter._curr->next;

			iter._curr->next = iter._curr->next->next;
			if (toDelete == _tail)
				_tail = iter._curr;
			delete toDelete;
			_size--;
			return iter;
		}
		const iterator& erase(const iterator& first, const iterator& last) {
			iterator iter = first;

			while (iter._curr->next != last._curr) {
				iter = erase(iter);
			}
			erase(iter);
			return first;
		}
	};
}

