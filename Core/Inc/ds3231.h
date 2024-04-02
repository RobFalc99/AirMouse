/*
 * ds3231.h
 *
 *  Created on: May 17, 2022
 *      Author: Acer
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#define DS3231_ADDRESS 0xD0

typedef struct {
	int16_t seconds;
	int16_t minutes;
	int16_t hour;
	int16_t dayofweek;
	int16_t dayofmonth;
	int16_t month;
	int16_t year;
} DS3231Time;

uint8_t decToBcd(int16_t val);
int16_t bcdToDec(uint8_t val);

void set_time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void get_time (void);
float get_temp (void);
void force_temp_conv (void);

#endif /* INC_DS3231_H_ */
