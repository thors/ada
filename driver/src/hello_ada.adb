pragma no_run_time;
with Interfaces.C;


package body Hello_Ada is
  -- sample module layout   
   procedure Printk( s : string );
   pragma import( C, printk, "printk" );
   procedure Hr_Start_Timer(T : Interfaces.C.long);
   pragma import( C, hr_start_timer, "hr_start_timer" );
   function Init_Module return Interfaces.C.int is
   begin
      Printk("Hello, Ada-World!" & Character'val(10) & character'val(0));
      Hr_Start_Timer(1000000000);
      return 0;
   end Init_Module;
   
   procedure Cleanup_Module is
   begin
      Printk("Goodbye, Ada-World!" & Character'val(10) & character'val(0));
   end Cleanup_Module;
   
   procedure Hr_Timer_Callback is
   begin
      Printk("Timer struck");
   end Hr_Timer_Callback;

end Hello_Ada;
