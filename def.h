#ifndef _DEF_H_
#define _DEF_H_

#include <list>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "XML/tinyxml.h"
#include "CodeTrans/UTF_GB.h"
#include "excp.h"

typedef unsigned char uint8_t;
typedef char int8_t;

typedef unsigned short uint16_t;
typedef short int16_t;

typedef unsigned int uint32_t;
typedef int int32_t;

typedef unsigned long long uint64_t;
typedef long long int64_t;

const int TS_PACKET_SIZE = 188;
const int TS_DVHS_PACKET_SIZE = 192;
const int TS_FEC_PACKET_SIZE = 204;
const int TS_MAX_PACKET_SIZE = 204;
const int MAX_PID_NUM = 8192;

//deal with the utc time
void utc_to_ymdhms(uint8_t* utc, char* str);
void utc_to_hms(uint8_t* utc, char* str);

//deal with the code translation
int coding_string_to_gb(uint8_t *p, uint8_t* buf_gb, int len);

#endif