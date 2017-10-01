#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H

class Disjoint_Union
{
public:
	Disjoint_Union(const int & n);
	int create();
	void merge(int i , int j);
	int find(const int & i);
	int size(){
		return container_size;
	}
	int numberOfSets(){
		return total;
	}
private:
	int * container;
	int container_size;
	int allocated_size;
	int total;
};

#endif // DISJOINT_SET_UNION_H
