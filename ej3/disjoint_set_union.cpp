#include <cstring>

#include "disjoint_set_union.h"

Disjoint_Union::Disjoint_Union(const int & n){
	container_size = n;
	total = n;
	allocated_size = 2 * (n);
	container = new int[allocated_size];
	memset(container , -1 , allocated_size * 4);
}

int Disjoint_Union::create(){ // add a new entry
	//check whetehr need to reallocate memory
	if(++container_size > allocated_size){
		allocated_size = allocated_size * 2;
		int * temp = new int[allocated_size];
		for(int i = 0 ; i < container_size-1 ; i++)
			temp[i] = container[i];
		delete[] container;
		container = NULL;
		container = temp;
		temp = NULL;
	}
	container[container_size-1] = -1;
	return container_size -1; //returns the index of the new element
}

void Disjoint_Union::merge(int i , int j){
	while(container[i] >= 0)
		i = container[i];
	while(container[j] >= 0)
		j = container[j];

	if(container[j] < container[i]){ // j has more elements (number of elements are denoted as negative numbers)
		container[j] += container[i];
		container[i] = j;
	} 
	else{
		container[i] += container[j];
		container[j] = i;
	}
	--total;
}

int Disjoint_Union::find(const int & index){
	if(index >= container_size || index < 0)
		throw "Segmentation fault";
	int i = index;
	while(container[i] >= 0)
		i = container[i];
	return i;
}