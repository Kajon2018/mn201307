/**
 * @file mipi_dsih_local.h
 * @brief instance context structure and enumerator definitions:
 * errors, events, color coding, video modes and driver state
 *
 *  Synopsys Inc.
 *  SG DWC PT02
 */
/*
	The Synopsys Software Driver and documentation (hereinafter "Software")
	is an unsupported proprietary work of Synopsys, Inc. unless otherwise
	expressly agreed to in writing between	Synopsys and you.

	The Software IS NOT an item of Licensed Software or Licensed Product under
	any End User Software License Agreement or Agreement for Licensed Product
	with Synopsys or any supplement	thereto.  Permission is hereby granted,
	free of charge, to any person obtaining a copy of this software annotated
	with this license and the Software, to deal in the Software without
	restriction, including without limitation the rights to use, copy, modify,
	merge, publish, distribute, sublicense,	and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so, subject
	to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS" BASIS
	AND ANY	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE	POSSIBILITY OF SUCH
	DAMAGE.
 */

#ifndef MIPI_DSIH_LOCAL_H_
#define MIPI_DSIH_LOCAL_H_

//#include <stdint.h>
#include <common.h>
#include "../sprdfb_chip_common.h"

//typedef unsigned char   uint8_t;
//typedef unsigned short  uint16_t;
//typedef unsigned int    uint32_t;

#define DSIH_PIXEL_TOLERANCE  2
#define DSIH_FIFO_ACTIVE_WAIT (5000)    /* no of tries to access the fifo*/ //read id failed: 500 -->5000
#define DSIH_PHY_ACTIVE_WAIT  (50000)
#define ONE_MS_ACTIVE_WAIT    (50000) /* 50MHz processor */
#define DEFAULT_BYTE_CLOCK	  (432000) /* a value to start PHY PLL - random */
#define MAX_NULL_SIZE		  (1023)
#define FIFO_DEPTH            (1096)
#define WORD_LENGTH           (4) /* bytes (32bit registers) */
/** Define D-PHY type */
#ifdef SPRD_MIPI_DPHY_GEN1
/** DWC_MIPI_DPHY_BIDIR_TSMC40LP 4 Lanes Gen 1 1GHz */
 #define DWC_MIPI_DPHY_BIDIR_TSMC40LP
#endif
#ifdef SPRD_MIPI_DPHY_GEN2
/** DWC_MIPI_DPHY_BIDIR_TSMC40LP / GF28LP 4 Lanes Gen 2 1.5GHz */
#define GEN_2
#endif
/** 4 Lanes Gen 2 1.5GHz testchips */
//#define TESTCHIP
/** TQL 2 Lane test chip */
/* #define DPHY2Btql */

/**
 * Errors generated by the DSI Host controller driver
 */
typedef enum
{
	OK = 0,
	ERR_DSI_COLOR_CODING,
	ERR_DSI_OUT_OF_BOUND,
	ERR_DSI_OVERFLOW,
	ERR_DSI_INVALID_INSTANCE,
	ERR_DSI_INVALID_IO,
	ERR_DSI_CORE_INCOMPATIBLE,
	ERR_DSI_VIDEO_MODE,
	ERR_DSI_INVALID_COMMAND,
	ERR_DSI_INVALID_EVENT,
	ERR_DSI_INVALID_HANDLE,
	ERR_DSI_PHY_POWERUP,
	ERR_DSI_PHY_INVALID,
	ERR_DSI_PHY_FREQ_OUT_OF_BOUND,
#ifdef GEN_2
    ERR_DSI_PHY_PLL_NOT_LOCKED,
#endif
    ERR_DSI_TIMEOUT
}
dsih_error_t;
/**
 * Video stream type
 */
typedef enum
{
	VIDEO_NON_BURST_WITH_SYNC_PULSES = 0,
	VIDEO_NON_BURST_WITH_SYNC_EVENTS,
	VIDEO_BURST_WITH_SYNC_PULSES
}
dsih_video_mode_t;
/**
 * Color coding type (depth and pixel configuration)
 */
typedef enum
{
	COLOR_CODE_16BIT_CONFIG1 		=  0,
	COLOR_CODE_16BIT_CONFIG2 		=  1,
	COLOR_CODE_16BIT_CONFIG3 		=  2,
	COLOR_CODE_18BIT_CONFIG1 		=  3,
	COLOR_CODE_18BIT_CONFIG2 		=  4,
	COLOR_CODE_24BIT 				=  5,
	COLOR_CODE_20BIT_YCC422_LOOSELY =  6,
	COLOR_CODE_24BIT_YCC422 		=  7,
	COLOR_CODE_16BIT_YCC422 		=  8,
	COLOR_CODE_30BIT 				=  9,
	COLOR_CODE_36BIT 				= 10,
	COLOR_CODE_12BIT_YCC420 		= 11,
	COLOR_CODE_MAX
}
dsih_color_coding_t;
/**
 * Events generated by the DSI Host controller
 */
