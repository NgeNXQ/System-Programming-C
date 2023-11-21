#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define BUFFER_LENGTH 256

int main(void) 
{
    int file_dialog = open("/dev/labwork5_device", O_RDONLY);

    if (file_dialog < 0)
    {
        printf("Error number %d", errno);
        return -1;
    }

    unsigned char buffer[BUFFER_LENGTH] = { 0 };

    read(file_dialog, buffer, BUFFER_LENGTH);

    printf("%s\n", buffer);

    close(file_dialog);

    return 0;
}

