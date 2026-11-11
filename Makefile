CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude -Ithird_party -MMD -MP

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test
BIN_MAIN = main
BIN_TEST = run_tests

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

OBJS_SEM_MAIN = $(filter-out $(BUILD_DIR)/main.o, $(OBJS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test_%.o, $(TEST_SRCS))

DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

.PHONY: all test clean coverage

all: $(BIN_MAIN)

$(BIN_MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(BIN_TEST)
	./$(BIN_TEST).exe

$(BIN_TEST): $(OBJS_SEM_MAIN) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

coverage:
	$(MAKE) clean
	$(MAKE) test CXXFLAGS="$(CXXFLAGS) --coverage -O0 -g"
	gcov -o $(BUILD_DIR) $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(BUILD_DIR)/*.gcno $(BUILD_DIR)/*.gcda *.gcov $(BIN_MAIN) $(BIN_MAIN).exe $(BIN_TEST) $(BIN_TEST).exe

-include $(DEPS)