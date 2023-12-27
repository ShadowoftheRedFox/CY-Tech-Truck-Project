#!/bin/bash
#? return code of the last command: $?
#? script name: $0
#? argument number: $#
#? argument list: $*
#? argument 0 2 and 4: $0 $2 $4
#? get all argument starting from the n one: ${@:n}
#? always ignore the first line of the csv file
#? CSV type: Route ID;Step ID;Town A;Town B;Distance;Driver name
# TODO count only the shell execution time
# TODO re read the pdf to check if everything is being done well and has the right place

# function that return a message before exiting the script, showing the time elapsed
ExitDisplay() {
    echo ""
    startTime=$1
    otherArgs=${@:2}
    if [ -n "${otherArgs}" ]; then
        echo -e ${otherArgs}
    fi
    # print the execution time from the first arg
    if [ ${startTime} == 0 ]; then
        echo "Execution time: 0s"
    else
        # endTimeCount=$(date +%s.%N)
        endTimeCount=$(date +%s)
        # calculate the execution
        # runtime=$(echo "${endTimeCount} - ${startTimeCount}" | bc)
        runtime=$(echo $((${endTimeCount} - ${startTimeCount})))
        # display it
        echo "Execution time:" ${runtime}"s"
    fi

    # use to wait before exiting the script
    read -p "Press any key to exit"
    # exit the script
    exit
}

# set tab title to what we want
echo -en "\033]0;CYTruck\a"

# cd to the absolute path of the parent folder containing this script
# to make sure all relativ script work as intended
cd "$(dirname "$0")"

# create the images folder if it isn't done already
if [ ! -d 'images' ]; then
    # create the dir
    mkdir -p 'images' #? check if errors?
    echo 'Created images directory.'
else
    echo 'The images directory exists already.'
fi
# clean if the temp folder exists, or create it if it isn't done already
if [ ! -d './temp' ]; then
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
# create the data folder if it isn't done already
if [ -d "./data" ]; then
    echo "Directory \"data\" exists."
else
    mkdir -p 'data'
    echo 'Created data directory.'
fi
# create the demo folder if it isn't done already
if [ -d "./demo/dir/" ]; then
    echo "Directory \"demo\" exists."
else
    mkdir -p 'demo'
    echo 'Created demo directory'
fi
# start to count the time
# startTimeCount=$(date +%s.%N)
startTimeCount=$(date +%s)

# check the argument number, if non exit
if [ $# == 0 ]; then
    ExitDisplay ${startTimeCount} "No argument found. Use \"-h\" to get help."
fi

# to check every argument who don't need a csv file
for arg in $*; do
    case $arg in
    "-h")
        # TODO update with bonus commands (clean)
        ExitDisplay ${startTimeCount} "Help:\n
- path :\t The path to a CSV file with the data. It must be the first argument.\n
- \"-h\" :\t Will show the help message, which is the list of arguments and what they do. It will not run any other argument.\n
- \"-d1\":\t Show the top 10 drivers with the most journeys.\n
- \"-d2\":\t Show the top 10 drivers with the longest distance travelled.\n
- \"-l\" :\t Show the top 10 longest routes.\n
- \"-t\" :\t Show the top 10 most crossed cities with how many different drivers cross it.\n
- \"-s\" :\t Min, max and average distances for every route."
        ;;
    "-c" | "-clean")
        echo "Cleaning compiled files..."
        make -f ./progc/Makefile clean
        ExitDisplay ${startTimeCount} "Done."
        ;;
    esac
done

# compile the program if not done
if [ ! -d "./progc/bin" ] || [ ! -f "./progc/bin/CYTruck" ]; then
    # check if make and gcc are installed
    if ! command -v make >/dev/null 2>&1; then
        ExitDisplay 0 "make could not be found"
    fi
    if ! command -v gcc >/dev/null 2>&1; then
        ExitDisplay 0 "gcc could not be found"
    fi
    make -f "./progc/Makefile" builddir
    make -f "./progc/Makefile" objdir
    compilation=$(make -f "./progc/Makefile")
    # check file compilation result
    if [ $? != 0 ]; then
        ExitDisplay 0 "Error during compilation:\n${compilation}"
    fi
fi

# path and name of the supposed csv file
filePath=$1

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
#TODO check if first line is the correct type of the wanted csv?

# check if gnuplot is installed
if ! command -v gnuplot >/dev/null 2>&1; then
    ExitDisplay 0 "gnuplot could not be found"
fi

