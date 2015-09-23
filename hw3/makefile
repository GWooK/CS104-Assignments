# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/alisttest: alisttest.cpp alistint.cpp
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

.PHONY: alistest

alisttest: $(BIN_DIR)/alisttest 
	-@$(BIN_DIR)/alisttest
	-@echo "--- All Tested!---"

clear:
	rm $(BIN_DIR)/alisttest
