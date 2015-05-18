/*  hello-1.c - The simplest kernel module.
 *
 *  Copyright (C) 2001 by Peter Jay Salzman
 *
 *  08/02/2006 - Updated by Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
 */

/* Kernel Programming */
//#define MODULE
#define LINUX
#define DRIVER_AUTHOR "Thorsten Moellers <github@thorzten.de>"
#define DRIVER_DESC   "A sample driver"
//#define __KERNEL__

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include "hr_timer_wrapper.h"
#include "ada_interface.h"


void __gnat_last_chance_handler (char *source_location,
                                 int line) {
  printk("Ada __gnat_last_chance_handler:");
  printk(source_location);
}


MODULE_LICENSE("GPL");

