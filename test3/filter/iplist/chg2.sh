#!/bin/bash

while read line;
	do
#echo $line
	    host $line | grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}" |tee -a test_ip.txt
	done < test_urls.txt
