#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 11:03:02 by macarval          #+#    #+#              #
#    Updated: 2026/04/10 18:56:42 by macarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Run tests
# Usage: make test -OU- make && ./test.sh

# Colors
red='\033[31;1m'
blue='\033[36;1m'
green='\033[32;1m'
yellow='\033[33;1m'
purple='\033[35;1m'
gray='\033[37;1m'
reset='\033[0m'

PROGRAM="./obj/test_malloc"
LIBRARY="./libft_malloc.so"

total_tests=0
successful_tests=0

declare -a descriptions=(
	"Basic malloc() and data integrity"
	"Edge case: malloc(0)"
	"Multiple allocations (Tiny/Small zones)"
	"Basic realloc() with data retention"
	"Edge case: realloc(NULL) and realloc(0)"
	"Stress test: 1000 loop allocations/frees"
	"Visual: Tiny zone allocations & frees"
	"Visual: Small zone allocations & frees"
	"Visual: Large zone allocations & frees"
	"Visual: Edge cases crash survival"
	"Visual: Fragmentation and Coalescing"
	"Large allocation test"
	"Overlaping test"
)

clear
echo
echo -e "${blue}-------------------------------------------------------------------------"
echo -e "************************* STARTING MALLOC TESTS *************************"
echo -e "-------------------------------------------------------------------------"
echo -e "${yellow}Compiling project with 'make re comp'...${reset}"

make re comp > /dev/null 2>&1

if [ ! -f "$PROGRAM" ] || [ ! -f "$LIBRARY" ]; then
	echo -e "${red}Error: Compilation failed. $PROGRAM or $LIBRARY not found.${reset}"
	exit 1
else
	echo -e "${green}Success: Compilation completed.${reset}"
fi

echo -e "${blue}\n-------------------------------------------------------------------------"
echo -e "Running Executions with LD_PRELOAD..."
echo -e "-------------------------------------------------------------------------${reset}"

for i in "${!descriptions[@]}"; do
	test_id=$((i + 1))
	desc="${descriptions[$i]}"

	((total_tests++))

	echo -en "${yellow}Test ${purple}#$test_id: ${yellow}${desc} -> ${reset}"

	env LD_PRELOAD=$LIBRARY $PROGRAM $test_id > /dev/null 2>&1
	exit_code=$?

	if [ $exit_code -eq 0 ]; then
		echo -e "${green}✅ Passed${reset}"
		((successful_tests++))
	elif [ $exit_code -eq 139 ]; then
		echo -e "${red}❌ Failed (Segmentation Fault)${reset}"
	else
		echo -e "${red}❌ Failed (Exit code: $exit_code)${reset}"
	fi

	sleep 0.2
done

echo -e "${blue}\n-------------------------------------------------------------------------"
echo -e "Tests finished..."
echo -e "-------------------------------------------------------------------------${reset}"

make fclean > /dev/null 2>&1
echo -e "${green}Cleanup completed.${reset}"

# Calculate percentage of hits
if [ $total_tests -gt 0 ]; then
	percentage=$(echo "scale=4; $successful_tests / $total_tests * 100" | bc)
else
	percentage=0
fi

# Print results with color
echo -en "\n\e[33mTotal number of tests performed: \e[94m$total_tests"
echo -en "\n\e[33mTests OK: \e[94m$successful_tests"
echo -e "\n\e[33mPercentage of hits: \e[94m$(printf "%.2f" "$percentage")%\n"

if [ "$(printf "%.2f" "$percentage")" = "100.00" ]; then
	echo -e "${green}------------------------ 𝙲𝚘𝚗𝚐𝚛𝚊𝚝𝚞𝚕𝚊𝚝𝚒𝚘𝚗𝚜!!!🎉🎊 ------------------------\n"
else
	echo -e "${red}------------------------- 𝚄𝚗𝚏𝚘𝚛𝚝𝚞𝚗𝚊𝚝𝚎𝚕𝚢!!!⛔😩 --------------------------\n"
fi
