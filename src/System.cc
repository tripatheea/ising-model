#include "System.h"

ising::System::System(unsigned width, unsigned height, float beta) : _width(width), _height(height), _beta(beta) {
	_current_lattice = ising::Lattice(width, height);
}

ising::Lattice ising::System::get_lattice() {
	return _current_lattice;
}

float ising::System::probability_of_lattice(ising::Lattice lattice) {
	return exp( - _beta * lattice.get_energy() );
}

ising::Lattice ising::System::new_random_lattice(ising::Lattice current_lattice) {
	// TODO: Maybe accept a parameter about how to select a new lattice.

	

	int lattice_width = current_lattice.get_width();
	int lattice_height = current_lattice.get_height();

	// Select a random x and y.
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> x_dist(0, (lattice_width - 1)); // distribution in range [0, width - 1]

	int x = x_dist(rng);

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> y_dist(0, (lattice_height - 1)); // distribution in range [0, height - 1]

	int y = y_dist(rng);

	// Take this coordinate (x, y) and flip the spin for just that vertex.
	//cout << "Flipping x = " << x << " y = " << y << endl;
	// new_lattice.get_vertex_at(x, y).flip_spin();

	// First, get all vertices.
	std::vector<std::vector<ising::Vertex>> all_vertices = current_lattice.get_vertices();

	// Take this coordinate (x, y) and flip the spin for just that vertex.


	// cout << all_vertices[x][y] << " vs. ";

	// Select the vertex to flip.
	all_vertices[x][y].flip_spin();

	// cout << all_vertices[x][y] << " and ";


	ising::Lattice new_lattice = ising::Lattice(all_vertices);

	// cout << new_lattice.get_vertices()[x][y] << endl;

	new_lattice.calculate_energy();


	return new_lattice;
}

bool ising::System::accept_new_lattice(ising::Lattice current_lattice, ising::Lattice new_lattice) {
	// Now, calculate the (non-normalized) probabilities of getting our current and new lattice.
	float p_current_lattice = probability_of_lattice(current_lattice);
	float p_new_lattice = probability_of_lattice(new_lattice);

	float alpha = p_new_lattice / p_current_lattice;

	if (alpha >= 1) {
		cout << "Moving to a new lattice as it has less energy: " << current_lattice.get_energy() << " vs. " << new_lattice.get_energy() << endl;
		return true;	// This is because, if alpha >= 1, P(new) >= P(current) so it's preferrable to continue with this transition.
	}
	else {
		// Accept wth probablity alpha.

		// To do that, generate a random number 1 to 1e25.
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> random_distribution(1, 1e25); // distribution in range [0, width - 1].
		float random_number = random_distribution(rng);

		cout << "Got the random number " << random_number << " vs. " << (alpha * 1e25) << endl;
		// Then, if the number is between 1 and int(alpha * 1e5), then accept the transition.
		if (random_number <= round(alpha * 1e25)) {
			cout << "Moving to a new lattice even though it has more energy: " << current_lattice.get_energy() << " vs. " << new_lattice.get_energy() << endl;
			return true;
		}
	}

	// cout << "Staying with the current lattice." << endl;

	return false;
}


void ising::System::step() {

	
	ising::Lattice current_lattice = ising::Lattice(_current_lattice);

	// Do a sweep with width x height new random lattices before proceeding so that all the spins have a chance to flip.

	ising::Lattice new_lattice = new_random_lattice(current_lattice);

	for (unsigned i=0; i < _width * _height; i++) {
		new_lattice = new_random_lattice(new_lattice);
	}
	

	
	// Sweep width * height times.
	for (unsigned i=0; i < _width * _height; i++) {
	// for (unsigned i=0; i < 0; i++) {

		// First, pick a random element by altering just one vertex of the lattice.
		new_lattice = new_random_lattice(new_lattice);
	}

	if (accept_new_lattice(current_lattice, new_lattice)) {
		_current_lattice = new_lattice;
		// cout << "Moving to new lattice." << endl;
	}
	else {
		// cout << "Staying with current lattice." << endl;
		// step();
	}
	

}
