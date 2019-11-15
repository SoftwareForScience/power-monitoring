/* The port number is passed as an argument */
#include "client.hpp"

void Client::Error(const char *msg) {
    perror(msg);
    exit(0);
}

bool Client::Stop() {
    if(!stop) {
        return false;
    }
    else {

        return true;
    }
}

void Client::Init() {
    hostname = fopen("/etc/hostname", "r");
    n = fscanf(hostname,"%s", host.c_str());
    fclose(hostname);
    //printf("%s", host.c_str());
    localhost += (string)host.c_str();
    //strncpy (localhost, host.c_str(), sizeof(localhost));
    printf("%s\n", localhost.c_str());
    localhost += local;
    printf("%s\n", localhost.c_str());

}
void Client::Connect() {
    pi_temp_zero = pi_zero;
    pi_temp_one = pi_one;
    pi_temp_two = pi_two;
    pi_temp_three = pi_three;
    pi_temp_g = pi_g;
}
/*
std::map<char *, char *> Client::Connect(char *argvv[]) {

    pi_temp_zero = pi_zero;
    pi_temp_one = pi_one;
    pi_temp_two = pi_two;
    pi_temp_three = pi_three;
    pi_temp_g = pi_g;

    // insert elements in random order
    temperatures.insert(pair<char *, char *>(argvv[3], pi_temp_zero));
    temperatures.insert(pair<char *, char *>(argvv[4], pi_temp_one));
    temperatures.insert(pair<char *, char *>(argvv[5], pi_temp_two));
    temperatures.insert(pair<char *, char *>(argvv[6], pi_temp_three));
    temperatures.insert(pair<char *, char *>(argvv[7], pi_temp_g));

    return temperatures;
}
*/
void Client::Command(int argcc, char *argvv[]) {
//    if(next == false) {

    if (argcc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argvv[0]);
        exit(0);
    }

    memset(pi_zero, 0, 15);
    memset(pi_one, 0, 15);
    memset(pi_two, 0, 15);
    memset(pi_three, 0, 15);
    memset(pi_g, 0, 15);

    pies = atoi(argvv[1]);
    printf("%d", pies);
    for(int i = 3; i < (pies + 3); i++) {

    portno = atoi(argvv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        Error("ERROR opening socket");
    }

        server = gethostbyname(argvv[i]);
        printf("%s\n", argvv[i]);

        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            Error("ERROR connecting");
        }

        //printf("Please enter the message: ");
        bzero(buffer, 256);
        //fgets(buffer, 255, stdin);
        buffer[tempp.size() + 1];
        strcpy(buffer, tempp.c_str());
        //printf("%s\n", buffer);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            Error("ERROR writing to socket");
        }
        if (strcmp(buffer, "temp\n") == 0) {
            //printf("hij gaat wat zeggen");
            if (strcmp(argvv[i], "raspberrypi-0.local") == 0) {
                //bzero(pi_temp_two_local, 256);
                n = read(sockfd, pi_zero, 14);
                //this->pi_temp_two_local = buffer;
            }
            else if (strcmp(argvv[i], "raspberrypi-1.local") == 0) {
                //bzero(pi_temp_three_local, 256);
                n = read(sockfd, pi_one, 14);
               // this-> = buffer;
            }
            else if (strcmp(argvv[i], "raspberrypi-2.local") == 0) {
                //bzero(pi_temp_three_local, 256);
                n = read(sockfd, pi_two, 14);
                // this-> = buffer;
            }
            else if (strcmp(argvv[i], "raspberrypi-3.local") == 0) {
                //bzero(pi_temp_three_local, 256);
                n = read(sockfd, pi_three, 14);
                // this-> = buffer;
            }
            else if (strcmp(argvv[i], "raspberrypi-g.local") == 0) {
                printf("so far so good");
            }
            else {
                bzero(buffer, 256);
                n = read(sockfd, buffer, 255);
            }
                // next = true;
        } else if (strcmp(buffer, "stop\n") == 0) {
            printf("hij gaat stoppen");
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            stop = true;
        } else {
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
        }
        if (n < 0) {
            Error("ERROR reading from socket");
        }

        //printf("pi-3: %s , pi-2: %s\n", pi_three, pi_two);

        //usleep(500000);

        close(sockfd);
    }
}