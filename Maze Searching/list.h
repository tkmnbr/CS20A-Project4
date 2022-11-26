#ifndef F22_CS20A_LIST_H
#define F22_CS20A_LIST_H

#include<iostream>
#include<assert.h>
template<typename Type>
class List {
public:

	List();

	List(const List<Type>& other);

	List<Type>& operator=(const List<Type>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Type &value);
	void	push_rear(const Type &value);
	void	push_at(int idx, const Type &value);

	Type	front() const;
	Type	rear() const;
	Type	at(int idx) const;

	int		size() const;
	int		count(const Type &value) const;

	int		find(const Type &value) const;

	bool	pop_front();
	bool	pop_rear();
	bool	pop_at(int idx);
	int		pop_value(const Type &value);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	class DLNode;
	DLNode*	m_front;
	DLNode*	m_rear;
	int	 m_size;
};

template<typename Type>
class List<Type>::DLNode {
public:
	DLNode() :nxt(nullptr), prv(nullptr) {}
	DLNode(Type v, DLNode* p, DLNode* n) : val(v), nxt(n), prv(p) {}

	DLNode * next() const { return nxt; } 
	void	 next(DLNode *n) { nxt = n; }

	DLNode * prev() const { return prv; } 
	void	 prev(DLNode *p) { prv = p; } 

	Type value() const { return val; }		
	void value(const Type &v) { val = v; }	

private:
	Type  val;
	DLNode* nxt;
	DLNode* prv;
};


//List Ctor
template<typename Type>
List<Type>::List() :m_front(nullptr), m_rear(nullptr), m_size(0) {
}


//Copy Ctor
template<typename Type>
List<Type>::List(const List<Type>& other) {
	if (other.empty()) return;
	DLNode* other_p = other.m_front;
	while (other_p != nullptr) {
		push_rear(other_p->value());
		other_p = other_p->next();
	}
}

//Overload assignment operator
template<typename Type>
List<Type>& List<Type>::operator=(const List<Type>& other) {
	if (this != &other) {

		//Clean up current list
		DLNode* clean = m_front;
		while (clean != nullptr)
		{
			DLNode* next = clean->next();
			delete clean;
			clean = next;
		}
		m_front = nullptr;
		m_rear = nullptr;
		m_size = 0;

		DLNode* p = other.m_front; //traverse the other list
		while (p != nullptr) {
			push_rear(p->value());
			p = p->next();
		}
	}
	return *this;
	/*if (this != &other) {
		DLNode* p = m_front;
		while (p != nullptr) {
			DLNode* temp = p->next();
			delete p;
			p = temp;
		}
		if (other.empty()) return *this;
		DLNode* other_p = other.m_front;
		while (other_p != nullptr) {
			push_rear(other_p->value());
			other_p = other_p->next();
		}
	}
	return *this;*/
}

//List Dtor
template<typename Type>
List<Type>::~List() {
	DLNode* p = m_front;
	while (p != nullptr) {
		DLNode* temp = p->next();
		delete p;
		p = temp;
	}
}

//List print
template<typename Type>
void List<Type>::print() const {
	if (m_size == 0) return;
	DLNode* curr = m_front;
	while (curr->next() != nullptr) {
		std::cout << curr->value() << " ";
		curr = curr->next();
	}
	std::cout << curr->value();
}

//List empty
template<typename Type>
bool List<Type>::empty() const {
	if (m_size == 0)
		return true;
	return false;
}

//List push Front
template<typename Type>
void List<Type>::push_front(const Type &value) {
	DLNode* node = new DLNode;
	if (m_size == 0)
	{
		m_front = node;
		m_rear = node;
		node->value(value);
		m_size++;
		return;
	}
	node->value(value);
	node->prev(nullptr);
	node->next(m_front);
	node->next()->prev(node);
	m_front = node;
	m_size++;
}

//List push rear
template<typename Type>
void List<Type>::push_rear(const Type &value) {
	if (m_size == 0) {
		push_front(value);
		return;
	}
	DLNode* node = new DLNode;
	node->value(value);
	node->next(nullptr);
	node->prev(m_rear);
	node->prev()->next(node);
	m_rear = node;
	m_size++;
}

