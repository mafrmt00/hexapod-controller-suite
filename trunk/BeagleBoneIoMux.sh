#!/bin/sh

echo "Configuring Pinmux"

echo 0 > /sys/kernel/debug/omap_mux/uart1_txd
echo 20> /sys/kernel/debug/omap_mux/uart1_rxd

echo "UART 1 (TX):"
cat /sys/kernel/debug/omap_mux/uart1_txd
echo

echo "UART 1 (RX):"
cat /sys/kernel/debug/omap_mux/uart1_rxd
echo

echo 1 > /sys/kernel/debug/omap_mux/spi0_d0
echo 21> /sys/kernel/debug/omap_mux/spi0_sclk

echo "UART 2 (TX):"
cat /sys/kernel/debug/omap_mux/spi0_d0
echo

echo "UART 2 (RX):"
cat /sys/kernel/debug/omap_mux/spi0_sclk
echo
