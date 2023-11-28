# CY Tech Truck Project

The CY Tech project of 2023/2024.

## Summary

- [The steps to compile the executable](#compilation)
- [Explain the goal of each folders](#what-is-what)
- [Explain how to use the program](#how-to-use)
- [List of things that are to be added soon](#todo)
- [The limits, unimplemented or known bugs](#functionnality-limits)

## Compilation

Just launch [CYTreuck.sh](./CYTruck.sh), it will compile (if needed) all the file, if given the right parameters.

You can just write in a console `make -f ./progc/Makefile` to run the makefile.

## What is what?

## How to use

You can see some examples in the [demo](./demo/) folder. It has its own README to explain the examples further.

The whole program start with [CYTruck.sh](./CYTruck.sh) and its arguments:
- **path**: The path to a CSV file with the data. It must be the first argument.
- "**-h**": Will show the help message, which is the list of arguments and what they do. It will not run any other argument.
- "**-d1**": Show the top 10 drivers with the most journeys.
- "**-d2**": Show the top 10 drivers with the longest distance travelled.
- "**-l**": Show the top 10 longest routes.
- "**-t**": Show the top 10 most crossed cities.
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

## Functionnality limits

### Not implemented

Everything

### Implemented but not fully

Everything

### Bugs

None yet