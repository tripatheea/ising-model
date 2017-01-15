#include <iostream>


#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iterator>
#include <iomanip>
#include <limits>
#include <chrono>
#include <math.h>


using namespace std;

int positive_modulo(int i, int n) {
	return (i % n + n) % n;
}

void mc_move(vector<vector<int>> & config, float beta) {
	int N = config.size();


	for (unsigned i=0; i < N; i++) {
		for (unsigned j=0; j < N; j++) {
			int a = rand() % N;
			int b = rand() % N;			
			
			int neighbors = config[ positive_modulo(a + 1, N) ][b] + config[a][ positive_modulo(b + 1, N) ] + config[ positive_modulo(a - 1, N) ][b] + config[a][ positive_modulo(b - 1, N) ];
			float cost = 2 * config[a][b] * neighbors;

			if (cost < 0.) {
				config[a][b] *= -1;
			}
			else if ( (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) < exp( - cost * beta ) ) {
				config[a][b] *= -1;
			}

		}
	}
}


float calculate_energy(vector<vector<int>> config) {
	float energy = 0.;


	int N = config.size();

	for (unsigned i=0; i < config.size(); i++) {
		for (unsigned j=0; j < config[0].size(); j++) {
			int current_state = config[i][j];

			int neighbors = config[ (i + 1) % N ][j] + config[i][ (j + 1) % N ] + config[ (i - 1) % N ][j] + config[i][ (j - 1) % N ];
			energy += - neighbors * current_state;
		}
	}
}

void write_to_file(vector<vector<int>> state) {
	// ofstream output_file("data/lattice.dat", ios::out | ios::app);
	ofstream output_file("data/lattice.dat", ios::out);

	for (unsigned x=0; x < state.size(); x++) {
		for (unsigned y=0; y < state[x].size(); y++) {
			if (state[x][y] > 0)
				output_file << " " << to_string(state[x][y]) + "\t";
			else
				output_file << to_string(state[x][y]) + "\t";
		}
		output_file << "\n";
	}

	// output_file << "===========================================" << endl;
}



int main(int argc, char * argv[]) {

	ofstream output_file("data/lattice.dat", ios::out);

	int N = 3;
	int nt = 128;

	vector<float> temps;
	for (unsigned i=0; i <= nt; i++) {
		temps.push_back( 1.0 + i * ( 4.0 - 1.0 ) / nt );
	}

	// Initialize energies.
	// vector<vector<float>> all_energies;
	// for (unsigned i=0; i < N; i++) {
		
	// 	vector<float> all_energies_row;

	// 	for (unsigned j=0; j < N; j++) {
	// 		all_energies_row.push_back(0.);
	// 	}

	// 	all_energies.push_back(all_energies_row);
	// }





	vector<float> all_energies;

	for (unsigned i=0; i < temps.size(); i++) {
		all_energies.push_back(0.0);
	}

	for (unsigned i=0; i < temps.size(); i++) {
		float temp = temps[i];

		float E1 = 0.;
		float E2 = 0.;

		// Get an initial state first.
		vector<vector<int>> state;
		for (unsigned i=0; i < N; i++) {
			vector<int> state_row;
			for (unsigned j=0; j < N; j++) {
				int random_int = (rand() % ((1 - 0) + 1) + 0);
				state_row.push_back( 2 * random_int - 1 );
			}
			state.push_back(state_row);
		}
		
		write_to_file(state);

		// Now, equilibriate the system.
		int eq_steps = 2000;
		for (unsigned j=0; j < eq_steps; j++) {
			mc_move(state, 1.0 / temp);

			// write_to_file(state);

			// stringstream plotting_command;
			// plotting_command << "python python/plot.py " << N << " " << N << " " << j << " " << fixed << setprecision(2) << calculate_energy(state);
			// system( plotting_command.str().c_str() );
		}


		// Now, do the main calculations.
		int mc_steps = 2000;
		for (unsigned k=0; k < mc_steps; k++) {
			mc_move(state, 1.0 / temp);

			float energy = calculate_energy(state);

			E1 += energy;
			E2 += energy * energy;

			all_energies[i] = E1 / (mc_steps * N * N);

		}


	}

	ofstream energies_output("data/energies.dat", ios::out);

	for (unsigned a=0; a < all_energies.size(); a++) {
		energies_output << temps[a] << "\t" << all_energies[a] << endl;
	} 

	return 1;
}