# to check each parameters option
for arg in $*; do
    case $arg in
    "-test")
        echo "Testing: 30 routes with all step"

        echo "Start awk"
        awk -F';' '$1 <=30 {printf "%d;%d;%s;%s\n", $1, $2, $3, $4 }' ${filePath} >"./temp/test_result.txt"
        echo "Start last sort"
        sort -t';' -k1n -k2n "./temp/test_result.txt" >"./temp/sorted_test_sorted.txt"

        ExitDisplay ${startTimeCount} "End of the test."
        ;;
    "-d1")
        echo "d1 arg found"
        # need to sort by route id or driver name
        # count the number of different routes
        # output the top 10 with number of routes and names
        # make the graph

        # separate in fields with ;, create a array of sum[route ID] += distance, then print each route ID with it's sum (with 3 decimals)
        echo "Summing drivers routes..."
        # if step ID is 1, add the route to the driver names, then at the end, print the name and it's route amount
        awk -F';' '$2 == 1 {sum[$6]+=1} END{for(i in sum) printf "%s;%d\n", i, sum[i]}' ${filePath} >"./temp/d1_argument_sum.csv"
        # sort the value from the second field (length), and only numerical, and reversed to have the longest on top
        echo "Sorting drivers routes..."
        sort -t';' -k2n "./temp/d1_argument_sum.csv" >"./temp/sorted_d1_argument_sum.csv"
        echo "Getting the top drivers..."
        # get the top 10 longest route
        tail -n 10 "./temp/sorted_d1_argument_sum.csv" >"./temp/d1_argument_top10.csv"
        # cat "./temp/d1_argument_top10.csv" # to show the top 10

        echo "Creating graph..."
        gnuplot ./progc/gnuplot/d1_script.gnu
        ;;
    "-d2")
        echo "d2 arg found"
        # need to sort by driver name
        # then add each distance
        # output the top 10 ones with distances to make the graph
        # make the graph

        # separate in fields with ;, create a array of sum[route ID] += distance, then print each route ID with it's sum (with 3 decimals)
        echo "Summing drivers routes..."
        awk -F';' 'NR>1{sum[$6]+=$5} END{for(i in sum) printf "%s;%.3f\n", i, sum[i]}' ${filePath} >"./temp/d2_argument_sum.csv"
        # sort the value from the second field (length), and only numerical, and reversed to have the longest on top
        echo "Sorting drivers routes..."
        sort -t';' -k2n "./temp/d2_argument_sum.csv" >"./temp/sorted_d2_argument_sum.csv"
        echo "Sorting drivers..."
        # get the top 10 longest route
        tail -n 10 "./temp/sorted_d2_argument_sum.csv" >"./temp/d2_argument_top10.csv"
        # cat "./temp/d2_argument_top10.csv" # to show the top 10

        echo "Creating graph..."
        gnuplot ./progc/gnuplot/d2_script.gnu
        ;;
    "-l")
        echo "l arg found"
        # need to sort by route id
        # sum the distance of each step
        # output the top 10 with distances and ID
        # make the graph

        # separate in fields with ;, create a array of sum[route ID] += distance, then print each route ID with it's sum (with 3 decimals)
        echo "Summing route's length..."
        awk -F';' 'NR>1{sum[$1]+=$5} END{for(i in sum) printf "%.3f;%s\n", sum[i], i}' ${filePath} >"./temp/l_argument_sum.csv"
        # sort the value from the second field (length), and only numerical, and reversed to have the longest on top
        echo "Sorting route's length..."
        sort -t';' -k1nr "./temp/l_argument_sum.csv" >"./temp/sorted_l_argument_sum.csv"
        echo "Sorting route's ID..."
        # get the top 10 longest route
        head -10 "./temp/sorted_l_argument_sum.csv" >"./temp/l_argument_top10.csv"
        # and sort them by id
        sort -t';' -k2n "./temp/l_argument_top10.csv" >"./temp/l_argument_top10_finish.csv"
        # to show the top 10
        # cat "./temp/l_argument_top10_finish.csv"

        echo "Creating graph..."
        gnuplot ./progc/gnuplot/l_script.gnu
        ;;
    "-t")
        echo "t arg found"
        # USE C TO SORT DATA
        # keep the city name,route id and drivers cut other data
        # put it in a file and use tl:he c file on it
        # count the number of occurances (how?)
        # output the top 10 with names, times crossed and number of different drivers that went by
        # make the graph

        echo "Sorting towns..."
        ./progc/bin/CYTruck "t" ${filePath} "./temp/t_result.txt"

        # check return result
        CYTruckReturnResult=$?
        # display error if the reutnr code is not 0
        if [ ${CYTruckReturnResult} != 0 ]; then
            ExitDisplay ${startTimeCount} "Something went wrong with the code.\nError code:" ${CYTruckReturnResult}
        fi

        # check the existance of the ouput file
        if [ ! -f "./temp/t_argument_result.txt" ]; then
            ExitDisplay ${startTimeCount} "Can not find the ouput file."
        fi

        # cat "./temp/t_argument_result.txt"

        echo "Creating graph..."
        gnuplot ./progc/gnuplot/t_script.gnu
        ;;
    "-s")
        echo "s arg found"
        # USE C TO SORT DATA
        # get all routes sorted and with their distances (cut other data)
        # put it in a file and use the c file on it
        # get the min, the max and average
        # make the graph

        #FIXME can be fast and RAM efficient without split?
        # lines_in_chunk=1000000
        # split -l ${lines_in_chunk} "./temp/s_argument_splitted.csv" ./temp/s_argument_sum_splitted_

        # use a C file with the distance as ABR number with the route ID, then get mix, max and average, output in a file
        # ./progc/bin/CYTruck "s" ./temp/s_argument_sum_splitted_* "./temp/s_argument_result.txt"
        ./progc/bin/CYTruck "s" $filePath "./temp/s_argument_result.txt"

        # check return result
        CYTruckReturnResult=$?
        # display error if the reutnr code is not 0
        if [ ${CYTruckReturnResult} != 0 ]; then
            ExitDisplay ${startTimeCount} "Something went wrong with the code.\nError code:" ${CYTruckReturnResult}
        fi

        # check the existance of the ouput file
        if [ ! -f "./temp/s_argument_result.txt" ]; then
            ExitDisplay ${startTimeCount} "Can not find the ouput file."
        fi

        # cat "./temp/s_argument_result.txt"

        echo "Creating graph..."
        gnuplot ./progc/gnuplot/s_script.gnu
        ;;
    *)
        if [ $arg != $filePath ]; then
            echo $arg ": found but not recognized, skipping..."
        fi
        ;;
    esac
done

ExitDisplay $startTimeCount
