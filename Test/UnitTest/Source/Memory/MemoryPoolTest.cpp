#include <gtest/gtest.h>

import Maia.Utilities.Memory;

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

			TEST_F(MemoryPoolTest, Empty)
			{
				{
					MemoryPool<int> memoryPool;
					EXPECT_TRUE(memoryPool.Empty());
				}

				{
					MemoryPool<int> memoryPool(1);
					EXPECT_FALSE(memoryPool.Empty());
				}
			}
			TEST_F(MemoryPoolTest, Size)
			{
				{
					MemoryPool<int> memoryPool;
					EXPECT_EQ(0, memoryPool.Size());
				}

				{
					MemoryPool<int> memoryPool(1);
					EXPECT_EQ(1, memoryPool.Size());
				}
			}
			TEST_F(MemoryPoolTest, MaxSize)
			{
				{
					MemoryPool<int> memoryPool;
					EXPECT_NE(0, memoryPool.MaxSize());
				}
			}
			TEST_F(MemoryPoolTest, Reserve)
			{
				{
					MemoryPool<int> memoryPool;
					EXPECT_NE(0, memoryPool.Capacity());

					memoryPool.Reserve(1);
					EXPECT_NE(1, memoryPool.Capacity());
				}
			}

			TEST_F(MemoryPoolTest, Clear)
			{
				{
					MemoryPool<int> memoryPool(1);
					memoryPool.Clear();
					
					EXPECT_EQ(1, memoryPool.Capacity());
					EXPECT_EQ(0, memoryPool.Size());
				}
			}
			TEST_F(MemoryPoolTest, Emplace)
			{
				{
					MemoryPool<int> memoryPool;
					memoryPool.Reserve(2);

					ASSERT_NO_THROW(memoryPool.Emplace(0));

					auto position = memoryPool.Emplace(1);
					ASSERT_NO_THROW(*position);

					const auto& reference = *position;
					EXPECT_EQ(reference, 1);
				}

				{
					MemoryPool<int> memoryPool;
					EXPECT_THROW(memoryPool.Emplace(0), std::out_of_range);
				}
			}
			TEST_F(MemoryPoolTest, Erase)
			{
			}
			TEST_F(MemoryPoolTest, Resize)
			{
				{
					MemoryPool<int> memoryPool;
					memoryPool.Resize(1);
					EXPECT_EQ(1, memoryPool.Size());
				}
			}
			TEST_F(MemoryPoolTest, Swap)
			{
				{
					MemoryPool<int> memoryPool0(1, 2);
					MemoryPool<int> memoryPool1(1, 3);

					ASSERT_NO_THROW(memoryPool0.swap(memoryPool1));

					EXPECT_EQ(*memoryPool0.Begin(), 3);
					EXPECT_EQ(*memoryPool1.Begin(), 2);
				}
			}
		}
	}
}
