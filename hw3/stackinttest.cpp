#include "stackint.h"
#include "gtest/gtest.h"

class StackIntTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	StackIntTest() {
		
	}

	virtual ~StackIntTest() {
		// You can do clean-up work that doesn't throw exceptions here.	
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		stack.push(3);
		stack.push(2);
		stack.push(1);
		stack.push(0);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	StackInt stack;
};

TEST_F(StackIntTest, TopAndPopNominal) {
	int i = 0;
	while(!stack.empty()){
		EXPECT_EQ(stack.top(), i);
		stack.pop();
		i++;
	}
}