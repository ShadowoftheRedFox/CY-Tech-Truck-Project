#!/bin/bash
#? return code of the last command: $?
#? script name: $0
#? argument number: $#
#? argument list: $*
#? argument 0 2 and 4: $0 $2 $4
#? get all argument starting from the n one: ${@:n}
# always ignore the first line if the csv file
# CSV: Route ID;Step ID;Town A;Town B;Distance;Driver name

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
elif [ -n "$(ls "./temp/")" ]; then
    echo 'The temp directory exists already, cleaning...'
    oldDir=$(pwd)
    cd "temp"
    rm -r * #? check if errors?
    cd "${oldDir}"
    echo 'Done.'
else
    echo 'The temp directory exists.'
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
- path :\t The path to a CSV file with the data. It must be the first argument.\n
- \"-h\" :\t Will show the help message, which is the list of arguments and what they do. It will not run any other argument.\n
- \"-d1\":\t Show the top 10 drivers with the most journeys.\n
- \"-d2\":\t Show the top 10 drivers with the longest distance travelled.\n
- \"-l\" :\t Show the top 10 longest routes.\n
- \"-t\" :\t Show the top 10 most crossed cities with how many different drivers cross it.\n
- \"-s\" :\t Min, max and average distances for every route."
    fi
done

# check if there are arguments after the file opath
if [ $# -lt 2 ]; then
    ExitDisplay ${startTimeCount} "You need at least an argument with the file path!"
fi

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
    "-d1")
        echo "d1 arg found"
        # need to sort by route id or driver name
        # count the number of different routes
        # output the top 10 with number of routes and names
        # make teh graph
        ;;
    "-d2")
        echo "d2 arg found"
        # need to sort by driver name
        # then add each distance
        # output the top 10 ones with distances to make the graph
        # make the graph
        ;;
    "-l")
        echo "l arg found"
        # need to sort by route id
        # sum the distance of each step
        # output the top 10 with distances and ID
        # make the graph

        # remove the first line (the column header)
        tail -n +2 "${filePath}" >"./temp/l_argument_sum_pre.csv"
        ################################# 10s constant #############################################
        # # separate in fields with ;, create a array of sum[route ID] += distance, then print each route ID with it's sum (with 3 decimals)
        # echo "Summing route's length..."
        # awk -F';' '{sum[$1]+=$5} END{for(i in sum) printf "%s;%.3f\n", i, sum[i]}' "./temp/l_argument_sum_pre.csv" >"./temp/l_argument_sum.csv"
        # # sort the value from the second field (length), and only numerical, ad reversed to have the longest on top
        # echo "Sorting route's length..."
        # sort -t';' -k 2 -n -r "./temp/l_argument_sum.csv" >"./temp/sorted_l_argument_sum.csv"
        # echo "Sorting route's ID..."
        # # get the top 10 longest route
        # head -n 10 "./temp/sorted_l_argument_sum.csv" >"./temp/l_argument_top10.csv"
        # # and sort them by id
        # sort -t';' -k 1 -n "./temp/l_argument_top10.csv" >"./temp/l_argument_top10_finish.csv" # TODO move to demo dir later
        # # cat "./temp/l_argument_top10_finish.csv" # to show the top 10
        ###########################################################################################

        ############################### between 8s and 14s ########################################
        split -l 800000 "./temp/l_argument_sum_pre.csv" ./temp/l_argument_chunk_
        # Process each chunk in parallel
        for chunk_file in ./temp/l_argument_chunk_*; do
            # Use awk to calculate the sum of values for each ID in the chunk
            awk -F';' '{sum[$1]+=$5} END{for(i in sum) printf "%s;%.3f\n", i, sum[i]}' "${chunk_file}" >"${chunk_file}.csv" &
        done
        # Wait for all background processes to finish
        wait

        # Concatenate the results from all chunks
        cat ./temp/l_argument_chunk_*.csv >./temp/l_argument_sum.csv

        # awk the last values
        # awk -F';' '{sum[$1]+=$2} END{for(i in sum) printf "%s;%.3f\n", i, sum[i]}' "./temp/l_argument_sum.csv" >"./temp/l_argument_sum_all.csv"

        echo "Sorting route's length..."
        sort -t';' -k 2 -n -r "./temp/l_argument_sum.csv" >"./temp/sorted_l_argument_sum.csv"
        echo "Sorting route's ID..."
        # get the top 10 longest route
        head -n 10 "./temp/sorted_l_argument_sum.csv" >"./temp/l_argument_top10.csv"
        # and sort them by id
        sort -t';' -k 1 -n "./temp/l_argument_top10.csv" >"./temp/l_argument_top10_finish.csv" # TODO move to demo dir later
        # cat "./temp/l_argument_top10_finish.csv" # to show the top 10
        ##########################################################################################

        echo "Creating graph..."
        #TODO graph
        ;;
    "-t")
        echo "t arg found"
        # USE C TO SORT DATA
        # keep the city name,route id and drivers cut other data
        # put it in a file and use tl:he c file on it
        # count the number of occurances (how?)
        # output the top 10 with names, times crossed and number of different drivers that went by
        # make the graph

        cut ${filePath} -d';' -f1,3,4,6 >"./temp/t_argument.csv"
        ;;
    "-s")
        echo "s arg found"
        # USE C TO SORT DATA
        # get all routes sorted and with their distances (cut other data)
        # put it in a file and use the c file on it
        # get the min, the max and average
        # make the graph

        cut ${filePath} -d';' -f1,5 >"./temp/s_argument.csv"

        ;;
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
