# CY Tech Truck Project

The CY Tech project of 2023/2024.
We use in this project [GNUPlot](http://www.gnuplot.info/) to plot the images, [GNU Make)](https://www.gnu.org/software/make/) to help compile the code, and [GNU GCC](https://gcc.gnu.org/install/download.html) to compile the code. Make sure they are installed before using the shell script. *We will check they are installed anyway.* 

## Table of content

- [The steps to compile the executable](#compilation)
- [Explain the goal of each folders](#what-is-what)
- [Explain how to use the program](#how-to-use)
- [List of things that are to be added soon](#todo)
- [The limits, unimplemented or known bugs](#functionnality-limits)
- [Show what has been done when](#planning)
- [Add large CSV file to the repository](#add-large-csv-file-to-the-repository)

## Compilation

Just launch [CYTreuck.sh](./CYTruck.sh), it will compile (if needed) all the file, if given the right parameters.

You can just write in a console `make -f ./progc/Makefile` to run the makefile.

## What is what?

- The [pdf file](./Projet_CY_Truck_preIng2_2023_2024_v1.0.0.pdf) is the subject for this whole project.
- [CYTruck.sh](./CYTruck.sh) is the main entry of the project.
- The [temp](./temp/) folder is where temporary file will be made during the execution.
- The [progc](./progc/) file is the source folder or the code. It contains the C, Headers, makefile ... files. The compiled files will be in there too.
- The [images](./images/) folder contains the result of the command.
- The [demo](./demo/) folder is where a C executable may put file for the shell file to use. You can also open them to read the raw data instead of the images. It also contains examples with their own README to reproduce them.
- The [data](./data/) folder is where the CSV files must be pasted before using the program.

## How to use

You can see some examples in the [demo](./demo/) folder. It has its own README to explain the examples further.

**You must paste your CSV file in the [data](./data/) folder before using the program! It may use it and will search it in this folder.**

The whole program start with [CYTruck.sh](./CYTruck.sh) and its arguments. The first one must be the path to the CSV file. You also need at least one argument, but you can use more than one at a time.
- **path**: The path to a CSV file with the data. It must be the first argument.
- "**-h**": Will show the help message, which is the list of arguments and what they do. It will not run any other argument.
- "**-d1**": Show the top 10 drivers with the most journeys.
- "**-d2**": Show the top 10 drivers with the longest distance travelled.
- "**-l**": Show the top 10 longest routes.
- "**-t**": Show the top 10 most crossed cities with how many different drivers cross it.
- "**-s**": Min, max and average distances for every route.

**Exemples:**
```sh
./CYTruck.sh -h # shows the help message
./CYTruck.sh ./data/data.csv -d1 -h # also shows the help message
./CYTruck.sh ./data/data.csv -s # shows the min, max and average distances for every routes
./CYTruck.sh ./data/data.csv -s -t # shows the min, max and average distances for every routes AND the top 10 most corssed cities
./CYTruck.sh -s -t # shows an error, the first parameter isn't a file path to a CSV file
```

## Todo
- [ ] Finish Readme
- [ ] PDF document for the task shared and worked on
- [ ] Planning realisation
- [ ] The whole project... 
- [ ] Add another shell file to call the clean method of the Makefile file (check [Bonus](#bonus))
- [x] Check if "-h" is in the arguments and display a help message
- [x] Check if the first argument is a csv file that exist
- [x] Create images directory if not present
- [x] Create temp directory if not present, or delete it's content
- [x] Display execution time
- [x] Display the execution time even in ExitDisplay
- [x] -l has its data ready, between 8s and 14s (or 10s)
- [x] do the graph for -l
- [x] finish C part for -s
- [ ] finish graph part for -s
- [ ] finish C part for -t
- [ ] finish graph part for -t
- [x] finish graph part for -d1
- [x] finish graph part for -d2
- [x] rename every absolute path to executable in command 
- [ ] change every temp file that should be in demo to demo 
- [ ] make a good looking folder in demo with each necessary file in it 

### Bonus

- [ ] Multiple files input (-m)
- [ ] Read all csv file from a dir and use them as input (-D)
- [ ] specify type of ouput? (png, pdf, csv...) (-o)
- [ ] option to compress result in a archive file (possibility to choose tar, gz, zip...) (-a)
- [x] argument to clean temp at the end when executed (-c)
- [ ] Display the timing but animated (on the last line or on one line, current display may only be for testing)

## Functionnality limits

### Not implemented

Everything

### Implemented but not fully

Everything

### Bugs

None yet

## Planning
- 28/11/2023: Created the repository and basic files (README, Makefile, the gnuplot executable...) (Hugo).
- 03/12/2023: Started the shell file and makefile, added data.csv to the repo (Git LFS) (Hugo).
- 04/12/2023: Started the data gathering for -l, -s and -t. -l is working between 8 and 14s (Hugo, Bilel, Prince). Started the C file (Bilel).
- 07/12/2023: Finished -l (Hugo), corrected data for -s (Hugo). Continued the C file for -s (Bilel, Hugo). Made gnuplot script for -s (Hugo).
- 15/12/2023: Finished graph for -d1, -d2, -l and -s (though not good looking) (Hugo). Optimized shell (Hugo) and C script (Bilel). 
- 18/12/2023: Corrected -s since the pdf file has been chaned (Hugo).

## Add large CSV file to the repository

You need to install [Git LFS](https://docs.github.com/fr/repositories/working-with-files/managing-large-files/installing-git-large-file-storage) (Github Large File System) and follow [this step in their documentation](https://docs.github.com/fr/repositories/working-with-files/managing-large-files/configuring-git-large-file-storage).

To download the [data.csv file](./data/data.csv), you need to go on the GitHub website and download the raw file, or you can use this [link](https://github.com/ShadowoftheRedFox/CY-Tech-Truck-Project/raw/main/data/data.csv?download=) directly.