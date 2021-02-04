#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/in.h>
#include <time.h>
#include "unique_id.h"

#define MAX_VALUE 20
#define MIN_VALUE 2

int random_gen(int ,int );


int cfd,sfd;
struct sockaddr_in saddr;
int len;
unsigned char Buffer[1024];

//structure init with Unique Program ID, Packet Number, data & timestamp
struct packet   {
    int Prgm_ID;
    int packet_num;
    int data;
    time_t time;
}acc_struct;



int random_gen(int min_num, int max_num)    {
    {
        int result = 0, low_num = 2, hi_num = 20;

        if (min_num < max_num)
        {
            low_num = min_num;
            hi_num = max_num + 1; // include max_num in output
        } else {
            low_num = max_num + 1; // include max_num in output
            hi_num = min_num;
        }

        srand(time(NULL));
        result = (rand() % (hi_num - low_num)) + low_num;
        return result;
    }
    
}

int main(int argc, char const *argv[])
{ 
    int i=1;
    while(i)
    {
        //def init 
         time_t second;
        acc_struct.time = time(&second);
        acc_struct.Prgm_ID = ACC_RC; //1 for Acceleration
        acc_struct.packet_num = i;
        acc_struct.data = 0;

        acc_struct.data = random_gen(MIN_VALUE, MAX_VALUE);

    //  printf("timestamp:%ld\ndata-%d\n", acc_struct.time, acc_struct.data);//check

	    cfd = socket(AF_INET, SOCK_STREAM,0);

        if(cfd == -1)   
        {
            perror("socket open/Acceleration_Rocket");
            return -1;  
         }

	    saddr.sin_family = AF_INET;
        saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        saddr.sin_port = htons(6601);

	    sfd = connect(cfd,(struct sockaddr *)&saddr,sizeof(struct sockaddr_in)); //session create...
        if(sfd == -1)   
        {
            perror("Connect() open/Acceleration_Rocket");
            return -1;  
        }

	    write(sfd,&acc_struct,sizeof(acc_struct));

	    
        
        i++;
        sleep(1);
    }
    return 0;
    close(cfd);
}