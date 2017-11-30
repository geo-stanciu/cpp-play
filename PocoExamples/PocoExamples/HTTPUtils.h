#pragma once

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include <fstream>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

class HTTPUtils
{
public:
	HTTPUtils();
	~HTTPUtils();

	bool http_get(string url, HTTPResponse &response, ostream &stream);
};
