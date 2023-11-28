# defines compiler
CC = gcc
# defines build directory 
BUILD_DIR = bin
# defines object directory
OBJ_DIR = obj
# defines the source directory
SRC_DIR = src
# defines the save directory
SAVE_DIR = save
# defines executable name 
EXEC_NAME = CYTruck

# get all c files
SRC=$(wildcard $(SRC_DIR)/*.c)
# get all o files
OBJ=$(SRC:.c=.o)
#strip the source folder from the names
OBJ_STRIP=$(OBJ:$(SRC_DIR)/%=%)
# list of o files in the object directory
OBJ_IN_DIR=$(addprefix $(OBJ_DIR)/, $(OBJ_STRIP))

# build everything
all: objdir savedir buildir exec

# build the executable
exec: $(OBJ_IN_DIR)
	$(CC) $^ -o $(BUILD_DIR)/$(EXEC_NAME)

# create bin directory
buildir: 
	mkdir -p $(BUILD_DIR)

# create obj directory
objdir: 
	mkdir -p $(OBJ_DIR)

# create save directory
savedir: 
	mkdir -p $(SAVE_DIR)

# delete bin then obj directory, with all files in it
clean: 
	if [ -d "$(BUILD_DIR)" ]; then\
		rm -r $(BUILD_DIR); \
	fi
	if [ -d "$(OBJ_DIR)" ]; then\
		rm -r $(OBJ_DIR); \
	fi
	if [ -d "$(SAVE_DIR)" ]; then\
		rm -r $(SAVE_DIR); \
	fi
# build o files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(OBJ_DIR) objdir # compile .c to .o object
	$(CC) -c $< -o $@
