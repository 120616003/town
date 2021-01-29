#ifndef MYSQL_OPT_HANDLE_INFC_G
#define MYSQL_OPT_HANDLE_INFC_G

#include "MysqlCommon.h"
#include "MysqlOpt.h"
// #include "MysqlOptHandle.h"

namespace town
{

class MysqlOptHandleInfc;
using MysqlOptHandleInfcPtr = std::shared_ptr<MysqlOptHandleInfc>;

class MysqlOptHandleInfc
{
public:
	static MysqlOptHandleInfcPtr GetInstance();
	void Initialization();
	MysqlOptPtr operator [] (MYSQL_OPT_TYPE eType);

protected:
	MysqlOptHandleInfc();
	~MysqlOptHandleInfc();
};

}

#endif /* MYSQL_OPT_HANDLE_INFC_G */