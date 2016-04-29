/* drivers/video/sc8825/lcd_rm68200g_mipi.c
 *
 * Support for rm68200g mipi LCD device
 *
 * Copyright (C) 2010 Spreadtrum
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/bug.h>
#include <linux/delay.h>
#include "../sprdfb_panel.h"

//#define LCD_Delay(ms)  uDelay(ms*1000)

#define MAX_DATA   64  ////48

typedef struct LCM_Init_Code_tag {
	unsigned int tag;
	unsigned char data[MAX_DATA];
}LCM_Init_Code;

typedef struct LCM_force_cmd_code_tag{
	unsigned int datatype;
	LCM_Init_Code real_cmd_code;
}LCM_Force_Cmd_Code;

#define LCM_TAG_SHIFT 24
#define LCM_TAG_MASK  ((1 << 24) -1)
#define LCM_SEND(len) ((1 << LCM_TAG_SHIFT)| len)
#define LCM_SLEEP(ms) ((2 << LCM_TAG_SHIFT)| ms)
//#define ARRAY_SIZE(array) ( sizeof(array) / sizeof(array[0]))

#define LCM_TAG_SEND  (1<< 0)
#define LCM_TAG_SLEEP (1 << 1)

static LCM_Init_Code init_data[] = {
#if 0 //RM68200GA0_T050SP01_GAMMA2.5_20150817

{LCM_SEND(2),  {0xFE,  0x01 }},
{LCM_SEND(2),  {0x24,  0xC0 }},
{LCM_SEND(2),  {0x25,  0x53 }},
{LCM_SEND(2),  {0x2B,  0xC5 }},
{LCM_SEND(2),  {0x16,  0x52 }},
{LCM_SEND(2),  {0x27,  0x0D }},
{LCM_SEND(2),  {0x29,  0x0D }},
{LCM_SEND(2),  {0x2A,  0x0D }},
{LCM_SEND(2),  {0x2F,  0x50 }}, //54

{LCM_SEND(2),  {0x34,  0x55 }},
{LCM_SEND(2),  {0x1B,  0x00 }},
{LCM_SEND(2),  {0x12,  0x08 }},
{LCM_SEND(2),  {0x1A,  0x06 }},

//{0x46,  0x7A},
{LCM_SEND(2),  {0x52,  0x78 }},
{LCM_SEND(2),  {0x53,  0x00 }},
{LCM_SEND(2),  {0x54,  0x78 }},
{LCM_SEND(2),  {0x55,  0x00 }},
{LCM_SEND(2),  {0xFE,  0x03 }},
{LCM_SEND(2),  {0x01,  0x14 }},
{LCM_SEND(2),  {0x02,  0x01 }},
{LCM_SEND(2),  {0x03,  0x00 }},
{LCM_SEND(2),  {0x04,  0x00 }},
{LCM_SEND(2),  {0x05,  0x00 }},
{LCM_SEND(2),  {0x06,  0x00 }},
{LCM_SEND(2),  {0x07,  0x05 }},
{LCM_SEND(2),  {0x08,  0x14 }},
{LCM_SEND(2),  {0x09,  0x06 }},
{LCM_SEND(2),  {0x0A,  0x00 }},
{LCM_SEND(2),  {0x0B,  0x00 }},
{LCM_SEND(2),  {0x0C,  0x00 }},
{LCM_SEND(2),  {0x0D,  0x00 }},
{LCM_SEND(2),  {0x0E,  0x0A }},
{LCM_SEND(2),  {0x0F,  0x0B }},
{LCM_SEND(2),  {0x10,  0x0C }},
{LCM_SEND(2),  {0x11,  0x0D }},
{LCM_SEND(2),  {0x12,  0x00 }},
{LCM_SEND(2),  {0x13,  0x00 }},
{LCM_SEND(2),  {0x14,  0x00 }},
{LCM_SEND(2),  {0x15,  0xC5 }},
{LCM_SEND(2),  {0x16,  0x08 }},
{LCM_SEND(2),  {0x17,  0x0E }},
{LCM_SEND(2),  {0x18,  0x0F }},
{LCM_SEND(2),  {0x19,  0x10 }},
{LCM_SEND(2),  {0x1A,  0x11 }},
{LCM_SEND(2),  {0x1B,  0x00 }},
{LCM_SEND(2),  {0x1C,  0x00 }},
{LCM_SEND(2),  {0x1D,  0x00 }},
{LCM_SEND(2),  {0x1E,  0x85 }},
{LCM_SEND(2),  {0x1F,  0x08 }},
{LCM_SEND(2),  {0x20,  0x00 }},
{LCM_SEND(2),  {0x21,  0x00 }},
{LCM_SEND(2),  {0x22,  0x0A }},
{LCM_SEND(2),  {0x23,  0x10 }},
{LCM_SEND(2),  {0x24,  0x12 }},
{LCM_SEND(2),  {0x25,  0x2D }},
{LCM_SEND(2),  {0x26,  0x00 }},
{LCM_SEND(2),  {0x27,  0x14 }},
{LCM_SEND(2),  {0x28,  0x16 }},
{LCM_SEND(2),  {0x29,  0x2D }},
{LCM_SEND(2),  {0x2A,  0x00 }},
{LCM_SEND(2),  {0x2B,  0x00 }},
{LCM_SEND(2),  {0x2C,  0x00 }},
{LCM_SEND(2),  {0x2D,  0x00 }},
{LCM_SEND(2),  {0x2E,  0x00 }},
{LCM_SEND(2),  {0x2F,  0x00 }},
{LCM_SEND(2),  {0x30,  0x00 }},
{LCM_SEND(2),  {0x31,  0x00 }},
{LCM_SEND(2),  {0x32,  0x00 }},
{LCM_SEND(2),  {0x33,  0x00 }},
{LCM_SEND(2),  {0x34,  0x00 }},
{LCM_SEND(2),  {0x35,  0x00 }},
{LCM_SEND(2),  {0x36,  0x00 }},
{LCM_SEND(2),  {0x37,  0x00 }},
{LCM_SEND(2),  {0x38,  0x00 }},
{LCM_SEND(2),  {0x39,  0x00 }},
{LCM_SEND(2),  {0x3A,  0x00 }},
{LCM_SEND(2),  {0x3B,  0x00 }},
{LCM_SEND(2),  {0x3C,  0x00 }},
{LCM_SEND(2),  {0x3D,  0x00 }},
{LCM_SEND(2),  {0x3E,  0x00 }},
{LCM_SEND(2),  {0x3F,  0x00 }},
{LCM_SEND(2),  {0x40,  0x00 }},
{LCM_SEND(2),  {0x41,  0x00 }},
{LCM_SEND(2),  {0x42,  0x00 }},
{LCM_SEND(2),  {0x43,  0x00 }},
{LCM_SEND(2),  {0x44,  0x00 }},
{LCM_SEND(2),  {0x45,  0x00 }},
{LCM_SEND(2),  {0x46,  0x00 }},
{LCM_SEND(2),  {0x47,  0x00 }},
{LCM_SEND(2),  {0x48,  0x00 }},
{LCM_SEND(2),  {0x49,  0x00 }},
{LCM_SEND(2),  {0x4A,  0x00 }},
{LCM_SEND(2),  {0x4B,  0x00 }},
{LCM_SEND(2),  {0x4C,  0x00 }},
{LCM_SEND(2),  {0x4D,  0x00 }},
{LCM_SEND(2),  {0x4E,  0x00 }},
{LCM_SEND(2),  {0x4F,  0x00 }},
{LCM_SEND(2),  {0x50,  0x00 }},
{LCM_SEND(2),  {0x51,  0x00 }},
{LCM_SEND(2),  {0x52,  0x00 }},
{LCM_SEND(2),  {0x53,  0x00 }},
{LCM_SEND(2),  {0x54,  0x00 }},
{LCM_SEND(2),  {0x55,  0x00 }},
{LCM_SEND(2),  {0x56,  0x00 }},
{LCM_SEND(2),  {0x57,  0x00 }},
{LCM_SEND(2),  {0x58,  0x00 }},
{LCM_SEND(2),  {0x59,  0x00 }},
{LCM_SEND(2),  {0x5A,  0x00 }},
{LCM_SEND(2),  {0x5B,  0x00 }},
{LCM_SEND(2),  {0x5C,  0x00 }},
{LCM_SEND(2),  {0x5D,  0x00 }},
{LCM_SEND(2),  {0x5E,  0x00 }},
{LCM_SEND(2),  {0x5F,  0x00 }},
{LCM_SEND(2),  {0x60,  0x00 }},
{LCM_SEND(2),  {0x61,  0x00 }},
{LCM_SEND(2),  {0x62,  0x00 }},
{LCM_SEND(2),  {0x63,  0x00 }},
{LCM_SEND(2),  {0x64,  0x00 }},
{LCM_SEND(2),  {0x65,  0x00 }},
{LCM_SEND(2),  {0x66,  0x00 }},
{LCM_SEND(2),  {0x67,  0x00 }},
{LCM_SEND(2),  {0x68,  0x00 }},
{LCM_SEND(2),  {0x69,  0x00 }},
{LCM_SEND(2),  {0x6A,  0x00 }},
{LCM_SEND(2),  {0x6B,  0x00 }},
{LCM_SEND(2),  {0x6C,  0x00 }},
{LCM_SEND(2),  {0x6D,  0x00 }},
{LCM_SEND(2),  {0x6E,  0x00 }},
{LCM_SEND(2),  {0x6F,  0x00 }},
{LCM_SEND(2),  {0x70,  0x00 }},
{LCM_SEND(2),  {0x71,  0x00 }},
{LCM_SEND(2),  {0x72,  0x00 }},
{LCM_SEND(2),  {0x73,  0x00 }},
{LCM_SEND(2),  {0x74,  0x00 }},
{LCM_SEND(2),  {0x75,  0x00 }},
{LCM_SEND(2),  {0x76,  0x00 }},
{LCM_SEND(2),  {0x77,  0x00 }},
{LCM_SEND(2),  {0x78,  0x00 }},
{LCM_SEND(2),  {0x79,  0x00 }},
{LCM_SEND(2),  {0x7A,  0x00 }},
{LCM_SEND(2),  {0x7B,  0x00 }},
{LCM_SEND(2),  {0x7C,  0x00 }},
{LCM_SEND(2),  {0x7D,  0x00 }},
{LCM_SEND(2),  {0x7E,  0x81 }},
{LCM_SEND(2),  {0x7F,  0x1C }},
{LCM_SEND(2),  {0x80,  0x1D }},
{LCM_SEND(2),  {0x81,  0x0B }},
{LCM_SEND(2),  {0x82,  0x09 }},
{LCM_SEND(2),  {0x83,  0x0F }},
{LCM_SEND(2),  {0x84,  0x3F }},
{LCM_SEND(2),  {0x85,  0x3F }},
{LCM_SEND(2),  {0x86,  0x3F }},
{LCM_SEND(2),  {0x87,  0x3F }},
{LCM_SEND(2),  {0x88,  0x3F }},
{LCM_SEND(2),  {0x89,  0x3F }},
{LCM_SEND(2),  {0x8A,  0x3F }},
{LCM_SEND(2),  {0x8B,  0x3F }},
{LCM_SEND(2),  {0x8C,  0x3F }},
{LCM_SEND(2),  {0x8D,  0x3F }},
{LCM_SEND(2),  {0x8E,  0x3F }},
{LCM_SEND(2),  {0x8F,  0x3F }},
{LCM_SEND(2),  {0x90,  0x3F }},
{LCM_SEND(2),  {0x91,  0x0D }},
{LCM_SEND(2),  {0x92,  0x05 }},
{LCM_SEND(2),  {0x93,  0x07 }},
{LCM_SEND(2),  {0x94,  0x06 }},
{LCM_SEND(2),  {0x95,  0x04 }},
{LCM_SEND(2),  {0x96,  0x0C }},
{LCM_SEND(2),  {0x97,  0x3F }},
{LCM_SEND(2),  {0x98,  0x3F }},
{LCM_SEND(2),  {0x99,  0x3F }},
{LCM_SEND(2),  {0x9A,  0x3F }},
{LCM_SEND(2),  {0x9B,  0x3F }},
{LCM_SEND(2),  {0x9C,  0x3F }},
{LCM_SEND(2),  {0x9D,  0x3F }},
{LCM_SEND(2),  {0x9E,  0x3F }},
{LCM_SEND(2),  {0x9F,  0x3F }},
{LCM_SEND(2),  {0xA0,  0x3F }},
{LCM_SEND(2),  {0xA2,  0x3F }},
{LCM_SEND(2),  {0xA3,  0x3F }},
{LCM_SEND(2),  {0xA4,  0x3F }},
{LCM_SEND(2),  {0xA5,  0x0E }},
{LCM_SEND(2),  {0xA6,  0x08 }},
{LCM_SEND(2),  {0xA7,  0x0A }},
{LCM_SEND(2),  {0xA9,  0x1D }},
{LCM_SEND(2),  {0xAA,  0x1C }},
{LCM_SEND(2),  {0xAB,  0x00 }},
{LCM_SEND(2),  {0xAC,  0x01 }},
{LCM_SEND(2),  {0xAD,  0x1D }},
{LCM_SEND(2),  {0xAE,  0x1C }},
{LCM_SEND(2),  {0xAF,  0x0C }},
{LCM_SEND(2),  {0xB0,  0x0E }},
{LCM_SEND(2),  {0xB1,  0x08 }},
{LCM_SEND(2),  {0xB2,  0x3F }},
{LCM_SEND(2),  {0xB3,  0x3F }},
{LCM_SEND(2),  {0xB4,  0x3F }},
{LCM_SEND(2),  {0xB5,  0x3F }},
{LCM_SEND(2),  {0xB6,  0x3F }},
{LCM_SEND(2),  {0xB7,  0x3F }},
{LCM_SEND(2),  {0xB8,  0x3F }},
{LCM_SEND(2),  {0xB9,  0x3F }},
{LCM_SEND(2),  {0xBA,  0x3F }},
{LCM_SEND(2),  {0xBB,  0x3F }},
{LCM_SEND(2),  {0xBC,  0x3F }},
{LCM_SEND(2),  {0xBD,  0x3F }},
{LCM_SEND(2),  {0xBE,  0x3F }},
{LCM_SEND(2),  {0xBF,  0x0A }},
{LCM_SEND(2),  {0xC0,  0x06 }},
{LCM_SEND(2),  {0xC1,  0x04 }},
{LCM_SEND(2),  {0xC2,  0x05 }},
{LCM_SEND(2),  {0xC3,  0x07 }},
{LCM_SEND(2),  {0xC4,  0x0B }},
{LCM_SEND(2),  {0xC5,  0x3F }},
{LCM_SEND(2),  {0xC6,  0x3F }},
{LCM_SEND(2),  {0xC7,  0x3F }},
{LCM_SEND(2),  {0xC8,  0x3F }},
{LCM_SEND(2),  {0xC9,  0x3F }},
{LCM_SEND(2),  {0xCA,  0x3F }},
{LCM_SEND(2),  {0xCB,  0x3F }},
{LCM_SEND(2),  {0xCC,  0x3F }},
{LCM_SEND(2),  {0xCD,  0x3F }},
{LCM_SEND(2),  {0xCE,  0x3F }},
{LCM_SEND(2),  {0xCF,  0x3F }},
{LCM_SEND(2),  {0xD0,  0x3F }},
{LCM_SEND(2),  {0xD1,  0x3F }},
{LCM_SEND(2),  {0xD2,  0x09 }},
{LCM_SEND(2),  {0xD3,  0x0F }},
{LCM_SEND(2),  {0xD4,  0x0D }},
{LCM_SEND(2),  {0xD5,  0x1C }},
{LCM_SEND(2),  {0xD6,  0x1D }},
{LCM_SEND(2),  {0xD7,  0x00 }},
{LCM_SEND(2),  {0xDC,  0x02 }},
{LCM_SEND(2),  {0xDE,  0x11 }},
{LCM_SEND(2),  {0xFE,  0x0E }},
{LCM_SEND(2),  {0x01,  0x75 }},
{LCM_SEND(2),  {0xFE,  0x04 }},
{LCM_SEND(2),  {0x60,  0x00 }},
{LCM_SEND(2),  {0x61,  0x18 }},
{LCM_SEND(2),  {0x62,  0x1F }},
{LCM_SEND(2),  {0x63,  0x0F }},
{LCM_SEND(2),  {0x64,  0x07 }},
{LCM_SEND(2),  {0x65,  0x14 }},
{LCM_SEND(2),  {0x66,  0x0E }},
{LCM_SEND(2),  {0x67,  0x0A }},
{LCM_SEND(2),  {0x68,  0x17 }},
{LCM_SEND(2),  {0x69,  0x0D }},
{LCM_SEND(2),  {0x6A,  0x0D }},
{LCM_SEND(2),  {0x6B,  0x06 }},
{LCM_SEND(2),  {0x6C,  0x0E }},
{LCM_SEND(2),  {0x6D,  0x0C }},
{LCM_SEND(2),  {0x6E,  0x09 }},
{LCM_SEND(2),  {0x6F,  0x00 }},
{LCM_SEND(2),  {0x70,  0x00 }},
{LCM_SEND(2),  {0x71,  0x18 }},
{LCM_SEND(2),  {0x72,  0x1F }},
{LCM_SEND(2),  {0x73,  0x0F }},
{LCM_SEND(2),  {0x74,  0x07 }},
{LCM_SEND(2),  {0x75,  0x14 }},
{LCM_SEND(2),  {0x76,  0x0E }},
{LCM_SEND(2),  {0x77,  0x0A }},
{LCM_SEND(2),  {0x78,  0x17 }},
{LCM_SEND(2),  {0x79,  0x0D }},
{LCM_SEND(2),  {0x7A,  0x0D }},
{LCM_SEND(2),  {0x7B,  0x06 }},
{LCM_SEND(2),  {0x7C,  0x0E }},
{LCM_SEND(2),  {0x7D,  0x0C }},
{LCM_SEND(2),  {0x7E,  0x09 }},
{LCM_SEND(2),  {0x7F,  0x00 }},
{LCM_SEND(2),  {0xFE,  0x0B }},
{LCM_SEND(2),  {0x21,  0x50 }},
{LCM_SEND(2),  {0x22,  0x50 }},
{LCM_SEND(2),  {0xFE,  0x00 }},
{LCM_SEND(2),  {0x35,  0x00 }},
{LCM_SEND(2),  {0x00,  0x00 }},
{LCM_SEND(2),  {0x11,  0x00 }},
{LCM_SLEEP(200),},
{LCM_SEND(2),  {0x29,  0x00 }},
{LCM_SLEEP(20),},                                      	
#endif


{LCM_SEND(2),{0xFE,0x01}},

{LCM_SEND(2),{0x24,0x00}},

{LCM_SEND(2),{0x25,0x53}},

{LCM_SEND(2),{0x26,0x00}},

{LCM_SEND(2),{0x27,0x0A}},

{LCM_SEND(2),{0x29,0x0A}},

{LCM_SEND(2),{0x2B,0xE5}},

{LCM_SEND(2),{0x16,0x52}},

{LCM_SEND(2),{0x2F,0x54}},

{LCM_SEND(2),{0x34,0x59}},

{LCM_SEND(2),{0x1B,0x50}},

{LCM_SEND(2),{0x12,0x02}},

{LCM_SEND(2),{0x1A,0x06}},

{LCM_SEND(2),{0x46,0x5F}},

{LCM_SEND(2),{0x52,0x70}},

{LCM_SEND(2),{0x53,0x00}},

{LCM_SEND(2),{0x54,0x70}},

{LCM_SEND(2),{0x55,0x00}},

{LCM_SEND(2),{0x5F,0x13}},

{LCM_SEND(2),{0xFE,0x03}},

{LCM_SEND(2),{0x00,0x05}},

{LCM_SEND(2),{0x01,0x16}},

{LCM_SEND(2),{0x02,0x0B}},

{LCM_SEND(2),{0x03,0x0F}},

{LCM_SEND(2),{0x04,0x7D}},

{LCM_SEND(2),{0x05,0x00}},

{LCM_SEND(2),{0x06,0x50}},

{LCM_SEND(2),{0x07,0x05}},

{LCM_SEND(2),{0x08,0x16}},

{LCM_SEND(2),{0x09,0x0D}},

{LCM_SEND(2),{0x0A,0x11}},

{LCM_SEND(2),{0x0B,0x7D}},

{LCM_SEND(2),{0x0C,0x00}},

{LCM_SEND(2),{0x0D,0x50}},

{LCM_SEND(2),{0x0E,0x07}},

{LCM_SEND(2),{0x0F,0x08}},

{LCM_SEND(2),{0x10,0x01}},

{LCM_SEND(2),{0x11,0x02}},

{LCM_SEND(2),{0x12,0x00}},

{LCM_SEND(2),{0x13,0x7D}},

{LCM_SEND(2),{0x14,0x00}},

{LCM_SEND(2),{0x15,0x85}},

{LCM_SEND(2),{0x16,0x08}},

{LCM_SEND(2),{0x17,0x03}},

{LCM_SEND(2),{0x18,0x04}},

{LCM_SEND(2),{0x19,0x05}},

{LCM_SEND(2),{0x1A,0x06}},

{LCM_SEND(2),{0x1B,0x00}},

{LCM_SEND(2),{0x1C,0x7D}},

{LCM_SEND(2),{0x1D,0x00}},

{LCM_SEND(2),{0x1E,0x85}},

{LCM_SEND(2),{0x1F,0x08}},

{LCM_SEND(2),{0x20,0x00}},

{LCM_SEND(2),{0x21,0x00}},

{LCM_SEND(2),{0x22,0x00}},

{LCM_SEND(2),{0x23,0x00}},

{LCM_SEND(2),{0x24,0x00}},

{LCM_SEND(2),{0x25,0x00}},

{LCM_SEND(2),{0x26,0x00}},

{LCM_SEND(2),{0x27,0x00}},

{LCM_SEND(2),{0x28,0x00}},

{LCM_SEND(2),{0x29,0x00}},

{LCM_SEND(2),{0x2A,0x07}},

{LCM_SEND(2),{0x2B,0x08}},

{LCM_SEND(2),{0x2D,0x01}},

{LCM_SEND(2),{0x2F,0x02}},

{LCM_SEND(2),{0x30,0x00}},

{LCM_SEND(2),{0x31,0x40}},

{LCM_SEND(2),{0x32,0x05}},

{LCM_SEND(2),{0x33,0x08}},

{LCM_SEND(2),{0x34,0x54}},

{LCM_SEND(2),{0x35,0x7D}},

{LCM_SEND(2),{0x36,0x00}},

{LCM_SEND(2),{0x37,0x03}},

{LCM_SEND(2),{0x38,0x04}},

{LCM_SEND(2),{0x39,0x05}},

{LCM_SEND(2),{0x3A,0x06}},

{LCM_SEND(2),{0x3B,0x00}},

{LCM_SEND(2),{0x3D,0x40}},

{LCM_SEND(2),{0x3F,0x05}},

{LCM_SEND(2),{0x40,0x08}},

{LCM_SEND(2),{0x41,0x54}},

{LCM_SEND(2),{0x42,0x7D}},

{LCM_SEND(2),{0x43,0x00}},

{LCM_SEND(2),{0x44,0x00}},

{LCM_SEND(2),{0x45,0x00}},

{LCM_SEND(2),{0x46,0x00}},

{LCM_SEND(2),{0x47,0x00}},

{LCM_SEND(2),{0x48,0x00}},

{LCM_SEND(2),{0x49,0x00}},

{LCM_SEND(2),{0x4A,0x00}},

{LCM_SEND(2),{0x4B,0x00}},

{LCM_SEND(2),{0x4C,0x00}},

{LCM_SEND(2),{0x4D,0x00}},

{LCM_SEND(2),{0x4E,0x00}},

{LCM_SEND(2),{0x4F,0x00}},

{LCM_SEND(2),{0x50,0x00}},

{LCM_SEND(2),{0x51,0x00}},

{LCM_SEND(2),{0x52,0x00}},

{LCM_SEND(2),{0x53,0x00}},

{LCM_SEND(2),{0x54,0x00}},

{LCM_SEND(2),{0x55,0x00}},

{LCM_SEND(2),{0x56,0x00}},

{LCM_SEND(2),{0x58,0x00}},

{LCM_SEND(2),{0x59,0x00}},

{LCM_SEND(2),{0x5A,0x00}},

{LCM_SEND(2),{0x5B,0x00}},

{LCM_SEND(2),{0x5C,0x00}},

{LCM_SEND(2),{0x5D,0x00}},

{LCM_SEND(2),{0x5E,0x00}},

{LCM_SEND(2),{0x5F,0x00}},

{LCM_SEND(2),{0x60,0x00}},

{LCM_SEND(2),{0x61,0x00}},

{LCM_SEND(2),{0x62,0x00}},

{LCM_SEND(2),{0x63,0x00}},

{LCM_SEND(2),{0x64,0x00}},

{LCM_SEND(2),{0x65,0x00}},

{LCM_SEND(2),{0x66,0x00}},

{LCM_SEND(2),{0x67,0x00}},

{LCM_SEND(2),{0x68,0x00}},

{LCM_SEND(2),{0x69,0x00}},

{LCM_SEND(2),{0x6A,0x00}},

{LCM_SEND(2),{0x6B,0x00}},

{LCM_SEND(2),{0x6C,0x00}},

{LCM_SEND(2),{0x6D,0x00}},

{LCM_SEND(2),{0x6E,0x00}},

{LCM_SEND(2),{0x6F,0x00}},

{LCM_SEND(2),{0x70,0x00}},

{LCM_SEND(2),{0x71,0x00}},

{LCM_SEND(2),{0x72,0x20}},

{LCM_SEND(2),{0x73,0x00}},

{LCM_SEND(2),{0x74,0x08}},

{LCM_SEND(2),{0x75,0x08}},

{LCM_SEND(2),{0x76,0x08}},

{LCM_SEND(2),{0x77,0x08}},

{LCM_SEND(2),{0x78,0x08}},

{LCM_SEND(2),{0x79,0x08}},

{LCM_SEND(2),{0x7A,0x00}},

{LCM_SEND(2),{0x7B,0x00}},

{LCM_SEND(2),{0x7C,0x00}},

{LCM_SEND(2),{0x7D,0x00}},

{LCM_SEND(2),{0x7E,0xBF}},

{LCM_SEND(2),{0x7F,0x3F}},

{LCM_SEND(2),{0x80,0x3F}},

{LCM_SEND(2),{0x81,0x3F}},

{LCM_SEND(2),{0x82,0x3F}},

{LCM_SEND(2),{0x83,0x3F}},

{LCM_SEND(2),{0x84,0x3F}},

{LCM_SEND(2),{0x85,0x02}},

{LCM_SEND(2),{0x86,0x06}},

{LCM_SEND(2),{0x87,0x3F}},

{LCM_SEND(2),{0x88,0x14}},

{LCM_SEND(2),{0x89,0x10}},

{LCM_SEND(2),{0x8A,0x16}},

{LCM_SEND(2),{0x8B,0x12}},

{LCM_SEND(2),{0x8C,0x08}},

{LCM_SEND(2),{0x8D,0x0C}},

{LCM_SEND(2),{0x8E,0x0A}},

{LCM_SEND(2),{0x8F,0x0E}},

{LCM_SEND(2),{0x90,0x00}},

{LCM_SEND(2),{0x91,0x04}},

{LCM_SEND(2),{0x92,0x3F}},

{LCM_SEND(2),{0x93,0x3F}},

{LCM_SEND(2),{0x94,0x3F}},

{LCM_SEND(2),{0x95,0x3F}},

{LCM_SEND(2),{0x96,0x05}},

{LCM_SEND(2),{0x97,0x01}},

{LCM_SEND(2),{0x98,0x0F}},

{LCM_SEND(2),{0x99,0x0B}},

{LCM_SEND(2),{0x9A,0x0D}},

{LCM_SEND(2),{0x9B,0x09}},

{LCM_SEND(2),{0x9C,0x13}},

{LCM_SEND(2),{0x9D,0x17}},

{LCM_SEND(2),{0x9E,0x11}},

{LCM_SEND(2),{0x9F,0x15}},

{LCM_SEND(2),{0xA0,0x3F}},

{LCM_SEND(2),{0xA2,0x07}},

{LCM_SEND(2),{0xA3,0x03}},

{LCM_SEND(2),{0xA4,0x3F}},

{LCM_SEND(2),{0xA5,0x3F}},

{LCM_SEND(2),{0xA6,0x3F}},

{LCM_SEND(2),{0xA7,0x3F}},

{LCM_SEND(2),{0xA9,0x3F}},

{LCM_SEND(2),{0xAA,0x3F}},

{LCM_SEND(2),{0xAB,0x3F}},

{LCM_SEND(2),{0xAC,0x3F}},

{LCM_SEND(2),{0xAD,0x3F}},

{LCM_SEND(2),{0xAE,0x3F}},

{LCM_SEND(2),{0xAF,0x3F}},

{LCM_SEND(2),{0xB0,0x3F}},

{LCM_SEND(2),{0xB1,0x3F}},

{LCM_SEND(2),{0xB2,0x3F}},

{LCM_SEND(2),{0xB3,0x05}},

{LCM_SEND(2),{0xB4,0x01}},

{LCM_SEND(2),{0xB5,0x3F}},

{LCM_SEND(2),{0xB6,0x17}},

{LCM_SEND(2),{0xB7,0x13}},

{LCM_SEND(2),{0xB8,0x15}},

{LCM_SEND(2),{0xB9,0x11}},

{LCM_SEND(2),{0xBA,0x0F}},

{LCM_SEND(2),{0xBB,0x0B}},

{LCM_SEND(2),{0xBC,0x0D}},

{LCM_SEND(2),{0xBD,0x09}},

{LCM_SEND(2),{0xBE,0x07}},

{LCM_SEND(2),{0xBF,0x03}},

{LCM_SEND(2),{0xC0,0x3F}},

{LCM_SEND(2),{0xC1,0x3F}},

{LCM_SEND(2),{0xC2,0x3F}},

{LCM_SEND(2),{0xC3,0x3F}},

{LCM_SEND(2),{0xC4,0x02}},

{LCM_SEND(2),{0xC5,0x06}},

{LCM_SEND(2),{0xC6,0x08}},

{LCM_SEND(2),{0xC7,0x0C}},

{LCM_SEND(2),{0xC8,0x0A}},

{LCM_SEND(2),{0xC9,0x0E}},

{LCM_SEND(2),{0xCA,0x10}},

{LCM_SEND(2),{0xCB,0x14}},

{LCM_SEND(2),{0xCC,0x12}},

{LCM_SEND(2),{0xCD,0x16}},

{LCM_SEND(2),{0xCE,0x3F}},

{LCM_SEND(2),{0xCF,0x00}},

{LCM_SEND(2),{0xD0,0x04}},

{LCM_SEND(2),{0xD1,0x3F}},

{LCM_SEND(2),{0xD2,0x3F}},

{LCM_SEND(2),{0xD3,0x3F}},

{LCM_SEND(2),{0xD4,0x3F}},

{LCM_SEND(2),{0xD5,0x3F}},

{LCM_SEND(2),{0xD6,0x3F}},

{LCM_SEND(2),{0xD7,0x3F}},

{LCM_SEND(2),{0xDC,0x02}},

{LCM_SEND(2),{0xDE,0x12}},

{LCM_SEND(2),{0xFE,0x0E}},

{LCM_SEND(2),{0x01,0x75}},

{LCM_SEND(2),{0xFE,0x04}},

{LCM_SEND(2),{0x60,0x00}},

{LCM_SEND(2),{0x61,0x08}},

{LCM_SEND(2),{0x62,0x0E}},

{LCM_SEND(2),{0x63,0x0D}},

{LCM_SEND(2),{0x64,0x05}},

{LCM_SEND(2),{0x65,0x10}},

{LCM_SEND(2),{0x66,0x0E}},

{LCM_SEND(2),{0x67,0x0A}},

{LCM_SEND(2),{0x68,0x16}},

{LCM_SEND(2),{0x69,0x0C}},

{LCM_SEND(2),{0x6A,0x10}},

{LCM_SEND(2),{0x6B,0x07}},

{LCM_SEND(2),{0x6C,0x0E}},

{LCM_SEND(2),{0x6D,0x13}},

{LCM_SEND(2),{0x6E,0x0C}},

{LCM_SEND(2),{0x6F,0x00}},

{LCM_SEND(2),{0x70,0x00}},

{LCM_SEND(2),{0x71,0x08}},

{LCM_SEND(2),{0x72,0x0E}},

{LCM_SEND(2),{0x73,0x0D}},

{LCM_SEND(2),{0x74,0x05}},

{LCM_SEND(2),{0x75,0x10}},

{LCM_SEND(2),{0x76,0x0E}},

{LCM_SEND(2),{0x77,0x0A}},

{LCM_SEND(2),{0x78,0x16}},

{LCM_SEND(2),{0x79,0x0C}},

{LCM_SEND(2),{0x7A,0x10}},

{LCM_SEND(2),{0x7B,0x07}},

{LCM_SEND(2),{0x7C,0x0E}},

{LCM_SEND(2),{0x7D,0x13}},

{LCM_SEND(2),{0x7E,0x0C}},

{LCM_SEND(2),{0x7F,0x00}},

{LCM_SEND(2),{0xFE,0x00}},

{LCM_SEND(2),{0x58,0xAD}},


{LCM_SEND(2),  {0x11,  0x00 }},
{LCM_SLEEP(200),},
{LCM_SEND(2),  {0x29,  0x00 }},
{LCM_SLEEP(20),},                                      	
};

static LCM_Init_Code sleep_in[] =  {
{LCM_SEND(1), {0x28 }},
{LCM_SLEEP(100)},
{LCM_SEND(1), {0x10 }},
{LCM_SLEEP(20)},
{LCM_SEND(2), {0x4f,0x01 }},
{LCM_SLEEP(100)},
};

static LCM_Init_Code sleep_out[] =  {
{LCM_SEND(1), {0x11 }},
{LCM_SLEEP(120)},
{LCM_SEND(1), {0x29 }},
{LCM_SLEEP(100)},
};

static LCM_Force_Cmd_Code rd_prep_code[]={
        {0x39, {LCM_SEND(4), {2, 0, 0xFE, 0x01}}},
        {0x37, {LCM_SEND(2), {0x3, 0}}},
};

static LCM_Force_Cmd_Code rd_prep_code_1[]={
	{0x37, {LCM_SEND(2), {0x1, 0 }},},
};
static int32_t rm68200g_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

#if 0
    volatile unsigned long temp = 0;

    temp = __raw_readl(CTL_PIN_BASE + REG_PIN_LCD_RSTN);
    temp &= ~(0xF); // Clear slp_wpu_wpd and slp_ie/oe bits; [3:0]
    temp |= (0x1 << 3); // SLP_WPU;
    __raw_writel(temp, CTL_PIN_BASE + REG_PIN_LCD_RSTN);
#endif

	pr_debug(KERN_DEBUG "rm68200g_mipi_init\n");

	// Fixme;
	self->info.mipi->ops->mipi_set_lp_mode();

	mipi_set_cmd_mode();

	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			msleep((init->tag & LCM_TAG_MASK));
		}
		init++;
	}

	return 0;
}

static uint32_t rm68200g_readid(struct panel_spec *self)
{
	//return 0x17;
	/*Jessica TODO: need read id*/
	int32_t i = 0;
	int32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data1[3] = {0};
	uint8_t read_data2[3] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	printk("lcd_rm68200g_mipi read id!\n");
	return 0x6820;	//debug
