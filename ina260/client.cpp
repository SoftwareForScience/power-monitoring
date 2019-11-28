/* The port number is passed as an argument */
#include <fstream>
#include "client.hpp"

Client::Client(const std::vector<std::string> hostnames)
{
	this->pies = hostnames.size();
	this->hostnames = hostnames;

	std::ifstream lhost("/etc/hostname");
	lhost >> this->localhost;
	lhost.close();
	this->localhost += this->local;

	std::cout << "localhost: " << this->localhost << "\n";

    this->portno = PORT;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

void Client::Error(const char *msg) {
    perror(msg);
    exit(0);
}

std::map<std::string, std::string> Client::Call()
{

    for (auto &a : this->hostnames)
    {

	    if (this->sockfd < 0)
	    {   Error("ERROR opening socket");  }

	    if (this->localhost != a)
	    {
		    this->server = gethostbyname(a.c_str());

		    if (this->server == nullptr)
		    {
			    fprintf(stderr, "ERROR, no such host\n");
			    exit(0);
		    }
		    bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
		    this->serv_addr.sin_family = AF_INET;
		    bcopy((char *) this->server->h_addr, (char *) &this->serv_addr.sin_addr.s_addr,
		    		this->server->h_length);
		    this->serv_addr.sin_port = htons(this->portno);

		    if (connect(this->sockfd, (struct sockaddr *) &this->serv_addr,
		    		sizeof(this->serv_addr)) < 0)
		    {   Error("ERROR connecting");  }

		    bzero(this->buffer, DEGREE);
		    strcpy(this->buffer, this->tempp.c_str());

		    this->n = write(this->sockfd, this->buffer, strlen(this->buffer));

		    if (n < 0)
		    {   Error("ERROR writing to socket");   }

		    bzero(this->buffer, DEGREE);
		    this->n = read(this->sockfd, this->buffer, (DEGREE - 1));
		    this->m[a] = std::string(this->buffer);

		    if (this->n < 0)
		    {   Error("ERROR reading from socket"); }

		    close(this->sockfd);
	    } else
	    {
	        std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
			int rawtemp;
			file >> rawtemp;
			file.close();

		    this->m[a] = std::to_string((float)rawtemp / 1000);
	    }
    }

    return this->m;
}
