#ifndef SERVER_GATEWAY_H
#define SERVER_GATEWAY_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

struct bufferevent;

namespace town {

class ServerGateway
{
public:
	ServerGateway();
	~ServerGateway();

	void DataDealCenter();
	void PushMsg(std::pair<bufferevent*, std::string>& bev_msg);

private:
	void PopMsg(std::pair<bufferevent*, std::string>& bev_msg);
	void DataForward(std::pair<bufferevent*, std::string>& bev_msg);
	void RegisterMsg(bufferevent* bev, const std::string& msg);
	void LoginMsg(bufferevent* bev, const std::string& msg);

private:
	std::queue<std::pair<bufferevent*, std::string>> m_queue;
	uint64_t m_write_index = 0;
	uint64_t m_read_index = 0;
	std::mutex m_lock;
	std::condition_variable m_cv;
};

} /* town */

#endif /* SERVER_GATEWAY_H */