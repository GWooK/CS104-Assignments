# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

CC        = g++
CPPFLAGS  = -Wall -g -std=c++11
BIN_DIR   = bin
TESTS_DIR = tests
DIRSTAMP  = $(BIN_DIR)/.dirstamp
GTEST_LL  = -I/usr/local/opt/gtest/include/ -lgtest -lgtest_main -pthread
TEST_TARGETS = $(BIN_DIR)/bstiteratortest $(BIN_DIR)/rbtreetest

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

$(BIN_DIR)/bstiteratortest: $(TESTS_DIR)/bstiteratortest.cpp $(DIRSTAMP)
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $@

$(BIN_DIR)/rbtreetest: $(TESTS_DIR)/rbtreetest.cpp $(DIRSTAMP)
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $@

tests: $(TEST_TARGETS)
	-@$(BIN_DIR)/bstiteratortest
	-@$(BIN_DIR)/rbtreetest
	-@echo "--- All Tested!---"
