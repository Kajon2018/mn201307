/******************************************************************************
 ** File Name:      pmu.c                                             *
 ** Author:         Chris                                              *
 ** DATE:           04/11/2014                                                *
 ** Copyright:      2014 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 04/11/2014     Chris               Create.                                   *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <asm/io.h>
#include "asm/arch/sc_reg.h"
#include "adi_hal_internal.h"
//#include "asm/arch/wdg_drvapi.h"
#include "asm/arch/sprd_reg.h"
#include "asm/arch/boot_drvapi.h"
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif

/**---------------------------------------------------------------------------*
 **                         Macro defines.
 **---------------------------------------------------------------------------*/
#define DDR_PHY_IND_ADDR  0x30010184
#define DDR_PHY_IND_ADDR1 0x30040000
#define DDR_PHY_IND_ADDR2 0x402e3048
#define DDR_PHY_IND_PHY_ALIVE 0x00000001


/**---------------------------------------------------------------------------*
 **                         Struct defines.
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
 **                         Global variables                                  *
 **---------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
 **                         Function Definitions                              *
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
 **                         Struct defines.
 **---------------------------------------------------------------------------*/


void fixup_pmic_items(void)
{
	/*set ldo_usb pd for tsharkl uboot64*/
	ANA_REG_OR(ANA_REG_GLB_LDO_PD_CTRL,BIT_LDO_USB_PD);
}


/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


