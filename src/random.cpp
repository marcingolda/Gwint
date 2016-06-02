#include "random.h"

Random::Random(double _d)
{
    d = _d;
	
	for (int i = 0; i < 1000; ++i) {
		rand();
	}
}


double Random::rand()
{
	double A = 16807.0;
	double M = 2147483647.0;
    double temp = A * d;

    d = temp - M * (static_cast<int> (temp / M));


    return (d / M);
}
