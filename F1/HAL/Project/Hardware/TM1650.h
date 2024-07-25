#ifndef _TM1650_H
#define _TM1650_H
#include "main.h"
/**
  ******************************************************************************
  * @file           : TM1650.h
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

//�����λ����ַ
#define	DIG0			0x68	//Dig0λ
#define	DIG1			0x6A	//Dig1λ
#define	DIG2			0x6C	//Dig2λ
#define	DIG3			0x6E    //Dig3λ


extern void TM1650_Init(void);
extern void DisplayNumber_4BitDig(uint16_t num);
extern void DigitalScan( void );

#endif

