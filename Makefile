CXX ?= g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude
TEST_FLAGS = -Ithird_party -DDOCTEST_CONFIG_NO_MULTITHREADING

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TESTS_DIR = tests
COVERAGE_DIR = coverage

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRC = $(SRC_DIR)/main.cpp
LIB_SRCS = $(filter-out $(MAIN_SRC), $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(LIB_SRCS))

TEST_SRCS = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTS_DIR)/%.cpp, $(OBJ_DIR)/test_%.o, $(TEST_SRCS))

TARGET = $(BUILD_DIR)/sistema_academico
TEST_TARGET = $(BUILD_DIR)/run_tests

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
    RMDIR = if exist "$(subst /,\,$(1))" rmdir /s /q "$(subst /,\,$(1))"
    RM = if exist "$(subst /,\,$(1))" del /q /f "$(subst /,\,$(1))"
    TARGET_EXT = .exe
else
    MKDIR = mkdir -p $(1)
    RMDIR = rm -rf $(1)
    RM = rm -f $(1)
    TARGET_EXT =
endif

TARGET := $(TARGET)$(TARGET_EXT)
TEST_TARGET := $(TEST_TARGET)$(TARGET_EXT)

.PHONY: all clean test coverage directories

all: directories $(TARGET)

directories:
	@$(call MKDIR,$(BUILD_DIR))
	@$(call MKDIR,$(OBJ_DIR))
	@$(call MKDIR,$(COVERAGE_DIR))

$(TARGET): directories $(OBJS) $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(MAIN_SRC)))
	@if [ -f "$(MAIN_SRC)" ] || [ -f "src/main.cpp" ]; then \
		$(CXX) $(CXXFLAGS) $^ -o $@; \
	else \
		echo "Aviso: $(MAIN_SRC) nao encontrado. O binario principal nao foi gerado."; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_%.o: $(TESTS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -c $< -o $@

$(TEST_TARGET): directories $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) -o $@

test: directories $(TEST_TARGET)
	@echo "Executando testes unitarios..."
	./$(TEST_TARGET)

coverage: CXXFLAGS += --coverage -O0
coverage: clean directories $(TEST_TARGET)
	@echo "Executando testes para geracao de dados de cobertura (.gcda)..."
	-./$(TEST_TARGET)
	@echo "Gerando relatorio de cobertura com gcovr..."
	gcovr -r . --filter "src/" --exclude "tests/" --exclude "third_party/" --print-summary --fail-under-line 60 --html --html-details -o $(COVERAGE_DIR)/relatorio.html

clean:
	@$(call RMDIR,$(OBJ_DIR))
	@$(call RMDIR,$(COVERAGE_DIR))
	@$(call RM,$(TARGET))
	@$(call RM,$(TEST_TARGET))
	@$(call RM,$(BUILD_DIR)/*.gcda)
	@$(call RM,$(BUILD_DIR)/*.gcno)
	@echo "Limpeza concluida."

