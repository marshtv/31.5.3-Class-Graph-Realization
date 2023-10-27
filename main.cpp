#include <iostream>
#include <vector>

class IGraph {
public:
	IGraph() = default;

	IGraph(const IGraph& other) = default;

	IGraph& operator=(const IGraph& other) = default;

	~IGraph() = default;

	virtual void AddEdge(unsigned int from, unsigned int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро

	virtual unsigned int VerticesCount() = 0; // Метод должен считать текущее количество вершин

	// Для конкретной вершины метод выводит в вектор «вершины» все вершины, в которые можно дойти по ребру из данной
	virtual void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) = 0;

	// Для конкретной вершины метод выводит в вектор «вершины» все вершины, из которых можно дойти по ребру в данную
	virtual void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) = 0;
};

class ListGraph : virtual public IGraph {
private:
	std::vector<std::vector<unsigned int>> graph_lists;
public:
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

	~ListGraph() = default;

	void AddEdge(unsigned int from, unsigned int to) override {
		for (unsigned int i = 0; i < graph_lists.size(); ++i) {
			if (i == from) {
				graph_lists[i].push_back(to);
			}
		}
	}

	unsigned int VerticesCount() override {
		return (unsigned int)graph_lists.size();
	}

	void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) override {
		for (unsigned int i = 0; i < graph_lists[vertex].size(); ++i) {
			vertices.push_back(graph_lists[vertex][i]);
		}
	}

	void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) override {
		for (int i = 0; i < graph_lists.size(); ++i) {
			for (int j = 0; j < graph_lists[i].size(); ++j) {
				if (graph_lists[i][j] == vertex)
					vertices.push_back(i);
			}
		}
	}
};

class MatrixGraph final : virtual public IGraph {
private:
	unsigned int vertex_count = 0;
	int edges_count = -1;
	std::vector<std::vector<int>> matrix;
public:
	explicit MatrixGraph(unsigned int _vertex_count) : vertex_count(_vertex_count) {
		for (unsigned int i = 0; i < _vertex_count; ++i) {
			std::vector<int> _matrix;
			for (unsigned int j = 0; j < _vertex_count; ++j) {
				_matrix.push_back(-1);
			}
			matrix.push_back(_matrix);
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

	~MatrixGraph() {
		for (unsigned int i = matrix.size() - 1; i <= 0 ; --i) {
			for (unsigned int j = matrix[i].size() - 1; j <= 0; --j) {
				matrix[i].pop_back();
			}
			matrix.pop_back();
		}
	}

	void AddEdge(unsigned int from, unsigned int to) override {
		edges_count++;
		matrix[from][to] = edges_count;
	}

	unsigned int VerticesCount() override {
		return vertex_count;
	}

	void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) override {
		for (unsigned int i = 0; i < matrix[vertex].size(); ++i) {
			if (matrix[vertex][i] >= 0)
				vertices.push_back(i);
		}
	}

	void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) override {
		for (int i = 0; i < matrix.size(); ++i) {
			if (matrix[i][vertex] >= 0)
				vertices.push_back(i);
		}
	}
};

int main() {
	auto* listGraph = new ListGraph();


	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Input number of vertices for MatrixGraph:";
	unsigned int vertex_count;
	std::cin >> vertex_count;
	auto* matrixGraph = new MatrixGraph(vertex_count);


	delete listGraph;
	delete matrixGraph;
}
