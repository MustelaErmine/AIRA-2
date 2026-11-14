#include "pch.h"
#include "../AIRA-2/Array.hpp"

TEST(Creation, Small) {
	// Arrange
	// Act
	for (int size = 0; size < 10; size++) {
		auto array = Array<int>();
		for (int i = 0; i < size; i++) {
			array.insert(i);
		}

		// Assert
		EXPECT_EQ(array.size(), size);
		EXPECT_GE(array.capacity(), size);
	}
}

TEST(Creation, WithCapacity) {
	// Arrange
	int size = 10;
	// Act
	auto array = Array<int>(size);

	// Assert
	EXPECT_EQ(array.size(), 0);
	EXPECT_GE(array.capacity(), size);
}

TEST(Creation, Big) {
	// Arrange
	int size = 1000000;

	// Act
	auto array = Array<int>();
	for (int i = 0; i < size; i++) {
		array.insert(i);
	}

	// Assert
	EXPECT_EQ(array.size(), size);
	EXPECT_GE(array.capacity(), size);
}

TEST(Creation, Copyable) {
	// Assert
	class A {
	public:
		A() noexcept = default;
		~A() noexcept = default;
		A(const A&) noexcept = default;
		A(A&&) noexcept = delete;
		A& operator=(const A&) = default;
		A& operator=(A&&) = delete;
	};

	// Act
	// Assert
	auto array = Array<A>();

	EXPECT_NO_THROW(array.insert(A()));

	EXPECT_EQ(array.size(), 1);
}

//TEST(Creation, Moveable) {
//	// Assert
//	class A {
//	public:
//		A() noexcept = default;
//		~A() noexcept = default;
//		A(const A&) = delete;
//		A(A&&) = default;
//		A& operator=(const A&) noexcept = delete;
//		A& operator=(A&&) noexcept = default;
//	};
//
//	// Act
//	// Assert
//	auto array = Array<A>();
//
//	EXPECT_NO_THROW(array.insert(A()));
//
//	EXPECT_EQ(array.size(), 1);
//}

TEST(Creation, String) {
	// Assert
	// Act
	auto array = Array<std::string>();
	auto str = std::string("a");

	// Assert

	EXPECT_NO_THROW(array.insert(str));
	EXPECT_NO_THROW(array.insert(str));
	EXPECT_NO_THROW(array.insert(str));
	EXPECT_NO_THROW(array.remove(1));
	EXPECT_EQ(array[1], str);

	EXPECT_EQ(array.size(), 2);
}