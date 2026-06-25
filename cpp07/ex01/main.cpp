#include "iter.hpp"

int	main(void) {
	int	x[] = {1, 2, 3, 4, 5};
	float	f[] = {21.21f, 7.77f};
	const float	cf[] = {42.42f, 3.14f};
	::iter(x, sizeof(x) / sizeof(x[0]), ::doubleValue<int>); // instantiated function template
	::iter(f, sizeof(f) / sizeof(f[0]), ::doubleValue);
	::iter(const_cast<const int *>(x), sizeof(x) / sizeof(x[0]), ::printValue);//with explicit casting to const
	::iter(f, sizeof(f) / sizeof(f[0]), ::printValue<float>);
	::iter(cf, sizeof(cf) / sizeof(cf[0]), ::printValue);
}