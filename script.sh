#!/bin/bash

for i in {1..16};do

	./taller11 1400000000 $i >> tiempos.txt
	sleep 0.25
done
