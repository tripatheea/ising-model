#include "Lattice.h"

ising::Lattice::Lattice() {
	// cout << "Empty lattice constructor." << endl;
}

ising::Lattice::Lattice(unsigned width, unsigned height) : _width(width), _height(height) {
	initialize_vertices();
	calculate_energy();

	// cout << "The head vertex is: " << _vertices[0][0] << endl;
}

ising::Lattice::Lattice(const ising::Lattice & source) : _width(source.get_width()), _height(source.get_height()), _energy(source.get_energy()), _vertices(source.get_vertices()) {

}

ising::Lattice::Lattice(std::vector<std::vector<ising::Vertex>> & source_vertices) : _width(source_vertices.size()), _height(source_vertices[0].size()), _vertices(source_vertices){
	calculate_energy();
}


unsigned ising::Lattice::get_width() const {
	return _width;
}

std::vector< std::vector<ising::Vertex> > ising::Lattice::get_vertices() const {
	return _vertices;
}

unsigned ising::Lattice::get_height() const {
	return _height;
}

const ising::Vertex & ising::Lattice::get_vertex_at(int x, int y) const {
	return _vertices[x][y];
}

void ising::Lattice::replace_vertex_at(int x, int y, Vertex v) {
	_vertices[x][y] = v;
}


int ising::Lattice::get_random_number(int lower_limit, int upper_limit) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> x_dist(lower_limit, upper_limit); 
	return x_dist(rng);
}


void ising::Lattice::initialize_vertices() {

	for (unsigned i=0; i < _width; i++) {
		std::vector<ising::Vertex> row;
		for (unsigned j=0; j < _height; j++) {
			// Generate a random spin (0 or 1).
			int spin = 2 * get_random_number(0, 1) - 1;
			row.push_back(Vertex(spin));
		}

		_vertices.push_back(row);

		row.clear();
		row.shrink_to_fit();
	}
}


std::string ising::Lattice::make_string() const {
	std::ostringstream lattice_string;
	for (unsigned i=0; i < _width; i++) {
		for (unsigned j=0; j < _height; j++) {
			//std::cout << _vertices[i][j] << std::endl;
			// string sigma = (_vertices[i][j].get_spin() == 1) ? "1" : "0";
			lattice_string << _vertices[i][j].make_string();
		}
		lattice_string << "\n";
	}

//	std::cout << lattice_string;

	return lattice_string.str();
}


float ising::Lattice::get_energy() const {
	return _energy;
}

void ising::Lattice::set_energy(float energy) {
	_energy = energy;
}

void ising::Lattice::calculate_energy() {
	
	float J = 1.0;

	float E = 0;
	
	for (unsigned x=0; x < _width; x++) {
		for (unsigned y=0; y < _height; y++) {
			
			// For this vertex, we need to loop through all its neighbors.
			float current_spin = _vertices[x][y].get_spin();

			// cout << current_spin << endl;

			float neighbors = J * (_vertices[(x + 1) % _width][y].get_spin() + _vertices[(x - 1) % _width][y].get_spin() + _vertices[x][(y + 1) % _height].get_spin() + _vertices[x][(y - 1) % _height].get_spin());
			
			E += - neighbors * current_spin;
		}
	}

	_energy = 0.25 * E / (_width * _height);

	// cout << "E = " << _energy << endl;
}

namespace ising {
	std::ostream& operator<< (std::ostream& os, Lattice& lattice) {
		os << lattice.make_string();
		return os;	
	}
}

