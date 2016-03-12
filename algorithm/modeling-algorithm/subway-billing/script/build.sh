#!/bin/bash

##! @FUNCTION: Build map and stations
##! @AUTHOR: wujie(404732744@qq.com)
##! @DATE: 2014/11/2
##! @VERSION: 1.0
##! @FILEIN: TODO
##! @FILEOUT: Subway.map


##!
##! @Global variable
##!

##! 对应从L1-L5每条线路的总站数
SUBWAY_LENGTH_LIST=(14 16 13 16 10)
##! 对应从X1-X8中转站的边
SUBWAY_TRANSFER_LIST=("L1-2 L1-3 L3-3 L3-4" "L1-4 X3 L2-8 X4" "X2 L1-5 L5-7 X4" "X3 L5-6 L3-7 L3-8" "L5-4 L5-5 L1-11 L1-12" "L1-13 L1-14 L2-12 L2-13" "L1-10 L1-11 L4-5 L4-6" "L4-8 L4-9 L1-7 L1-8 L3-9 L3-10")
SUBWAY_TRANSFER_NUM=8

##!
##! @Functions
##!

function build_line()
{
	for ((i=0; i<${#SUBWAY_LENGTH_LIST[@]}; i++))
	do
		local line_length=${SUBWAY_LENGTH_LIST[i]}
		for ((j=1; j<${line_length}; j++))
		do
			local line=$((i+1))
			local next_num=$((j+1))
			if [[ ${line} -eq 1 ]]
			then
				if [[ ${j} -eq 2 ]] || [[ ${j} -eq 4 ]] || [[ ${j} -eq 7 ]] || [[ ${j} -eq 10 ]] || \
					[[ ${j} -eq 11 ]] || [[ ${j} -eq 13 ]]
				then
					continue;
				fi
			fi
			if [[ ${line} -eq 2 ]]
			then
				if [[ ${j} -eq 8 ]] || [[ ${j} -eq 12 ]]
				then
					continue;
				fi
			fi
			if [[ ${line} -eq 3 ]]
			then
				if [[ ${j} -eq 3 ]] || [[ ${j} -eq 7 ]] || [[ ${j} -eq 9 ]]
				then
					continue;
				fi
			fi
			if [[ ${line} -eq 4 ]]
			then
				if [[ ${j} -eq 5 ]] || [[ ${j} -eq 8 ]]
				then
					continue;
				fi
			fi
			if [[ ${line} -eq 5 ]]
			then
				if [[ ${j} -eq 3 ]] || [[ ${j} -eq 6 ]]
				then
					continue;
				fi
			fi
			echo "L${line}-${j} L${line}-${next_num}"
			echo "L${line}-${next_num} L${line}-${j}"
		done
	done
}

function build_transfer()
{
	for ((i=0; i<${#SUBWAY_TRANSFER_LIST[@]}; i++))
	do
		##! not local
		transfer_list=(${SUBWAY_TRANSFER_LIST[i]})
		for ((j=0; j<${#transfer_list[@]}; j++))
		do
			local trans=$((i+1))
			echo "X${trans} ${transfer_list[j]}"
			echo "${transfer_list[j]} X${trans}"
		done
	done
}

function build_station()
{
	for ((i=0; i<${#SUBWAY_LENGTH_LIST[@]}; i++))
	do
		for ((j=1; j<=${SUBWAY_LENGTH_LIST[i]}; j++))
		do
			echo "L$((i+1))-${j}"
		done
	done
	for ((i=1; i<=${SUBWAY_TRANSFER_NUM}; i++))
	do
		echo "X${i}"
	done
}


function work()
{
	build_station > stations.list
	build_line > subway.map
	build_transfer >> subway.map
	sort -u subway.map -o subway.map
	sort -u stations.list -o stations.list
}

##!
##! @Running
##!

work

