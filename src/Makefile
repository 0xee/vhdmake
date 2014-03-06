#  Copyright (C) 2014 Lukas Schuller
# 
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
# 
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
# 
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <http://www.gnu.org/licenses/>.

include ../cfg.mk

TARGET=vhdmake

CXX=g++
CXXFLAGS=-g3 -std=c++11 -O0 
LDFLAGS=-lboost_system -lboost_filesystem

NODEPS=clean

PARSERS = vhdl cfg

GENHEADER = vhdl/Parser.h vhdl/Scanner.h cfg/Parser.h cfg/Scanner.h
GENSRC    = $(patsubst %.h, %.cpp, $(GENHEADER))

SRC = $(wildcard *.cpp) $(GENSRC)
HEADERS = $(wildcard *.h) $(GENHEADER)

OBJS = $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(OBJS:.o=.d)

TESTSRC=../test

test: $(TARGET)
	./$(TARGET) -s ../test/test.vhd

install: $(TARGET)
	install $(TARGET) $(PREFIX)


$(GENHEADER) $(GENSRC): $(wildcard $(patsubst %, %/*.atg, $(PARSERS)))
	$(foreach p, $(PARSERS), $(MAKE) -C $(p);)


$(TARGET): $(OBJS) 
	g++ -o $(TARGET) $(LDFLAGS) $(OBJS)

#Don't create dependencies when we're cleaning
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

#This is the rule for creating the dependency files
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cpp,$(OBJDIR)/%.o,$<)' $< -MF $@

%.o : %.cpp
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

check-syntax:
	$(CXX) -std=c++11 -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)

.PHONY: check-syntax

clean:
	rm -rf  core.* $(TARGET) *.log $(OBJS) $(LOG) $(DEPS) parser.target
	$(foreach p, $(PARSERS), $(MAKE) -C $(p) clean;)

.PHONY: clean 

