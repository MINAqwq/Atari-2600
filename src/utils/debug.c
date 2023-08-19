#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

#ifdef ATARI_DEBUG
void
debug_log(const char *format, ...)
{
	va_list arglist;
	va_start(arglist, format);

	vprintf(format, arglist);
	fputc(10, stdout);

	va_end(arglist);
}
#else
void
debug_log(const char *format, ...)
{
	(void)format;
	/* no debug build == no debug prints */
}
#endif

void
debug_print_cpu_status(const C6507 *c)
{
	printf("------ CPU Status ------\n"
	       "A:\t%d\n"
	       "X:\t%d\n"
	       "Y:\t%d\n"
	       "SP:\t%d\n"
	       "CF:\t%d\n"
	       "ZF:\t%d\n"
	       "ID:\t%d\n"
	       "DM:\t%d\n"
	       "VF:\t%d\n"
	       "NF:\t%d\n"
	       "PC:\t%d\n\n"
	       "Cycle Count: %d\n",
	       c->regs.a, c->regs.y, c->regs.x, c->regs.s, c->regs.p.carry,
	       c->regs.p.zero, c->regs.p.irq_disable, c->regs.p.decimal_mode,
	       c->regs.p.overflow, c->regs.p.negative, c->regs.pc,
	       c->cycle_count);
}