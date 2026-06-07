#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
//#include <cstdint> // c++11style - forbidden
#include <stdint.h> //c-style
#include "Data.hpp"

class	Serializer {
	private:
		Serializer();
		Serializer(const Serializer &An);
		Serializer	&operator=(const Serializer &An);
		~Serializer();
	public:
		static uintptr_t	serialize(Data *ptr);
		static Data		*deserialize(uintptr_t raw);
};

#endif
