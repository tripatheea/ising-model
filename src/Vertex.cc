#include "Vertex.h"

ising::Vertex::Vertex(int spin) {
	_spin = spin;
}

const int ising::Vertex::get_spin() const {
	return _spin;
}

void ising::Vertex::flip_spin() {
	_spin = int( ! bool(_spin) );
}

std::string ising::Vertex::make_string() {
	return std::to_string(get_spin());	
}


namespace ising {
	std::ostream& operator<< (std::ostream& os, const Vertex& vertex) {
		os << std::to_string(vertex.get_spin());
		return os;	
	}
}

