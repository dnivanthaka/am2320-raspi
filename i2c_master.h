#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <stdint.h>

int i2c_mopen(uint8_t channel);
int i2c_mset_addr(int fd, uint8_t addr);

int i2c_mwrite(int fd, uint8_t data);
int i2c_mread(int fd, uint8_t *data, int count);

int i2c_mread_reg(int fd, uint8_t reg);
int i2c_mwrite_reg(int fd, uint8_t reg, uint8_t data);

int i2c_mwrite_reg_pair(int fd, uint8_t reg, uint16_t data);
int i2c_mread_reg_pair(int fd, uint8_t reg);

int i2c_mread_regs(int fd, uint8_t st_reg, uint8_t* data, uint8_t count);
int i2c_mwrite_regs(int fd, uint8_t st_reg, uint8_t* data, uint8_t count);
#endif
