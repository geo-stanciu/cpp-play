#include <iostream>
#include <occi.h>
#include "DBUtils.h"

using namespace oracle::occi;
using namespace std;

int main(int argc, char **argv) {
	const string userName = "geo";
	const string password = "geo";
	const string connectString = "db1";

	CDBUtils *db = new CDBUtils();
	Connection *conn = NULL;

	db->SetDetails(userName, password, connectString);

	try {
		conn = db->getConnection();

		Statement *stmt = conn->createStatement(
			"SELECT to_char(sysdate, 'dd/mm/yyyy hh24:mi:ss') FROM dual");

		ResultSet *rs = stmt->executeQuery();
		
		while (rs->next())
		{
			cout << rs->getString(1) << endl;
		}

		stmt->closeResultSet(rs);
		conn->terminateStatement(stmt);
	}
	catch (SQLException &ex) {
		cout << ex.getMessage() << endl;
	}

	db->closeConnection(conn);

	db->close();
	delete db;

	return 0;
}
