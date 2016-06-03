#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <stdint.h>

#include "i2c_master.h"

int i2c_mopen(uint8_t channel)
{
    int fd;
    char fpath[12];
    
    sprintf(fpath, "/dev/i2c-%d", channel);
    
    fd = open(fpath, O_RDWR|O_SYNC);
    if(fd < 0){
        printf("Error opening file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    return fd;
}

void i2c_mclose(int fd)
{
    if(fd){
        close(fd);
    }
}

int i2c_mset_addr(int fd, uint8_t addr)
{
    if(ioctl(fd, I2C_SLAVE, addr) < 0){
        printf("ioctl error");
        return EXIT_FAILURE;
    }
    
    return 0;
}

int i2c_mwrite(int fd, uint8_t data)
{
    if(write(fd, &data, 1) < 0){
        printf("Cannot write data %x\n", data);
        return -1;
    }
}

int i2c_mread(int fd, uint8_t *data, int count)
{
    if(read(fd, data, count) < count){
        printf("Cannot read data\n");
        return -1;
    }
}


int i2c_mread_reg(int fd, uint8_t reg)
{
    uint8_t data;
    
    if(write(fd, &reg, 1) < 0){
        printf("Cannot write to reg %x\n", reg);
        return -1;
    }
    
    if(read(fd, &data, 1) < 0){
        printf("Cannot read from reg %x\n", reg);
        return -1;
    }
    
    return data;
}

int i2c_mwrite_reg(int fd, uint8_t reg, uint8_t data)
{
    uint8_t dta[2] = {0};
    dta[0] = reg;
    dta[1] = data;
    
    if(write(fd, dta, 2) < 0){
        printf("Cannot write to reg %x\n", reg);
        return -1;
    }
    
    return 0;
}

int i2c_mwrite_reg_pair(int fd, uint8_t reg, uint16_t data)
{
    uint8_t byte[2];
    byte[0] = (uint8_t)(data & 0xff);
    byte[1] = (uint8_t)((data >> 8) & 0xff);
    
    
    i2c_mwrite_reg(fd, reg, byte[0]);
    i2c_mwrite_reg(fd, reg + 1, byte[1]);
    
    return 0;
}

int i2c_mread_reg_pair(int fd, uint8_t reg)
{
    uint16_t word;
    uint8_t byte[2];
    
    byte[0] = i2c_mread_reg(fd, reg);
    byte[1] = i2c_mread_reg(fd, reg + 1);
    
    word = (8 << byte[1]) | byte[0];
    return word;
}

int i2c_mread_regs(int fd, uint8_t st_reg, uint8_t* data, uint8_t count)
{
    int i;
    
    if(write(fd, &st_reg, 1) < 0){
        printf("Cannot write to reg %x\n", st_reg);
        return -1;
    }
    if(read(fd, data, count) < 0){
        printf("Cannot read from reg %x\n", st_reg);
        return -1;
    }
    
    return count;
}

int i2c_mwrite_regs(int fd, uint8_t st_reg, uint8_t* data, uint8_t count)
{
    int i;
      
    if(write(fd, &st_reg, 1) < 0){
        printf("Cannot write to reg %x\n", st_reg);
        return -1;
    }
    if(write(fd, data, count) < 0){
        printf("Cannot write to reg %x\n", st_reg);
        return -1;
    }
    
    return count;
}
