#!/bin/bash

# Prompt for WEEK if not provided
if [ -z "$1" ]; then
    read -p "Enter WEEK number: " WEEK
else
    WEEK=$1
fi

# Prompt for EXERCISE if not provided
if [ -z "$2" ]; then
    read -p "Enter EXERCISE number: " EXERCISE
else
    EXERCISE=$2
fi

g++ -Wc++11-extensions Week_$WEEK/exercise_$EXERCISE.cpp -o a
./a