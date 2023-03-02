#include <xcore/chanend.h>
#include <xcore/channel.h>
#include "ep0_offtile_helpers.h"

/** Functions the off tile EP0 uses to communicate with the EP0 proxy running on the same tile as USB */

void offtile_set_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num)
{
    chan_out_byte(chan_ep0_proxy, e_set_stall_by_addr);
    chan_out_word(chan_ep0_proxy, ep_num);
    // No status since XUD_SetStallByAddr has void return type
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy); // Block to ensure operation completed on the XUD tile
}

void offtile_clear_stall_by_addr(chanend_t chan_ep0_proxy, unsigned ep_num)
{
    chan_out_byte(chan_ep0_proxy, e_clear_stall_by_addr);
    chan_out_word(chan_ep0_proxy, ep_num);
    // No status since XUD_ClearStallByAddr has void return type
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy); // Block to ensure operation completed on the XUD tile
}

XUD_Result_t offtile_do_get_request(chanend_t chan_ep0_proxy, uint8_t *buffer, uint8_t length)
{
    chan_out_byte(chan_ep0_proxy, e_do_get_request);
    chan_out_byte(chan_ep0_proxy, length);
    chan_out_buf_byte(chan_ep0_proxy, (uint8_t*)buffer, length);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy);
    return result;
}

XUD_Result_t offtile_set_req_status(chanend_t chan_ep0_proxy)
{
    chan_out_byte(chan_ep0_proxy, e_set_req_status);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy);
    return result;
}

void offtile_hal_set_device_address(chanend_t chan_ep0_proxy, unsigned char address)
{
    chan_out_byte(chan_ep0_proxy, e_hal_set_device_addr);
    chan_out_byte(chan_ep0_proxy, address);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy); // Block to ensure operation completed on the XUD tile
}

void offtile_reset_ep_state_by_addr(chanend_t chan_ep0_proxy, uint8_t ep_addr)
{
    chan_out_byte(chan_ep0_proxy, e_reset_ep_state_by_addr);
    chan_out_byte(chan_ep0_proxy, ep_addr);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy); // Block to ensure operation completed on the XUD tile
}

void offtile_set_stall(chanend_t chan_ep0_proxy)
{
    chan_out_byte(chan_ep0_proxy, e_set_stall);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy); // Block to ensure operation completed on the XUD tile
}

uint8_t offtile_reset_endpoint(chanend_t chan_ep0_proxy)
{
    chan_out_byte(chan_ep0_proxy, e_reset_endpoint);
    uint8_t usb_bus_speed = chan_in_byte(chan_ep0_proxy);
    return usb_bus_speed;
}

void offtile_set_test_mode(chanend_t chan_ep0_proxy, unsigned test_mode)
{
    chan_out_byte(chan_ep0_proxy, e_set_test_mode);
    chan_out_word(chan_ep0_proxy, test_mode);
    XUD_Result_t result = chan_in_byte(chan_ep0_proxy); // Block to ensure operation completed on the XUD tile
}




