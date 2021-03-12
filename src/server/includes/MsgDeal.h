#ifndef MSG_DEAL_H
#define MSG_DEAL_H

#include "ServerCommon.h"
#include "MysqlOptHandleInfc.h"
#include "ServerEvent.h"
#include "SecureQueue.hpp"

namespace town {

class MsgDeal
{
public:
	MsgDeal() {}
	virtual ~MsgDeal() {}
	virtual void MsgDealCenter(std::unique_ptr<MSG_DATA>& bev_msg) = 0;

	void RegisterDBLogicHandle(MysqlOptHandleInfcPtr pMysqlOptHandleInfc)
	{
		m_pMysqlOptHandleInfc = pMysqlOptHandleInfc;
	}

	MysqlOptHandleInfcPtr GetMysqlOpt()
	{
		return m_pMysqlOptHandleInfc;
	}

	void MsgForward()
	{
		while (true) {
			std::unique_lock<std::mutex> lk(m_lock);
			while (m_queue.empty()) m_cv.wait_for(lk, 1s);
			std::unique_ptr<MSG_DATA> pMsgData = PopMsg();
			MsgDealCenter(pMsgData);
		}
	}

	void PushMsg(std::unique_ptr<MSG_DATA>& pMsgData)
	{
		m_queue.push(std::move(pMsgData));
		m_cv.notify_one();
	}

	void RegisterServerHandle(ServerEventPtr pServerEvent)
	{
		m_pServerEvent = pServerEvent;
	}

	ServerEventPtr GetServerHandle()
	{
		return m_pServerEvent;
	}

	void WriteData(bufferevent* bev, const std::string& msg, MSG_TYPE eType)
	{
		m_pServerEvent->WriteData(bev, msg, eType);
	}

private:
	std::unique_ptr<MSG_DATA> PopMsg()
	{
		return m_queue.pop();
	}

private:
	SecureQueue<std::unique_ptr<MSG_DATA>> m_queue;
	std::mutex m_lock;
	std::condition_variable m_cv;
	MysqlOptHandleInfcPtr m_pMysqlOptHandleInfc;
	ServerEventPtr m_pServerEvent;
};

} /* town */

#endif /* MSG_DEAL_H */