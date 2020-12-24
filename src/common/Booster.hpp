#ifndef BOOSTER_H
#define BOOSTER_H

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include <regex>

namespace town {

class Booster
{
public:
	static std::string GetUUID()
	{
		boost::uuids::random_generator rgen;
		return std::regex_replace(boost::uuids::to_string(rgen()), std::regex(R"(-)"), "");
	}
};

}

#endif