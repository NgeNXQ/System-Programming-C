#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/current_time_device"

int main(void) 
{
    int fd = open(DEVICE_PATH, O_RDONLY);

    if (fd < 0) 
    {
        perror("Failed to open the device");
        return -1;
    }

    char buffer[256];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead < 0) 
    {
        perror("Failed to read from the device");
        close(fd);
        return -1;
    }

    printf("%s", buffer);

    close(fd);

    return 0;
}
