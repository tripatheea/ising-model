#include "Lattice.h"

ising::Lattice::Lattice() {
	cout << "Empty lattice constructor." << endl;
}

ising::Lattice::Lattice(unsigned width, unsigned height) : _width(width), _height(height), _energy(0.) {
	initialize_vertices();
}

ising::Lattice::Lattice(const ising::Lattice & source) : _width(source.get_width()), _height(source.get_height()), _energy(0.), _vertices(source.get_vertices()) {
}

/*
ising::Lattice::Lattice(ising::Lattice & source_lattice) : _width(source_lattice.get_width()), _height(source_lattice.get_height()) {

	// std::vector< std::vector<ising::Vertex> > vertices_for_new_lattice;

	// for (unsigned i=0; i < _width; i++) {
		
	// 	std::vector<ising::Vertex> row;

	// 	for (unsigned j=0; j < _height; j++) {
	// 		ising::Vertex v = source_lattice.get_vertex_at(i, j);
	// 		// row.push_back(v);
	// 	}

	// 	vertices_for_new_lattice.push_back(row);
	// }

	// _vertices = vertices_for_new_lattice;

	// calculate_energy();
}
*/			

unsigned ising::Lattice::get_width() {
	return _width;
}

std::vector<ising::Vertex> ising::Lattice::get_vertices() {
	return _vertices;
}

unsigned ising::Lattice::get_height() {
	return _height;
}

ising::Vertex & ising::Lattice::get_vertex_at(int x, int y) {
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
			
			spin = (dist6(rng) <= 5) ? -1 : +1;
			row.push_back(Vertex(spin));
		}

		_vertices.push_back(row);

		row.clear();
		row.shrink_to_fit();
	}

	calculate_energy();
}


std::string ising::Lattice::make_string() {
	std::ostringstream lattice_string;
	for (unsigned i=0; i < _width; i++) {
		for (unsigned j=0; j < _height; j++) {
			//std::cout << _vertices[i][j] << std::endl;
			string sigma = (_vertices[i][j].get_spin() == 1) ? "1" : "0";
			lattice_string << sigma;
		}
		lattice_string << "\n";
	}

//	std::cout << lattice_string;

	return lattice_string.str();
}


float ising::Lattice::get_energy() {
	return _energy;
}

void ising::Lattice::calculate_energy() {
	
	float J = 1.0;

	float E = 0;
	
	for (unsigned i=0; i < _width; i++) {
		for (unsigned j=0; j < _height; j++) {
			E -= J * _vertices[i][j].get_spin();
		}
	}

	_energy = E;
}

namespace ising {
	std::ostream& operator<< (std::ostream& os, Lattice& lattice) {
		os << lattice.make_string();
		return os;	
	}
}

