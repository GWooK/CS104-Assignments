# CSCI 104 - HW # 4 Tests

#### Step 1:
 
 + The GTest file `gtest_myset.cpp` is provided to test this problem. To compile the GTest file with your implementation of `myset`, use following command. 

```shell
$ g++ -g -Wall -std=c++0x gtest_myset.cpp webpage.cpp myset.cpp \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o myset
```

#### Step 2:

 + The test file for this step is `parse_md_test.cpp`. Change [line 7](https://github.com/usc-csci104-fall2015/homework-resources/tree/master/hw4_tests/parse_md_test.cpp#L7) to include your `md_parser` file. Also modify [line 10](https://github.com/usc-csci104-fall2015/homework-resources/tree/master/hw4_tests/parse_md_test.cpp#L10) to indicate the name of the class you've given for the `MDParser`, so that it is instantiated properly within the main method.

 + Compile `parse_md_test.cpp` using following command:

```shell
$ g++ -g -Wall parse_md_test.cpp util.cpp myset.cpp md_parser.cpp \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o mdparser
```

Run your compiled program using:

```shell
$ ./mdparser data/data<i>.txt out<i>.txt
```

There are 5 data files provided in the `data` folder for this test. The solution files are provided as `mdparse_solution<i>.out` in the `soln` folder. One would compare the `out<i>.txt` files with `mdparse_solution<i>.out` files to determine if program has correctly parsed the given test files.

#### Step 3, 4:

 + For these steps, test files are provided in the `data` and `cmd` folders. Run your compiled program using following commands:

 ```shell
 $ ./search data/index<i>.txt < cmds/cmd_0<i>.in > search_out<i>.out
 ```

 Compare your `search_out<i>.out` files with the solution files named as `solution_out<i>.out` provided in the `soln` folder.

 + You may also want to test your program for memory leaks using valgrind.
