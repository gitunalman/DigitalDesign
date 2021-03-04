/*
 * max6675.h
 *
 *  Created on: Mar 2, 2021
 *      Author: ber-a
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

#include <stdint.h>

void initSPI2(void);
uint16_t ReadTemp(void);

#endif /* INC_MAX6675_H_ */
