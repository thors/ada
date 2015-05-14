Plans:

Implement a onewire kernel driver supporting multiple onewire slaves
on one GPIO pin for the raspberry pi

will try to implement the driver mainly in ADA, but with a C wrapper for convenience

Features planned:
	  - Treat one GPIO pin as a one-wire bus
	  - Implement binary search to detect all slaves on that bus
	  - Read data of a selected device

