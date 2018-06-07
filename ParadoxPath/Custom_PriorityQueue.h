#ifndef _CUSTOM_PRIORITYQUEUE_
#define _CUSTOM_PRIORITYQUEUE_

#include <algorithm>

template <typename T>
class Custom_PriorityQueue
{
	std::deque<T> open;
	bool(*compare)(T const&, T const&);

public:

	//	Constructs a Priority Queue that heap sorts nodes
	explicit Custom_PriorityQueue(bool(*)(T const&, T const&));

	//	Returns true if the heap contains no nodes
	bool empty() const;

	//	Removes all nodes from heap
	void clear();

	//	Returns the number of nodes currently in the heap
	std::size_t size() const;

	//	Pushes the specified node onto the heap
	void push(T const& node);

	//	Returns the top node in the heap
	T front() const;

	//	Removes the top node from the heap
	void pop();

	//	Removes all instances of the specified node from the heap
	void remove(T const& node);
};

template <typename T>
Custom_PriorityQueue<T>::Custom_PriorityQueue(bool(*c)(T const&, T const&)) : open(), compare(c) {
}

template <typename T>
bool Custom_PriorityQueue<T>::empty() const {
	return open.empty();
}

template <typename T>
void Custom_PriorityQueue<T>::clear() {
	open.clear();
}

template <typename T>
std::size_t Custom_PriorityQueue<T>::size() const {
	return open.size();
}

template <typename T>
void Custom_PriorityQueue<T>::push(T const& node) {
	open.insert(std::upper_bound(open.begin(), open.end(), node, compare), node);
}

template <typename T>
T Custom_PriorityQueue<T>::front() const {
	return open.back();
}

template <typename T>
void Custom_PriorityQueue<T>::pop() {
	open.pop_back();
}

template <typename T>
void Custom_PriorityQueue<T>::remove(T const& node) {
	open.erase(std::remove(open.begin(), open.end(), node), open.end());
}

#endif