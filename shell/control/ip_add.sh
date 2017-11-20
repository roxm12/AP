#! /bin/bash

sudo iptables -A PREROUTING -t nat -p tcp -s $1 -d $2 -j DNAT --to 172.24.1.1:3000

sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
