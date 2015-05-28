obj-m += wrapper.o

ADA_SOURCES = src/hello_ada.ada 

C_SOURCES = src/wrapper.c \
	src/hr_timer_wrapper.c \
	src/ada_proc.c

ADAC=gnatmake
ADA_FLAGS=-a -s -mcmodel=kernel
wrapper-objs := $(wrapper-objs) $(subst .ada,.o,$(ADA_SOURCES)) $(subst .c,.o,$(C_SOURCES))

%.o : %.adb
	$(ADAC) $(ADA_FLAGS) -D `echo $< | sed "s/^\(.*\)\/[^\/]*/\1/g"` -o `echo $< | sed "s/^.*\/\([^\/]\)/\1/g"` $<

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f $(wrapper-objs)
