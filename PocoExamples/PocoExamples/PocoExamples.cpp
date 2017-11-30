// PocoExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeParser.h"
#include "Poco/LocalDateTime.h"
#include <ctime>
#include <fstream>
#include "HTTPUtils.h"

using namespace std;

void timestampAndLocaldate();

int main(int argc, char** argv) {
	// datetime, timestamp and local datetime
	//timestampAndLocaldate();

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

    return 0;
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

