#ifndef MYSQL_OPT_HANDLE_G
#define MYSQL_OPT_HANDLE_G

#include "MysqlOpt.h"
#include "MysqlAddOpt.h"
#include "MysqlChangeOpt.h"
#include "MysqlDeleteOpt.h"
#include "MysqlSearchOpt.h"
#include "MysqlOptHandleInfc.h"

#include <unordered_map>

namespace town
{

class MysqlOptHandle;
using MysqlOptHandlePtr = std::shared_ptr<MysqlOptHandle>;

class MysqlOptHandle : public MysqlOptHandleInfc
{
public:
	MysqlOptHandle();
	~MysqlOptHandle();

	void Initialization();
	MysqlOptPtr GetOptHandle(MYSQL_OPT_TYPE eType);

private:
	std::unordered_map<MYSQL_OPT_TYPE, MysqlOptPtr> m_mMysqlOptPtr;
};

}

#endif /* MYSQL_OPT_HANDLE_G */