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

int init_module(void)
{
  int result;
  printk("C Module wrapper init\n");
  // A non 0 return means init_module failed; module can't be loaded.
  result = ada_init_module();
  return result;
}


void cleanup_module(void)
{
  printk(KERN_ALERT "C Module wrapper cleanup\n");
  ada_cleanup_module();
}  

MODULE_LICENSE("GPL");

