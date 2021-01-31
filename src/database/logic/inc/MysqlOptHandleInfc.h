#ifndef MYSQL_OPT_HANDLE_INFC_G
#define MYSQL_OPT_HANDLE_INFC_G

#include "MysqlOpt.h"

namespace town
{

enum MYSQL_OPT_TYPE : uint32_t {
	ADD = 0,
	DELETE,
	CHANGE,
	SEARCH
};

class MysqlOptHandleInfc;
using MysqlOptHandleInfcPtr = std::shared_ptr<MysqlOptHandleInfc>;

class MysqlOptHandleInfc
{
public:
	static MysqlOptHandleInfcPtr GetInstance();
	void Initialization();
	MysqlOptPtr GetOptHandle (MYSQL_OPT_TYPE eType);

protected:
	MysqlOptHandleInfc();
	~MysqlOptHandleInfc();
};

}

#endif /* MYSQL_OPT_HANDLE_INFC_G */