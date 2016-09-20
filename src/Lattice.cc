#include "Lattice.h"


ising::Lattice::Lattice(unsigned width, unsigned height, float beta) : _width(width), _height(height), _beta(beta) {
	initialize_vertices();
}
			
void ising::Lattice::step() {
}

ising::Vertex ising::Lattice::get_vertex_at(int x, int y) {
	return _vertices[x][y];
}

void ising::Lattice::initialize_vertices() {

	for (unsigned i=0; i < _width; i++) {
		std::vector<ising::Vertex> row;
		for (unsigned j=0; j < _height; j++) {
			// Generate a random spin (0 or 1).
			int spin;			
	
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0,9); // distribution in range [1, 6]
			
			spin = (dist6(rng) <= 5) ? 0 : 1;
			row.push_back(Vertex(spin));
		}

		_vertices.push_back(row);

		row.clear();
		row.shrink_to_fit();
	}
}


const std::string ising::Lattice::make_string() const {
	std::ostringstream lattice_string;
	for (unsigned i=0; i < _width; i++) {
		for (unsigned j=0; j < _height; j++) {
			//std::cout << _vertices[i][j] << std::endl;
			lattice_string << _vertices[i][j];
		}
		lattice_string << "\n";
	}

//	std::cout << lattice_string;

	return lattice_string.str();
}

namespace ising {
	std::ostream& operator<< (std::ostream& os, const Lattice& lattice) {
		os << lattice.make_string();
		return os;	
	}
}

