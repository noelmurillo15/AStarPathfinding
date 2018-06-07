#pragma once


template <typename type>

class DynArray{

public:

	DynArray();
	~DynArray();

	DynArray(const DynArray<type>& c);
	DynArray<type>& operator=(const DynArray<type>& a);

	type& operator[](const unsigned int index);
	const type& operator[](const unsigned int index) const;

	unsigned int size() const;
	unsigned int capacity() const;

	void append(const type& item);
	void reserve(const unsigned int & newCap = 0);
	void clear();

	//Challenge
	void insert(const type val, const unsigned int index);
	void insert(const type * val, const unsigned int n, const unsigned int index);

	void remove(const unsigned int index);
	void remove(const unsigned int index, const unsigned int n);
	// End Challenge


	unsigned int currSize, currCap, newCap;

	type *DynArr;
};


template<typename type>
DynArray<type>::DynArray(){

	currCap = 0;
	currSize = 0;

	DynArr = NULL;
}

template<typename type>
DynArray<type>::~DynArray(){
	delete[] DynArr;
}

template<typename type>
DynArray<type>::DynArray(const DynArray<type>& c){

	DynArr = NULL;

	currCap = c.currCap;
	currSize = c.currSize;
	newCap = c.newCap;

	DynArr = new type[currCap];

	for (unsigned int i = 0; i < currSize; i++){
		DynArr[i] = c.DynArr[i];
	}
}

template<typename type>
DynArray<type>& DynArray<type>::operator=(const DynArray<type>& a){
	if (this != &a){

		delete[] DynArr;

		currCap = a.currCap;
		currSize = a.currSize;
		newCap = a.newCap;

		DynArr = new type[currCap];

		for (unsigned int i = 0; i < currSize; i++){
			DynArr[i] = a.DynArr[i];
		}
	}
	return *this;
}

template<typename type>
unsigned int DynArray<type>::size() const{
	return currSize;
}

template<typename type>
unsigned int DynArray<type>::capacity() const{
	return currCap;
}

template<typename type>
void DynArray<type>::append(const type& item){
	
	if (currCap == 0){
		currCap = 1;

		DynArr = new type[currCap];
		DynArr[currSize] = item;
	}

	else if (currCap == currSize){
		currCap *= 2;
		
		type *tmp = new type[currCap];
		for (unsigned int i = 0; i < currSize; i++){
			type newItem = DynArr[i];
			tmp[i] = newItem;
		}
		tmp[currSize] = item;

		delete[] DynArr;
		DynArr = tmp;

		tmp = NULL;
		delete[] tmp;
	}

	else{
		DynArr[currSize] = item;
	}

	currSize++;
}

template<typename type>
void DynArray<type>::reserve(const unsigned int & newCap = 0){

	if (newCap == NULL){
		if (currCap == 0)
			currCap = 1;

		else{
			currCap *= 2;

			type* tmp = new type[currCap];
			for (unsigned int i = 0; i < currSize; i++){
				type newItem = DynArr[i];
				tmp[i] = newItem;
			}
			delete[] DynArr;
			DynArr = tmp;
			tmp = NULL;
			delete[] tmp;
		}
	}
	else if (newCap < currCap){

	}
	else{
		type* tmp = new type[newCap];
		currCap = newCap;
		for (unsigned int i = 0; i < currSize; i++){
			type newItem = DynArr[i];
			tmp[i] = newItem;
		}
		delete[] DynArr;
		DynArr = tmp;
		tmp = NULL;
		delete[] tmp;
	}
}

template<typename type>
void DynArray<type>::clear(){
	delete[] DynArr;
	DynArr = NULL;

	currCap = 0;
	currSize = 0;
}

template<typename type>
type& DynArray<type>::operator[](const unsigned int index){
	return DynArr[index];
}

template<typename type>
const type& DynArray<type>::operator[](const unsigned int index) const{
	return DynArr[index];
}


// Challenge
template<typename type>
void DynArray<type>::insert(const type val, const unsigned int index){

	if (index > currCap){

	}

	else{
		if (currSize + 1 > currCap){
			DynArray<type>::reserve();
		}
		type* tmp = new type[currCap];
		for (unsigned int i = 0; i < index; i++){
			type newItem = DynArr[i];
			tmp[i] = newItem;
		}
		tmp[index] = val;
		for (unsigned int i = index; i < currSize; i++){
			type newItem = DynArr[i];
			tmp[i + 1] = newItem;
		}
		delete[] DynArr;
		DynArr = tmp;
		tmp = NULL;
		delete[] tmp;

		currSize++;
	}
	
}

template<typename type>
void DynArray<type>::insert(const type * val, const unsigned int n, const unsigned int index){
	if (index > currCap){

	}
	else{
		if (currSize + n > currCap){
			DynArray<type>::reserve();
		}
		type* tmp = new type[currCap];
		for (unsigned int i = 0; i < index; i++){
			type newItem = DynArr[i];
			tmp[i] = newItem;
		}
		int x = 0;
		while (x != n){
			tmp[index + x] = val[x];
			x++;
		}
		for (unsigned int i = index; i < currSize; i++){
			type newItem = DynArr[i];
			tmp[i + n] = newItem;

		}
		delete[] DynArr;
		DynArr = tmp;
		tmp = NULL;
		delete[] tmp;

		currSize += n;
	}
}

template<typename type>
void DynArray<type>::remove(const unsigned int index){
	if (index >= currSize){

	}
	else{
		type* tmp = new type[currCap];
		for (unsigned int i = 0; i < index; i++){
			type newItem = DynArr[i];
			tmp[i] = newItem;
		}
		for (unsigned int i = index; i < currSize - 1; i++){
			type newItem = DynArr[i + 1];
			tmp[i] = newItem;
		}
		delete[] DynArr;
		DynArr = tmp;
		tmp = NULL;
		delete[] tmp;

		currSize--;
	}
}
template<typename type>
void DynArray<type>::remove(const unsigned int index, const unsigned int n){
	if (index >= currSize){

	}
	else{
		type* tmp = new type[currCap];
		for (unsigned int i = 0; i < index; i++){
			type newItem = DynArr[i];
			tmp[i] = newItem;
		}
		for (unsigned int i = index; i < currSize - n; i++){
			type newItem = DynArr[i + n];
			tmp[i] = newItem;
		}
		delete[] DynArr;
		DynArr = tmp;
		tmp = NULL;
		delete[] tmp;

		currSize -= n;
	}
}
// End Challenge