#include "rtc.h"

#include <time.h>
#include "config.h"

time_t curTime;

uint32_t lastSync = 0;

bool isSynchronized = false;

void setRTC(int year, int month, int day, int hr, int min, int sec)
{
    tm t;

    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hr;
    t.tm_min = min;
    t.tm_sec = sec;

    curTime = mk_gmtime(&t);

    lastSync = millis();

    isSynchronized = true;
}

bool isRTCSynchronized()
{
    return isSynchronized;
}

void getRTC(int &year, int &month, int &day, int &hr, int &min, int &sec)
{
    auto mdiff = millis() - lastSync;
    time_t timeraw = curTime + mdiff / 1000UL;

    auto tm = gmtime(&timeraw);

    year = tm->tm_year + 1900;
    month = tm->tm_mon + 1;
    day = tm->tm_mday;
    hr = tm->tm_hour;
    min = tm->tm_min;
    sec = tm->tm_sec;
}

void maintenanceRTC()
{
    if (!isSynchronized) return;
    
    auto m = millis();
    auto mdiff = m - lastSync;
    if (mdiff >= FLUSH_RTC_MS_MINIMUM)
    {
        curTime += mdiff / 1000UL;
        lastSync = m;        
    }
}