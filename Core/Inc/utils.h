/*
 * utils.h
 *
 *  Created on: Jun 15, 2022
 *      Author: rf199
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "ff.h"

void myprintf(const char *fmt, ...);
void write_on_file(FIL *fil, char* buffer);
void read_from_file(FIL *fil, char* buffer, int buffer_len);


#endif /* INC_UTILS_H_ */
