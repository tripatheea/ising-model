#include "System.h"

ising::System::System(unsigned width, unsigned height, float beta) : _width(width), _height(height), _beta(beta) {
	_current_lattice = ising::Lattice(width, height);
	// std::cout << "initializing system: " << _current_lattice << std::endl;
}

ising::Lattice & ising::System::get_lattice() {
	// std::cout << "getting lattice: " << _current_lattice << std::endl;
	return _current_lattice;
}

float ising::System::probability_of_lattice(ising::Lattice lattice) {
	return exp( - _beta * lattice.get_energy() );
}

void ising::System::stabilize(int steps) {
	// cout << "Stabilizing" << endl;
	for (unsigned i=0; i < steps; i++) {
		step();
	}
	// cout << "I'm done stabilizing." << endl;
}

int ising::System::get_random_number(int lower_limit, int upper_limit) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> x_dist(lower_limit, upper_limit); 
	return x_dist(rng);
}


int ising::System::positive_modulo(int i, int n) {
	return (i % n + n) % n;
}

void ising::System::mc_update(int number_of_iterations) {
	float energy = 0.0;
	for (unsigned i=0; i < number_of_iterations; i++) {

		// if ((i % 10000) == 0)
		// 	cout << "Step #" << i << endl;
		
		step();
		energy += _current_lattice.get_energy();
		// cout << "Here it is " << _current_lattice.get_energy() << endl;
	}
	_current_lattice.set_energy(energy / number_of_iterations);

	// cout << "==========================" << endl;
}



void ising::System::step() {

	for (unsigned i=0; i < _width; i++) {
		for (unsigned j=0; j < _height; j++) {
			// Select a random x and y.
			int x = get_random_number(0, _width - 1);
			int y = get_random_number(0, _height - 1);

			Lattice lat = _current_lattice;

			// Get the spin of (x, y) vertex.
			Vertex current_vertex = lat.get_vertices()[x][y];

			// Calculate the total energy contribution by this vertex because of its interaction with its neighbors.
			float energy = 2 * current_vertex.get_spin() * (lat.get_vertices()[positive_modulo(x + 1, _width)][y].get_spin() + lat.get_vertices()[positive_modulo(x - 1, _width)][y].get_spin() + lat.get_vertices()[x][positive_modulo(y + 1, _height)].get_spin() + lat.get_vertices()[x][positive_modulo(y - 1, _height)].get_spin());

			// cout << "Old spin: " << lat.get_vertices()[x][y].get_spin() << endl;
			// cout << current_vertex.get_spin() << endl;

			if (energy < 0)
				current_vertex.flip_spin();
			else if (get_random_number(0, 10) < 10 * exp( - _beta * energy))
				current_vertex.flip_spin();

			// cout << current_vertex.get_spin() << endl;
			// lat.replace_vertex_at(x, y, Vertex(current_vertex));
			_current_lattice.replace_vertex_at(x, y, Vertex(current_vertex));

			// _current_lattice = ising::Lattice(lat);
			_current_lattice.calculate_energy();

			// cout << "Updated spin: " << _current_lattice.get_vertices()[x][y].get_spin() << endl;

		}
	}
}
