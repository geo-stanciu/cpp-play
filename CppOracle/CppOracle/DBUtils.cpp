#include "DBUtils.h"



CDBUtils::CDBUtils()
{
	env = NULL;
	scp = NULL;
}

CDBUtils::~CDBUtils()
{
	close();
}

void CDBUtils::close()
{
	if (env)
	{
		if (scp)
		{
			env->terminateStatelessConnectionPool(scp);
			scp = NULL;
		}

		Environment::terminateEnvironment(env);
		env = NULL;
	}
}

void CDBUtils::SetDetails(const string &user, const string &pass, const string &connString)
{
	userName = user;
	password = pass;
	connectString = connString;
}

Connection * CDBUtils::getConnection()
{
	if (!env)
	{
		env = Environment::createEnvironment(Environment::DEFAULT);
		scp = env->createStatelessConnectionPool(userName, password, connectString, 25, 1);
	}

	Connection *conn = scp->getConnection();
	return conn;
}

void CDBUtils::closeConnection(Connection *conn)
{
	if (conn && scp)
		scp->releaseConnection(conn);
}
