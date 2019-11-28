#include "client.hpp"

//g++ -o client2 maindata.cpp client.cpp

int main (int argc, char *argv[]) {
    Client client;
    client.Init();

    while (1) {
        usleep(1000000);
        client.Call(argc, argv);
        map<string, pair<string, string> >::const_iterator it;
        for (auto &it : client.Mapping(argv)) {
            std::cout << it.first << " " << it.second << "\n";
        }
    }
    return 0;
}