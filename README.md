# iot-atmega8a-as-rtc

use of atmega8a as dummy rtc through i2c

## description

pins:
- gnd common to other master i2c
- PC5 "A5" ( SCL )
- PC4 "A4" ( SDA )

SCL and SDA need to be pulled using 4.7k resistor each line.

## i2c commands

### set time utc

```
/set YYYY-MM-DD HH:mm:ss
```

set current time

### get time utc

```
/get
```

retrieve current time in YYYY-MM-DD HH:mm:ss format ( length: 19 bytes )