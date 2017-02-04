// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp"

void LightBulb::AbstractMutationAlgorithm::setZigguratGenerator(ZigguratGenerator& newZigguratGenerator)
{
	zigguratGenerator = &newZigguratGenerator;
}
