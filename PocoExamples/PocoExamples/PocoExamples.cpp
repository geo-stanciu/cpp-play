// PocoExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <fstream>
#include "HTTPUtils.h"
#include "LEIParser.h"

#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeParser.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/JSON/JSONException.h"

#include <assert.h>

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;

void timestampAndLocaldate();
std::string base64encode(std::string val);
std::string base64decode(std::string val);

int main(int argc, char** argv) {
	// datetime, timestamp and local datetime
	//timestampAndLocaldate();

	// encode base64
	cout << base64encode("The quick brown fox jumps over the lazy dog") << endl;

	// decode base64
	cout << base64decode("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==") << endl;

	// get HTTP
	//string url = "http://www.bvb.ro/Rss/ATSNews.ashx";
	//HTTPUtils hutils;
	//HTTPResponse response;
	//ofstream ofs("d:/test1.xml", fstream::binary);
	//if (!hutils.http_get(url, response, ofs)) {
	//	cout << response.getStatus() << " " << response.getReason() << endl;
	//}
	//ofs.close();

	// get https
	//string url = "https://leilookup.gleif.org/api/v1/leirecords?lei=NKY7JRBKJHQQ68KJ6252";
	//HTTPResponse response;
	//HTTPUtils hutils;
	//ofstream ofs("d:/test1.json", fstream::binary);
	//if (!http_get(url, response, ofs)) {
	//	cout << response.getStatus() << " " << response.getReason() << endl;
	//}
	//ofs.close();

	// json objects
	//{
	//	string json = "{ \"test\" : { \"property\" : \"value\" } }";
	//	Parser parser;
	//	Var result = parser.parse(json);
	//	Object::Ptr object = result.extract<Object::Ptr>();
	//	Var test = object->get("test");
	//	object = test.extract<Object::Ptr>();
	//	test = object->get("property");
	//	string value = test.convert<string>();
	//	std::cout << value << endl;
	//}

	// json array of objects
	//{
	//	string json = "[ {\"test\" : 0}, { \"test1\" : [1, 2, 3], \"test2\" : 4 } ]";
	//	Parser parser;
	//	Var result = parser.parse(json);

	//	assert(result.isArray());
	//	Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
	//	Object::Ptr object = arr->getObject(0);//
	//	assert(object->getValue<int>("test") == 0);
	//	object = arr->getObject(1);
	//	arr = object->getArray("test1");
	//	result = arr->get(0);
	//	std::cout << result.convert<int>() << endl;
	//}

	// LEI parse - bad lei 1
	//{
	//	string json = "[]";
	//	LEIParser p;
	//	LEIObject lei;
	//	
	//	if (!p.parseFromJSONString(json, lei)) {
	//		cout << p.error_message << endl;
	//	}
	//	else {
	//		ofstream out("d:/leioutput_1.txt");
	//		out << lei.toString() << endl;
	//		out.close();
	//	}
	//}

	// LEI parse - bad lei 2
	//{
	//	string json = "{ \"message\":\"`NKY7JRBKJHQQ68KJ62521` should be a 20 char string containing 0-9 or A-Z.\",\"status_code\" : 400 }";
	//	LEIParser p;
	//	LEIObject lei;
	//	
	//	if (!p.parseFromJSONString(json, lei)) {
	//		cout << p.error_message << endl;
	//	}
	//	else {
	//		ofstream out("d:/leioutput_1.txt");
	//		out << lei.toString() << endl;
	//		out.close();
	//	}
	//}

	// LEI parse - good lei
	//{
	//	string json = "[{\"LEI\":{\"$\":\"NKY7JRBKJHQQ68KJ6252\"},\"Entity\":{\"LegalName\":{\"$\":\"Global Macro Absolute Return Advantage Portfolio\"},\"LegalAddress\":{\"Line1\":{\"$\":\"Two International Place\"},\"City\":{\"$\":\"Boston\"},\"Region\":{\"$\":\"US-MA\"},\"Country\":{\"$\":\"US\"},\"PostalCode\":{\"$\":\"02110\"}},\"HeadquartersAddress\":{\"Line1\":{\"$\":\"Two International Place\"},\"City\":{\"$\":\"Boston\"},\"Region\":{\"$\":\"US-MA\"},\"Country\":{\"$\":\"US\"},\"PostalCode\":{\"$\":\"02110\"}},\"BusinessRegisterEntityID\":{\"@register\":\"RA000613\"},\"LegalJurisdiction\":{\"$\":\"US\"},\"LegalForm\":{\"$\":\"OTHER\"},\"EntityStatus\":{\"$\":\"ACTIVE\"}},\"Registration\":{\"InitialRegistrationDate\":{\"$\":\"2012-06-28T09:07:00.161Z\"},\"LastUpdateDate\":{\"$\":\"2017-10-17T03:07:32.454Z\"},\"RegistrationStatus\":{\"$\":\"ISSUED\"},\"NextRenewalDate\":{\"$\":\"2018-09-29T20:44:17.481Z\"},\"ManagingLOU\":{\"$\":\"EVK05KS7XY1DEII3R011\"},\"ValidationSources\":{\"$\":\"FULLY_CORROBORATED\"}}}]";
	//	LEIParser p;
	//	LEIObject lei;

	//	if (!p.parseFromJSONString(json, lei)) {
	//		cout << p.error_message << endl;
	//	}
	//	else {
	//		ofstream out("d:/leioutput.txt");
	//		out << lei.toString() << endl;
	//		out.close();
	//	}
	//}

    return 0;
}

std::string base64encode(std::string val)
{
	std::stringstream ss;
	Poco::Base64Encoder b64enc(ss);
	b64enc << val;
	b64enc.close();

	return ss.str();
}

std::string base64decode(std::string val)
{
	std::stringstream ss;
	ss << val;

	std::stringstream ostr;

	Poco::Base64Decoder b64dec(ss);
	copy(std::istreambuf_iterator<char>(b64dec),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(ostr));

	return ostr.str();
}

void timestampAndLocaldate() {
	Timestamp now; // the current date and time
	time_t t1 = now.epochTime();                 // convert to time_t
	Timestamp ts1(Timestamp::fromEpochTime(t1)); // ... and back again
	string s = DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT);
	cout << "now (GMT): " << s << endl;

	LocalDateTime ldt(now);
	s = DateTimeFormatter::format(ldt, DateTimeFormat::HTTP_FORMAT);
	cout << "now: " << s << endl;

	int tzd;
	string s1("Sat, 1 Jan 2005 12:00:00 GMT");
	DateTime dt;
	DateTimeParser::parse(DateTimeFormat::RFC1123_FORMAT, s1, dt, tzd);
	s = DateTimeFormatter::format(dt, DateTimeFormat::HTTP_FORMAT);
	cout << "time (GMT): " << s << endl;

	Timestamp ts = dt.timestamp();
	s = DateTimeFormatter::format(ts, DateTimeFormat::HTTP_FORMAT);
	cout << "timestamp (GMT): " << s << endl;

	LocalDateTime ldt1(dt);
	s = DateTimeFormatter::format(ldt1, DateTimeFormat::HTTP_FORMAT);
	cout << "time: " << s << endl;
}

