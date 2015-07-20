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
#include "direct.h"

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

template<class T>
struct cmp_secp
{
    bool operator()(T* secp1, T* secp2) const 
    {
        return (*secp1) < (*secp2);
    }
};

template<class T>
class LimitQueue
{
public:
    LimitQueue(int sz);
    ~LimitQueue();

    void Push(T& elem); 
    void Pop();
    int Size();
    int Capacity();

    T& Front();
    T& operator[](int idx);

private:
    std::vector<T> vec;
    int capacity;
    int size;
};

template<class T>
LimitQueue<T>::LimitQueue(int sz)
    : vec(),
    capacity(sz > 0 ? sz : 0),
    size(0)
{
}

template<class T>
LimitQueue<T>::~LimitQueue()
{
}

template<class T>
int LimitQueue<T>::Size()
{
    return size;
}

template<class T>
int LimitQueue<T>::Capacity()
{
    return capacity;
}

template<class T>
void LimitQueue<T>::Push(T& elem)
{
    if(capacity == 0)
        return ;

    if(size == capacity)
    {
        Pop();
    }
    vec.push_back(elem);
    ++size;
}

template<class T>
void LimitQueue<T>::Pop()
{
    if(vec.empty())
        return ;

    vec.erase(vec.begin());
    --size;
}

template<class T>
T& LimitQueue<T>::Front()
{
    if(!vec.empty())
        return vec.front();

    throw std::out_of_range("Empty Queue!\n");
}

template<class T>
T& LimitQueue<T>::operator[](int idx)
{
    if(idx >= 0 && idx < size)
        return vec[idx];

    throw std::out_of_range("Invalidate Index!\n");
}

#endif