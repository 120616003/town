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
        boost::crc_ccitt_type crc_ccitt;
        crc_ccitt.process_bytes(data, data_len);
        return crc_ccitt.checksum();
    }

    static std::wstring StringToWString(const std::string& src)
    {
        std::setlocale(LC_CTYPE, "zh_CN");

        size_t const wcs_len = mbstowcs(NULL, src.c_str(), 0);
        std::vector<wchar_t> tmp(wcs_len + 1);
        mbstowcs(&tmp[0], src.c_str(), src.size());

        std::wstring dest(tmp.begin(), tmp.end() - 1);

        return dest;
    }

    static std::string WStringToString(std::wstring const & src)
    {
        std::setlocale(LC_CTYPE, "");

        size_t const mbs_len = wcstombs(NULL, src.c_str(), 0);
        std::vector<char> tmp(mbs_len + 1);
        wcstombs(&tmp[0], src.c_str(), tmp.size());

        std::string dest(tmp.begin(), tmp.end() - 1);

        return dest;
    }

};

}

#endif