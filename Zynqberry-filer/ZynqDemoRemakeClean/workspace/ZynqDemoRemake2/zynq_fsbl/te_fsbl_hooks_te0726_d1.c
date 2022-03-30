/******************************************************************************
*
* 
* 
*
******************************************************************************/

/*****************************************************************************
*
* @file te_fsbl_hooks.c
*
*
******************************************************************************/


#include "fsbl.h"
#include "xstatus.h"
//rename to correct board name
#include "te_fsbl_hooks_te0726_d1.h"


  
#include "te_vdma.h"
#include "xparameters.h"
#include "xil_hal.h"
#include "sleep.h"
#include "xvtc.h"

#define ENABLE_CAMERA
#define DIRECT_CAMERA_VIEW

#ifdef DIRECT_CAMERA_VIEW
#define HDMI_FB_ADDR			0x1FC00000
#define CAMERA_FB_ADDR			0x1FC00000
#endif

#ifndef DIRECT_CAMERA_VIEW
#define HDMI_FB_ADDR			0x1FC00000
#define CAMERA_FB_ADDR			0x1F800000
#endif



/************************** Variable Definitions *****************************/


/************************** Function Prototypes ******************************/


/******************************************************************************
* This function is the hook which will be called  before the bitstream download.
* The user can add all the customized code required to be executed before the
* bitstream download to this routine.
*
* @param None
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
****************************************************************************/
u32 TE_FsblHookBeforeBitstreamDload_Custom(void)
{
	u32 Status;

	Status = XST_SUCCESS;
  
    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");
    xil_printf("TE0726 Demo1 TE_FsblHookBeforeBitstreamDload_Custom\r\n"); 
	/* Add the code here */
    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");


	return (Status);
}

/******************************************************************************
* This function is the hook which will be called  after the bitstream download.
* The user can add all the customized code required to be executed after the
* bitstream download to this routine.
*
* @param None
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
****************************************************************************/
u32 TE_FsblHookAfterBitstreamDload_Custom(void)
{
	u32 Status;

	Status = XST_SUCCESS;

    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");
    xil_printf("TE0726 Demo1 TE_FsblHookAfterBitstreamDload_Custom\r\n"); 
	/* Add the code here */
    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");

	return (Status);
}

/******************************************************************************
* This function is the hook which will be called  before the FSBL does a handoff
* to the application. The user can add all the customized code required to be
* executed before the handoff to this routine.
*
* @param None
*
* @return
*		- XST_SUCCESS to indicate success
*		- XST_FAILURE.to indicate failure
*
****************************************************************************/
u32 TE_FsblHookBeforeHandoff_Custom(void)
{
	u32 Status;

	Status = XST_SUCCESS;

    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");
    xil_printf("TE0726 Demo1 TE_FsblHookBeforeHandoff_Custom\r\n"); 
	/* Add the code here */
	XVtc Vtc;
	
    xil_printf("FSBL: Enabling VTC..\n\r");
	XVtc_Config *Config;
	Config = XVtc_LookupConfig(XPAR_VTC_0_DEVICE_ID);
	if (NULL == Config) {
		xil_printf("XVtc_LookupConfig failure\r\n");
		return XST_FAILURE;
	}

	Status = XVtc_CfgInitialize(&Vtc, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("XVtc_CfgInitialize failure\r\n");
		return XST_FAILURE;
	}

	XVtc_DisableSync(&Vtc);
	XVtc_EnableGenerator(&Vtc);

    xil_printf("FSBL: Enabling Out VDMA at 0x%08x..\n\r",HDMI_FB_ADDR);
    vdma_out_init(XPAR_VIDEO_OUT_AXI_VDMA_0_DEVICE_ID, HDMI_FB_ADDR, 1280, 720, 4);
#ifdef ENABLE_CAMERA
    xil_printf("FSBL: Enabling In  VDMA at 0x%08x..\n\r",CAMERA_FB_ADDR);
    vdma_in_init(XPAR_VIDEO_IN_AXI_VDMA_0_DEVICE_ID, CAMERA_FB_ADDR, 1280, 720, 4);
#endif
	
    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");
  
  
  
  
	return (Status);
}


/******************************************************************************
* This function is the hook which will be called in case FSBL fall back
*
* @param None
*
* @return None
*
****************************************************************************/
void TE_FsblHookFallback_Custom(void)
{
  
    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");
    xil_printf("TE0726 Demo1 TE_FsblHookFallback_Custom\r\n"); 
	/* Add the code here */
    xil_printf("\r\n--------------------------------------------------------------------------------\r\n");
  
  
	//while(1);
}


