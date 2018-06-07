#pragma once
#include "DynArray.h"

template<typename type>
class BinaryHeap : private DynArray<type>{

public:

	void enqueue(const type & v);
	void clear();

	type dequeue();
	type& operator[](int index);

	unsigned int size();
};

template<typename type>
void BinaryHeap <type>::enqueue(const type &e)
{
	this->DynArray::append(e);
	int currIndex = this->DynArray::size() - 1;
	int Parent = (currIndex - 1) / 2;

	while (0 < currIndex){
		Parent = (currIndex - 1) / 2;
		if (this->DynArray::DynArr[Parent] > e){

			type tmp = e;

			this->DynArray::DynArr[currIndex] = this->DynArray::DynArr[Parent];
			this->DynArray::DynArr[Parent] = tmp;

			currIndex = Parent;
		}
		else{
			currIndex = 0;
		}
	}
}


template<typename type>
type BinaryHeap <type>::dequeue()
{
	int currIndex = 0;
	unsigned int leftIndex = 1;
	unsigned int rightIndex = 2;

	bool atBottom = false;
	bool rightchildempty = false;

	type removethis = this->DynArray::DynArr[0]; // store root
	type swapthis = this->DynArray::DynArr[DynArray::size() - 1]; //store the new root
	type leftChild = this->DynArray::DynArr[leftIndex];
	type rightChild = this->DynArray::DynArr[rightIndex];

	if (DynArray::size() - 1 == 0){
		this->DynArray::remove(DynArray::size() - 1);
		return removethis;
	}
	else if (DynArray::size() - 1 == 1){

		this->DynArray::DynArr[0] = leftChild; // swap left child to parent
		this->DynArray::remove(DynArray::size() - 1);
		return removethis;
	}
	else{
		DynArray::DynArr[0] = swapthis; // copy bottom to root
		this->DynArray::remove(DynArray::size() - 1);
	}

	while ((swapthis > leftChild || swapthis > rightChild) && atBottom != true){ // if the parent is greater than left child or right child

		if (leftChild < rightChild || rightchildempty == true){ // if left child is less than right child
			if (leftChild < rightChild){
				type tmp = swapthis; // store the parent
				this->DynArray::DynArr[currIndex] = leftChild; // swap left child to parent
				this->DynArray::DynArr[leftIndex] = swapthis; // swap parent to left child
			}
			currIndex = (currIndex * 2) + 1; // make index = to left child
		}
		else if (rightChild < leftChild){
			if (rightchildempty != true){
				type tmp = swapthis; // store the parent
				this->DynArray::DynArr[currIndex] = rightChild; // swap left child to parent
				this->DynArray::DynArr[rightIndex] = swapthis; // swap parent to left child
			}

			currIndex = (currIndex * 2) + 2; // make index = to right child
		}

		rightIndex = (currIndex * 2) + 2; // set correct right index
		leftIndex = (currIndex * 2) + 1; // set correct left index

		if (leftIndex <= DynArray::size() - 1){
			leftChild = this->DynArray::DynArr[leftIndex];
			if (rightIndex <= DynArray::size() - 1){
				rightChild = this->DynArray::DynArr[rightIndex];
			}
			else{ rightchildempty = true; }
		}
		else{ atBottom = true; }
	}
	return removethis;
}

template<typename type>
unsigned int BinaryHeap<type>::size(){
	return this->DynArray::currSize;
}

template<typename type>
void BinaryHeap<type>::clear(){
	this->DynArray::clear();
}

template<typename type>
type& BinaryHeap<type>::operator[](int index){
	return this->DynArray::operator[](index);
}