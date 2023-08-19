#ifndef ATARI_UTILS_DEBUG
#define ATARI_UTILS_DEBUG

#include "../cpu/6507.h"

void debug_log(const char *format, ...);

void debug_print_cpu_status(const C6507 *c);

#endif
