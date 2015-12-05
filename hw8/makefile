# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

CC        = g++
CPPFLAGS  = -Wall -g -std=c++11
BIN_DIR   = bin
TESTS_DIR = tests
DIRSTAMP  = $(BIN_DIR)/.dirstamp
GTEST_LL  = -I/usr/local/opt/gtest/include/ -lgtest -lgtest_main -pthread
TEST_TARGETS = $(BIN_DIR)/tests

.PHONY: all clean $(TEST_TARGETS)

all: $(TEST_TARGETS)
	-@echo "--- All Built!---"

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
$(DIRSTAMP):
	-@mkdir -p $(BIN_DIR)
	-@touch "$@"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"

# Object Files
$(BIN_DIR)/%.o: %.cpp $(DIRSTAMP)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/tests: hashtable.o minheap.o $(DIRSTAMP) 
	$(CC) $(CPPFLAGS) tests.cpp hashtable.o minheap.o $(GTEST_LL) -o $@

tests: $(TEST_TARGETS)
	-@$(BIN_DIR)/tests
	-@echo "--- All Tested!---"