typedef enum
{
	ACK_SOT_ERR = 0,
	ACK_SOT_SYNC,
	ACK_EOT_SYNC,
	ACK_ESCAPE_CMD_ERR,
	ACK_LP_TX_SYNC_ERR,
	ACK_HS_RX_TIMEOUT_ERR,
	ACK_FALSE_CONTROL_ERR,
	ACK_RSVD_DEVICE_ERR_7,
	ACK_ECC_SINGLE_BIT_ERR,
	ACK_ECC_MULTI_BIT_ERR,
	ACK_CHECKSUM_ERR,
	ACK_DSI_TYPE_NOT_RECOGNIZED_ERR,
	ACK_VC_ID_INVALID_ERR,
	ACK_INVALID_TX_LENGTH_ERR,
	ACK_RSVD_DEVICE_ERR_14,
	ACK_DSI_PROTOCOL_ERR,

	DPHY_ESC_ENTRY_ERR,
	DPHY_SYNC_ESC_LP_ERR,
	DPHY_CONTROL_LANE0_ERR,
	DPHY_CONTENTION_LP0_ERR,
	DPHY_CONTENTION_LP1_ERR,
	/* start of st1 */
	HS_CONTENTION,
	LP_CONTENTION,
	RX_ECC_SINGLE_ERR,
	RX_ECC_MULTI_ERR,
	RX_CRC_ERR,
	RX_PKT_SIZE_ERR,
	RX_EOTP_ERR,
	DPI_PLD_FIFO_FULL_ERR,
	GEN_TX_CMD_FIFO_FULL_ERR,
	GEN_TX_PLD_FIFO_FULL_ERR,
	GEN_TX_PLD_FIFO_EMPTY_ERR,
	GEN_RX_PLD_FIFO_EMPTY_ERR,
	GEN_RX_PLD_FIFO_FULL_ERR,

	DBI_TX_CMD_FIFO_FULL_ERR,
	DBI_TX_PLD_FIFO_FULL_ERR,
	DBI_RX_PLD_FIFO_EMPTY_ERR,
	DBI_RX_PLD_FIFO_FULL_ERR,
	DBI_ILLEGAL_CMD_ERR,
	DSI_MAX_EVENT
}
dsih_event_t;
/**
 * DSI Host state machine states
 * Holds the mapping of D-PHY to the OS, logging I/O, and hardware access layer.
 */
typedef enum
{
	NOT_INITIALIZED = 0,
	INITIALIZED,
	ON,
	OFF
}
dsih_state_t;

/**
 * MIPI D-PHY
 * Holds the mapping of API to the OS, logging I/O, and hardware access layer
 * and HW module information.
 */
typedef struct dphy_t
{
	/** Physical base address of PHY module - REQUIRED */
	unsigned long address;
	/** Reference frequency provided to PHY module [KHz] - REQUIRED */
	uint32_t reference_freq;
	/** D-PHY driver state - used internally by driver */
	dsih_state_t status;
	/** Function handle of any board function that needs to be called
	 * in order to set up the environment for the D-PHY before it is
	 * configured. */
	void (*bsp_pre_config)(struct dphy_t *instance, void* param);
	/** Register read access function handle - REQUIRED */
	uint32_t (*core_read_function)(unsigned long addr, uint32_t offset);
	/** Register write access function handle - REQUIRED */
	void (*core_write_function)(unsigned long addr, uint32_t offset, uint32_t data);
	/** Log errors function handle */
	void (*log_error)(const char * string);
	/** Log information function handle */
	void (*log_info)(const char *fmt, ...);
}
dphy_t;

/**
 * MIPI DSI Host Controller
 * Holds important information for the functioning of the DSI Host Controller API
 * Holds the mapping of API to the OS, logging I/O, and hardware access layer.
 * It also holds important information set by the user about the HW considerations
 * and internal state variables.
 */
