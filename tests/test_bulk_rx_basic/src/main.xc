// Copyright (c) 2018-2019, XMOS Ltd, All rights reserved
#include <xs1.h>
#include <print.h>
#include <stdio.h>
#include "xud.h"
#include "platform.h"
#include "shared.h"

#define XUD_EP_COUNT_OUT   5
#define XUD_EP_COUNT_IN    5

#ifndef PKT_LENGTH_START
#define PKT_LENGTH_START 10
#endif

#ifndef PKT_LENGTH_END
#define PKT_LENGTH_END 14
#endif

#ifndef TEST_EP_NUM
#define TEST_EP_NUM   1
#endif

/* Endpoint type tables */
XUD_EpType epTypeTableOut[XUD_EP_COUNT_OUT] = {XUD_EPTYPE_CTL, XUD_EPTYPE_BUL, XUD_EPTYPE_ISO, XUD_EPTYPE_BUL, XUD_EPTYPE_BUL};
XUD_EpType epTypeTableIn[XUD_EP_COUNT_IN] =   {XUD_EPTYPE_CTL, XUD_EPTYPE_BUL, XUD_EPTYPE_ISO, XUD_EPTYPE_BUL, XUD_EPTYPE_BUL};

#ifdef XUD_TEST_RTL
int testmain()
#else
int main()
#endif
{
    chan c_ep_out[XUD_EP_COUNT_OUT], c_ep_in[XUD_EP_COUNT_IN];
            
    par
    {
        XUD_Main(c_ep_out, XUD_EP_COUNT_OUT, c_ep_in, XUD_EP_COUNT_IN,
                null, epTypeTableOut, epTypeTableIn,
                null, null, -1, XUD_SPEED_HS, XUD_PWR_BUS);

        {
            unsigned fail = TestEp_Rx(c_ep_out[TEST_EP_NUM], TEST_EP_NUM, PKT_LENGTH_START, PKT_LENGTH_END);

#ifdef XUD_TEST_RTL
            if(fail)
                TerminateFail(fail);
            else
                TerminatePass(fail);    
#endif
            XUD_ep ep0 = XUD_InitEp(c_ep_out[0]);
            XUD_Kill(ep0);
            exit(0);
        }
    }

    return 0;
}
