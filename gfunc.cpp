#include "def.h"

void utc_to_ymdhms(uint8_t* utc, char* str)
{
    int k = 0;
    int yt, mt, dt;
    int y, m, d, hr, mn, sc;
    int ymd = utc[0] * 256 + utc[1];

    yt = (ymd - 15078.2) / 365.25;
    mt = yt * 365.25;
    mt = (ymd - 14956.1 - mt) / 30.6001;
    dt = yt * 365.25 + mt * 30.6001;
    
    if(mt == 14 || mt == 15)
        k = 1;

    y = yt + k + 1900;
    m = mt - 1 - k * 12;
    d = ymd - 14956 - dt;

    hr = (utc[2] & 0xf0) * 10 / 16 + (utc[2] & 0x0f);
    mn = (utc[3] & 0xf0) * 10 / 16 + (utc[3] & 0x0f);
    sc = (utc[4] & 0xf0) * 10 / 16 + (utc[4] & 0x0f);

    sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d", y, m, d, hr, mn, sc);

    return ;
}

void utc_to_hms(uint8_t* utc, char* str)
{
    int hr, mn, sc;

    hr = (utc[0] & 0xf0) * 10 / 16 + (utc[0] & 0x0f);
    mn = (utc[1] & 0xf0) * 10 / 16 + (utc[1] & 0x0f);
    sc = (utc[2] & 0xf0) * 10 / 16 + (utc[2] & 0x0f);

    sprintf(str, "%02d:%02d:%02d", hr, mn, sc);

    return ;
}

int coding_string_to_gb(uint8_t *p, uint8_t* buf_gb, int len)
{
    uint8_t coding = *p;
    int ret = 0;

    if (!buf_gb || len <= 0)
    {
        return -1;
    }

    if(0x01 <= coding && coding <= 0x1F) {
        p++; len--; /* pass first byte */
    }
    switch(coding) {
    case 0x11:
        ret = utf16_gb((const uint16_t *)p, (char*)buf_gb, len, BIG_ENDIAN);
        break;
    default:
        memcpy(buf_gb, p, len);
        buf_gb[len] = '\0';
        ret = len + 1;
        break;
    }
    return ret;
}