typedef struct dsih_ctrl_t
{
	/** Physical base address of controller - REQUIRED */
	unsigned long address;
	/** D-PHY instance associated with the DSI host controller - REQUIRED */
	dphy_t phy_instance;
	/**D-PHY frequency*/
	uint32_t phy_feq;
	/** Number of lanes physically connected to controller - REQUIRED */
	uint8_t max_lanes;
	/** Maximum number of byte clock cycles needed by the PHY to perform
	 * the Bus Turn Around operation - REQUIRED */
	uint16_t max_bta_cycles;
	/** Describe the color mode pin (dpicolorm) whether it is active high or low - REQUIRED */
	int color_mode_polarity;
	/** Describe the shut down pin (dpishutdn) whether it is active high or low - REQUIRED */
	int shut_down_polarity;
	/** initialised or not */
	dsih_state_t status;
	/** Register read access function handle - REQUIRED */
	uint32_t (*core_read_function)(unsigned long addr, uint32_t offset);
	/** Register write access function handle - REQUIRED */
	void (*core_write_function)(unsigned long addr, uint32_t offset, uint32_t data);
	/** Log errors function handle */
	void (*log_error)(const char * string);
	/** Log information function handle */
	void (*log_info)(const char *fmt, ...);
	/** Event registry holds handlers of the callbacks of registered events */
	void (*event_registry[DSI_MAX_EVENT])(struct dsih_ctrl_t *instance, void *handler);
}
dsih_ctrl_t;
/**
 * Video configurations
 * Holds information about the video stream to be sent through the DPI interface.
 */
typedef struct
{
	/** Number of lanes used to send current video */
	uint8_t  no_of_lanes;
	/** Virtual channel number to send this video stream */
	uint8_t  virtual_channel;
	/** Video mode, whether burst with sync pulses, or packets with either sync pulses or events */
	dsih_video_mode_t video_mode;
	/** Maximum number of byte clock cycles needed by the PHY to transition
	 * the data lanes from high speed to low power - REQUIRED */
	uint8_t max_hs_to_lp_cycles;
	/** Maximum number of byte clock cycles needed by the PHY to transition
	 * the data lanes from low power to high speed - REQUIRED */
	uint8_t max_lp_to_hs_cycles;
	/** Maximum number of byte clock cycles needed by the PHY to transition
	 * the clock lane from high speed to low power - REQUIRED */
	uint8_t max_clk_hs_to_lp_cycles;
	/** Maximum number of byte clock cycles needed by the PHY to transition
	 * the clock lane from low power to high speed - REQUIRED */
	uint8_t max_clk_lp_to_hs_cycles;
	/** Enable non coninuous clock for energy saving
	 * - Clock lane will go to LS while not transmitting video */
	int non_continuous_clock;
	/** Enable receiving of ack packets */
	int 	 receive_ack_packets;
	/** Byte (lane) clock [KHz] */
	uint32_t byte_clock;
	/** Pixel (DPI) Clock [KHz]*/
	uint32_t pixel_clock;
	/** Colour coding - BPP and Pixel configuration */
	dsih_color_coding_t color_coding;
	/** Is 18-bit loosely packets (valid only when BPP == 18) */
	int  	 is_18_loosely;
	/** Data enable signal (dpidaten) whether it is active high or low */
	int  	 data_en_polarity;
	/** Horizontal synchronisation signal (dpihsync) whether it is active high or low */
	int      h_polarity;
	/** Horizontal resolution or Active Pixels */
	uint16_t h_active_pixels; /* hadr */
	/** Horizontal Sync Pixels - min 4 for best performance */
	uint16_t h_sync_pixels;
	/** Horizontal back porch pixels */
	uint16_t h_back_porch_pixels;   /* hbp */
	/** Total Horizontal pixels */
	uint16_t h_total_pixels;  /* h_total */
	/** Vertical synchronisation signal (dpivsync) whether it is active high or low */
	int      v_polarity;
	/** Vertical active lines (resolution) */
	uint16_t v_active_lines; /* vadr */
	/** Vertical sync lines */
	uint16_t v_sync_lines;
	/** Vertical back porch lines */
	uint16_t v_back_porch_lines;   /* vbp */
	/** Total no of vertical lines */
	uint16_t v_total_lines;  /* v_total */
}
dsih_dpi_video_t;

typedef struct
{
	/** virtual channel */
	uint8_t 			virtual_channel;
	/** Commands to be sent in high speed or low power */
	int 				lp;
	/** Colour coding - BPP and Pixel configuration */
	dsih_color_coding_t color_coding;
	/** Top horizontal pixel position in the display */
	uint16_t 			h_start;
	/** Horizontal resolution or Active Pixels */
	uint16_t 			h_active_pixels; /* hadr */
	/** Left most line position in the display */
	uint16_t			v_start;
	/** Vertical active lines (resolution) */
	uint16_t 			v_active_lines; /* vadr */
	/** Whether Tearing effect should be requested */
	int 				te;
	/** packet size of write memory command -
	 * 0 is default (optimum usage of RAM) */
	uint16_t 			packet_size;
}
dsih_cmd_mode_video_t;
/**
 * Register configurations
 */
typedef struct
{
	/** Register offset */
	uint32_t addr;
	/** Register data [in or out] */
	uint32_t data;
}
register_config_t;

#endif /* MIPI_DSIH_LOCAL_H_ */
