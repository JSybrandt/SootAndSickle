#include "Building.h"

namespace HouseNS
{
	const int HOUSING = 10;
};

class House : public Building
{
private:
public:
	House():Building(){setCapacity(0);}
};