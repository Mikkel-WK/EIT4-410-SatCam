/*
 */

#include "xil_printf.h"
//#include "sleep.h"


#include "te_vdma.h"

XAxiVdma OutVdma;
XAxiVdma InVdma;

XAxiVdma_DmaSetup VDMAOutCfg;
XAxiVdma_DmaSetup VDMAInCfg;

u32 vdma_version() {
	return XAxiVdma_GetVersion(&OutVdma);
}

int vdma_out_start() {
	   int Status;

	   // MM2S Startup
	   Status = XAxiVdma_DmaStart(&OutVdma, XAXIVDMA_READ);
	   if (Status != XST_SUCCESS)
	   {
	      xil_printf("Start read transfer failed %d\n\r", Status);
	      return XST_FAILURE;
	   }

	   return XST_SUCCESS;
}

int vdma_in_start() {
	   int Status;

	   // MM2S Startup
	   Status = XAxiVdma_DmaStart(&InVdma, XAXIVDMA_WRITE);
	   if (Status != XST_SUCCESS)
	   {
	      xil_printf("Start read transfer failed %d\n\r", Status);
	      return XST_FAILURE;
	   }

	   return XST_SUCCESS;
}

int vdma_stop() {
	   XAxiVdma_DmaStop(&OutVdma, XAXIVDMA_READ);
	   return XST_SUCCESS;
}


int vdma_out_init(short DeviceID, int base_address, int h_width, int v_width, int bpp)
{
	XAxiVdma_Config *Config;
	int Status;


	Config = XAxiVdma_LookupConfig(DeviceID);
	if (NULL == Config) {
		xil_printf("XAxiVdma_LookupConfig failure\r\n");
		return XST_FAILURE;
	}

	Status = XAxiVdma_CfgInitialize(&OutVdma, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("XAxiVdma_CfgInitialize failure\r\n");
		return XST_FAILURE;
	}

	VDMAOutCfg.EnableCircularBuf = 1;
	VDMAOutCfg.EnableFrameCounter = 0;
	VDMAOutCfg.FixedFrameStoreAddr = 0;

	VDMAOutCfg.EnableSync = 1;
	VDMAOutCfg.PointNum = 1;

	VDMAOutCfg.FrameDelay = 0;

	VDMAOutCfg.VertSizeInput = v_width;
	VDMAOutCfg.HoriSizeInput = h_width * bpp;
	VDMAOutCfg.Stride = VDMAOutCfg.HoriSizeInput;

	Status = XAxiVdma_DmaConfig(&OutVdma, XAXIVDMA_READ, &VDMAOutCfg);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,
				"Read channel config failed %d\r\n", Status);

			return XST_FAILURE;
	}

	VDMAOutCfg.FrameStoreStartAddr[0] = base_address;

	Status = XAxiVdma_DmaSetBufferAddr(&OutVdma, XAXIVDMA_READ, VDMAOutCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,"Read channel set buffer address failed %d\r\n", Status);
			return XST_FAILURE;
	}


	Status = vdma_out_start();
	if (Status != XST_SUCCESS) {
		   xil_printf("error starting VDMA..!");
		   return Status;
	}
	return XST_SUCCESS;

}

int vdma_in_init(short DeviceID, int base_address, int h_width, int v_width, int bpp)
{
	XAxiVdma_Config *Config;
	int Status;

	Config = XAxiVdma_LookupConfig(DeviceID);
	if (NULL == Config) {
		xil_printf("XAxiVdma_LookupConfig failure\r\n");
		return XST_FAILURE;
	}

	Status = XAxiVdma_CfgInitialize(&InVdma, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("XAxiVdma_CfgInitialize failure\r\n");
		return XST_FAILURE;
	}

	VDMAInCfg.EnableCircularBuf = 1;
	VDMAInCfg.EnableFrameCounter = 0;
	VDMAInCfg.FixedFrameStoreAddr = 0;

	VDMAInCfg.EnableSync = 1;
	VDMAInCfg.PointNum = 1;

	VDMAInCfg.FrameDelay = 0;

	VDMAInCfg.VertSizeInput = v_width;
	VDMAInCfg.HoriSizeInput = h_width * bpp;
	VDMAInCfg.Stride = VDMAInCfg.HoriSizeInput;

	Status = XAxiVdma_DmaConfig(&InVdma, XAXIVDMA_WRITE, &VDMAInCfg);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,
				"Read channel config failed %d\r\n", Status);

			return XST_FAILURE;
	}

	VDMAInCfg.FrameStoreStartAddr[0] = base_address;

	Status = XAxiVdma_DmaSetBufferAddr(&InVdma, XAXIVDMA_WRITE, VDMAInCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
			xdbg_printf(XDBG_DEBUG_ERROR,"Write channel set buffer address failed %d\r\n", Status);
			return XST_FAILURE;
	}


	Status = vdma_in_start();
	if (Status != XST_SUCCESS) {
		   xil_printf("error starting VDMA..!");
		   return Status;
	}

	return XST_SUCCESS;

}

