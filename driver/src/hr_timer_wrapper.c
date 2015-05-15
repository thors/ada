#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>



static struct hrtimer hr_timer;

extern void ada_hr_timer_callback(void);

enum hrtimer_restart my_hrtimer_callback( struct hrtimer *timer ) {
  ada_hr_timer_callback();
  return HRTIMER_NORESTART;
}

int hr_init( void ) {
  hrtimer_init( &hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );  
  hr_timer.function = &my_hrtimer_callback;
  return 0;
}

void hr_start_timer(long time_ns) {
  ktime_t ktime; 
  printk("hr_timer_wrapper: Start timer...\n");
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
