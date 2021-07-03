CC = g++
PYLIBPATH = $(shell python-config --exec-prefix)/lib
LIB = -L$(PYLIBPATH) $(shell python-config --libs) -lboost_python
OPTS = $(shell python-config --include) -O2

CFLAGS = -c -O2 -pthread -std=c++0x
LFLAGS = -O2 -pthread -std=c++0x

TARGET = build/othello

SRCS  := $(wildcard src/*.cpp)
OBJS  := $(SRCS:.cpp=.o)

RM = /bin/rm -rf

all: $(TARGET)

$(TARGET): $(OBJS) main.cpp
	$(CC) $(LFLAGS) $(OBJS) main.cpp -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

check:
	@$(CC) $(LFLAGS) $(OBJS) ./test/main.cpp -o ./test/test
	@echo "\n...test begin...\n"
	@./test/test input.txt
	@rm -f test/test
	@echo "...test end...\n"

clean: 
	$(RM) $(OBJS) $(TARGET)
