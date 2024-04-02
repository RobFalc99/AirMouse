/*
 * ds3231.c
 *
 *  Created on: May 17, 2022
 *      Author: Acer
 */

#include "i2c.h"
#include "ds3231.h"

DS3231Time ds3231time;

// Convert normal decimal numbers to binary coded decimal
uint8_t decToBcd(int16_t val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
int16_t bcdToDec(uint8_t val)
{
  return (int16_t)( (val/16*10) + (val%16) );
}


/* function to set time */

void set_time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c2, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

void get_time (void)
{
	uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);
	ds3231time.seconds = bcdToDec(get_time[0]);
	ds3231time.minutes = bcdToDec(get_time[1]);
	ds3231time.hour = bcdToDec(get_time[2]);
	ds3231time.dayofweek = bcdToDec(get_time[3]);
	ds3231time.dayofmonth = bcdToDec(get_time[4]);
	ds3231time.month = bcdToDec(get_time[5]);
	ds3231time.year = bcdToDec(get_time[6]);
}


float get_temp (void)
{
	uint8_t temp[2];
	HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}


void force_temp_conv (void)
{
	uint8_t status=0;
	uint8_t control=0;
	HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x0F, 1, &status, 1, 100);  // read status register
	if (!(status&0x04))  // if the BSY bit is not set
	{
		HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x0E, 1, &control, 1, 100);  // read control register
		HAL_I2C_Mem_Write(&hi2c2, DS3231_ADDRESS, 0x0E, 1, (uint8_t *)(control|(0x20)), 1, 100);  // write modified control register with CONV bit as'1'
	}
}
