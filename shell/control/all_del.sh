#! /bin/bash

sudo iptables -F PREROUTING -t nat 

sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
