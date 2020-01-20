#!/bin/bash

YELLOW='\033[0;93m'
GREEN='\033[0;92m'
RED='\033[0;91m'
CYAN='\033[0;36m'
WHITE='\033[m'

git status &> /tmp/.minishell_git_logs

cat /tmp/.minishell_git_logs | while read line ; do
	if [[ $line == *"not a git repository"* ]]
	then
		printf "${YELLOW} » ${WHITE}"
		rm /tmp/.minishell_git_logs
		exit 0
	elif [[ $line == *"nothing to commit, working tree clean"* ]]
	then
		printf "${GREEN} » ${WHITE}"
		rm /tmp/.minishell_git_logs
		exit 0
	elif [[ $line == *"Untracked files:"* || $line == *"Changes not staged for commit:"* ]]
	then
		printf "${RED} » ${WHITE}"
		rm /tmp/.minishell_git_logs
		exit 0
	fi
done
