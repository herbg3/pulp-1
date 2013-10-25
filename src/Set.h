#pragma once


//---------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>

template <class ARG_TYPE>
class Set {
protected:
	unsigned int capacity;
	unsigned int size;
	ARG_TYPE *list;
public:
	Set(){
		size = capacity = 0;
		list = NULL;
	}

	Set(const unsigned int iCapacity){
		size = 0;
		capacity = iCapacity;
		list = (ARG_TYPE *) malloc(capacity * sizeof(ARG_TYPE));
	}
	
	~Set(){
		free(list);
	}

	ARG_TYPE *getArray() const { return list; }

	ARG_TYPE &operator [] (const unsigned int index) const {
		return list[index];
	}

	void setSize(const unsigned int newSize){
		capacity = size = newSize;
		list = (ARG_TYPE *) realloc(list,capacity * sizeof(ARG_TYPE));		
	}

	unsigned int add(const ARG_TYPE object){
		if (size >= capacity){
			if (capacity) capacity += capacity; else capacity = 32;
			list = (ARG_TYPE *) realloc(list,capacity * sizeof(ARG_TYPE));
		}
		list[size] = object;
		return size++;
	}

	void remove(const unsigned int index){
		if (index < size){
			size--;
			list[index] = list[size];
		}
	}

	void orderedRemove(const unsigned int index){
		if (index < size){
			size--;
			memmove(list + index, list + index + 1, (size - index) * sizeof(ARG_TYPE));
		}
	}

	void removeObject(const ARG_TYPE object){
		for (unsigned int i = 0; i < size; i++){
			if (object == list[i]){
				remove(i);
				return;
			}
		}
	}

	void clear(){
		size = 0;
	}

	void reset(){
		free(list);
		list = NULL;
		size = capacity = 0;
	}

	unsigned int getSize() const {	return size;	}

private:
	int partition(int (*compare)(const ARG_TYPE &elem0, const ARG_TYPE &elem1), int p, int r){
		ARG_TYPE tmp, pivot = list[p];
		int left = p;

		for (int i = p + 1; i <= r; i++){
			if (compare(list[i], pivot) < 0){
				left++;
				tmp = list[i];
				list[i] = list[left];
				list[left] = tmp;
			}
		}
		tmp = list[p];
		list[p] = list[left];
		list[left] = tmp;
		return left;
	}

	void quickSort(int (*compare)(const ARG_TYPE &elem0, const ARG_TYPE &elem1), int p, int r){
		if (p < r){
			int q = partition(compare, p, r);
			quickSort(compare, p, q - 1);
			quickSort(compare, q + 1, r);
		}
	}
public:
	void sort(int (*compare)(const ARG_TYPE &elem0, const ARG_TYPE &elem1)){
		quickSort(compare, 0, size - 1);
	}
};