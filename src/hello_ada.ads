pragma no_run_time;
with Interfaces.C;


package Hello_Ada is
  -- sample module layout
   
   function Init_Module return Interfaces.C.int;
   pragma Export(C, Init_Module, "ada_init_module");
   procedure Cleanup_Module; 
   pragma Export(C, Cleanup_Module, "ada_cleanup_module");
end Hello_Ada;
