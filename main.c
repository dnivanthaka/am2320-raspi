#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>

//#include "pca9685.h"
#include "i2c_master.h"

#define I2C_ADDR         (0xB8 >> 1)


int main(int argc, char* argv[])
{
    int fd;
    uint8_t data[4] = {0};
    
    fd = i2c_mopen(1);
    i2c_mset_addr(fd, I2C_ADDR);
    	
    data[0] = 0x03;
    write(fd, &data, 1);
    data[0] = 0x00;
    write(fd, &data, 1);
    data[0] = 0x04;
    write(fd, &data, 1);
    read(fd, &data, 4);
    //data[0] = 0x00;
    //data[1] = 0x04;

    //i2c_mwrite_regs(fd, 0x03, data, 2);
    //i2c_mread(fd, data, 4);

    printf("data 0 = %x\n", data[0]); 
    printf("data 1 = %x\n", data[1]); 
    printf("data 2 = %x\n", data[2]); 
    printf("data 3 = %x\n", data[3]); 

    uint16_t humidity = data[0] << 8 | data[1];
    uint16_t temp = data[2] << 8 | data[3];
    printf("Temp = %d\n", temp);
    printf("Humidity  = %d\n", humidity);
    
    i2c_mclose(fd);
    
    return 0;
}


