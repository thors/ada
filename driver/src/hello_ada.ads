pragma no_run_time;
with Interfaces.C;


package Hello_Ada is
  -- sample module layout
   
   function Init_Module return Interfaces.C.int;
   pragma Export(C, Init_Module, "init_module");
   procedure Cleanup_Module; 
   pragma Export(C, Cleanup_Module, "cleanup_module");
   procedure Hr_Timer_Callback; 
   pragma Export(C, Hr_Timer_Callback, "ada_hr_timer_callback");
end Hello_Ada;
