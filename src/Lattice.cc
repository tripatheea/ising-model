#include "Lattice.h"

ising::Lattice::Lattice() {
	// cout << "Empty lattice constructor." << endl;
}

ising::Lattice::Lattice(unsigned width, unsigned height) : _width(width), _height(height), _energy(0.) {
	initialize_vertices();
}

ising::Lattice::Lattice(const ising::Lattice & source) : _width(source.get_width()), _height(source.get_height()), _energy(source.get_energy()), _vertices(source.get_vertices()) {

}

ising::Lattice::Lattice(std::vector<std::vector<ising::Vertex>> & source_vertices) : _width(source_vertices.size()), _height(source_vertices[0].size()), _vertices(source_vertices){
	calculate_energy();
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

void ising::Lattice::calculate_energy() {
	
	float J = 1.0;

	float E = 0;
	
	for (unsigned x=0; x < _width; x++) {
		for (unsigned y=0; y < _height; y++) {
			
			// For this vertex, we need to loop through all its neighbors.

			float current_vertex_E = 0;
			int sigma_x = _vertices[x][y].get_spin();
						
			if (x > 0 and x < (_width - 1)) {
				
				// The 0.5 factor is because we count each pariwise contribution twice.

				// current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin();
				// current_vertex_E += 0.5 * J * sigma_x * _vertices[x + 1][y].get_spin();
				
				if (y > 0 and y < (_height - 1)) {
					// Not on any boundary.
					
					current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y - 1].get_spin();
					current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y + 1].get_spin();

					current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin();
					current_vertex_E += 0.5 * J * sigma_x * _vertices[x + 1][y].get_spin();
				}
				else {
					// On a horizontal boundary so need to use periodic boundary conditions.
					if (y == 0) {
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y + 1].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][_height - 1].get_spin();		// Periodic Boundary Condition.
					}
					else if (y == (_height - 1)) {
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y - 1].get_spin(); 
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][0].get_spin();		// Periodic Boundary Condition.
					}

					current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin();
					current_vertex_E += 0.5 * J * sigma_x * _vertices[x + 1][y].get_spin();
				}
			}
			else {
				// On a vertical boundary.

				if (x == 0) {	// Vertical + Horizontal Boundary. Left most strip.
					
					if (y == 0) { // Upper left corner.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x + 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y + 1].get_spin();	

						// Periodic Boundary Condition.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[_width - 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][_height - 1].get_spin();
					}
					else if (y == (_height - 1)) { // Lower left corner.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x + 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y - 1].get_spin();	

						// Periodic Boundary Condition.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[_width - 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][0].get_spin();		
					}
					else {
						// Left boundary but not on a corner.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x + 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y - 1].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y + 1].get_spin();

						// PBC.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[_width - 1][y].get_spin();
					}
				}
				else if (x == (_width - 1)) {	 // Vertical + Horizontal Boundary. Right most strip.


					// current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin(); 
					// current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin(); 
					
					// // Periodic Boundary Condition.
					// current_vertex_E += 0.5 * J * sigma_x * _vertices[0][y].get_spin();

					if (y == 0) { // Upper right corner.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y + 1].get_spin();	

						// Periodic Boundary Condition.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[0][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][_height - 1].get_spin();
					}
					else if (y == (_height - 1)) { // Lower right corner.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y - 1].get_spin();	

						// Periodic Boundary Condition.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[0][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][0].get_spin();		
					}
					else {
						// Right boundary but not on a corner.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x - 1][y].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y - 1].get_spin();
						current_vertex_E += 0.5 * J * sigma_x * _vertices[x][y + 1].get_spin();

						// PBC.
						current_vertex_E += 0.5 * J * sigma_x * _vertices[0][y].get_spin();
					}

				}
			}

			E += current_vertex_E;
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

