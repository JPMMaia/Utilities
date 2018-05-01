#include <gtest/gtest.h>
#include <numeric>

import Maia.Utilities.Memory.MemoryPool;

using namespace Maia::Utilities;

namespace Maia
{
	namespace Utilities
	{
		namespace UnitTest
		{
			class MemoryPoolTest : public ::testing::Test
			{
			};

			TEST_F(MemoryPoolTest, DefaultConstructorCreatesEmptyMemoryPool)
			{
				MemoryPool<int> memoryPool;
				EXPECT_TRUE(memoryPool.Empty());
			}
			TEST_F(MemoryPoolTest, CustomConstructorCreatesEmptyMemoryPool)
			{
				MemoryPool<int> memoryPool(1);
				EXPECT_TRUE(memoryPool.Empty());
			}

			TEST_F(MemoryPoolTest, DefaultConstructorCreatesMemoryPoolWithSize0)
			{
				MemoryPool<int> memoryPool;
				EXPECT_EQ(0, memoryPool.Size());
			}
			TEST_F(MemoryPoolTest, CustomConstructorCreatesMemoryPoolWithSize0)
			{
				MemoryPool<int> memoryPool(1);
				EXPECT_EQ(0, memoryPool.Size());
			}

			TEST_F(MemoryPoolTest, MaxSizeReturnsNonZero)
			{
				MemoryPool<int> memoryPool;
				EXPECT_NE(0, memoryPool.MaxSize());
			}

			TEST_F(MemoryPoolTest, ReserveAffectsCapacity)
			{
				MemoryPool<int> memoryPool;
				EXPECT_EQ(0, memoryPool.Capacity());

				memoryPool.Reserve(1);
				EXPECT_EQ(1, memoryPool.Capacity());
			}

			TEST_F(MemoryPoolTest, ClearAffectsSize)
			{
				MemoryPool<int> memoryPool(1);

				memoryPool.Emplace(0);
				memoryPool.Clear();

				EXPECT_EQ(0, memoryPool.Size());
			}

			TEST_F(MemoryPoolTest, EmplaceReturnsIterator)
			{
				MemoryPool<int> memoryPool(2);

				ASSERT_NO_THROW(memoryPool.Emplace(0));

				auto position = memoryPool.Emplace(1);
				ASSERT_NO_THROW(*position);

				const auto& reference = *position;
				EXPECT_EQ(reference, 1);
			}
			TEST_F(MemoryPoolTest, EmplaceAffectsSize)
			{
				MemoryPool<int> memoryPool(1);
				ASSERT_TRUE(memoryPool.Empty());

				ASSERT_NO_THROW(memoryPool.Emplace(0));
				ASSERT_FALSE(memoryPool.Empty());
			}
			TEST_F(MemoryPoolTest, EmplaceThrowsExceptionIfNoCapacity)
			{
				MemoryPool<int> memoryPool;
				EXPECT_THROW(memoryPool.Emplace(0), std::out_of_range);
			}

			TEST_F(MemoryPoolTest, EraseElementAffectsSize)
			{
				MemoryPool<int> memoryPool(1);

				auto position = memoryPool.Emplace(2);
				ASSERT_FALSE(memoryPool.Empty());

				EXPECT_NO_THROW(memoryPool.Erase(position));
				EXPECT_TRUE(memoryPool.Empty());
			}

			TEST_F(MemoryPoolTest, Swap)
			{
				MemoryPool<int> memoryPool0(1);
				memoryPool0.Emplace(1);

				MemoryPool<int> memoryPool1(1);
				memoryPool1.Emplace(2);

				ASSERT_NO_THROW(memoryPool0.Swap(memoryPool1));

				EXPECT_EQ(*memoryPool0.Begin(), 2);
				EXPECT_EQ(*memoryPool1.Begin(), 1);
			}
		}
	}
}
