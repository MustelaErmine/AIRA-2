#include "pch.h"

#include "../AIRA-2/Array.hpp"

TEST(Iterator, Read) {
	// Arrange
	int size = 10;
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	// Act
	// Assert
	int i = 0;
	for (auto it = array.iterator(); it.hasNext(); it.next()) {
		EXPECT_EQ(it.get(), i++);
	}
	EXPECT_EQ(i, size - 1);
}

TEST(Iterator, Write) {
	// Arrange
	int size = 10;
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	// Act
	// Assert
	int i = 0;
	for (auto it = array.iterator(); it.hasNext(); it.next()) {
		it.set(it.get() * 2);

		EXPECT_EQ(it.get(), i++ * 2);
	}
	EXPECT_EQ(i, size - 1);
}