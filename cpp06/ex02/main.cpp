#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Functions.hpp"
#include <cstdlib>
#include <ctime>

int	main(void) {
	std::srand(std::time(NULL));
	Base	*sample = generate();
	Base	&sampleRef = *sample;
	identify(sample);// as pointer
	identify(sampleRef);// as reference
	delete sample;
}
