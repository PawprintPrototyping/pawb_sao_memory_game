#ifdef DEEPSLEEP_H_
#define DEEPSLEEP_H_

#include <stdint.h>

void deepsleep_init();

void deepsleep(uint32_t sleep_time);

#endif