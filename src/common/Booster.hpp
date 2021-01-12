#ifndef BOOSTER_H
#define BOOSTER_H

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/asio.hpp"
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

    static void Timer(int64_t seconds, int64_t milliseconds, int64_t microseconds)
    {
        boost::asio::io_service io;
        boost::asio::deadline_timer timer1(io, boost::posix_time::seconds(seconds));
        boost::asio::deadline_timer timer2(io, boost::posix_time::microseconds(microseconds + milliseconds * 1000));
        timer1.wait();
        timer2.wait();
    }
};

}

#endif