#!/bin/bash

W='\033[0;00m'
R='\033[0;91m'
Y='\033[0;93m'
G='\033[0;92m'
P='\033[0;95m'
C='\033[0;36m'

git status &> /tmp/.minishell_git_logs

while read line; do
	if [[ $line == *"not a git repository"* ]]; then
		let "id = 0"
	elif [[ $line == "Untracked files:" || $line == "Changes not staged for commit:" ]]; then
		let "id = id + 1000"
	elif [[ $line == "Changes to be committed:" ]]; then
		let "id = id + 100"
	elif [[ $line == *"nothing to commit, working tree clean"* ]]; then
		let "id = id + 1"
	elif [[ $line == *"Your branch is ahead of"* ]]; then
		let "id = id + 10"
	fi
done < <(cat /tmp/.minishell_git_logs)

if [ $id -eq 0 ]; then
	printf "${C} » ${W}"
elif [ $id -lt 10 ]; then
	printf "${G} » ${W}"
elif [ $id -lt 100 ]; then
	printf "${P} » ${W}"
elif [ $id -lt 1000 ]; then
	printf "${Y} » ${W}"
else
	printf "${R} » ${W}"
fi

rm -f /tmp/.minishell_git_logs
