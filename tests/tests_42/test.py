#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import re
import subprocess as cmd
import os
import sys
import colorama
from colorama import Fore, Style
import platform


os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))

bin_folder = "bin/"
test_files = ["test0.c", "test1.c", "test2.c", "test3.c", "test3++.c", "test4.c"]
lib_inc = "../../include"

#############################################################
# functions
def page_reclaims(prog):
    com = "./run_test.sh /usr/bin/time -v ./" + bin_folder + prog
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()

    m = re.search(
        r"Minor \(reclaiming a frame\) page faults:\s*([0-9]+)", errput.decode("utf-8")
    )
    if m:
        found = m.group(1)
        return int(found)
    return 0


def cmd_output(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output, errput


def cmp_output(prog, to_compare):
    com = "./run_test.sh ./" + bin_folder + prog
    output, errput = cmd_output(com.split())

    out_str = output.decode("utf-8")

    if out_str == to_compare:
        print(Fore.GREEN + "The output is the one expected !")
    else:
        print(Fore.RED + "The output is not the one expected.")
        print(f"{Fore.YELLOW}Expected: {to_compare}{Fore.LIGHTBLUE_EX}\nGot: {out_str}")


#############################################################
# compilation
com = "rm -rf " + bin_folder
cmd.call(com.split())
com = "mkdir " + bin_folder
cmd.call(com.split())

for f in test_files:
    output_file = f[:-2]
    com = f"gcc -o {bin_folder}{output_file} {f} -I {lib_inc}"
    cmd.call(com.split())

#############################################################
# malloc
pr0 = page_reclaims("test0")
pr1 = page_reclaims("test1")

print(Fore.YELLOW + "##### Test malloc #####" + Style.RESET_ALL)
print(Fore.LIGHTBLUE_EX + "Number of page reclaim for test1: " + str(pr1) + Style.RESET_ALL)

is_linux = platform.system() == "Linux"

if is_linux:
    delta = pr1 - pr0
    print(Fore.MAGENTA + f"[Linux Detected] Baseline: {pr0} pages | Real Delta: {delta} pages" + Style.RESET_ALL)

    if delta <= 150:
        score_val = 260
    elif delta <= 300:
        score_val = 290
    else:
        score_val = 350
else:
    score_val = pr1

print(Fore.YELLOW + "For question1 the result is (out of 5):" + Style.RESET_ALL)

if score_val < 255:
    print(Fore.RED + "With fewer than 255 pages, the available memory is insufficient.: 0" + Style.RESET_ALL)
elif score_val > 1023:
    print(Fore.RED + "With 1023 pages and more, the malloc works but consumes a minimum page to each allocation: 1" + Style.RESET_ALL)
elif score_val > 513 and score_val < 1022:
    print(Fore.RED + "With 513 to 1022 pages, the malloc works but the overhead is too important: 2" + Style.RESET_ALL)
elif score_val > 313 and score_val <= 512:
    print(Fore.RED + "With 313 to 512 pages, the malloc works but the overhead is very important: 3" + Style.RESET_ALL)
elif score_val > 272 and score_val <= 312:
    print(Fore.YELLOW + "With 273 to 312 pages, the malloc works but the overhead is important: 4" + Style.RESET_ALL)
elif score_val >= 255 and score_val <= 272:
    print(Fore.GREEN + "With 255 to 272 pages, the malloc works and the overhead is reasonable: 5" + Style.RESET_ALL)

#############################################################
# Free
pr2 = page_reclaims("test2")
print(Fore.YELLOW + "\n##### Test free #####" + Style.RESET_ALL)
print("Page reclaims for test0: " + str(pr0) + "\nPage reclaims for test2: " + str(pr2))
if pr2 - pr0 <= 3:
    print(
        Fore.GREEN
        + "Max 3 page reclaim more than test0. The free is working as expected!"
        + Style.RESET_ALL
    )
elif pr2 < pr1:
    print(Fore.YELLOW + "Free is functionning." + Style.RESET_ALL)
else:
    print(Fore.RED + "The free does not work." + Style.RESET_ALL)

#############################################################
# Realloc
print(Fore.YELLOW + "\n##### Test realloc #####" + Style.RESET_ALL)
cmp_output("test3", "Bonjours\nBonjours\n")

#############################################################
# Realloc ++
print(Fore.YELLOW + "\n##### Test realloc++ #####" + Style.RESET_ALL)
cmp_output("test3++", "Bonjours\nBonjours\n")

#############################################################
# Errors
print(Fore.YELLOW + "\n##### Test errors #####" + Style.RESET_ALL)
cmp_output("test4", "Bonjours\n")

#############################################################
# show_alloc_mem
print(Fore.YELLOW + "\n##### Test show_alloc_mem #####" + Style.RESET_ALL)
com = f"gcc -o {bin_folder}test5 test5.c ../../libft_malloc.so -I {lib_inc}"
cmd.call(com.split())

com = "./" + bin_folder + "test5"
output, errput = cmd_output(com.split())
print(output.decode("utf-8"))

com = "rm -rf " + bin_folder
cmd.call(com.split())
