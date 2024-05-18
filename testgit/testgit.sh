#!/bin/bash

Location=LearnGit

function setup() {
	clear

	mkdir -p $Location
	cd $Location

	rm -rf BitBucketComputer
	rm -rf LocalComputer

	mkdir BitBucketComputer
	mkdir LocalComputer

	cd BitBucketComputer
	git init --bare sample-repo.git
	cd ..

	cd LocalComputer

	mkdir sample-repo
	cd sample-repo
}

function menu() {
	clear

	echo "Menu"
	echo "1: Init, Remote add repo, Pull"
	echo "2: Init, Remote add repo, Push"
	echo "3: Init, Add & commit file, Remote add repo, Pull"
	echo "4: Init, Add & commit file, Remote add repo, Push"
	echo -n "Enter your choice: "
	read choice
	echo

	set -x
}

function option1() {
	git init

	git remote add alias-for-remote-repo $Location/BitBucketComputer/sample-repo.git

	git pull alias-for-remote-repo master
}

function option2() {
	git init

	git remote add alias-for-remote-repo $Location/BitBucketComputer/sample-repo.git

	git push alias-for-remote-repo master
}

function option3() {
	git init

	touch a.txt
	git add .
	git commit -m "added a.txt"

	git remote add alias-for-remote-repo $Location/BitBucketComputer/sample-repo.git

	git pull alias-for-remote-repo master

	git pull alias-for-remote-repo master --allow-unrelated-histories
}

function option4() {
	git init

	touch a.txt
	git add .
	git commit -m "added a.txt"

	git remote add alias-for-remote-repo $Location/BitBucketComputer/sample-repo.git

	git push alias-for-remote-repo master

	git push -u alias-for-remote-repo master
}

setup

menu

case $choice in
	1) option1 
	   ;;

	2) option2 
	   ;;

	3) option3
	   ;;

	4) option4
	   ;;

	*) echo "Ha ha!"
	   ;;
esac

exit 0
