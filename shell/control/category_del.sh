#! /bin/bash

if [ "$1" -eq 0 ]; then

while read line;

do
sudo iptables -D PREROUTING -t nat -p tcp -s $2 -d $line -j DNAT --to 172.24.1.1:3000

done < ~/AP/shell/iplist/naver_ip.txt

elif [ "$1" -eq 1 ]; then

while read line;
do
sudo iptables -D PREROUTING -t nat -p tcp -s $2 -d $line -j DNAT --to 172.24.1.1:3000

done < ~/AP/shell/iplist/daum_ip.txt

elif [ "$1" -eq 2 ]; then

while read line;
do
sudo iptables -D PREROUTING -t nat -p tcp -s $2 -d $line -j DNAT --to 172.24.1.1:3000
done < ~/AP/shell/iplist/amazon_ip.txt

elif [ "$1" -eq 3 ]; then

while read line;
do
sudo iptables -D PREROUTING -t nat -p tcp -s $2 -d $line -j DNAT --to 172.24.1.1:3000
done < ~AP/shell/iplist/google_ip.txt

else
echo "wrong category num"
fi
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
