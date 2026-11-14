#include "pch.h"

#include "../AIRA-2/Array.hpp"

TEST(Insert_Index, Default) {
	// Arrange
	int size = 10;

	// Act
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	// Assert
	EXPECT_EQ(array.size(), size);
}

TEST(Insert_Index, At_Position) {
	// Arrange
	int size = 10;

	// Act
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i, i);
	}

	// Assert
	EXPECT_EQ(array.size(), size);
}

TEST(Insert_Index, Index_Read) {
	// Arrange
	int size = 10;

	// Act
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	// Assert
	for (int i = 0; i < size; i++) {
		EXPECT_EQ(array[i], i);
	}
}

TEST(Insert_Index, Index_Write) {
	// Arrange
	int size = 10;

	// Act
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i);
		array[i] *= 2;
	}

	// Assert
	for (int i = 0; i < size; i++) {
		EXPECT_EQ(array[i], i * 2);
	}
}