#include "Building.h"

namespace BuildingNS
{
	const int POP_PER_HOUSE = 10;
};

class House : public Building
{
private:
public:
	House():Building(){setCapacity(0);}
};