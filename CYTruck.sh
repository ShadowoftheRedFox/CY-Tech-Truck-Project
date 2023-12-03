#!/bin/bash
#? return code of the last command: $?
#? script name: $0
#? argument number: $#
#? argument list: $*
#? argument 0 2 and 4: $0 $2 $4
#? get all argument starting from the n one: ${@:n}

# function that return a message before exiting the script
ExitDisplay() {
    startTime=$1
    otherArgs=${@:2}
    if [ -n "${otherArgs}" ]; then
        echo -e ${otherArgs}
    fi
    # print the execution time from the first arg
    # endTimeCount=$(date +%s.%N)
    endTimeCount=$(date +%s)

    # calculate the execution time
    # runtime=$(echo "${endTimeCount} - ${startTimeCount}" | bc)
    runtime=$(echo $((endTimeCount - startTimeCount)))
    # display it
    echo "Execution time:" ${runtime}"s"

    # use to wait before exiting the script
    read -p "Press any key to exit"
    # exit the script
    exit
}

# set tab title to what we want
echo -en "\033]0;CYTruck\a"

# todo compile the program if not done
# todo check file compilation result

# check if the images dir exist
if [ ! -d 'images' ]; then
    # create the dir
    mkdir -p 'images' #? check if errors?
    echo 'Created images directory.'
else
    echo 'The images directory exists already.'
fi

# check if the temp dir exist
if [ ! -d 'temp' ]; then
    # create the dir
    mkdir -p 'temp' #? check if errors?
    echo 'Created temp directory.'
else
    if [ -n "$(ls "./temp/")" ]; then
        echo 'The temp directory exists already, cleaning...'
        oldDir=$(pwd)
        cd "temp"
        rm -r * #? check if errors?
        cd "${oldDir}"
        echo 'Done.'
    else
        echo 'The temp directory exists.'
    fi
fi

# todo check: data dir, temp dir, demo dir and images dir

# start to count the time
# startTimeCount=$(date +%s.%N)
startTimeCount=$(date +%s)

# check the argument number, if non exit
if [ $# == 0 ]; then
    ExitDisplay ${startTimeCount} "No argument found. Use \"-h\" to get help."
fi
# ask an input from the user and put it in name
# read -p "Enter your name : " name

# use the newly created name variable
# echo "Hi, $name. Let us be friends!"

# path and name of the supposed csv file
filePath=$1

# to check if -h is in the parameters
for arg in $*; do
    if [ $arg == '-h' ]; then
        ExitDisplay ${startTimeCount} "Help:\n
- path:\t The path to a CSV file with the data. It must be the first argument.\n
- \"-h\":\t Will show the help message, which is the list of arguments and what they do. It will not run any other argument.\n
- \"-d1\":\t Show the top 10 drivers with the most journeys.\n
- \"-d2\":\t Show the top 10 drivers with the longest distance travelled.\n
- \"-l\":\t Show the top 10 longest routes.\n
- \"-t\":\t Show the top 10 most crossed cities.\n
- \"-s\":\t Min, max and average distances for every route."
    fi
done

# check if the first argument is a file ending with .csv
if [ ${filePath##*.} != "csv" ]; then
    ExitDisplay ${startTimeCount} "The first argument is not a CSV file."
fi
if [ ! -f $filePath ]; then
    ExitDisplay ${startTimeCount} "Can not find the CSV file."
fi

# to check each parameters option
for arg in $*; do
    case $arg in
    "-d1") echo "d1 arg found" ;;
    "-d2") echo "d2 arg found" ;;
    "-l") echo "l arg found" ;;
    "-t") echo "t arg found" ;;
    "-s") echo "s arg found" ;;
    *) echo $arg ": found" ;;
    esac
done

# end of the time count
# endTimeCount=$(date +%s.%N)
endTimeCount=$(date +%s)

# calculate the execution time
# runtime=$(echo "${endTimeCount} - ${startTimeCount}" | bc)
runtime=$(echo $((endTimeCount - startTimeCount)))
# display it
echo "Execution time:" ${runtime}"s"

# use to wait before exiting the script
read -p "Press any key to exit"
