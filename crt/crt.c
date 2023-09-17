/* Copyright (C) 2023 John Törnblom

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

#include "payload.h"
#include "syscall.h"


/**
 * Dependencies provided by the ELF linker.
 **/
extern void (*__init_array_start[])(payload_args_t*) __attribute__((weak));
extern void (*__init_array_end[])(payload_args_t*) __attribute__((weak));

extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));

extern unsigned char __bss_start[] __attribute__((weak));
extern unsigned char __bss_end[] __attribute__((weak));


/**
 * Entry point to the main program.
 **/
extern int main(int argc, char* argv[], char *envp[]);



static int
fork(void) {
  return (int)syscall(2);
}


static int
set_procname(const char *s) {
  return (int)syscall(0x1d0, -1, s);
}


static int
getdtablesize(void) {
  return (int)syscall(89);
}


static int
close(int fd) {
  return (int)syscall(6, fd);
}


static void
_exit(int exit_code) {
  syscall(1, exit_code);
}


/**
 * Entry-point used by the ELF loader.
 **/
void
_start(payload_args_t *args) {
  unsigned long count;

  *args->payloadout = 0;

  // clear bss
  for(unsigned char* bss=__bss_start; bss<__bss_end; bss++) {
    *bss = 0;
  }

  // run module constructors
  count = __init_array_end - __init_array_start;
  for(int i=0; i<count; i++) {
    __init_array_start[i](args);
  }

  if(fork() == 0) {
    set_procname("homebrew.elf"); //set proc name

    // close open file descriptors inherited from parent
    for(int i=3; i<getdtablesize(); i++) {
      if(i != args->rwpair[0] && i != args->rwpair[1] &&
	 i != args->rwpipe[0] && i != args->rwpipe[1]) {
	close(i);
      }
    }
    _exit(main(0, 0, 0));
  }

  // run module destructors
  count = __fini_array_end - __fini_array_start;
  for(int i=0; i<count; i++) {
    __fini_array_start[i]();
  }
}
