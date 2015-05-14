pragma no_run_time;
with Interfaces.C;


package body Hello_Ada is
  -- sample module layout   
   procedure Printk( s : string );
   pragma import( C, printk, "printk" );
   function Init_Module return Interfaces.C.int is
   begin
      Printk("Hello, Ada-World!" & Character'val(10) & character'val(0));
      return 0;
   end Init_Module;
   
   procedure Cleanup_Module is
   begin
      Printk("Goodbye, Ada-World!" & Character'val(10) & character'val(0));
   end Cleanup_Module;
end Hello_Ada;
