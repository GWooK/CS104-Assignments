#include "gtest/gtest.h"
//#include "hashtable.h"
#include <map>
#include <exception>
#include <string>
#include "minheap.h"
#include <iostream>
using namespace std;

TEST(HashTableTest, SimpleAdd)
{
	HashTable h;
	h.add(make_pair("Iuri", 1));
	EXPECT_EQ(h["Iuri"], 1);
	h.add(make_pair("Iara", 2));
	h.add(make_pair("42", 42));
	h.add(make_pair("pi", 3));
	h.add(make_pair("e", 2));
	h.add(make_pair("this", 0));
	h.add(make_pair("dozedozedoze", 12));
	h.add(make_pair("aaaa", 2));
	h.add(make_pair("30", 42));
	h.add(make_pair("Caio", 3));
	h.add(make_pair("USC", 2));
	h.add(make_pair("abc", 2));
	h.add(make_pair("bac", 2));
	h.add(make_pair("USP", 0));
	h.add(make_pair("eita", 12));
	h.add(make_pair("HUEHUHE", 13));
	EXPECT_THROW(h.add(make_pair("this", 0)), exception);
	EXPECT_THROW(h.add(make_pair("42", 43)), exception);
	EXPECT_THROW(h.add(make_pair("e", 3)), exception);
	EXPECT_EQ(h.find("Iuri"), 1);
	EXPECT_EQ(h.find("Iara"), 2);
	EXPECT_EQ(h.find("42"), 42);
	EXPECT_EQ(h.find("pi"), 3);
	EXPECT_EQ(h.find("e"), 2);
	EXPECT_EQ(h.find("dozedozedoze"), 12);
	EXPECT_EQ(h.find("this"), 0);
	EXPECT_THROW(h.find("me"), exception);
	EXPECT_THROW(h.find("iuri"), exception);
	EXPECT_THROW(h.find("TheAnswer"), exception);
	EXPECT_THROW(h.find("somesense"), exception);

	//h.print();
}

TEST(HashTableTest, BigAdd)
{
	HashTable h;
	for (int i = 0; i < 1024; i++) {
		h.add(make_pair(std::to_string(i), i));
	}
	for (int i = 0; i < 1024; i++) {
		int t = (i*31+7)%1024;
		EXPECT_THROW(h.find(to_string(t+1024)), exception);
		EXPECT_EQ(h.find(to_string(t)), t);
		EXPECT_THROW(h.add(make_pair(to_string(i), i)), exception);
	}

	//h.print();
}


TEST(HashTableTest, remove)
{
	HashTable h;
	for (int i = 0; i < 1024; i++) {
		h.add(make_pair(to_string(i), i));
	}
	for (int i = 0; i < 512; i++) {
		int t = (i*31+7)%1024;
		h.remove(to_string(t));
	}
	for (int i = 0; i < 1024; i++) {
		int t = (i*31+7)%1024;
		if (i < 512) {
			EXPECT_THROW(h.find(to_string(t)), exception);
		} else {
			EXPECT_EQ(h.find(to_string(t)), t);
		}
	}
}


TEST(HashTableTest, updateFind)
{
	HashTable h;
	for (int i = 0; i < 1024; i++) {
		h.add(make_pair(to_string(i), i));
	}

	for (int i = 0; i < 512; i++) {
		int t = (i*31+7)%1024;
		h.update(make_pair(to_string(t), i));
	}
	for (int i = 0; i < 1024; i++) {
		int t = (i*31+7)%1024;
		if (i < 512) {
			EXPECT_EQ(h.find(to_string(t)), i);
		} else {
			EXPECT_EQ(h.find(to_string(t)), t);
		}
	}
}


TEST(HashTableTest, updateThrow)
{
	HashTable h;
	for (int i = 0; i < 1024; i++) {
		h.add(make_pair(to_string(i), i));
	}
	for (int i = 0; i < 512; i++) {
		EXPECT_THROW(h.update(make_pair(to_string(i+1024), i)), exception);
	}
}


TEST(MinHeapTest, simpleAdd)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		m.add("x", 10);
		EXPECT_EQ(m.peek(), "x");
		m.add("i", 1);
		m.add("v", 5);
		EXPECT_EQ(m.peek(), "i");
	}
}


TEST(MinHeapTest, manyAdds)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		for (int i = 1023; i >= 0; i--) {
			m.add(to_string(i), i);
			EXPECT_EQ(m.peek(), to_string(i));
		}
	}
}


TEST(MinHeapTest, smallD)
{
	EXPECT_THROW(MinHeap a(1), exception);
	EXPECT_THROW(MinHeap b(0), exception);
}



TEST(MinHeapTest, multiplePriority)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		m.add("j", 0);
		m.add("e", 0);
		EXPECT_EQ(m.peek(), "e");
		m.add("i", 0);
		EXPECT_EQ(m.peek(), "e");
		m.add("c", 0);
		EXPECT_EQ(m.peek(), "c");
	}
}

TEST(MinHeapTest, isEmpty)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		EXPECT_EQ(m.isEmpty(), true);
		m.add("a", 0);
		EXPECT_EQ(m.isEmpty(), false);
	}
}

TEST(MinHeapTest, emptyExceptions)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		EXPECT_THROW(m.peek(), exception);
		EXPECT_THROW(m.remove(), exception);
		EXPECT_THROW(m.update("a", 0), exception);
	}
}




TEST(MinHeapTest, remove)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		m.add("a", 99);
		m.add("b", 99);
		m.add("c", 99);
		m.add("e", 99);
		m.add("f", 99);
		m.add("d", 99);
		m.add("mmm", 10);
		m.add("mmi", 5);
		EXPECT_EQ(m.peek(), "mmi");
		m.remove();
		EXPECT_EQ(m.peek(), "mmm");
		m.remove();
		EXPECT_EQ(m.peek(), "a");
	}
}



TEST(MinHeapTest, update)
{
	for (int i = 2; i < 6; i++) {
		MinHeap m(i);
		m.add("a", 10);
		m.update("a", 11);
		m.add("b", 5);
		m.add("c", 2);
		EXPECT_EQ(m.peek(), "c");
		m.update("c", 34);
		EXPECT_EQ(m.peek(), "b");
		m.update("a", 3);
		EXPECT_EQ(m.peek(), "a");
		EXPECT_THROW(m.update("e", 8), exception);
	}
}



TEST(MinHeapTest, HeapSort)
{
	for (int i = 2; i < 11; i++) {
		MinHeap m(i);
		for (int i = 0; i < 1024; i++) {
			int t = ((1023-i)*31+7)%1024;
			//cout << "inserting " << i << endl;
			m.add(to_string(i), t);
		}
		for (int i = 0; i < 1024; i++) {
			//cout << "updating " << i << endl;
			m.update(to_string(i), 1023-i);
		}
		for (int i = 0; i < 1024; i++) {
			m.update(to_string(i), i);
		}
		for (int i = 0; i < 1024; i++) {
			EXPECT_EQ(m.peek(), to_string(i));
			m.remove();
		}
		EXPECT_EQ(m.isEmpty(), true);
	}
}