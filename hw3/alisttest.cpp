#include "alistint.h"
#include "gtest/gtest.h"

class AListIntTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	AListIntTest() {
		list = new AListInt();
		list2 = new AListInt(10);
		emptyList = new AListInt(2);
	}

	virtual ~AListIntTest() {
		// You can do clean-up work that doesn't throw exceptions here.	
		delete list;
		delete list2;
		delete emptyList;
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		list->insert(0, 1);
		list->insert(1, 2);
		list->insert(2, 3);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	AListInt * list;
	AListInt * list2;
	AListInt * emptyList;
};

TEST_F(AListIntTest, GetNominal) {
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list->get(i), i + 1);
	}

	// Test get when resizing
	for(int i = list->size(); i <= 20; i++){
		list->insert(i, i);
		EXPECT_EQ(list->get(i), i);
	}
}

TEST_F(AListIntTest, GetOffNominal) {
	//Get of negative index
	list->get(-10);
	//Check the status of the list
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);

	//Get of a invalid index
	list->get(10);
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);
}

TEST_F(AListIntTest, InsertNominal) {
	//Insert at the end
	int size = list->size();
	list->insert(size, 4);
	EXPECT_EQ(list->get(3), 4);

	//Insert at the 0th index
	list->insert(0, 0);
	for(int i = 0; i < 4; i++){
		EXPECT_EQ(list->get(i), i);
	}

	//Check inserting in invalid indexes
	size = list->size();
	list->insert(-1,-1);
	EXPECT_NE(list->get(-1), -1);
	EXPECT_NE(list->size(), size+1);

	//Test resizing, adding a lot of elements in a empty list
	for(int i = emptyList->size(); i <= 100; i++)
	{
		emptyList->insert(i, i);
		EXPECT_EQ(emptyList->get(i), i);
		EXPECT_EQ(emptyList->size(), i+1);
	}


}

TEST_F(AListIntTest, InsertOffNominal){
	list->insert(-10, 10);
	//Check the status of the list
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);

	list->insert(200, 10);
	//Check the status of the list
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);
}

TEST_F(AListIntTest, RemoveNominal) {

	int size = list->size();
	//Test element shift
	list->remove(1);
	EXPECT_EQ(list->get(1), 3);
	EXPECT_EQ(list->size(), size-1);

	//Remove the first
	size = size-1;
	list->remove(0);
	EXPECT_NE(list->get(0), 1);
	EXPECT_EQ(list->size(), size-1);

	//Remove the last
	
	size = size-1;
	list->remove(size-1);
	//Test removed (outbound tests will crash the test program)
	//EXPECT_NE(list->get(size-1), 3);
	EXPECT_EQ(list->size(), size-1);

	//Remove from a empty list
	emptyList->remove(0);
	EXPECT_EQ(list->size(), 0);
}

TEST_F(AListIntTest, RemoveOffNominal){
	list->remove(-10);
	//Check the status of the list
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);

	list->remove(100);
	//Check the status of the list
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);
}

TEST_F(AListIntTest, SetNominal)
{
	for(int i = 0; i < list->size(); i++)
	{
		list->set(i, i);
		EXPECT_EQ(list->get(i), i);
		EXPECT_NE(list->get(i), i+1);
	}
}

TEST_F(AListIntTest, SetOffNominal) {

	//Set in a negative index
	list->set(-1, 10);
	EXPECT_NE(list->get(-1),10);
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);

	//Set in a outbound index
	list->set(4, 10);
	EXPECT_NE(list->get(4), 10);
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);

	list->set(5, 10);
	EXPECT_NE(list->get(5), 10);
	EXPECT_EQ(list->get(0), 1);
	EXPECT_EQ(list->get(1), 2);
	EXPECT_EQ(list->get(2), 3);
}

TEST_F(AListIntTest, PlusOperator){
	AListInt newList = *list + *list2;

	//Check sizes
	int sumSizes = list->size() + list2->size();
	EXPECT_EQ(newList.size(), sumSizes);

	//Check content
	for(int i = 0; i < newList.size(); i++){
		EXPECT_EQ(newList.get(i), i+1);
	}

	newList = *list + *emptyList;
	//Check sizes
	EXPECT_EQ(newList.size(), list->size());

	//Check content
	for(int i = 0; i < newList.size(); i++){
		EXPECT_EQ(newList.get(i), i+1);
	}
}

TEST_F(AListIntTest, IndexOperator) {
	AListInt tempList(10);
	tempList = *list;

	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(tempList[i], i + 1);
	}

	// Test get when resizing
	for(int i = tempList.size(); i <= 20; i++){
		tempList.insert(i, i);
		EXPECT_EQ(tempList[i], i);
	}
}