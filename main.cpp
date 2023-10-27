#include <iostream>
#include <vector>

class IGraph {
public:
	IGraph() = default;

	IGraph(const IGraph& other) = default;

	IGraph& operator=(const IGraph& other) = default;

	~IGraph() = default;

	virtual void AddEdge(unsigned int from, unsigned int to) = 0;

	virtual unsigned int VerticesCount() = 0;

	virtual void GetNextVertices(unsigned int vertex, std::vector<unsigned int>& vertices) = 0;

	virtual void GetPrevVertices(unsigned int vertex, std::vector<unsigned int>& vertices) = 0;
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

	void GetNextVertices(unsigned int vertex, std::vector<unsigned int>& vertices) override {
		for (unsigned int i = 0; i < graph_list[vertex].size(); ++i) {
			vertices.push_back(graph_list[vertex][i]);
		}
	}

	void GetPrevVertices(unsigned int vertex, std::vector<unsigned int>& vertices) override {
		for (int i = 0; i < graph_list.size(); ++i) {
			for (int j = 0; j < graph_list[i].size(); ++j) {
				if (graph_list[i][j] == vertex)
					vertices.push_back(i);
			}
		}
	}
};

class MatrixGraph : virtual public IGraph {
private:
	unsigned int vertex_count = 0;
	int edges_count = -1;
	std::vector<std::vector<int>> matrix;
public:
	explicit MatrixGraph(unsigned int _vertex_count) : vertex_count(_vertex_count) {
		for (unsigned int i = 0; i < _vertex_count; ++i) {
			std::vector<int> _matrix;
			for (unsigned int j = 0; j < _vertex_count; ++j) {
				_matrix.push_back(edges_count);
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

	~MatrixGraph() = default;

	void AddEdge(unsigned int from, unsigned int to) override {
		edges_count++;
		matrix[from][to] = edges_count;
	}

	unsigned int VerticesCount() override {
		return vertex_count;
	}

	void GetNextVertices(unsigned int vertex, std::vector<unsigned int>& vertices) override {
		for (unsigned int i = 0; i < matrix[vertex].size(); ++i) {
			if (matrix[vertex][i] >= 0)
				vertices.push_back(i);
		}
	}

	void GetPrevVertices(unsigned int vertex, std::vector<unsigned int>& vertices) override {
		for (int i = 0; i < matrix.size(); ++i) {
			if (matrix[i][vertex] >= 0)
				vertices.push_back(i);
		}
	}
};

void inputVertices(int& from, int& to) {
	std::cout << "For add edge to ListGraph,";
	std::cout << "Input numbers of two vertices(from, to) or \"-1\" for finish input:" << std::endl;
	std::cout << "From:";
	std::cin >> from;
	std::cout << "To:";
	std::cin >> to;
}

void addingEdges(IGraph* _graph) {
	int _from, _to;
	inputVertices(_from, _to);
	while (_from != -1 && _to != -1) {
		while (_from >= _graph->VerticesCount() || _to >= _graph->VerticesCount()) {
			std::cout << "!!!!---INCORRECT INPUT---!!!!" << std::endl;
			inputVertices(_from, _to);
		}
		if (_from != -1 && _to != -1) {
			_graph->AddEdge(_from, _to);
			std::cout << "--------------------------------------" << std::endl;
			inputVertices(_from, _to);
		} else {
			std::cout << "-------EXIT-------" << std::endl;
			break;
		}
	}
}

void print_next_vertices(unsigned  int _vertex, IGraph* _graph) {
	std::vector<unsigned int> _vertices;
	_graph->GetNextVertices(_vertex, _vertices);
	for (int i = 0; i < _vertices.size(); ++i) {
		std::cout << _vertices[i] << " ";
	}
	std::cout << std::endl;
}

void print_prev_vertices(unsigned  int _vertex, IGraph* _graph) {
	std::vector<unsigned int> _vertices;
	_graph->GetPrevVertices(_vertex, _vertices);
	for (int i = 0; i < _vertices.size(); ++i) {
		std::cout << _vertices[i] << ", ";
	}
	std::cout << std::endl;
}

void search_next_vertices(IGraph* _graph) {
	int _vertex;
	while(true) {
		std::cout << "Input vertex number (0 - " << _graph->VerticesCount() - 1 << ") or \"-1\" for exit search:";
		std::cin >> _vertex;
		if (_vertex == -1)
			break;
		print_next_vertices(_vertex, _graph);
	}
	std::cout << "-----------End of searching-----------" << std::endl;
}

void search_prev_vertices(IGraph* _graph) {
	int _vertex;
	while(true) {
		std::cout << "Input vertex number (0 - " << _graph->VerticesCount() - 1 << ") or \"-1\" for exit search:";
		std::cin >> _vertex;
		if (_vertex == -1)
			break;
		print_prev_vertices(_vertex, _graph);
	}
	std::cout << "-----------End of searching-----------" << std::endl;
}

int select_search(IGraph* _graph) {
	int command;
	std::cout << R"(Select searching type (1 - "next", 2 - "prev", 3 - "exit"):)";
	std::cin >> command;
	while (command < 1 || command > 3) {
		std::cout << "!!!!---INCORRECT INPUT---!!!!" << std::endl;
		std::cout << R"(Select searching type (1 - "next", 2 - "prev", 3 - "exit"):)";
		std::cin >> command;
	}
	return command;
}

void search_process(IGraph* _graph) {
	int command = select_search(_graph);
	while (command != 3) {
		switch (command) {
			default:
			case 1:
				search_next_vertices(_graph);
				break;
			case 2:
				search_prev_vertices(_graph);
				break;
		}
		command = select_search(_graph);
	}
}

int main() {
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Input number of vertices for ListGraph:";
	unsigned int vertex_count;
	std::cin >> vertex_count;
	auto* listGraph = new ListGraph(vertex_count);
	std::cout << "--------------------------------------" << std::endl;
	addingEdges(listGraph);
	std::cout << "All edges added. " << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	search_process(listGraph);

	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Input number of vertices for MatrixGraph:";
	std::cin >> vertex_count;
	auto* matrixGraph = new MatrixGraph(vertex_count);
	std::cout << "--------------------------------------" << std::endl;
	addingEdges(matrixGraph);
	std::cout << "All edges added. " << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	search_process(matrixGraph);

	delete listGraph;
	delete matrixGraph;
}
