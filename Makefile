CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = thermal_controller
SIMULATION = thermal_simulator
TEST_CONTROLLER = thermal_controller_test
TEST_DRIVER = fan_driver_test
DASHBOARD = thermal_dashboard

SRC = src/main.cpp \
      src/thermal_monitor.cpp \
      src/fan_controller.cpp \
      driver/fan_driver.cpp

TEST_CONTROLLER_SRC = tests/test_fan_controller.cpp \
                      src/fan_controller.cpp

TEST_DRIVER_SRC = tests/test_fan_driver.cpp \
                  driver/fan_driver.cpp
dashboard:
	$(CXX) $(CXXFLAGS) simulation/dashboard.cpp \
		src/thermal_monitor.cpp src/fan_controller.cpp \
		driver/fan_driver.cpp \
		$$(pkg-config --cflags --libs sdl2 SDL2_ttf) \
		-o $(DASHBOARD)
	./$(DASHBOARD)

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) $(TEST_CONTROLLER_SRC) -o $(TEST_CONTROLLER)
	./$(TEST_CONTROLLER)
	$(CXX) $(CXXFLAGS) $(TEST_DRIVER_SRC) -o $(TEST_DRIVER)
	./$(TEST_DRIVER)

clean:
	rm -f $(TARGET) $(TEST_CONTROLLER) $(TEST_DRIVER) $(SIMULATION) $(DASHBOARD) thermal_monitor

simulation:
	$(CXX) $(CXXFLAGS) simulation/main.cpp simulation/simulation.cpp \
		src/thermal_monitor.cpp src/fan_controller.cpp \
		driver/fan_driver.cpp -o $(SIMULATION)
	./$(SIMULATION)

.PHONY: all test clean run simulation dashboard
