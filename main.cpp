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
	unsigned int vertex_count = 0;
	std::vector<std::vector<unsigned int>> graph_list;
public:
	explicit ListGraph(unsigned int _vertex_count) : vertex_count(_vertex_count) {
		for (int i = 0; i < _vertex_count; ++i) {
			std::vector<unsigned int> edges;
			graph_list.push_back(edges);
		}
	}

	ListGraph(const ListGraph& other) {
		vertex_count = other.vertex_count;
		for (int i = 0; i < other.graph_list.size(); ++i) {
			for (int j = 0; j < other.graph_list[i].size(); ++j) {
				graph_list[i].push_back(other.graph_list[i][j]);
			}
		}
	}

	ListGraph& operator=(const ListGraph& other) {
		vertex_count = other.vertex_count;
		for (int i = 0; i < other.graph_list.size(); ++i) {
			for (int j = 0; j < other.graph_list[i].size(); ++j) {
				graph_list[i].push_back(other.graph_list[i][j]);
			}
		}
		return *this;
	}

	~ListGraph() = default;

	void AddEdge(unsigned int from, unsigned int to) override {
		graph_list[from].push_back(to);
	}

	unsigned int VerticesCount() override {
		return vertex_count;
	}

	void GetNextVertices(unsigned int vertex, std::vector<unsigned int> &vertices) override {
		for (unsigned int i = 0; i < graph_list[vertex].size(); ++i) {
			vertices.push_back(graph_list[vertex][i]);
		}
	}

	void GetPrevVertices(unsigned int vertex, std::vector<unsigned int> &vertices) override {
		for (int i = 0; i < graph_list.size(); ++i) {
			for (int j = 0; j < graph_list[i].size(); ++j) {
				if (graph_list[i][j] == vertex)
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
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Input number of vertices for ListGraph:";
	unsigned int vertex_count;
	std::cin >> vertex_count;
	auto* listGraph = new ListGraph(vertex_count);
	std::cout << "--------------------------------------" << std::endl;

	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Input number of vertices for MatrixGraph:";
	unsigned int vertex_count2;
	std::cin >> vertex_count2;
	auto* matrixGraph = new MatrixGraph(vertex_count2);
	std::cout << "--------------------------------------" << std::endl;

	delete listGraph;
	delete matrixGraph;
}
