// Includes
#include "LightBulb/IO/Exporter/JSONStringElement.hpp"

namespace LightBulb
{
	std::string JSONStringElement::toString()
	{
		return "\"" + content + "\"";
	}

	JSONStringElement::JSONStringElement(std::string content_)
	{
		content = content_;
	}
}