/* A simple client in the internet domain using TCP
The ip adresse and port number on server is passed as arguments
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm

Modified: Michael Alrøe
Extended to support file client!
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include "iknlib.h"

#define STRBUFSIZE 256
#define PORT 9001

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * @brief Receives a file from a server socket
 * @param serverSocket Socket stream to server
 * @param fileName Name of file. Might include path on server!
 */

void receiveFile(int serverSocket, const char *fileName, long fileSize)
{
	printf("Receiving: '%s', size: %li\n", fileName, fileSize);

	// Open the received file for writing
	FILE *file = fopen(fileName, "wb"); // Open file for writing in binary mode
	if (file == NULL)
	{
		error("ERROR opening file for writing");
	}

	uint8_t buffer[BUFSIZE];
	ssize_t bytes_received;
	long total_bytes_received = 0;

	// Receive file data from the server
	while (total_bytes_received < fileSize)
	{
		// Receive data from the server
		bytes_received = recv(serverSocket, buffer, BUFSIZE, 0);
		printf("Bytes received: %li\n", total_bytes_received);
		if (bytes_received < 0)
		{
			error("ERROR receiving file data from server");
		}
		else if (bytes_received == 0)
		{
			// Connection closed by server
			break;
		}

		// Write received data to the file
		fwrite(buffer, 1, bytes_received, file);

		total_bytes_received += bytes_received;
	}

	// Close the file
	printf("Bytes received: %li\n", total_bytes_received);
	fclose(file);

	printf("File received successfully\n");
}

int main(int argc, char *argv[])
{
	printf("Starting client...\n");

	if (argc < 3)
	{
		error("ERROR usage: "
			  "hostname"
			  ",  "
			  "filename"
			  "\n");
	}

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	uint8_t buffer[BUFSIZE];

	if (argc < 3)
	{
		error("ERROR usage: "
			  "hostname"
			  ",  "
			  "filename"
			  "\n");
	}
	portno = PORT;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(argv[1]);
	if (server == NULL)
		error("ERROR no such host");

	printf("Server IP: %s, Filename: %s\n", argv[1], argv[2]);

	printf("Connect...\n");
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(PORT);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	
	// printf("Please enter the message: ");
	// fgets((char*)buffer,sizeof(buffer),stdin);
	// strcpy((char*)buffer, "img.jpg");

	// Remove the newline character, if present
	// size_t len = strlen((char*)buffer);
	// if (len > 0 && buffer[len - 1] == '\n') {
	//     buffer[len - 1] = '\0'; // Replace newline with null terminator
	// }
	// Send filename to the server
	writeTextTCP(sockfd, argv[2]);

	// writeTextTCP(sockfd, (char*)buffer);

	long size = readFileSizeTCP(sockfd);

	if (size > 0)
	{
		printf("Filename: %s\n", argv[2]);
		// Receive the file from the server
		receiveFile(sockfd, argv[2], size);
		printf("Size: %li\n", size);
	}
	else if (size <= 0){
		printf("File does not exist");
	}
	// receiveFile(sockfd, (char*)buffer, size);
	

	// if (size > 0)
	// {
	// 	printf("Filename: %s\n", (char *)buffer);
	// 	receiveFile(sockfd, (char *)buffer, size);
	// }
	// bzero(buffer,sizeof(buffer));
	// n = read(sockfd,buffer,sizeof(buffer));  // socket read
	// n = recv(sockfd, buffer, sizeof(buffer), MSG_WAITALL);  // waits for full buffer or connection close
	// if (n < 0)
	//     error("ERROR reading from socket");
	printf("\n%s\n", (char *)buffer);

	printf("Closing client...\n\n");
	close(sockfd);
	return 0;
}
