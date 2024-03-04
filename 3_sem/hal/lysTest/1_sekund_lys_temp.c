#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#define BUF_SIZE 1024

int turnOnLED(int l1, int l2, int l3);
int turnOffLED(int l1, int l2, int l3);

int main(int argc, char *argv[])
{
	/*HTML BUFFER*/
	char html[255];
	int htmlTemp = open("/www/pages/index.html", O_RDWR);

	/*LEDS open file as read write*/
	int LED1=open("/sys/class/gpio/gpio26/value", O_RDWR);
	int LED2=open("/sys/class/gpio/gpio20/value", O_RDWR);
	int LED3=open("/sys/class/gpio/gpio21/value", O_RDWR);

	/*Make char for writing 1 or 0 to turn on or off*/
	char light[1] = "1";
	char noLight[1] = "0";

	/*file descriptor*/
	int fd = open("/dev/i2c-1", O_RDWR);
	int data_len = 2;

	/*char for temp*/
	char temp[10];
	int addr = 0x48;
	int err = ioctl(fd, 0x0703, addr); // i2cdev sys call (0x0703) to set I2C addr
	float decTemp;
	/* do until ctrl+c*/
	while(1){
		/*Read temp*/
 		read(fd, temp, data_len); 
		decTemp = temp[0] + (temp[1] >> 7)*0.5;
		printf("Temperature is: %.1f\n",decTemp);
		sleep(1);
		if (temp[0] > 30){
			turnOnLED(LED1, LED2, LED3);
			printf("Temp too high\nTURN DOWN THE HEAT MOTHERFUCKER\n");
		}
		else{
			turnOffLED(LED1, LED2, LED3);
			printf("Temp is tranquil\n");
		}
		sprintf(html, "<html><body><h1>Temperature: %.1f </h1></body></html>", decTemp);
		write(htmlTemp, html, 50);
		
	}	
 	close(fd);
}

int turnOnLED(int l1, int l2, int l3){
	/*Make char for writing 1 turn on*/
	char light[1] = "1";
	write(l1, light, 1);
	write(l2, light, 1);
	write(l3, light, 1);
	return 0;
}
int turnOffLED(int l1, int l2, int l3){
	/*Make char for writing 0 turn off*/
	char light[1] = "0";
	write(l1, light, 1);
	write(l2, light, 1);
	write(l3, light, 1);
	return 0;
}