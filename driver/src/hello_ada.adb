pragma no_run_time;
with Interfaces.C;
with Interfaces.C.Strings;


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
   procedure Printk( s : String );
   pragma import( C, printk, "printk" );
   procedure Hr_Start_Timer(T : Interfaces.C.long);
   pragma import( C, hr_start_timer, "hr_start_timer" );
   IntStringBuffer : String := "                      t"  & Character'Val(10) & Character'Val(0);
   procedure TestBusyWait(C: Integer);
   --   function UInt2String(I : Integer) return String;
   Counter : Integer;
   Jiffies_Start, Jiffies_End : Integer;
   function Init_Module return Interfaces.C.int is
      result : Interfaces.C.Int;
   begin
      Printk("Hello, Ada-World!" & Character'Val(0));
      Result := Hr_Init;
      Counter := 10;
      Jiffies_Start := Jiffies;
      Hr_Start_Timer(1000000000);
      -- TestBusyWait(1000);
      return Result;
   end Init_Module;
   
   procedure Cleanup_Module is
   begin
      Printk("Goodbye, Ada-World!" & Character'Val(0));
      Hr_Cleanup;
   end Cleanup_Module;
   
   procedure UInt2String(J : Integer) is
      P : Integer;
      I : Integer;
   begin      
      I := J;
      P := 20;
      while I > 0
      loop
	 IntStringBuffer(P) := Character'Val(48 + I rem 10);
	 I := I / 10;
	 P := P-1;
      end loop;
   end;
   procedure TestBusyWait(C: Integer) is
      I : Integer := C;
   begin
      Printk("Start busy wait 1: " & Character'Val(10) & Character'Val(0));
      UInt2String(jiffies);
      Printk(IntStringBuffer);
      Printk("Start busy wait 2: " & Character'Val(10) & Character'Val(0));
      while I > 0
      loop
	 UDelay(10);
	 I := I - 1;
      end loop;
      Printk("Stop busy wait: " & Character'Val(10) & Character'Val(0));
      UInt2String(jiffies);
      Printk(IntStringBuffer);
   end;
   
   procedure Hr_Timer_Callback is
   begin
      Counter := Counter - 1;
      Jiffies_End := Jiffies;
      Printk("Timer struck..." & Character'Val(10) & Character'Val(0));
      Printk("Jiffies past: " & Character'Val(10) & Character'Val(0));
      UInt2String(Jiffies_End - Jiffies_Start);
      Printk(IntStringBuffer);
      TestBusyWait(1000);
   end Hr_Timer_Callback;
   
end Hello_Ada;
