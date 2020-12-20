#ifndef BOOSTER_H
#define BOOSTER_H

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

namespace town {

class Booster
{
public:
	static std::string GetUUID6()
	{
		boost::uuids::random_generator rgen;
		boost::uuids::uuid u6 = rgen();
		std::string strUuid = boost::uuids::to_string(u6);
		return strUuid;
	}
};

}

#endif