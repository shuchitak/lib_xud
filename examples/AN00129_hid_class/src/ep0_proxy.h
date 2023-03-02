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
    e_sp_not_processed,
    ep_sp_pkt_done
}ep0_proxy_cmds_t;

void offtile_set_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num);
void offtile_clear_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num);
XUD_Result_t offtile_do_get_request(chanend_t chan_ep0_proxy, uint8_t *buffer, uint8_t length);

#endif