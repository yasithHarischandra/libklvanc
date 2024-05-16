#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock.h>
#include <stdint.h>

#ifndef _BUILTINS_H
#define _BUILTINS_H

#ifndef _posix_
#define __inline__ inline
#endif

/**
 * @brief	Alternative function for GCC builtin __builtin_parity
 * @param[x]	uint16_t x, integer value to calculate parity
 * @return      Calculated parity
 */
static __inline__ int __builtin_parity(uint16_t x) {
    int result = 0;
    while (x) {
        result ^= 1;
        x &= x - 1; // This removes the lowest set bit
    }
    return result;
}

/**
 * @brief	Alternative function for gettimeofday linux function
 * source  - https://stackoverflow.com/questions/10905892/equivalent-of-gettimeofday-for-windows
 * @param[x]	struct timeval* tp, time from epoch in seconds and microseconds
 * @return      always return 0
 */
static __inline__ int gettimeofday(struct timeval* tp, struct timezone* tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    time = ((uint64_t)file_time.dwLowDateTime);
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec = (long)((time - EPOCH) / 10000000L);
    tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
    return 0;
}

#endif /* _BUILTINS_H */