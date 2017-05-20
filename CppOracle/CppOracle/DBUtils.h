#pragma once
#include <occi.h>

using namespace oracle::occi;
using namespace std;

class CDBUtils
{
private:
	Environment *env;
	StatelessConnectionPool *scp;

	string userName;
	string password;
	string connectString;

public:
	CDBUtils();
	~CDBUtils();

	void SetDetails(const string &user, const string &pass, const string &db);
	void close();

	Connection * getConnection();
	void closeConnection(Connection *conn);
};
