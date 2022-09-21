# Definition of intermediate (BUILD_DIR) and destination (DEST_DIR) paths
BUILD_DIR ?= ./build
DEST_DIR ?= ./bin

# Definition of target names for test and program
TARGET_TEST ?= datalib_test
TARGET_EXEC ?= datalib

# Definition of source paths for test and program
SRC_DIRS_TEST ?= ./prog/src ./test/src
SRC_DIRS_EXEC ?= ./prog/src

# Definition of files to exclude from test because of different main
PRG_EXEC := ./prog/src/main.c

# Get list of all source files for test
SRCS_RAW := $(shell find $(SRC_DIRS_TEST) -name *.cpp -or -name *.c -or -name *.s)
# Remove main of program
SRCS_TEST := $(filter-out $(PRG_EXEC), $(SRCS_RAW))
# Get list of all source files for program
SRCS_EXEC := $(shell find $(SRC_DIRS_EXEC) -name *.cpp -or -name *.c -or -name *.s)
# Build generic list of object files
OBJS_TEST := $(SRCS_TEST:%=$(BUILD_DIR)/%.o)
OBJS_EXEC := $(SRCS_EXEC:%=$(BUILD_DIR)/%.o)

# Build generic list of include files
INC_DIRS_TEST := $(shell find $(SRC_DIRS_TEST) -type d)
INC_DIRS_EXEC := $(shell find $(SRC_DIRS_EXEC) -type d)
# Append additional include paths
INC_FLAGS_TEST := $(addprefix -I,$(INC_DIRS_TEST)) -I./prog/include -I./test/include -I./vendor/acutest/include
INC_FLAGS_EXEC := $(addprefix -I,$(INC_DIRS_EXEC)) -I./prog/include -I./test/include

# Set compile flags
# https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
CPPFLAGS ?= $(INC_FLAGS_TEST) -MMD -MP -g3 -gdwarf-2 -Debug -Wall -Werror -Wextra -Wshadow -Wformat=2 -Wformat-truncation -Wundef -fno-common -fstack-usage -Os -ffunction-sections -fdata-sections
# There seems to be a bug in acutest.h which prevents the usage of this flag
# -Wdouble-promotion
# Cannot separate between program and test
# -Wstack-usage=

# First target is default target
# https://stackoverflow.com/questions/2057689/how-does-make-app-know-default-target-to-build-if-no-target-is-specified
test: $(BUILD_DIR)/$(TARGET_TEST)

# Target for program
# Later it will be a lib, but for testing purposes it's an executable
exec: $(BUILD_DIR)/$(TARGET_EXEC)

# Target for make all
all: exec test

# Target for cleanup
.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(DEST_DIR)
	$(RM) $(shell find -name *.log)

# For debugging purposes, print makefile variables
# https://www.cmcrossroads.com/article/dumping-every-makefile-variable
.PHONY: printvars
printvars:
	@$(foreach V,$(sort $(.VARIABLES)), $(if $(filter-out environment% default automatic, $(origin $V)),$(warning $V=$($V) ($(value $V)))))

# Internal target to ensure paths exists
MKDIR_P ?= mkdir -p

# Build exec
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_EXEC)
	$(CC) $(OBJS_EXEC) -o $@ $(LDFLAGS)
	mkdir -p $(DEST_DIR)
	cp $(BUILD_DIR)/$(TARGET_EXEC) $(DEST_DIR)/$(TARGET_EXEC)

# Build tests
$(BUILD_DIR)/$(TARGET_TEST): $(OBJS_TEST)
	$(CC) $(OBJS_TEST) -o $@ $(LDFLAGS)
	mkdir -p $(DEST_DIR)
	cp $(BUILD_DIR)/$(TARGET_TEST) $(DEST_DIR)/$(TARGET_TEST)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
