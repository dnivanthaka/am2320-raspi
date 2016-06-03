#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>

#include "pca9685.h"
#include "i2c_master.h"

void pca9685_init(int fd)
{
    //Check for valid device reg values
    pca9685_regs[MODE1] = i2c_mread_reg(fd, MODE1);
    pca9685_regs[MODE2] = i2c_mread_reg(fd, MODE2);
    //setting device to sleep mode
    pca9685_regs[MODE1] |= SLEEP_BIT;
    i2c_mwrite_reg(fd, MODE1, pca9685_regs[MODE1]);

    //Restart routine, as per datasheet
    if(pca9685_regs[MODE1] & RESTART_BIT){
        pca9685_regs[MODE1] &= ~SLEEP_BIT;
        i2c_mwrite_reg(fd, MODE1, pca9685_regs[MODE1]);
	usleep(1000);
        pca9685_regs[MODE1] |= RESTART_BIT;
        i2c_mwrite_reg(fd, MODE1, pca9685_regs[MODE1]);
    }
    
    printf("MODE1 = %x\n", pca9685_regs[MODE1]);
    printf("MODE2 = %x\n", pca9685_regs[MODE2]);
    
    if(pca9685_regs[MODE1] != 0x11 || pca9685_regs[MODE2] != 0x04){
        printf("Invalid status values read.\n");
        return;
    }

    //uint8_t tmp[2] = {0};
    //pca9685_read_regs(fd, MODE1, tmp, 1);
    //printf("tmp1 = %x\n", tmp[0]);
    //printf("tmp2 = %x\n", tmp[1]);
    
    //waking up device
    pca9685_regs[MODE1] &= ~SLEEP_BIT;
    i2c_mwrite_reg(fd, MODE1, pca9685_regs[MODE1]);
    //delay as per datasheet
    usleep(1000);
}

