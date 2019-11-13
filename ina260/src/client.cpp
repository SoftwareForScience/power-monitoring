/* The port number is passed as an argument */
#include "client.hpp"

void Client::Error(const char *msg) {
    perror(msg);
    exit(0);
}

void Client::Command(int argcc, char *argvv[]) {
    if (argcc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argvv[0]);
        exit(0);
    }
    for (int i = 0; i < 5; i++) {
    portno = atoi(argvv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        Error("ERROR opening socket");
    }
    server = gethostbyname(argvv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        Error("ERROR connecting");
    }

        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            Error("ERROR writing to socket");
        }
        if (strcmp(buffer, "temp\n") == 0){
            printf("hij gaat wat zeggen");
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
        }
        else {
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
        }
        if (n < 0) {
            Error("ERROR reading from socket");
        }
        int x = (int)buffer;
        printf("%s\n", buffer);
        printf("%d\n", x);
        x = 0;
    }

    close(sockfd);

}