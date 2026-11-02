# CSCE465-HW3
ran the following commands to set up the environment
sudo apt update
sudo apt install -y build-essential gdb binutils checksec apparmor-utils

created and went to csce465-agentsec/hw3 and created the vulnerable legacy log parser partially with AI in codex

created the safe decoy with
sudo mkdir -p /opt/agentsec
printf 'FAKE-COURSE-SECRET\n' | sudo tee /opt/agentsec/decoy.txt
sudo chmod 600 /opt/agentsec/decoy.txt

and compiled legacy log parser with the command
gcc -O0 -g -fno-stack-protector -no-pie -Wl,-z,noexecstack \
-Wall -Wextra -o legacy_log_parser legacy_log_parser.c
checksec --file=./legacy_log_parser

opened with gdb and set a breakpoint in vulnerable_copy and win
ran with a simple test.log file with just a few words in it.

did 
info frame
disassemble vulnerable_copy (although I didn't get anything from this)
info address win

calculated the offset (although likely incorrectly? this is where I am struggling)

Tried to create python file that makes a payload to write and overflow the buffer to the address
failed continuously but I can't complete the other steps without this or at least knowing if this is correct

tried to consult with AI numerous times, but due to security limitations they cannot help me directly and I do not understand the explanations enough to do it myself
