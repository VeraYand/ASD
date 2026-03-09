#pragma once
#include <stdexcept>

//перенести в ветку algorithms в проект Algorithms

class DSU {
	int *_parent, * _rank;
	size_t _size;
public:
	inline DSU(size_t size);
	inline ~DSU();
	inline void dsu_union(int x, int y);
	inline int find(int x);
	inline int find_rec(int x);
};

inline DSU::DSU(size_t size) : _size(size) {
	if (size == 0) {
		throw std::logic_error("Size cannot be zero");
	}

	_parent = new int[size];
	_rank = new int[size];

	for (size_t i = 0; i < size; ++i) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

inline DSU::~DSU() {
	delete[] _parent;
	delete[] _rank;
}

inline void DSU::dsu_union(int x, int y) {
	if (x >= _size || y >= _size || x < 0 || y < 0) {
		throw std::logic_error("Error!");
	}
	if (x == y) return;

	int parent_x = find(x);
	int parent_y = find(y);

	if (parent_x == parent_y) return; 

	if (_rank[parent_x] > _rank[parent_y]) {
		_parent[parent_y] = parent_x;
	}
	else if (_rank[parent_x] < _rank[parent_y]) {
		_parent[parent_x] = parent_y;
	}
	else { 
		_parent[parent_y] = parent_x;  
		_rank[parent_x]++;             
	}

}

inline int DSU::find(int x) {
	if (x >= _size || x < 0) {
		throw std::logic_error("Error!");
	}
	int root = x;
	while (root != _parent[root]) {
		root = _parent[root];
	}

	while (x != root) {
		int next = _parent[x];
		_parent[x] = root;
		x = next;
	}

	return root;
}

inline int DSU::find_rec(int x) {
	if (x >= _size || x < 0) {
		throw std::logic_error("Error!");
	}
	if (_parent[x] == x) {
		return x;
	}
	_parent[x] = find_rec(_parent[x]);
}
