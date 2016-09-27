#ifndef SYSTEM_H
#define SYSTEM_H


#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <string>

#include "Lattice.h"
#include "Vertex.h"


using namespace std;

namespace ising {
	class System {

		public:
			System(unsigned width, unsigned height, float beta);
			
			ising::Lattice get_lattice();

			void step();


			ising::Lattice new_random_lattice(ising::Lattice current_lattice);
			
		private:
			unsigned _width;
			unsigned _height;
			float _beta;
			
			ising::Lattice _current_lattice;
	};
}


#endif /* SYSTEM_H */