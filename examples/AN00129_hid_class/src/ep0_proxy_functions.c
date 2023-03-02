#include <xcore/chanend.h>
#include <xcore/channel.h>
#include "ep0_proxy.h"

void offtile_set_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num)
{
    chan_out_byte(chan_ep0_proxy, e_set_stall_by_addr);
    chan_out_word(chan_ep0_proxy, ep_num);
    // No status since XUD_SetStallByAddr has void return type
}

void offtile_clear_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num)
{
    chan_out_byte(chan_ep0_proxy, e_clear_stall_by_addr);
    chan_out_word(chan_ep0_proxy, ep_num);
    // No status since XUD_ClearStallByAddr has void return type
}

XUD_Result_t offtile_do_get_request(chanend_t chan_ep0_proxy, uint8_t *buffer, uint8_t length)
{
    chan_out_byte(chan_ep0_proxy, e_do_get_request);
    chan_out_byte(chan_ep0_proxy, length);
    chan_out_buf_byte(chan_ep0_proxy, (uint8_t*)buffer, length);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy);
    return result;
}

