#ifndef SYSTEM_H
#define SYSTEM_H


#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <string>
#include <math.h>
#include <sstream>
#include <fstream>

#include "Lattice.h"
#include "Vertex.h"


using namespace std;

namespace ising {
	class System {

		public:
			System(unsigned width, unsigned height, float beta);
			
			ising::Lattice & get_lattice();

			void stabilize(int steps);
			void step();

			int get_random_number(int lower_limit, int upper_limit);

			void mc_update(int number_of_iterations);
			
			int positive_modulo(int i, int n);
			
		private:
			unsigned _width;
			unsigned _height;
			float _beta;
			
			ising::Lattice _current_lattice;

			float probability_of_lattice(ising::Lattice lattice);

			bool accept_new_lattice(ising::Lattice current_lattice, ising::Lattice new_lattice);
			
	};
}


#endif /* SYSTEM_H */
