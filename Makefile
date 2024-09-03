INCLUDE_DIR = include
TEST_DIR = tests

OBJ_DIR = obj
BIN_DIR = bin

CXXOPTS = -std=c++17 -Wall -Wextra -Werror

DIRS = $(OBJ_DIR) $(BIN_DIR)

TESTS = $(patsubst $(TEST_DIR)/%.cpp,%,$(wildcard $(TEST_DIR)/*.cpp))
INCLUDES = $(wildcard $(INCLUDE_DIR)/lith/*.hpp)

.PHONY: test clean $(TESTS)

test: $(TESTS)

$(TESTS): %: $(BIN_DIR)/%
	./$<

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(INCLUDES)  | $(BIN_DIR)
	g++ -std=c++17 -I$(INCLUDE_DIR) -o $@ $<

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(INCLUDES) | $(OBJ_DIR)
	g++ $(CXXOPTS) -I$(INCLUDE_DIR) -o $@ -c $<

$(DIRS): %:
	mkdir $@

clean:
	rm -rf $(DIRS)