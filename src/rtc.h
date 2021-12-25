#ifndef _RTC_H
#define _RTC_H

#include <Arduino.h>

/**
 * @brief set current time (gmt)
 */
void setRTC(int year, int month, int day, int hr, int min, int sec);

/**
 * @brief states if setRTC was called first time
 */
bool isRTCSynchronized();

/**
 * @brief retrieve current time (gmt) ; note : valid only if isRTCSynchronized() true
 */
void getRTC(int &year, int &month, int &day, int &hr, int &min, int &sec);

/**
 * @brief to be called at least each 49 days to flush lastsync difference into date/time
 */
void maintenanceRTC();

#endif