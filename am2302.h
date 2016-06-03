#ifndef PCA9685_H
#define PCA9685_H

#define MODE1        0x00
#define MODE2        0x01
#define SUBADR1      0x02
#define SUBADR2      0x03
#define SUBADR3      0x04
#define ALLCALLADR   0x05

#define LED0_ON_L    0x06
#define LED0_ON_H    0x07
#define LED0_OFF_L   0x08
#define LED0_OFF_H   0x09

#define LED1_ON_L    0x0A
#define LED1_ON_H    0x0B
#define LED1_OFF_L   0x0C
#define LED1_OFF_H   0x0D

#define LED2_ON_L    0x0E
#define LED2_ON_H    0x0F
#define LED2_OFF_L   0x10
#define LED2_OFF_H   0x11

#define LED3_ON_L    0x12
#define LED3_ON_H    0x13
#define LED3_OFF_L   0x14
#define LED3_OFF_H   0x15

#define SLEEP_BIT    (1 << 4)
#define AI_BIT       (1 << 5)
#define RESTART_BIT  (1 << 7)

void pca9685_init(int fd);

#endif
