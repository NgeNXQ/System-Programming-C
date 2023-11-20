#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define BUFFER_LENGTH 256

int main(void) 
{
    int fd = open("/dev/my_cdev", O_RDONLY);

    if (fd < 0)
    {
        printf("Error number %d", errno);
        return -1;
    }

    unsigned char buf[BUFFER_LENGTH] = { 0 };

    read(fd, buf, BUFFER_LENGTH);

    printf("%s\n", buf);

    close(fd);

    return 0;
}