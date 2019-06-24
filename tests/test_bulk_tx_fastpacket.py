#!/usr/bin/env python

import random
import xmostest
from  usb_packet import *
from usb_clock import Clock
from helpers import do_usb_test, runall_rx

def do_test(arch, clk, phy, seed):
    rand = random.Random()
    rand.seed(seed)

    address = 1
    ep = 3

    # The inter-frame gap is to give the DUT time to print its output
    packets = []

    data_val = 0;
    pkt_length = 20
    data_pid = 0x3 #DATA0 

    for pkt_length in range(10, 20):
    
        #317 lowest for valid data (non-dual issue version)
        #337 for initial dual-issue version
        AppendInToken(packets, ep, address, inter_pkt_gap=337)
        packets.append(RxDataPacket(rand, data_start_val=data_val, length=pkt_length, pid=data_pid))
        packets.append(TxHandshakePacket())

        data_val = data_val + pkt_length
        data_pid = data_pid ^ 8

    do_usb_test(arch, clk, phy, packets, __file__, seed,
               level='smoke', extra_tasks=[])

def runtest():
    random.seed(1)
    runall_rx(do_test)
