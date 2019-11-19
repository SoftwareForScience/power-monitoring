/* The port number is passed as an argument */
#include "server.hpp"

void Server::Error(const char *msg) {
    perror(msg);
    exit(1);
}

bool Server::Stop(){
    if(!stop) {
        return false;
    }
    else {
        close(newsockfd);
        close(sockfd);
        return true;
    }
}

void Server::Connect(int argcc, char *argvv[]) {

    if (argcc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    // create a socket
    // socket(int domain, int type, int protocol)
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        Error("ERROR opening socket");
    }

    // clear address structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argvv[1]);

    /* setup the host_addr structure for use in bind call */
    // server byte order
    serv_addr.sin_family = AF_INET;

    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // convert short integer value for port must be converted into network byte order
    serv_addr.sin_port = htons(portno);

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure,
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        Error("ERROR on binding");
    }
}

void Server::Command() {


    // This listen() call tells the socket to listen to the incoming connections.
    // The listen() function places all incoming connection into a backlog queue
    // until accept() call accepts the connection.
    // Here, we set the maximum size for the backlog queue to 5.
    listen(sockfd,5);

    // The accept() call actually accepts an incoming connection

        clilen = sizeof(cli_addr);

        // This accept() function will write the connecting client's address info
        // into the the address structure and the size of that structure is clilen.
        // The accept() returns a new socket file descriptor for the accepted connection.
        // So, the original socket file descriptor can continue to be used
        // for accepting new connections while the new socker file descriptor is used for
        // communicating with the connected client.
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            Error("ERROR on accept");
        }

        //printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

        bzero(buffer, sizeof(buffer));

        n = read(newsockfd, buffer, (sizeof(buffer) - 1));

        if (n < 0) {
            Error("ERROR reading from socket");
        }
        if (strcmp(buffer, "stop\n") == 0) {
            stop = true;
        }
        else if (strcmp(buffer, "temp\n") == 0) {
            thermal = fopen("/sys/class/thermal/thermal_zone0/temp","r");
            x = fscanf(thermal,"%f",&millideg);
            fclose(thermal);
            systemp = millideg / 1000;
            temp = to_string(systemp);
            send(newsockfd, temp.c_str(), 13, 0);
        }
        else {
            send(newsockfd, "stuur is wat", 13, 0);
            //printf("Here is the message: %s\n", buffer);
        }
    // This send() function sends the 13 bytes of the string to the new socket

}
