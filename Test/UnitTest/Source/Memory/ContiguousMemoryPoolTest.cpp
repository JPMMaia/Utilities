#include <gtest/gtest.h>
#include <numeric>
#include <vector>

import Maia.Utilities.Memory.ContiguousMemoryPool;

using namespace Maia::Utilities;

namespace Maia
{
	namespace Utilities
	{
		namespace UnitTest
		{
			class ContiguousMemoryPoolTest : public ::testing::Test
			{
			};

			TEST_F(ContiguousMemoryPoolTest, DefaultConstructorCreatesEmptyMemoryPool)
			{
				ContiguousMemoryPool<int> memoryPool;
				EXPECT_TRUE(memoryPool.Empty());
			}
			TEST_F(ContiguousMemoryPoolTest, CustomConstructorCreatesEmptyMemoryPool)
			{
				ContiguousMemoryPool<int> memoryPool(1);
				EXPECT_TRUE(memoryPool.Empty());
			}

			TEST_F(ContiguousMemoryPoolTest, DefaultConstructorCreatesMemoryPoolWithSize0)
			{
				ContiguousMemoryPool<int> memoryPool;
				EXPECT_EQ(0, memoryPool.Size());
			}
			TEST_F(ContiguousMemoryPoolTest, CustomConstructorCreatesMemoryPoolWithSize0)
			{
				ContiguousMemoryPool<int> memoryPool(1);
				EXPECT_EQ(0, memoryPool.Size());
			}

			TEST_F(ContiguousMemoryPoolTest, MaxSizeReturnsNonZero)
			{
				ContiguousMemoryPool<int> memoryPool;
				EXPECT_NE(0, memoryPool.MaxSize());
			}

			TEST_F(ContiguousMemoryPoolTest, ReserveAffectsCapacity)
			{
				ContiguousMemoryPool<int> memoryPool;
				EXPECT_EQ(0, memoryPool.Capacity());

				memoryPool.Reserve(1);
				EXPECT_EQ(1, memoryPool.Capacity());
			}

			TEST_F(ContiguousMemoryPoolTest, ClearAffectsSize)
			{
				ContiguousMemoryPool<int> memoryPool(1);

				memoryPool.EmplaceBack(0);
				memoryPool.Clear();

				EXPECT_EQ(0, memoryPool.Size());
			}

			TEST_F(ContiguousMemoryPoolTest, EmplaceBackReturnsReference)
			{
				ContiguousMemoryPool<int> memoryPool(2);

				ASSERT_NO_THROW(memoryPool.EmplaceBack(0));

				auto& reference = memoryPool.EmplaceBack(1);
				EXPECT_EQ(reference, 1);
			}
			TEST_F(ContiguousMemoryPoolTest, EmplaceBackAffectsSize)
			{
				ContiguousMemoryPool<int> memoryPool(1);
				ASSERT_TRUE(memoryPool.Empty());

				ASSERT_NO_THROW(memoryPool.EmplaceBack(0));
				ASSERT_FALSE(memoryPool.Empty());
			}
			TEST_F(ContiguousMemoryPoolTest, EmplaceBackThrowsExceptionIfSizeEqualsCapacity)
			{
				ContiguousMemoryPool<int> memoryPool;
				ASSERT_EQ(memoryPool.Size(), memoryPool.Capacity());
				EXPECT_THROW(memoryPool.EmplaceBack(0), std::out_of_range);
			}

			TEST_F(ContiguousMemoryPoolTest, SwapWithBackAndPopBack)
			{
				ContiguousMemoryPool<int> memoryPool(3);

				memoryPool.EmplaceBack(0);
				memoryPool.EmplaceBack(1);
				memoryPool.EmplaceBack(2);
				ASSERT_EQ(3, memoryPool.Size());
				ASSERT_EQ(0, *memoryPool.Begin());

				memoryPool.SwapWithBackAndPopBack(memoryPool.Begin());
				EXPECT_EQ(2, memoryPool.Size());
				EXPECT_EQ(2, *memoryPool.Begin());

				memoryPool.SwapWithBackAndPopBack(memoryPool.Begin());
				EXPECT_EQ(1, memoryPool.Size());
				EXPECT_EQ(1, *memoryPool.Begin());

				EXPECT_NO_THROW(memoryPool.SwapWithBackAndPopBack(memoryPool.Begin()));
				EXPECT_TRUE(memoryPool.Empty());
			}

			TEST_F(ContiguousMemoryPoolTest, Swap)
			{
				ContiguousMemoryPool<int> memoryPool0(1);
				memoryPool0.EmplaceBack(1);

				ContiguousMemoryPool<int> memoryPool1(1);
				memoryPool1.EmplaceBack(2);

				ASSERT_NO_THROW(memoryPool0.Swap(memoryPool1));

				EXPECT_EQ(*memoryPool0.Begin(), 2);
				EXPECT_EQ(*memoryPool1.Begin(), 1);
			}
		}
	}
}
