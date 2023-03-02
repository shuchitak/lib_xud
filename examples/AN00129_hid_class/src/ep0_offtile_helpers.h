#ifndef EP0_PROXY_H
#define EP0_PROXY_H

#include <xcore/chanend.h>
#include <xcore/channel.h>
#include "xud_device.h"

typedef enum {
    e_do_get_request = 36,
    e_set_req_status,
    e_set_stall_by_addr,
    e_clear_stall_by_addr,
    e_hal_set_device_addr,
    e_reset_ep_state_by_addr,
    e_set_stall,
    e_reset_endpoint,
    e_set_test_mode,
    e_sp_not_processed,
    ep_sp_pkt_done
}ep0_proxy_cmds_t;

void offtile_set_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num);
void offtile_clear_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num);
XUD_Result_t offtile_do_get_request(chanend_t chan_ep0_proxy, uint8_t *buffer, uint8_t length);
XUD_Result_t offtile_set_req_status(chanend_t chan_ep0_proxy);
void offtile_hal_set_device_address(chanend_t chan_ep0_proxy, unsigned char address);
void offtile_reset_ep_state_by_addr(chanend_t chan_ep0_proxy, uint8_t ep_addr);
void offtile_set_stall(chanend_t chan_ep0_proxy); //Stall ep0 in and out endpoints
uint8_t offtile_reset_endpoint(chanend_t chan_ep0_proxy);
void offtile_set_test_mode(chanend_t chan_ep0_proxy, unsigned test_mode);

XUD_Result_t USB_StandardRequests_offtile(chanend_t chan_ep0_proxy,
    unsigned char *devDesc_hs, int devDescLength_hs,
    unsigned char *cfgDesc_hs, int cfgDescLength_hs,
    unsigned char *devDesc_fs, int devDescLength_fs,
    unsigned char *cfgDesc_fs, int cfgDescLength_fs,
    char *strDescs[], int strDescsLength,
    USB_SetupPacket_t *sp, XUD_BusSpeed_t usbBusSpeed);
#endif