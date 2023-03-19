#include "constants.h"

double randd()
{
	static std::uniform_real_distribution<double> d(0.0, 1.0);
	static std::mt19937 gen;
	return d(gen);
}

double randd(double mn, double mx)
{
	return mn + ((mx - mn) * randd());
}
