// PocoExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include <ctime>

using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::LocalDateTime;
using namespace std;

int main(int argc, char** argv)
{
	Timestamp now; // the current date and time

	time_t t1 = now.epochTime();                 // convert to time_t
	Timestamp ts1(Timestamp::fromEpochTime(t1)); // ... and back again

	string s = DateTimeFormatter::format(now, DateTimeFormat::RFC1123_FORMAT);
	cout << s << endl;

    return 0;
}

