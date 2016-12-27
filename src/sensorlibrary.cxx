#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sensorlibrary.h"

// Based on mmapGpio from found http://hertaville.com/rpimmapgpio.html
volatile unsigned *gpio;

/**
 * Call this method to open the memory mapped GPIO pins.
 */
int bem_initialize() {
	int mem_fd = 0;
	void *regAddrMap = MAP_FAILED;

	if(!mem_fd) {
		if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0) {
			perror("can't open /dev/mem");
			return 1;
		}
	}

	regAddrMap = mmap(
		NULL,
		GPIO_LEN,
		PROT_READ|PROT_WRITE|PROT_EXEC,
		MAP_SHARED|MAP_LOCKED,
		mem_fd,
		GPIO_BASE
	);

	if (regAddrMap == MAP_FAILED) {
		perror("mmap error");
		close(mem_fd);
		return 1;
	}

	if(close(mem_fd) < 0) {
		perror("Couldn't close /dev/mem file descriptor");
		return 1;
	}
	
	gpio = (volatile unsigned *)regAddrMap;
	return 0;
}

int bem_get_sample(bem_reading_t *sample, int sample_length) {
	for(int i = 0; i < sample_length; i++) {
		// TODO: Currently, I am pulling the time to ensure I can really pull the values at correct intervals, with uninterrupted cpu frames.
		timeval curTime;
		gettimeofday(&curTime, NULL);
		// TODO: Use the gpio map to pull the value.
		sample[i].reading = i + 1;
		sample[i].time = curTime;
	}
	return 0;
}

/**
 * Call this method to shutdown the library at the end of usage.
 */
int bem_shutdown() {
	if (munmap((void*)gpio, GPIO_LEN) < 0) {
		perror("munmap (gpio) failed");
		return 1;
	}

	return 0;
}
