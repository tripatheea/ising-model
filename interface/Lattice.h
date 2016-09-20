#ifndef LATTICE_H
#define LATTICE_H


#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <string>


#include "Vertex.h"

namespace ising {
	class Lattice {

		public:
			Lattice(unsigned width, unsigned height, float beta);
			
			void step();
			ising::Vertex get_vertex_at(int x, int y);
			const std::string make_string() const;
						
			friend std::ostream& operator<< (std::ostream&, const Lattice&);

		private:
			std::vector< std::vector<ising::Vertex> > _vertices;
			const unsigned _width;
			const unsigned _height;
			const float _beta;

			void initialize_vertices();
	};
}


#endif /* LATTICE_H */
