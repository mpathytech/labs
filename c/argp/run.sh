#! /bin/bash

# Script to show and test the usage of the argp_simple program

echo "Failure examples"
echo "----------------"

echo "./argp_simple -g m"
./argp_simple -g m
echo

echo "./argp_simple -a 20"
./argp_simple -a 20
echo

echo "./argp_simple -g m -a 20"
./argp_simple -g m -a 20 
echo

echo './argp_simple -g x -a 0 "some name"'
./argp_simple -g x -a 0    "some name"
echo

echo './argp_simple -g f -a -1 "some name"'
./argp_simple -g f -a -1   "some name"
echo

echo './argp_simple -g f -a 150  "some name"'
./argp_simple -g f -a 150  "some name"
echo

echo './argp_simple -g m -a 20 "name 1234"'
./argp_simple -g m -a 20   "name 1234"
echo

echo "Success examples"
echo "----------------"

echo './argp_simple -g f -a 25   "some"'
./argp_simple -g f -a 25 "some"
echo

echo './argp_simple -g m -a 0    "some name"'
./argp_simple -g m -a 0 "some name"
echo
