#ifndef DEBUG_H
#define DEBUG_H

/* -- Macro Definitions */
#ifndef NODEBUG
 #define TRACE(x)    dbg_printer x
#else
 #define TRACE(x)
#endif /* DEBUG */

#include <stdarg.h>

void dbg_printer(int module, const char *fmt, ...);

void dbg_printer(int module , const char *fmt, ...)
{
	if (dbg_mod_stderr & module)
	{
		va_list ap;

		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
	}

	if (dbg_file != NULL && (dbg_mod_file & module))
	{
		va_list ap;

		va_start(ap, fmt);
		vfprintf(dbg_file, fmt, ap);
		va_end(ap);
	}
}


#endif 
