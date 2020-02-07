Gpp = g++ -std=c++11 -O3 -Wno-unused-result	
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
OBJSDIR = obj
CC = g++

OBJS = $(patsubst %, $(OBJSDIR)/%, $(SRCS:.cpp=.o) )
DEPS = $(patsubst %, $(OBJSDIR)/%, $(SRCS:.cpp=.d) )


all: MTSP.exe

MTSP.exe: $(OBJS)
		$(Gpp) $^ -o $@

$(OBJSDIR)/%.o: %.cpp
		$(Gpp) -MMD -MP -c $< -o $@

.PHONY: clean

clean:
		$(RM) $(OBJS) $(DEPS)

-include $(DEPS)
