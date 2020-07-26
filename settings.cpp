#include "settings.h"

#include <EEPROM.h>

#include "CRC32.h"

struct EepromSettings
{
    uint32_t crc32;
    Settings payload;
};

bool settings(Settings &s)
{
    int coffset = EEPROM.length()/2;
    if (sizeof(EepromSettings) > coffset)
        return false;

    EepromSettings es1, es2;
    EEPROM.get(0      , es1);
    EEPROM.get(coffset, es2);
    if (memcmp(&es1, &es2, sizeof(es1)) == 0 && es1.crc32 == CRC32::calculate(&es1.payload, sizeof(es1.payload))) {
        s = es1.payload;
    } else { // try to restore integrity

    }
    return true;
}

bool writeSettings()
{
    return false;
}
