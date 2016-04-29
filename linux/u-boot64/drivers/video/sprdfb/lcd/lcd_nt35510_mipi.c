/* drivers/video/sc8825/lcd_nt35516_mipi.c
 *
 * Support for nt35510 mipi LCD device
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

#include "../sprdfb_chip_common.h"
#include "../sprdfb.h"
#include "../sprdfb_panel.h"

#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define MAX_DATA   56

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
{LCM_SEND(8), {6, 0, 0xF0,0x55,0xAA,0x52,0x08,0x01}}, 
{LCM_SEND(6), {4, 0, 0xB0,0x09,0x09,0x09}}, 
{LCM_SEND(6), {4, 0, 0xB6,0x34,0x34,0x34}}, 
{LCM_SEND(6), {4, 0, 0xB1,0x09,0x09,0x09}}, 
{LCM_SEND(6), {4, 0, 0xB7,0x24,0x24,0x24}}, 
{LCM_SEND(6), {4, 0, 0xB3,0x05,0x05,0x05}}, 
{LCM_SEND(6), {4, 0, 0xB9,0x24,0x24,0x24}}, 
{LCM_SEND(2), {0xBF,0x01}}, 
{LCM_SEND(6), {4, 0, 0xB5,0x0B,0x0B,0x0B}}, 
{LCM_SEND(6), {4, 0, 0xBA,0x34,0x24,0x24}}, 
{LCM_SEND(6), {4, 0, 0xBC,0x00,0xd3,0x00}}, 
{LCM_SEND(6), {4, 0, 0xBD,0x00,0xd3,0x00}}, 
{LCM_SEND(5), {3, 0, 0xBE,0x00,0x60}}, 

{LCM_SEND(55), {53, 0, 0xD1,0x00,0x37,0x00,0x64,0x00,0x84,0x00,0xA3,0x00,0xB6,
0x00,0xDC,0x00,0xF4,0x01,0x2a,0x01,0x4A,0x01,0x8a,0x01,0xbb,0x02,0x0C,0x02,
0x48,0x02,0x4A,0x02,0x82,0x02,0xbC,0x02,0xE1,0x03,0x0F,0x03,0x32,0x03,0x5B,
0x03,0x73,0x03,0x91,0x03,0xA0,0x03,0xAF,0x03,0xBA,0x03,0xC1}}, 
{LCM_SEND(55), {53, 0, 0xD2,0x00,0x37,0x00,0x64,0x00,0x84,0x00,0xA3,0x00,0xB6,
0x00,0xDC,0x00,0xF4,0x01,0x2a,0x01,0x4A,0x01,0x8a,0x01,0xbb,0x02,0x0C,0x02,
0x48,0x02,0x4A,0x02,0x82,0x02,0xbC,0x02,0xE1,0x03,0x0F,0x03,0x32,0x03,0x5B,
0x03,0x73,0x03,0x91,0x03,0xA0,0x03,0xAF,0x03,0xBA,0x03,0xC1}}, 
{LCM_SEND(55), {53, 0, 0xD3,0x00,0x37,0x00,0x64,0x00,0x84,0x00,0xA3,0x00,0xB6,
0x00,0xDC,0x00,0xF4,0x01,0x2a,0x01,0x4A,0x01,0x8a,0x01,0xbb,0x02,0x0C,0x02,
0x48,0x02,0x4A,0x02,0x82,0x02,0xbC,0x02,0xE1,0x03,0x0F,0x03,0x32,0x03,0x5B,
0x03,0x73,0x03,0x91,0x03,0xA0,0x03,0xAF,0x03,0xBA,0x03,0xC1}}, 
{LCM_SEND(55), {53, 0, 0xD4,0x00,0x37,0x00,0x64,0x00,0x84,0x00,0xA3,0x00,0xB6,
0x00,0xDC,0x00,0xF4,0x01,0x2a,0x01,0x4A,0x01,0x8a,0x01,0xbb,0x02,0x0C,0x02,
0x48,0x02,0x4A,0x02,0x82,0x02,0xbC,0x02,0xE1,0x03,0x0F,0x03,0x32,0x03,0x5B,
0x03,0x73,0x03,0x91,0x03,0xA0,0x03,0xAF,0x03,0xBA,0x03,0xC1}}, 
{LCM_SEND(55), {53, 0, 0xD5,0x00,0x37,0x00,0x64,0x00,0x84,0x00,0xA3,0x00,0xB6,
0x00,0xDC,0x00,0xF4,0x01,0x2a,0x01,0x4A,0x01,0x8a,0x01,0xbb,0x02,0x0C,0x02,
0x48,0x02,0x4A,0x02,0x82,0x02,0xbC,0x02,0xE1,0x03,0x0F,0x03,0x32,0x03,0x5B,
0x03,0x73,0x03,0x91,0x03,0xA0,0x03,0xAF,0x03,0xBA,0x03,0xC1}}, 
{LCM_SEND(55), {53, 0, 0xD6,0x00,0x37,0x00,0x64,0x00,0x84,0x00,0xA3,0x00,0xB6,
0x00,0xDC,0x00,0xF4,0x01,0x2a,0x01,0x4A,0x01,0x8a,0x01,0xbb,0x02,0x0C,0x02,
0x48,0x02,0x4A,0x02,0x82,0x02,0xbC,0x02,0xE1,0x03,0x0F,0x03,0x32,0x03,0x5B,
0x03,0x73,0x03,0x91,0x03,0xA0,0x03,0xAF,0x03,0xBA,0x03,0xC1}}, 

{LCM_SEND(8), {6, 0, 0xF0,0x55,0xAA,0x52,0x08,0x00}},
{LCM_SEND(2), {0xB6,0x0A}},
{LCM_SEND(5), {3, 0, 0xB7,0x00,0x00}}, 
{LCM_SEND(7), {5, 0, 0xB8,0x01,0x05,0x05,0x05}},
{LCM_SEND(2), {0xBA,0x01}}, 
{LCM_SEND(6), {4, 0, 0xBC,0x02,0x02,0x02}}, 
{LCM_SEND(6), {4, 0, 0xCC,0x03,0x00,0x00}}, 
{LCM_SEND(8), {6, 0, 0xBD,0x01,0x4d,0x07,0x31,0x00}}, 

{LCM_SEND(5), {3, 0, 0xB1,0xf8,0x00}},
{LCM_SEND(2), {0xB5,0x50}},
//{LCM_SEND(2), {0x21,0x00}},


{LCM_SEND(2), {0x35,0x00}},// Tearing Effect On 

{LCM_SEND(2), {0x3A, 0x77}},
{LCM_SEND(2), {0x36,0x00}},//03

{LCM_SEND(1), {0x11}}, // sleep out 
{LCM_SLEEP(150),},
{LCM_SEND(1), {0x29}}, // display on
{LCM_SEND(1), {0x2c}}, // normal on
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t nt35510_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;	

	LCD_PRINT("nt35510_init\n");

	mipi_set_cmd_mode();

	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			mdelay((init->tag & LCM_TAG_MASK));
		}
		init++;
	}
	return 0;
}


static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x39, {LCM_SEND(8), {0x6, 0, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static uint32_t nt35510_readid(struct panel_spec *self)
{
	/*Jessica TODO: need read id*/
	int32_t i = 0;
	uint32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[3] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;
	
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;//huafeizhou141023 add
       mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;//huafeizhou141023 add

	LCD_PRINT("lcd_nt35510_mipi read id!\n");
	//return 0x5510;	//fix lcd id read problem

	mipi_set_lp_mode();
	//mipi_set_hs_mode();//huafeizhou141023 add	
