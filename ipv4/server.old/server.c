#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define PORT 8080 //Default port

void usage (char *name) {
  fprintf (stderr, "Usage: %s <src ip>\n", name);
  exit (1);
}

int main(int argc, char *argv[]){

    int fd =0;
    int confd = 0;
    int b,tot;
    char *name = argv[0];
    char *ip = argv[1];
    struct sockaddr_in sin4;
    char *filename = "tx-file.img";
    FILE* fp;
    char buff[1025];

    if (argc != 2) {
        usage (name);
    }

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    fprintf(stdout, "[+]Socket created\n");

    memset(&sin4, '0', sizeof(sin4));
    memset(buff, '0', sizeof(buff));

    sin4.sin_family = AF_INET;
    //sin4.sin_addr.s_addr = htonl(INADDR_ANY);
    sin4.sin_addr.s_addr = inet_addr(ip);
    sin4.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr*)&sin4, sizeof(sin4)) < 0) {
        perror("[-]Error in Binding");
        exit(1);
    }

     if (listen(fd, 10) == -1 ) {
        perror("[-]Error in Listening");
        exit(1);
     }

    fprintf(stdout,"[+]Listening in %s in port %d\n", ip, PORT);

    while(1){
        if ((confd = accept(fd, (struct sockaddr*)NULL, NULL)) == -1) {;
            perror("[-]Accept");
            continue;
        }

        if ((fp = fopen(filename, "wb")) == NULL) {
            perror("[-]File");
            return 2;
        }

        tot=0;
        if(fp != NULL){
            while( (b = recv(confd, buff, 1024,0))> 0 ) {
                tot+=b;
                fwrite(buff, 1, b, fp);
            }

            fprintf(stdout,"[+]Received byte: %d\n",tot);
            if (b<0)
               perror("[-]Receiving");

            fclose(fp);
        } else {
            perror("[-]File");
        }
        close(confd);
        
    }
    fclose (fp);
    close (confd);
    return 0;
}
