#!/bin/bash

W='\033[0;00m'
R='\033[0;91m'
Y='\033[0;93m'
G='\033[0;92m'
P='\033[0;95m'
C='\033[0;36m'

git status &> /tmp/.minishell_git_logs

while read line
do
	if [[ $line == *"not a git repository"* ]]
	then
		id=0
	elif [[ $line == "Untracked files:" || $line == "Changes not staged for commit:" ]]
	then
		id=1
	elif [[ $line == "Changes to be committed:" ]]
	then
		id=2
	elif [[ $line == *"Your branch is ahead of"* ]]
	then
		id=3
	elif [[ $line == *"nothing to commit, working tree clean"* ]]
	then
		id=4
	fi
done < <(cat /tmp/.minishell_git_logs)

case $id in
	0)
		printf "${C} » ${W}";;
	1)
		printf "${R} » ${W}";;
	2)
		printf "${G} » ${W}";;
	3)
		printf "${P} » ${W}";;
	4)
		printf "${Y} » ${W}";;
esac

rm -f /tmp/.minishell_git_logs
