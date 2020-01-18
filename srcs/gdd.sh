#!/bin/bash

YELLOW='\033[0;33m'

git status &> /tmp/.minishell_git_logs

cat /tmp/.minishell_git_logs | while read line ; do
	if [[ $line == "fatal: not a git repository (or any parent up to mount point /Users)" ]]
	then
		rm /tmp/.minishell_git_logs
		exit 0
	elif [[ $line == "nothing to commit, working tree clean" ]]
	then
		printf "${YELLOW} -"
		rm /tmp/.minishell_git_logs
		exit 0
	elif [[ $line == "Untracked files:" || $line == "Changes not staged for commit:" ]]
	then
		printf "${YELLOW} +"
		rm /tmp/.minishell_git_logs
		exit 0
	fi
done
