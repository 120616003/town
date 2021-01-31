#ifndef MSG_DEAL_H
#define MSG_DEAL_H

#include "ServerCommon.h"
#include "MysqlOptHandleInfc.h"
#include "ServerEvent.h"

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
			std::unique_ptr<MSG_DATA> pMsgData;
			std::unique_lock<std::mutex> lk(m_lock);
			while (m_queue.empty()) m_cv.wait_for(lk, 1s);
			PopMsg(pMsgData);
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

private:
	void PopMsg(std::unique_ptr<MSG_DATA>& pMsgData)
	{
		pMsgData = std::move(m_queue.front());
		m_queue.pop();
	}

private:
	std::queue<std::unique_ptr<MSG_DATA>> m_queue;
	std::mutex m_lock;
	std::condition_variable m_cv;
	MysqlOptHandleInfcPtr m_pMysqlOptHandleInfc;
	ServerEventPtr m_pServerEvent;
};

} /* town */

#endif /* MSG_DEAL_H */