#if 1
	mipi_set_cmd_mode();
	mipi_eotp_set(0,1);
	for(j = 0; j < 4; j++){
		rd_prepare = rd_prep_code;
		for(i = 0; i < ARRAY_SIZE(rd_prep_code); i++){
			tag = (rd_prepare->real_cmd_code.tag >> 24);
			if(tag & LCM_TAG_SEND){
				mipi_force_write(rd_prepare->datatype, rd_prepare->real_cmd_code.data, (rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}else if(tag & LCM_TAG_SLEEP){
				mdelay((rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}
			rd_prepare++;
		}
		read_rtn = mipi_force_read(0xDE, 1,(uint8_t *)read_data1);
		printk("lcd_rm68200g_mipi read id 0xde value is 0x%x!\n", read_data1[0]);
		read_rtn = mipi_force_read(0xDF, 1,(uint8_t *)read_data2);
		printk("lcd_rm68200g_mipi read id 0xdf value is 0x%x!\n", read_data2[0]);

		if((0x20 == read_data1[0])&&(0x68 == read_data2[0])){
			printk("lcd_rm68200g_mipi read id success!\n");
			mipi_eotp_set(1,1);
			return 0x6820;
		}
	}
	mipi_eotp_set(1,1);
	return 0x0;
#endif
}

static int32_t rm68200g_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	int32_t i;
	LCM_Init_Code *sleep_in_out = NULL;
	unsigned int tag;
	int32_t size = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	printk(KERN_DEBUG "rm68200g_enter_sleep, is_sleep = %d\n", is_sleep);

	if(is_sleep){
		sleep_in_out = sleep_in;
		size = ARRAY_SIZE(sleep_in);
	}else{
		sleep_in_out = sleep_out;
		size = ARRAY_SIZE(sleep_out);
	}
	
	self->ops->panel_reset(self);
	
	// Fixme;
	self->info.mipi->ops->mipi_set_lp_mode();
	
	mipi_set_cmd_mode();
	for(i = 0; i <size ; i++){
		tag = (sleep_in_out->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(sleep_in_out->data, (sleep_in_out->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			msleep((sleep_in_out->tag & LCM_TAG_MASK));
		}
		sleep_in_out++;
	}
	
	// Fixme;
	self->info.mipi->ops->mipi_set_hs_mode();

	return 0;
}

static uint32_t rm68200g_readpowermode(struct panel_spec *self)
{
	int32_t i = 0;
	uint32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code_1;
	uint8_t read_data[1] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;

	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	pr_debug("lcd_rm68200g_mipi read power mode!\n");
	mipi_eotp_set(0,1);
	for(j = 0; j < 4; j++){
		rd_prepare = rd_prep_code_1;
		for(i = 0; i < ARRAY_SIZE(rd_prep_code_1); i++){
			tag = (rd_prepare->real_cmd_code.tag >> 24);
			if(tag & LCM_TAG_SEND){
				mipi_force_write(rd_prepare->datatype, rd_prepare->real_cmd_code.data, (rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}else if(tag & LCM_TAG_SLEEP){
				msleep((rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}
			rd_prepare++;
		}
		read_rtn = mipi_force_read(0x0A, 1,(uint8_t *)read_data);
		pr_debug("lcd_rm68200g mipi read power mode 0x0A value is 0x%x! , read result(%d)\n", read_data[0], read_rtn);
		if((0x9c == read_data[0])  && (0 == read_rtn)){
			pr_debug("lcd_rm68200g_mipi read power mode success!\n");
			mipi_eotp_set(1,1);
			return 0x9c;
		}
	}

	printk("lcd_rm68200g mipi read power mode fail!0x0A value is 0x%x! , read result(%d)\n", read_data[0], read_rtn);
	mipi_eotp_set(1,1);
	return 0x0;
}

static int32_t rm68200g_check_esd(struct panel_spec *self)
{
	uint32_t power_mode;
	//return 1;
	mipi_set_lp_mode_t mipi_set_data_lp_mode = self->info.mipi->ops->mipi_set_data_lp_mode;
	mipi_set_hs_mode_t mipi_set_data_hs_mode = self->info.mipi->ops->mipi_set_data_hs_mode;
	mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;
	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
	uint16_t work_mode = self->info.mipi->work_mode;
/*
	pr_debug("rm68200g_check_esd!\n");
	if(SPRDFB_MIPI_MODE_CMD==work_mode){
		mipi_set_lp_mode();
	}else{
		mipi_set_data_lp_mode();
	}*/
	power_mode = rm68200g_readpowermode(self);
	//power_mode = 0x0;
	/*
	if(SPRDFB_MIPI_MODE_CMD==work_mode){
		mipi_set_hs_mode();
	}else{
		mipi_set_data_hs_mode();
	}*/
	if(power_mode == 0x9c){
		printk("rm68200g_check_esd OK!\n");
		return 1;
	}else{
		printk("rm68200g_check_esd fail!(0x%x)\n", power_mode);
		return 0;
	}
}

static int32_t rm68200g_after_suspend(struct panel_spec *self)
{
    // Do nothing;

    return 0;
}

static struct panel_operations lcd_rm68200g_mipi_operations = {
	.panel_init = rm68200g_mipi_init,
	.panel_readid = rm68200g_readid,
	.panel_enter_sleep = rm68200g_enter_sleep,
	.panel_esd_check = rm68200g_check_esd,
    .panel_after_suspend = rm68200g_after_suspend,
};

static struct timing_rgb lcd_rm68200g_mipi_timing = {
#if 0
	.hfp = 40,  /* 80unit: pixel */
	.hbp = 40, //80
	.hsync = 10,
	.vfp = 16, /*unit: line*/
	.vbp = 14,
	.vsync = 2,
#elif 0
	.hfp =32,
	.hbp = 4,
	.hsync =8,
	.vfp = 17,
	.vbp = 18,
	.vsync = 7,
#elif 1
	.hfp = 26,
	.hbp = 36,
	.hsync =2,
	.vfp = 16,
	.vbp = 36,
	.vsync = 4,
#endif
};

static struct info_mipi lcd_rm68200g_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 500*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_rm68200g_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_rm68200g_mipi_spec = {
	.width = 720,
	.height = 1280,
	.fps = 50,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
//	.is_clean_lcd = true,
	.info = {
		.mipi = &lcd_rm68200g_mipi_info
	},
	.ops = &lcd_rm68200g_mipi_operations,
	.suspend_mode = SEND_SLEEP_CMD,
};

struct panel_cfg lcd_rm68200g_mipi = {
	/* this panel can only be main lcd */
	.dev_id = SPRDFB_MAINLCD_ID,
	.lcd_id = 0x6820,
	.lcd_name = "lcd_rm68200g_mipi",
	.panel = &lcd_rm68200g_mipi_spec,
};

static int __init lcd_rm68200g_mipi_init(void)
{
	return sprdfb_panel_register(&lcd_rm68200g_mipi);
}

subsys_initcall(lcd_rm68200g_mipi_init);
