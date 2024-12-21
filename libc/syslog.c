/* Copyright (C) 2024 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <stdarg.h>
#include <syslog.h>


void
vsyslog(int pri, const char *fmt, va_list ap) {
#warning "vsyslog() not implemented"
}


void
syslog(int pri, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vsyslog(pri, fmt, ap);
  va_end(ap);
}


void
openlog(const char *ident, int logstat, int logfac) {
#warning "openlog() not implemented"
}


void
closelog(void) {
#warning "closelog() not implemented"
}


int
setlogmask(int pmask) {
#warning "setlogmask() not implemented"
  return -1;
}
