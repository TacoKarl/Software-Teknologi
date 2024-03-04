#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	/*LEDS open file as read write*/
	int LED1=open("/sys/class/gpio/gpio26/value", O_RDWR);
	int LED2=open("/sys/class/gpio/gpio20/value", O_RDWR);
	int LED3=open("/sys/class/gpio/gpio21/value", O_RDWR);

	/*Make char for writing 1 or 0 to turn on or off*/
	char light[1] = "1";
	char noLight[1] = "0";

	/* do until ctrl+c*/
	while(1){
		/*Turn on*/
		usleep(500000);
		write(LED1, light, 1);
		usleep(500000);
		write(LED2, light, 1);
		usleep(500000);
		write(LED3, light, 1);

		/*Turn off*/
		usleep(500000);
		write(LED1, noLight, 1);
		usleep(500000);
        	write(LED2, noLight, 1);
		usleep(500000);
	        write(LED3, noLight, 1);
	}	
}
