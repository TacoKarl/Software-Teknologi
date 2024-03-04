/* A simple server in the internet domain using TCP
The port number is passed as an argument 
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm 

Modified: Michael Alrøe
Extended to support file server!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "iknlib.h"

#define STRBUFSIZE 256
#define BUFSIZE_RX 200
#define BUFSIZE_TX 1000
#define PORT 9001

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * @brief Sends a file to a client socket
 * @param clientSocket Socket stream to client
 * @param fileName Name of file to be sent to client
 * @param fileSize Size of file
 */
void sendFile(int clientSocket, const char* fileName, long fileSize)
{
	printf("Sending: %s, size: %li\n", fileName, fileSize);
    // Open the file for reading

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        error("ERROR opening file");
    }

    // Buffer to read and send file data
    uint8_t buffer[BUFSIZE_TX];

    // Read file data and send it over the socket
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (send(clientSocket, buffer, bytes_read, 0) <= 0) {
            error("ERROR sending file");
        }
		printf("Bytes send: %li\n", bytes_read);
    }
    fclose(file);
    printf("File sent successfully\n");	
}


int main(int argc, char *argv[])
{
	printf("Starting server...\n");

	int sockfd, conSocket, portno, n;
	uint8_t bufferRx[BUFSIZE_RX];
	uint8_t bufferTx[BUFSIZE_TX];
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	// if (argc < 2) // start server at port 9000
	// 	error("ERROR usage: port");
		
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	printf("Binding...\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	printf("Listen...\n");
	listen(sockfd,5);
	
	clilen = sizeof(cli_addr);
	long filesize;
	for (;;)
	{
		printf("Accept...\n");
		conSocket = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (conSocket < 0) error("ERROR on accept");
		else printf("Accepted\n");
		char *name = (char*)bufferRx;
		//extractFileName(name);
		readTextTCP(conSocket, name, STRBUFSIZE);

		printf("File: %s\n", name);

		filesize = getFilesize(name);
		char fSize[20];
		snprintf(fSize, sizeof(fSize), "%ld", filesize);
		printf("size: %li\n", filesize);

		writeTextTCP(conSocket, fSize);

		if (filesize > 0){
			sendFile(conSocket, name, filesize); // newsockfd is clientsocket, bufferrx is the filename.
		}
		

		//snprintf((char*)bufferTx, sizeof(bufferTx), "Got message: %s",(char*)bufferRx);

		
		close(conSocket);
	}
	close(sockfd);
	return 0; 
}