#include "stdafx.h"
#include "HTTPUtils.h"
#include <fstream>


HTTPUtils::HTTPUtils()
{
}


HTTPUtils::~HTTPUtils()
{
}

bool doRequest(HTTPClientSession& session, HTTPRequest& request, HTTPResponse& response, ostream &stream) {
	session.sendRequest(request);
	istream& rs = session.receiveResponse(response);

	if (response.getStatus() == HTTPResponse::HTTP_OK)
	{
		StreamCopier::copyStream(rs, stream);
		return true;
	}
	else
	{
		Poco::NullOutputStream null;
		StreamCopier::copyStream(rs, null);
		return false;
	}
}

bool doRequest(HTTPSClientSession& session, HTTPRequest& request, HTTPResponse& response, ostream &stream) {
	session.sendRequest(request);
	istream& rs = session.receiveResponse(response);

	if (response.getStatus() == HTTPResponse::HTTP_OK)
	{
		StreamCopier::copyStream(rs, stream);
		return true;
	}
	else
	{
		Poco::NullOutputStream null;
		StreamCopier::copyStream(rs, null);
		return false;
	}
}

bool HTTPUtils::http_get(string url, HTTPResponse &response, ostream &stream) {
	try {
		bool useHTTPS = false;
		URI uri(url);
		string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		string scheme(uri.getScheme());
		if (scheme == "HTTPS" || scheme == "https") useHTTPS = true;

		if (useHTTPS) {
			const Context::Ptr context = new Context(
				Context::CLIENT_USE,
				"",
				"",
				"",
				Context::VERIFY_NONE,
				9,
				false, // don't load default CAs
				"ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

			HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
			HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
			return doRequest(session, request, response, stream);
		}
		else {
			HTTPClientSession session(uri.getHost(), uri.getPort());
			HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
			return doRequest(session, request, response, stream);
		}
	}
	catch (Exception& exc) {
		cerr << exc.displayText() << endl;
		return false;
	}
}
