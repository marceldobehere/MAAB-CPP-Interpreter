#pragma once

/* sys/ioctl.h
   Copyright 1998, 2001 Red Hat, Inc.
This file is part of Cygwin.
This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

/* sys/ioctl.h */

#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#include "cdefs.h"

/* /dev/windows ioctls */

#define WINDOWS_POST	0	/* Set write() behavior to PostMessage() */
#define WINDOWS_SEND	1	/* Set write() behavior to SendMessage() */
#define WINDOWS_HWND	2	/* Set hWnd for read() calls */


int ioctl(int __fd, int __cmd, void*);


#endif