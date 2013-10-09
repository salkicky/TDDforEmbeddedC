#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- for environment ----------
export CC="gcc"

#---- Outputs ----#
COMPONENT_NAME = BookCode_CppUTest

#--- Inputs ----#
CPPUTEST_HOME = CppUTest
CPP_PLATFORM = gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src \
	$(PROJECT_HOME_DIR)/src/CpputestSample \
	$(PROJECT_HOME_DIR)/src/HomeAutomation \

TEST_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/CpputestSample \
	$(PROJECT_HOME_DIR)/tests/HomeAutomation \
	
INCLUDE_DIRS =\
  $(PROJECT_HOME_DIR)/src \
  $(PROJECT_HOME_DIR)/src/CpputestSample \
  $(PROJECT_HOME_DIR)/include/HomeAutomation \
  $(CPPUTEST_HOME)/include\

MOCKS_SRC_DIRS = \
	mocks\
	
CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror 
#CPPUTEST_CFLAGS = -std=c89 
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
#LD_LIBRARIES = -lpthread
	
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

