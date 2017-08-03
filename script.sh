#!/bin/bash

for i in {1..16};do

	./taller11 100000 $i >> tiempos.txt
done
