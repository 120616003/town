#ifndef SERVER_GATEWAY_H
#define SERVER_GATEWAY_H

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <map>

#include "user.pb.h"

struct bufferevent;

namespace town {

class MsgDeal;
class ServerGateway
{
public:
	ServerGateway();
	~ServerGateway();

	void MsgForwardCenter();
	void PushMsg(std::pair<bufferevent*, std::string>& bev_msg);

private:
	void PopMsg(std::pair<bufferevent*, std::string>& bev_msg);
	void MsgFactory();
	void RunFactoryMsg();

private:
	std::queue<std::pair<bufferevent*, std::string>> m_queue;
	std::map<common_enum::MESSAGE_TYPE, std::shared_ptr<MsgDeal>> m_eMsgDeal;
	uint64_t m_write_index = 0;
	uint64_t m_read_index = 0;
	std::mutex m_lock;
	std::condition_variable m_cv;
};

} /* town */

#endif /* SERVER_GATEWAY_H */