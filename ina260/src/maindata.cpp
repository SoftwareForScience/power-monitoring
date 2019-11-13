#include "client.hpp"

int main (int argc, char *argv[]) {

    Client klant;

    while(1){
        klant.Command(argc, argv);
    }

    return 0;
}