#include <stddef.h>
#include <stdint.h>
#include <time.h>

#include "freertos_time.h"

#include "joylink_stdio.h"
#include "joylink_time.h"

static long long m_time_sec_offset = 0;

/**
 * 初始化系统时间
 *
 * @return: 0 - success or -1 - fail
 *
 */
int32_t jl_set_UTCtime(jl_time_stamp_t ts)
{
    struct timeval tv = {0,};
    unsigned int ticks = 0;
    
    jl_platform_printf("[%s]second: %d, ms: %d\r\n", __func__, ts.second, ts.ms);

    tv.tv_sec = ts.second;
    tv.tv_usec = ts.ms * 1000;

    /* TODO: OS_Ticks是一个32位ms计数器，需要考虑设备49天不断电，计数器溢出的情况！*/
    m_time_sec_offset = tv.tv_sec - OS_TicksToSecs(OS_GetTicks());
    jl_platform_printf("[%s]second:%d, m_time_sec_offset:%d\r\n", __func__, ts.second, m_time_sec_offset);
}

/**
* @brief 获取系统UTC时间，精确到毫秒
* @param none
* @return time ms
*/
int jl_get_time_msec(jl_time_stamp_t *ts)
{
    struct timeval now = {0,};
    int temp = 0;

    if (ts) {
        temp = OS_TicksToMSecs(OS_GetTicks());
        ts->second = (uint32_t)(temp / 1000) + m_time_sec_offset;
        ts->ms = (uint32_t)(temp % 1000);
    }
    return 0;
}

/**
 * 获取系统UTC时间，精确到秒
 *
 * @return: UTC Second
 *
 */
uint32_t jl_get_time_second(uint32_t *jl_time)
{
    return OS_TicksToSecs(OS_GetTicks()) + m_time_sec_offset;
}

/**
 * get time string
 *
 * @out param: 
 * @return: success or fail
 *
 */
int jl_get_time(jl_time_t *jl_time)
{
    time_t timep = 0;

    timep = (time_t)jl_get_time_second(NULL);
    struct tm *p = localtime(&timep);

    jl_time->year      = p->tm_year;
    jl_time->month     = p->tm_mon;
    jl_time->week      = p->tm_wday;
    jl_time->day       = p->tm_mday;
    jl_time->hour      = p->tm_hour;
    jl_time->minute    = p->tm_min;
    jl_time->second    = p->tm_sec;

    return 0;
}

/**
 * 获取时间字符串
 *
 * @out param: "year-month-day hour:minute:second.millisecond"
 * @return: success or fail
 *
 */
char *jl_get_time_str(void)
{
    static char time_buffer[30];
    memset(time_buffer, 0, sizeof(time_buffer));

    // 获取“年-月-日 时:分:秒.毫秒”字符串类型的时间戳
    time_t timep = 0;
    jl_time_stamp_t ts = {0,};
    struct tm *p = NULL;

    timep = jl_get_time_second(NULL);
    p = localtime(&timep);
    jl_get_time_msec(&ts);

    jl_platform_sprintf(time_buffer, "%02d-%02d-%02d %02d:%02d:%02d.%03d\r\n", 
        1900 + p->tm_year,
        1 + p->tm_mon,
        p->tm_mday,
        p->tm_hour,
        p->tm_min,
        p->tm_sec,
        ts.ms
        );
    return time_buffer;
}

/**
 * get os time
 *
 * @out param: none
 * @return: sys time ticks ms since sys start
*/
uint32_t jl_get_os_time(void)
{
    jl_time_stamp_t ts = {0};

    jl_get_time_msec(&ts);
    return (ts.second * 1000 + ts.ms); // FIXME: do not recommand this method
}