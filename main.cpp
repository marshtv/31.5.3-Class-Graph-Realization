#include <iostream>
#include <vector>

class IGraph {
public:
	virtual ~IGraph() = default;

	IGraph() = default;

	IGraph(const IGraph& other) = default;

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
	std::vector<std::vector<unsigned int>> graph_lists{};
public:
	~ListGraph() override = default;

	ListGraph() = default;

	ListGraph(const ListGraph& other) {
		for (int i = 0; i < other.graph_lists.size(); ++i) {
			for (int j = 0; j < other.graph_lists[i].size(); ++j) {
				graph_lists[i].push_back(other.graph_lists[i][j]);
			}
		}
	}

	ListGraph& operator=(const ListGraph& other) {
		for (int i = 0; i < other.graph_lists.size(); ++i) {
			for (int j = 0; j < other.graph_lists[i].size(); ++j) {
				graph_lists[i].push_back(other.graph_lists[i][j]);
			}
		}
		return *this;
	}

	void AddEdge(unsigned int from, unsigned int to) override {
		for (unsigned int i = 0; i < graph_lists.size(); ++i) {
			if (i == from) {
				graph_lists[i].push_back(to);
			}
		}
	}

	virtual unsigned int VerticesCount() {
		return (unsigned int)graph_lists.size();
	}

	virtual void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) {
		for (unsigned int i = 0; i < graph_lists[vertex].size(); ++i) {
			vertices.push_back(graph_lists[vertex][i]);
		}
	}

	virtual void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) {
		for (int i = 0; i < graph_lists.size(); ++i) {
			for (int j = 0; j < graph_lists[i].size(); ++j) {
				if (graph_lists[i][j] == vertex)
					vertices.push_back(i);
			}
		}
	}
};

class MatrixGraph : virtual public IGraph {
private:
	unsigned int vertex_count = 0;
	int edges_count = -1;
	std::vector<std::vector<int>> matrix{};
public:
	~MatrixGraph() override = default;

	MatrixGraph(unsigned int _vertex_count) : vertex_count(_vertex_count) {
		for (int i = 0; i < vertex_count; ++i) {
			for (int j = 0; j < vertex_count; ++j) {
				matrix[i].push_back(-1);
			}
		}
	}

	MatrixGraph(const MatrixGraph& other) {
		vertex_count = other.vertex_count;
		edges_count = other.edges_count;
		for (int i = 0; i < other.matrix.size(); ++i) {
			for (int j = 0; j < other.matrix[i].size(); ++j) {
				matrix[i].push_back(other.matrix[i][j]);
			}
		}
	}

	MatrixGraph& operator=(const MatrixGraph& other) {
		vertex_count = other.vertex_count;
		edges_count = other.edges_count;
		for (int i = 0; i < other.matrix.size(); ++i) {
			for (int j = 0; j < other.matrix[i].size(); ++j) {
				matrix[i].push_back(other.matrix[i][j]);
			}
		}
		return *this;
	}

	void AddEdge(unsigned int from, unsigned int to) override {
		edges_count++;
		matrix[from][to] = edges_count;
	}

	virtual unsigned int VerticesCount() {
		return vertex_count;
	}

	virtual void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) {
		for (unsigned int i = 0; i < matrix[vertex].size(); ++i) {
			if (matrix[vertex][i] >= 0)
				vertices.push_back(i);
		}
	}

	virtual void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) {
		for (int i = 0; i < matrix.size(); ++i) {
			if (matrix[i][vertex] >= 0)
				vertices.push_back(i);
		}
	}
};

int main() {

}
