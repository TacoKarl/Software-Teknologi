/* Creates a datagram server.  The port
number is passed as an argument.  This
server runs forever
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm

Modified: Michael Alrøe
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 9000
#define MAX_BUFFER_SIZE 256

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	printf("Starting UDP server on port %i...\n", PORT);
	int sock, n;
	socklen_t fromlen;
	size_t bytes_read;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[256];

	// if (argc < 2)
	// 	error("ERROR, no port provided\n");

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		error("ERROR, socket");

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	printf("Binding...\n");
	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		error("ERROR, binding");

	fromlen = sizeof(from);
	while (1)
	{
		printf("Receive...\n");
		n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&from, &fromlen);
		if (n < 0)
			error("ERROR, recvfrom");
		buf[n] = 0; // handle null termination
		printf("Received a datagram: %s\n", buf);

		if (buf[0] == 'U' || buf[0] == 'u')
		{
			FILE *fp = fopen("/proc/uptime", "r");
			if (fp == NULL)
			{
				error("Fejl ved åbning af /proc/uptime fil");
				exit(EXIT_FAILURE);
			}
			bytes_read = fread(buf, 1, MAX_BUFFER_SIZE, fp);
			fclose(fp);
		}
		// Læs indhold af /proc/loadavg og send det til klienten
		else if (buf[0] == 'L' || buf[0] == 'l')
		{
			FILE *fp = fopen("/proc/loadavg", "r");
			if (fp == NULL)
			{
				error("Fejl ved åbning af /proc/loadavg fil");
				exit(EXIT_FAILURE);
			}
			bytes_read = fread(buf, 1, MAX_BUFFER_SIZE, fp);
			fclose(fp);
		}
		else
		{
			// fejlbesked
			const char *error_msg = "ERROR WRONG COMMAND";
			// kopier fejlen ind i buffer
			strncpy(buf, error_msg, sizeof(buf));
			// Sæt bytes_read til størrelsen af error_msg
			bytes_read = strlen(error_msg);
		}
		n = sendto(sock, buf, bytes_read, 0, (struct sockaddr *)&from, fromlen);
		if (n < 0)
			error("ERROR, sendto");
	}

	return 0;
}
