/******************************************************************************
*
* 
* 
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file te_fsbl_hooks.h
*
*
******************************************************************************/
//rename to correct board name
#ifndef TE_FSBL_HOOKS_CUSTOM_H_
#define TE_FSBL_HOOKS_CUSTOM_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "fsbl.h"

/************************** Function Prototypes ******************************/

/* FSBL hook function which is called before bitstream download */
u32 TE_FsblHookBeforeBitstreamDload_Custom(void);

/* FSBL hook function which is called after bitstream download */
u32 TE_FsblHookAfterBitstreamDload_Custom(void);

/* FSBL hook function which is called before handoff to the application */
u32 TE_FsblHookBeforeHandoff_Custom(void);

/* FSBL hook function which is called in FSBL fallback */
void TE_FsblHookFallback_Custom(void);

#ifdef __cplusplus
}
#endif

#endif	/* end of protection macro */
