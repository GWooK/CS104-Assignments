# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
#$(BIN_DIR)/alisttest: alisttest.cpp alistint.cpp
#	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

#$(BIN_DIR)/stackinttest: stackinttest.cpp stackint.cpp alistint.cpp
#	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

parsertester: parsertester.cpp markdownparser.cpp myset.cpp
	$(CC) $(CPPFLAGS)  -std=c++11 $^ -o $@

webpagetester: webpagetester.cpp webpage.cpp markdownparser.cpp myset.cpp
	$(CC) $(CPPFLAGS)  -std=c++11 $^ -o $@

search: search.cpp searcheng.cpp util.cpp webpage.cpp markdownparser.cpp myset.cpp
	$(CC) $(CPPFLAGS)  -std=c++11 $^ -o $@
clear:
	rm parsertester
	rm markdownparser
	rm search