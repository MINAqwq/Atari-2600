#ifndef ATARI_UTILS_MEMORY_PAGE_H
#define ATARI_UTILS_MEMORY_PAGE_H

#include <stdint.h>

/* addr & 0xFF00 */
#define page(addr) (addr & 0xFF00)
#endif