#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H

#include <vector>

class Disjoint_Union
{
public:
	Disjoint_Union(const int & n);
	void merge(int i , int j);
	int find(const int & i);
	int size(){
		return container_size;
	}
	int numberOfSets(){
		return total;
	}
private:
	int container_size;
	int total;
	std::vector<int> container;
};

#endif // DISJOINT_SET_UNION_H
