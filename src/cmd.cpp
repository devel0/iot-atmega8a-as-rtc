#include "cmd.h"

#include "rtc.h"

#include <Wire.h>

String wireResponse = "";

String fmtInt(int val, int size)
{
    String res = "";

    int k = 0;
    int v = val;
    while (v / 10 != 0)
    {
        v /= 10;
        ++k;
    }
    for (int j = k + 1; j < size; ++j)
        res += "0";
    res += String(val);

    return res;
}

String fmtDateTime(int YYYY, int MM, int DD, int HH, int mm, int ss)
{
    return fmtInt(YYYY, 4) + "-" + fmtInt(MM, 2) + "-" + fmtInt(DD, 2) +
           " " + fmtInt(HH, 2) + ":" + fmtInt(mm, 2) + ":" + fmtInt(ss, 2);
}

void processCmd(const String &cmd)
{
    if (cmd.length() == 0)
        return;

    if (cmd.startsWith("/set "))
    {
        String YYYY_str = "";
        String MM_str = "";
        String DD_str = "";
        String HH_str = "";
        String mm_str = "";
        String ss_str = "";

        int l = cmd.length();
        int i = 5;
        while (i < l && cmd[i] != '-')
            YYYY_str += cmd[i++];
        ++i;
        while (i < l && cmd[i] != '-')
            MM_str += cmd[i++];
        ++i;
        while (i < l && cmd[i] != ' ')
            DD_str += cmd[i++];
        ++i;
        while (i < l && cmd[i] != ':')
            HH_str += cmd[i++];
        ++i;
        while (i < l && cmd[i] != ':')
            mm_str += cmd[i++];
        ++i;
        while (i < l)
            ss_str += cmd[i++];

        auto YYYY = YYYY_str.toInt();
        auto MM = MM_str.toInt();
        auto DD = DD_str.toInt();
        auto HH = HH_str.toInt();
        auto mm = mm_str.toInt();
        auto ss = ss_str.toInt();

        auto str = fmtDateTime(YYYY, MM, DD, HH, mm, ss);
#ifndef DISABLE_SERIAL_DEBUG
        Serial.println(str);
#endif
        wireResponse = str;

        setRTC(YYYY, MM, DD, HH, mm, ss);
    }
    else if (cmd == "/get")
    {
        int YYYY, MM, DD, HH, mm, ss;
        getRTC(YYYY, MM, DD, HH, mm, ss);

        auto str = fmtDateTime(YYYY, MM, DD, HH, mm, ss);
#ifndef DISABLE_SERIAL_DEBUG
        Serial.println(str);
#endif
        wireResponse = str;
    }
}