#define _DEFAULT_SOURCE

#ifndef HW_CHECK_HH
#define HW_CHECK_HH

#include <iostream>
#include <cstdlib>

#if defined(__unix__) || defined(__UNIX__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ipc.h>
#endif // FreeBSd

#if defined(__linux__) || defined (__gnu_linux__)
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <limits.h>
#include <linux/limits.h>
#include <linux/param.h>
#endif // GNU Linux

extern bool chk_camera(void);

#endif
