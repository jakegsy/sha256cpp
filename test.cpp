#include <iostream>
#include "sha256.h"
 
using std::string;
using std::cout;
using std::endl;

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

/* Remove if already defined */
typedef long long int64; typedef unsigned long long uint64;

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
 * windows and linux. */

uint64 GetTimeMs64()
{
#ifdef _WIN32
 /* Windows */
 FILETIME ft;
 LARGE_INTEGER li;

 /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
  * to a LARGE_INTEGER structure. */
 GetSystemTimeAsFileTime(&ft);
 li.LowPart = ft.dwLowDateTime;
 li.HighPart = ft.dwHighDateTime;

 uint64 ret = li.QuadPart;
 ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
 ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

 return ret;
#else
 /* Linux */
 struct timeval tv;

 gettimeofday(&tv, NULL);

 uint64 ret = tv.tv_usec;
 /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
 ret /= 1000;

 /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
 ret += (tv.tv_sec * 1000);

 return ret;
#endif
}
 
int main(int argc, char *argv[])
{
    string input = "grape";
    int lim = atoi(argv[1]);
    cout << lim << endl;
    uint64 time1 = GetTimeMs64();
    string output1 = sha256(input);

    for(int i=1;i<lim;i++){
    	//cout << i <<endl;
    	output1 = sha256(output1);
    }
 	uint64 time2 = GetTimeMs64();
    cout << "sha256('"<< input << "'):" << output1 << endl;
    cout << "time taken : "<< (time2-time1) << "ms" << endl;
    return 0;
}

