/* The port number is passed as an argument */
#include <fstream>
#include "client.hpp"

Client::Client(std::vector<std::string> hostnames)
{
	this->pies = hostnames.size();
	this->hostnames = hostnames;

	std::ifstream lhost("/etc/hostname");
	lhost >> this->localhost;
	lhost.close();
	this->localhost += this->local;

	std::cout << "localhost: " << this->localhost << "\n";
}

void Client::Error(const char *msg) {
    perror(msg);
    exit(0);
}

std::map<std::string, std::string> Client::Call()
{
    for (auto &a : this->hostnames)
    {
        std::cout << "Call " << a << std::endl;

	    portno = PORT;
	    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	    if (sockfd < 0)
	    {   Error("ERROR opening socket");  }

	    const char* chost = a.c_str();
	    if (this->localhost != a)
	    {
		    server = gethostbyname(chost);
		    printf("%s\n", chost);

		    if (server == nullptr)
		    {
			    fprintf(stderr, "ERROR, no such host\n");
			    exit(0);
		    }
		    bzero((char *) &serv_addr, sizeof(serv_addr));
		    serv_addr.sin_family = AF_INET;
		    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
		    serv_addr.sin_port = htons(portno);

		    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		    {   Error("ERROR connecting");  }

		    bzero(buffer, 256);
		    buffer[this->pies + 1];
		    strcpy(buffer, tempp.c_str());

		    n = write(sockfd, buffer, strlen(buffer));

		    if (n < 0)
		    {   Error("ERROR writing to socket");   }

		    bzero(buffer, DEGREE);
		    n = read(sockfd, buffer, (DEGREE - 1));
		    this->m[a] = std::string(buffer);

		    if (n < 0)
		    {   Error("ERROR reading from socket"); }

		    close(sockfd);
	    } else
	    {
	        std::cout << "getting local temperature" << std::endl;

	        std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
			int rawtemp;
			file >> rawtemp;
			file.close();

		    this->m[a] = std::to_string((float)rawtemp / 1000);
	    }
    }

    return this->m;
}
