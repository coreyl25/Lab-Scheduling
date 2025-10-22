CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = scheduler
OBJS = main.o scheduler.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp scheduler.h
	$(CXX) $(CXXFLAGS) -c main.cpp

scheduler.o: scheduler.cpp scheduler.h
	$(CXX) $(CXXFLAGS) -c scheduler.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run