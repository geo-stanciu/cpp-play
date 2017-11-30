#pragma once

#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"

#include "LEIObject.h"

class LEIParser
{
public:
	LEIParser();
	~LEIParser();

	bool success = false;
	char *error_message = NULL;

	bool parseFromJSONString(const std::string &str, LEIObject &lei);
	bool parseFromJSONString(const char *str, LEIObject &lei);
};
