/* The port number is passed as an argument */
#include "client.hpp"

void Client::Error(const char *msg) {
    perror(msg);
    exit(0);
}

void Client::Init() {       //get clients own hostname
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

void Client::Call(int argcc, char *argvv[]) { //expects input to have amount of servers to ask, port, server names
    if (pass == false) {                      //example ./file 5 20001 raspberrypi-0.local raspberrypi-1.local raspberrypi-2.local raspberrypi-3.local raspberrypi-g.local

        if (argcc < 3) {
            fprintf(stderr, "usage %s hostname port\n", argvv[0]);
            exit(0);
        }

        pies = atoi(argvv[1]);
        printf("%d", pies);
        for (int i = 3; i < (pies + 3); i++) {

            portno = atoi(argvv[2]);
            sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if (sockfd < 0) {
                Error("ERROR opening socket");
            }
            if (!(strcmp(argvv[i], localhost.c_str()) == 0)) {
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
                bzero(buffer, DEGREE);
                n = read(sockfd, buffer, (DEGREE - 1));
                strncpy(templogs[(i - 3)], buffer, DEGREE);

                if (n < 0) {
                    Error("ERROR reading from socket");
                }

                close(sockfd);
            } else {
                thermal = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
                x = fscanf(thermal, "%f", &millideg);
                fclose(thermal);
                systemp = millideg / 1000;
                sprintf(templogs[i - 3], "%f", systemp);
            }
        }
    }
    pass = true;
}

map<std::string, std::string> Client::Mapping(char *argvv[]) {      //make map and return the value
    if (pass == true) {
        for (int i = 0; i < pies; i++) {
            printf("%s: %s\n", argvv[(i + 3)], templogs[i]);
            // temps.insert(argvv[(i + 3)], templogs[i] );

            this->m[argvv[(i + 3)]] = templogs[i];
        }
    }
    pass = false;
    return m;
}
