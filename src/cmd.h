#ifndef _CMD_H
#define _CMD_H

#include <Arduino.h>

extern String wireResponse;

void processCmd(const String &cmd);

#endif
