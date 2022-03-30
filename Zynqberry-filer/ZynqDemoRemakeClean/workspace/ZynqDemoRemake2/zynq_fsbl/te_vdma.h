
#ifndef VDMA_H_
#define VDMA_H_

#include "xaxivdma.h"


extern XAxiVdma Vdma;		/**< Instance of the VDMA Device */
int vdma_out_init(short DeviceID, int base_address, int h_width, int v_width, int bpp);
int vdma_in_init(short DeviceID, int base_address, int h_width, int v_width, int bpp);

u32 vdma_version();

#endif /* VDMA_H_ */
