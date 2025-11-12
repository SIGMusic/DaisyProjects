# Project Name
TARGET = PitchShifter

# Sources
CPP_SOURCES = PitchShifter.cpp

# Library Locations
LIBDAISY_DIR = ../../DaisyExamples/libDaisy/
DAISYSP_DIR = ../../DaisyExamples/DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

# Required for making serial printing work with floats
LDFLAGS += -u _printf_float

