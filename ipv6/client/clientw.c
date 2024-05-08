#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define PORT 8080 //Defaul port

void usage (char *name) {
  fprintf (stderr, "Usage: %s <dst ip> [<dst port>] [<filename>]\n", name);
  exit (1);
}

int main(int argc, char *argv[]){

    int fd =0;
    int b;
    int size = 0;
    char *name = argv[0];
    char rbuff[1025];
    char sendbuffer[1024];
    char *ip = argv[1];
    int port = PORT;
    char *filename = argv[3];
    FILE *fp;
    int tot = 0;

    struct sockaddr_in6 sin6;
    struct stat st;

    if ((argc < 2) || (argc > 4)) {
        usage (name);
    }
    if (argc == 2) {
        port = PORT;
        filename = "file10MB.img"; //Default file to transfer
    }
    else if (argc == 3) {
        filename = "file10MB.img"; //Default file to transfer
    }
    else {
        port = atoi (argv[2]);
        filename = argv[3];
    }

    if ((fp = fopen(filename, "rb")) == NULL) {
        perror("[-]File");
        return 2;
    }

    stat(filename,&st);
    size = st.st_size;
    fprintf(stdout,"[+]File size %d\n", size);

    memset(rbuff, '0', sizeof(rbuff));

    if ((fd = socket(AF_INET6, SOCK_STREAM, 0)) < 0){
        perror("[-]Socket creation\n");
    }

    sin6.sin6_family = AF_INET6;
    sin6.sin6_port = htons(port);
    inet_pton(AF_INET6, ip, &sin6.sin6_addr);

    if ((connect(fd, (struct sockaddr *)&sin6, sizeof(sin6))) == -1) {
        perror("[-]Connect");
        return 1;
    }

    while( (b = fread(sendbuffer, 1, sizeof(sendbuffer), fp))>0 ){
        write(fd, sendbuffer, sizeof(sendbuffer));
        tot +=b;
    }
    fprintf(stdout, "[+]Total bytes send %d\n", tot);

    fclose(fp);
    close(fd);
    return 0;

}
