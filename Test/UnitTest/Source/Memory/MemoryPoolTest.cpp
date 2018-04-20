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
			}
			TEST_F(MemoryPoolTest, MaxSize)
			{
			}
			TEST_F(MemoryPoolTest, Reserve)
			{
			}

			TEST_F(MemoryPoolTest, Clear)
			{
			}
			TEST_F(MemoryPoolTest, Emplace)
			{
			}
			TEST_F(MemoryPoolTest, Erase)
			{
			}
			TEST_F(MemoryPoolTest, Push)
			{
			}
			TEST_F(MemoryPoolTest, Resize)
			{
			}
			TEST_F(MemoryPoolTest, Swap)
			{
			}
		}
	}
}
