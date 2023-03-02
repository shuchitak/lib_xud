// Copyright 2015-2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
/**
 * @brief      Implements USB Device standard requests
 * @author     Ross Owen, XMOS Limited
 */

#include "xud_device.h"          /* Defines related to the USB 2.0 Spec */
#include <xcore/chanend.h>
#include <xcore/channel.h>

#include "ep0_proxy.h"

#ifndef MAX_INTS
/* Maximum number of interfaces supported */
#define MAX_INTS    16
#endif

#ifndef MAX_EPS
/* Maximum number of EP's supported */
#define MAX_EPS     USB_MAX_NUM_EP
#endif

static unsigned char g_currentConfig = 0;
static unsigned char g_interfaceAlt[MAX_INTS]; /* Global endpoint status arrays */

static unsigned short g_epStatusOut[MAX_EPS];
static unsigned short g_epStatusIn[MAX_EPS];

// Off tile implementation
XUD_Result_t XUD_DoSetRequestStatus_offtile(chanend_t chan_ep0_proxy, unsigned epNum, unsigned halt)
{
    /* Inspect for IN bit */
    if(epNum & 0x80)
    {
        /* Range check */
        if((epNum&0x7F) < MAX_EPS)
        {
            g_epStatusIn[epNum & 0x7F] = halt;
            if(halt)
                offtile_set_stall_by_addr(chan_ep0_proxy, epNum);
            else
                offtile_clear_stall_by_addr(chan_ep0_proxy, epNum);
            return 0;
        }
    }
    else
    {
        if(epNum < MAX_EPS)
        {
            g_epStatusOut[epNum] = halt;
            if(halt)
                offtile_set_stall_by_addr(chan_ep0_proxy, epNum);
            else
                offtile_clear_stall_by_addr(chan_ep0_proxy, epNum);

            return 0;
        }
    }

    return 1;
}