//List push at
//If the index <= 0, add front.
//If the index >= m_size, add rear.
//Otherwise, push at the index indicated.
template<typename Type>
void List<Type>::push_at(int idx, const Type &value) {
	if (idx <= 0) {
		push_front(value);
		return;
	}
	if (idx >= m_size) {
		push_rear(value);
		return;
	}
	DLNode* node = new DLNode;
	DLNode* p = m_front;
	node->value(value);
	for (int i = 1; i < idx; i++)
		p = p->next();
	node->prev(p);
	node->next(p->next());
	p->next()->prev(node);
	p->next(node);
	m_size++;
}

//List front
//Return the value of the first node.
template<typename Type>
Type List<Type>::front() const {
	assert(m_front != nullptr);
	return(m_front->value());
}

//List rear
//Return the value of the last node.
template<typename Type>
Type List<Type>::rear() const {
	assert(m_rear != nullptr);
	return (m_rear->value());
}

//List at
//Return the value of the given index.
template<typename Type>
Type List<Type>::at(int idx) const {
	assert(idx >= 0 && idx < m_size);

	DLNode* p = m_front;
	for (int i = 0; i < idx; i++)
		p = p->next();
	return(p->value());
}

//List size
//Return the size of m_size
template<typename Type>
int List<Type>::size() const {
	return(m_size);
}

//List count
//Return the total # of the values in the list that match the given value.
template<typename Type>
int List<Type>::count(const Type &value) const {
	int result = 0;
	DLNode* p = m_front;
	while (p != nullptr) {
		if (p->value() == value)
			result++;
		p = p->next();
	}
	return result;
}

//List find
//Search the list if the given value is curently in the list.
//If it is, return the index of that position, otherwise return -3.
template<typename Type>
int List<Type>::find(const Type &value) const {
	int index = 0;
	DLNode* p = m_front;
	while (p != nullptr) {
		if (p->value() == value) return index;
		p = p->next();
		index++;
	}
	return -3;
}

//List pop front
//Remove the first node in the list.
//If the value was deleted return true, otherwise return false.
template<typename Type>
bool List<Type>::pop_front() {
	if (m_front == nullptr) return false;
	if (m_size == 1) {
		delete m_front;
		m_front = nullptr;
		m_rear = nullptr;
		m_size--;
		return true;
	}
	DLNode* p = m_front;
	m_front = p->next();
	p->next()->prev(nullptr);
	delete p;
	m_size--;
	return true;
}

//List pop rear
//Remove the very last node in thelist.
//If the value was deleted return true, otherwise return false.
template<typename Type>
bool List<Type>::pop_rear() {
	if (empty()) return false;
	if (m_size == 1) {
		delete m_front;
		m_front = nullptr;
		m_rear = nullptr;
		m_size--;
		return true;
	}
	DLNode* p = m_rear;
	m_rear = p->prev();
	p->prev()->next(nullptr);
	delete p;
	m_size--;
	return true;
}

//List pop at
//Remove the value at the index of the list.
//If the value was deleted return true, otherwise return false.
//If the index is out of bound, do nothing n return false.
template<typename Type>
bool List<Type>::pop_at(int idx) {
	if (idx < 0 or idx >= m_size) return false;
	if (idx == 0) {
		pop_front();
		return true;
	}
	if (idx == m_size - 1) {
		pop_rear();
		return true;
	}
	DLNode* p = m_front;
	for (int i = 0; i < idx; i++) p = p->next();
	p->prev()->next(p->next());
	p->next()->prev(p->prev());
	delete p;
	m_size--;
	return true;
}

//List pop value
//Remove the first occurence the value relative to the front of the list.
//Return the index of the removed value. If the list is empty, return -3.
//If the value is not found, return -2.
template<typename Type>
int List<Type>::pop_value(const Type &value) {
	if (m_size == 0) return -3;
	int retVal = find(value);
	if (retVal == -3) return -2;
	pop_at(retVal);
	return retVal;
}


#endif



























































































// _X_XMMXXI