//	mipi_eotp_set(0,1);

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

		read_rtn = mipi_force_read(0xc5, 3,(uint8_t *)read_data);
		LCD_PRINT("lcd_nt35510_mipi read id 0xc5 value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);
		if((0x55 == read_data[0])&&(0x10 == read_data[1])){
			LCD_PRINT("lcd_nt35510_mipi read id success!\n");
			mipi_eotp_set(1,1);
			return 0x5510;
		}
	}
//	mipi_eotp_set(1,1);
	return 0;
}

static struct panel_operations lcd_nt35510_mipi_operations = {
	.panel_init = nt35510_mipi_init,
	.panel_readid = nt35510_readid,
};

static struct timing_rgb lcd_nt35510_mipi_timing = {
	.hfp = 100,  /* unit: pixel */// 100
	.hbp = 80,//80
	.hsync = 60,//6
	.vfp = 20, /*unit: line*/
	.vbp = 14,
	.vsync =6, //6,
};

static struct info_mipi lcd_nt35510_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO, //SPRDFB_MIPI_MODE_VIDEO  SPRDFB_MIPI_MODE_CMD
	.video_bus_width = 24, /*18,16*/
	.lan_number = 2,
	.phy_feq = 500*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_nt35510_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_nt35510_mipi_spec = {
	//.cap = PANEL_CAP_NOT_TEAR_SYNC,
	.width = 480,
	.height = 800,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_nt35510_mipi_info
	},
	.ops = &lcd_nt35510_mipi_operations,
};
