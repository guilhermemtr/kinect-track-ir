// In order to use the the logger, you have to define __YAL_ON__ flag.
// If the flag is not defined, there will be no logs.

#ifndef __YAL_LOG__
#define __YAL_LOG__

#include <stdio.h>

extern int __yal_dbg_lvl;
extern FILE * __yal_output;

#define __yal_init_logger() __yal_set_output(stdout)

#define __yal_set_output(out) (__yal_output = out)

#define __yal_set_log_file(file) (__yal_output = fopen(file,"a"))
#define __yal_close_log_file() (fclose(__yal_output))

#define __yal_set_lvl_err() (__yal_dbg_lvl = __YAL_ERROR)
#define __yal_set_lvl_warn() (__yal_dbg_lvl = __YAL_WARN)
#define __yal_set_lvl_dbg() (__yal_dbg_lvl = __YAL_DBG)
#define __yal_set_lvl_info() (__yal_dbg_lvl = __YAL_INFO)

#define __YAL_ERROR 1
#define __YAL_WARN 2
#define __YAL_DBG 3
#define __YAL_INFO 4

#define __YAL_ON__

#ifdef __YAL_ON__
#define __yal_log(lvl,...) do {				\
  if(__yal_dbg_lvl >= lvl)					\
    fprintf(__yal_output, __VA_ARGS__);		\
  } while(0)
#else
#define __yal_log(...) {}
#endif

#endif
