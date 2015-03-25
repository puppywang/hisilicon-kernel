
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_priv.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_DISP_PRIV_H__
#define __DRV_DISP_PRIV_H__

#include "hi_drv_video.h"
#include "hi_drv_disp.h"
#include "drv_disp_hal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

#define DISP_DEVICE_STATE_CLOSE   0
#define DISP_DEVICE_STATE_OPEN    1
#define DISP_DEVICE_STATE_SUSPEND 2

#define DISP_SET_TIMEOUT_THRESHOLD  10

/* default back ground color */
#define DISP_DEFAULT_COLOR_RED   0
#define DISP_DEFAULT_COLOR_GREEN 0
#define DISP_DEFAULT_COLOR_BLUE  0

/* default csc parameters value */
#define DISP_DEFAULT_BRIGHT       50
#define DISP_DEFAULT_HUE          50
#define DISP_DEFAULT_SATURATION   50
#define DISP_DEFAULT_CONTRAST     50
#define DISP_DEFAULT_KR           50
#define DISP_DEFAULT_KG           50
#define DISP_DEFAULT_KB           50

#define DISP_DEFAULT_SATURATION_OFFSET 0
#define DISP_DEFAULT_BRIGHT_OFFSET     0
#define DISP_DEFAULT_CONTRAST_OFFSET   0
#define DISP_DEFAULT_HUE_OFFSET        0
#define DISP_DEFAULT_KR_OFFSET         0
#define DISP_DEFAULT_KG_OFFSET         0
#define DISP_DEFAULT_KB_OFFSET         0


typedef enum tagDISP_PRIV_STATE_E
{
    DISP_PRIV_STATE_DISABLE = 0,
    DISP_PRIV_STATE_WILL_ENABLE, //1
    DISP_PRIV_STATE_ENABLE, //2
    DISP_PRIV_STATE_WILL_DISABLE, //3
    DISP_PRIV_STATE_BUTT
}DISP_PRIV_STATE_E;


typedef struct tagDISP_SETTING_S
{
    HI_U32  u32Version; //0
    HI_U32  u32BootVersion; //4
    //HI_BOOL bSelfStart;
    HI_BOOL bGetPDMParam; //8
    
    /* output format */
    HI_DRV_DISP_STEREO_E eDispMode; //12
    HI_BOOL bRightEyeFirst; //16
    HI_DRV_DISP_FMT_E enFormat; //20
    HI_BOOL bFmtChanged;

    HI_DRV_DISP_TIMING_S stCustomTimg; //28
#if 0
    HI_BOOL bCustomTimingIsSet;
    HI_BOOL bCustomTimingChange;
#endif

    /* about color */
    HI_DRV_DISP_COLOR_SETTING_S stColor; //128

    /* background color */
    HI_DRV_DISP_COLOR_S stBgColor; //180

    //HI_BOOL bCGMSAEnable;
    //HI_DRV_DISP_CGMSA_TYPE_E  eCGMSAType;
    //HI_DRV_DISP_CGMSA_MODE_E  eCGMSAMode;

    //HI_DRV_DISP_MACROVISION_E eMcvnType;

    /* interface setting */
    HI_U32 u32IntfNumber;
    //HI_DRV_DISP_INTF_S stIntf[HI_DRV_DISP_INTF_ID_MAX];
    DISP_INTF_S stIntf[HI_DRV_DISP_INTF_ID_MAX]; //188

    HI_U32 u32LayerNumber; //800
    HI_DRV_DISP_LAYER_E enLayer[HI_DRV_DISP_LAYER_BUTT]; /* Z-order is from bottom to top */


    /*we define a vitual format size, all the size settings  users can see are referenced to this rect.
     *      * so users can make a fixed setting not according to the real format size such as 1280*720 50hz.
     *           * it's manual-kindly. When setting to devices, we make a transfer according the real resolution.
     *                */     
    HI_RECT_S stVirtaulScreen; //816

    /*as a result of cutting off by crt tv, we make a offset setting to make sure
     *      * that the display is complete, not cut by tv.*/
    HI_DRV_DISP_OFFSET_S stOffsetInfo; //832


    
    HI_BOOL bCustomRatio; //848
    HI_U32 u32CustomRatioWidth; //852
    HI_U32 u32CustomRatioHeight; //856

    HI_U32  u32Reseve; //860
    HI_VOID *pRevData; //864
    //868
}DISP_SETTING_S;

typedef struct tagDISP_S
{
    HI_DRV_DISPLAY_E enDisp; //0

    //state
    HI_BOOL bSupport; //4
    HI_BOOL bOpen; //8
    HI_BOOL bEnable; //12
    HI_BOOL bStateBackup;
        
    /* for attach display */
    HI_BOOL bIsMaster; //20
    HI_BOOL bIsSlave; //24
    HI_DRV_DISPLAY_E enAttachedDisp; //28

    DISP_SETTING_S stSetting; //32
    HI_BOOL bDispSettingChange; //900

    volatile DISP_PRIV_STATE_E eState; //904
    HI_U32 u32Underflow; //908
    HI_U32 u32StartTime; //912

    // for other module get
    //HI_BOOL bDispInfoValid;
    HI_DISP_DISPLAY_INFO_S stDispInfo; //916
    
    //mirrorcast
    HI_HANDLE hCast; //1056
    HI_HANDLE Cast_ptr;

    //algrithm operation
    //HI_HANDLE hAlgOpt;

    //component operation
    DISP_INTF_OPERATION_S *pstIntfOpt; //1064
    //1068
}DISP_S;

typedef struct tagDISP_ATTACH_ID_S
{
    HI_DRV_DISPLAY_E eMaster;
    HI_DRV_DISPLAY_E eSlave;
}DISP_ATTACH_ID_S;

typedef struct tagDISP_DEV_S
{
    HI_BOOL bHwReseted; //0
    DISP_S  stDisp[HI_DRV_DISPLAY_BUTT+1]; //4

    HI_BOOL bAttachEnable;
    DISP_ATTACH_ID_S stAttchDisp;
    DISP_INTF_OPERATION_S stIntfOpt; //4288
    //4508
}DISP_DEV_S;



#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /*  __DRV_DISP_PRIV_H__  */

