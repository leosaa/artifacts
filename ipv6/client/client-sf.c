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
#include <sys/sendfile.h>	/* sendfile */

#include <fcntl.h>

#define PORT 8080 //Defaul port

void usage (char *name) {
  fprintf (stderr, "Usage: %s <dst ip> [<dst port>] [<filename>]\n", name);
  exit (1);
}

int main(int argc, char *argv[]){

    int fd =0;
    char *name = argv[0];
    char rbuff[1024];
    char *ip = argv[1];
    int port = PORT;
    off_t off = 0;
    char *filename = argv[3];
    int file_fd;
    int tot=0;

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

    file_fd = open(filename,  O_RDONLY);
    fstat(file_fd, &st);
    fprintf(stdout,"[+]File size %ld\n", st.st_size);

    memset(rbuff, '0', sizeof(rbuff));
    if ((fd = socket(AF_INET6, SOCK_STREAM, 0)) <0){
        perror("[-]Socket creation\n");
    }

    sin6.sin6_family = AF_INET6;
    sin6.sin6_port = htons(port);
    //sin6.sin6_addr = inet_addr(ip);
    inet_pton(AF_INET6, ip, &sin6.sin6_addr);

    if ((connect(fd, (struct sockaddr *)&sin6, sizeof(sin6))) == -1) {
        perror("[-]Connect");
        return 1;
    }

    if ((tot=sendfile(fd, file_fd,&off,st.st_size)) == -1) {
        perror("[-]Error in sendfile\n");
    } else {
        fprintf(stdout,"[+]Total bytes send %d\n", tot);
    }

    //fclose(fp);
    close(file_fd);
    close(fd);
    return 0;

}
