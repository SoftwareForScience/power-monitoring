#include "client.hpp"

//g++ -o client2 maindata.cpp client.cpp

int main (int argc, char *argv[]) {
    Client client;
    client.Init();
    //map<char *, char *> temperaturemap;

    while(!client.Stop()){
        usleep(1000000);
        client.Stop();
        client.Command(argc, argv);
        client.Connect();
        printf("pi-0: %s , pi-1: %s pi-2: %s , pi-3: %s pi-g: %s\n",
                client.pi_temp_zero, client.pi_temp_one,
               client.pi_temp_two, client.pi_temp_three,
               client.pi_temp_g);

        /*temperaturemap = client.Connect(argv);
        map<char *, char *>::iterator itr;

        for (itr = temperaturemap.begin(); itr != temperaturemap.end(); ++itr) {
            cout << '\t' << itr->first
                 << '\t' << itr->second << '\n';
        }
        cout << endl;*/
        //client.next = false;
        //client.Command(argc, pi);
        //client.next = false;
    }

    return 0;
}