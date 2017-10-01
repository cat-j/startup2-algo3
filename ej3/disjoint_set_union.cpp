// #include <cstring>

#include "disjoint_set_union.h"

Disjoint_Union::Disjoint_Union(const int & n) 
	: container_size(n)
	, total(n)
	, container(n, -1) {
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