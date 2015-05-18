#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/delay.h>



static struct hrtimer hr_timer;

extern void ada_hr_timer_callback(void);

enum hrtimer_restart my_hrtimer_callback( struct hrtimer *timer ) {
  ada_hr_timer_callback();
  return HRTIMER_NORESTART;
}

/*
  Apparently, udelay is implemented as a macro or inline function in 
  Kernel header files and can not be imported to ruby. It could probably
  be re-implemented, but would take a great deal of effort in order to
  get all the calibration for CPU frequency adjustment etc.

  Therefore I export the function here.
 */
void udelay_export(long usecs) {
  udelay(usecs);
}

int hr_init( void ) {
  hrtimer_init( &hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );  
  hr_timer.function = &my_hrtimer_callback;
  return 0;
}

void hr_start_timer(long time_ns) {
  ktime_t ktime; 
  //printk("hr_timer_wrapper: Start timer...\n");
  udelay(5);
  ktime = ktime_set( 0, time_ns); 
  hrtimer_start( &hr_timer, ktime, HRTIMER_MODE_REL );
}

void hr_cleanup( void ) {
  int ret;
  ret = hrtimer_cancel( &hr_timer );
  if (ret) printk("The timer was still in use...\n");

  printk("HR Timer module uninstalling\n");

  return;
}
