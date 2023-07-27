#!/bin/bash
sudo modprobe vcan
sudo ip link add can0 type vcan
sudo ip link set can0 up
sudo ip link add can1 type vcan
sudo ip link set can1 up
