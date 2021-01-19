#ifndef BOOSTER_H
#define BOOSTER_H

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/asio.hpp"
#include "boost/crc.hpp"
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
        boost::asio::deadline_timer timer(io, boost::posix_time::microseconds(seconds * 1000 * 1000 +  milliseconds * 1000 + microseconds));
        timer.wait();
    }

    static std::size_t Crc(uint8_t* data, std::size_t data_len)
    {
        boost::crc_ccitt_false_t crc_ccitt;
        crc_ccitt.process_bytes(data, data_len);
        return crc_ccitt.checksum();
    }
};

}

#endif