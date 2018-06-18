#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Utilities/Containers/Pools/ContiguousMemoryPool.hpp>
/*#include <Utilities/Containers/Pools/Memory_pool.hpp>
#include <Utilities/Containers/Pools/PointedContiguousMemoryPool.hpp>*/


int main(int argc, char** argv) 
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
