CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = thermal_controller
TEST = thermal_controller_test

SRC = src/main.cpp \
      src/thermal_monitor.cpp \
      src/fan_controller.cpp \
      driver/fan_driver.cpp

TEST_SRC = tests/test_fan_controller.cpp \
           src/fan_controller.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST) fan_driver_test thermal_monitor

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run
