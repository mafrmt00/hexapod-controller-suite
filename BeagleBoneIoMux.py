#!/usr/bin/python 
import os 
import logging 
DDR_IN  = (1 << 5) 
DDR_OUT = (0 << 5) 
PULL_R_UP       = (1 << 4) 
PULL_R_DOWN     = (0 << 4) 
PULL_R_EN       = (1 << 3) 
PULL_R_DIS      = (0 << 3) 
uart1_pin_mux = [ 
        ('uart1_rxd', (0 | DDR_IN)), 
        ('uart1_txd', (0)), 
] 
logging.basicConfig(level=logging.DEBUG) 
for (fname, mode) in uart1_pin_mux: 
        logging.debug("%s = %s" % (fname, mode)) 
        with open(os.path.join('/sys/kernel/debug/omap_mux', fname), 'wb') as f:

                f.write("%X" % mode) 

