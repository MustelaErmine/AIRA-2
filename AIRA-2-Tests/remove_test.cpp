#include "pch.h"

#include "../AIRA-2/Array.hpp"

TEST(Remove, Size) {
	// Arrange
	int size = 10;

	// Act
	auto array = Array<int>();
	
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	array.remove(0);
	array.remove(0);

	// Assert
	EXPECT_EQ(array.size(), 8);
}

TEST(Remove, Value) {
	// Arrange
	int size = 10;
	int to_remove = 3;

	// Act
	auto array = Array<int>();
	
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	for (int i = 0; i < to_remove; i++) {
		array.remove(0);
	}

	// Assert
	EXPECT_EQ(array[0], to_remove);
}