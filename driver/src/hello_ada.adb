pragma no_run_time;
with Interfaces.C;


package body Hello_Ada is
   -- sample module layout
   type Unsigned_long is mod 2**64;
   jiffies : Integer;
   pragma import( C, jiffies, "jiffies" );
   procedure UDelay(Duration : Unsigned_long);
   pragma import( C, Udelay, "udelay_export" );
   function Hr_Init return Interfaces.C.int;
   pragma import( C, hr_init, "hr_init" );
   procedure Hr_Cleanup;
   pragma import( C, hr_cleanup, "hr_cleanup" );
   procedure Printk( s : string );
   pragma import( C, printk, "printk" );
   procedure Hr_Start_Timer(T : Interfaces.C.long);
   pragma import( C, hr_start_timer, "hr_start_timer" );
   -- Result : String := "                    ";
   --   function UInt2String(I : Integer) return String;
   Counter : Integer;
   function Init_Module return Interfaces.C.int is
      result : Interfaces.C.Int;
   begin
      Printk("Hello, Ada-World!");
      Result := Hr_Init;
      Counter := 1000;
      Hr_Start_Timer(1000000000);
---      Udelay(5);
      return Result;
   end Init_Module;
   
   procedure Cleanup_Module is
   begin
      Printk("Goodbye, Ada-World!\n");
      Hr_Cleanup;
   end Cleanup_Module;
   
--   function UInt2String(I : Integer) return String is
--     P : Integer;
--   begin      
--      P := 20;
--      while I > 0
--      loop
--	 Result(P) := Character'Val(48 + I rem 10);
--	 P := P-1;
--      end loop;
--      return Result(P..20);
--      return "";
--   end;
   procedure TestBusyWait is
   begin
      Printk("Start busy wait: ");
--      Printk(UInt2String(jiffies));
      for i in  1 .. 1000 
      loop
	   UDelay(5);
      end loop;
--      Printk("End busy wait: " & UInt2String(jiffies));
   end;
   
   procedure Hr_Timer_Callback is
   begin
      Counter := Counter - 1;
      if (Counter > 0) then 
	 Hr_Start_Timer(1000);
      else 
	 Printk("Timer struck 1000 times now...\n");
      end if;
   end Hr_Timer_Callback;

end Hello_Ada;
