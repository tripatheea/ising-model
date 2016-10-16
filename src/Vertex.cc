#include "Vertex.h"

ising::Vertex::Vertex(int spin) : _spin(spin) {
}

ising::Vertex::Vertex(const ising::Vertex & source_vertex) : _spin(source_vertex.get_spin()) {
	// _spin = source_vertex.get_spin();
}



const int ising::Vertex::get_spin() const {
	return _spin;
}

void ising::Vertex::flip_spin() {
	// _spin = int( ! bool(_spin) );
	if (_spin == -1) {
		_spin = 1;
	}
	else if (_spin == 1) {
		_spin = -1;
	}
}

std::string ising::Vertex::make_string() const {
	return (get_spin() == -1) ? "0" : "1";
}


namespace ising {
	std::ostream& operator<< (std::ostream& os,  Vertex& vertex) {
		os << vertex.make_string();
		return os;	
	}
}

