CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = thermal_controller

SRC = src/main.cpp \
      src/thermal_monitor.cpp \
      src/fan_controller.cpp \
      driver/fan_driver.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) fan_driver_test thermal_monitor

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
