Plans:

Implement a onewire kernel driver supporting multiple onewire slaves
on one GPIO pin for the raspberry pi

will try to implement the driver mainly in ADA, but with a C wrapper for convenience

Features planned:
	  - Treat one GPIO pin as a one-wire bus
	  - Implement binary search to detect all slaves on that bus
	  - Read data of a selected device


Done:

- Implemented first hello-world ada driver for linux on x86 Fedora
  Driver is implemented as a small C wrapper linked against Ada objects

Todo:
- Compile initial module on Raspberry (Raspbian); see 
  raspberry_kernel_module.txt for detailed information
- Add some access to timer for onewire-timing
      hrtimer required. Since structures from kernel-headers are required and 
      callbacks are to be implemented, we will implement hr-interface in the
      C-part of the driver

- Get information how to access GPIO hardware on raspberry
