#include <iostream>
#include <vector>

class IGraph {
public:
	virtual ~IGraph() = default;
	IGraph() = default;
	IGraph(const IGraph& _oth) = default;
	IGraph& operator=(const IGraph& other) = default;
	virtual void AddEdge(unsigned int from, unsigned int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
	virtual unsigned int VerticesCount() const = 0; // Метод должен считать текущее количество вершин
	// Для конкретной вершины метод выводит в вектор «вершины» все вершины, в которые можно дойти по ребру из данной
	virtual void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) const = 0;
	// Для конкретной вершины метод выводит в вектор «вершины» все вершины, из которых можно дойти по ребру в данную
	virtual void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) const = 0;
};

class ListGraph : virtual public IGraph {
private:
	std::vector<unsigned int> vertexes{};
	std::vector<unsigned int> edges{};
	std::vector<std::vector<unsigned int>> graph_lists{};
public:
	~ListGraph() override = default;
	ListGraph() = default;
	ListGraph(const ListGraph& other) {

	}
	ListGraph& operator=(const ListGraph& other) {

	}
	void AddEdge(unsigned int from, unsigned int to) override {

	}
	virtual int VerticesCount() {

	}
	virtual void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) {

	}
	virtual void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) {

	}
};

class MatrixGraph : virtual public IGraph {
private:

public:

};

int main() {

}
