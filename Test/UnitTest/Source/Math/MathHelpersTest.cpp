#include <gtest/gtest.h>

import Maia.Utilities.Math;

using namespace Maia::Utilities::Math;

namespace Maia
{
	namespace Utilities
	{
		namespace UnitTest
		{
			class MathHelpersTest : public ::testing::Test
			{
			};

			TEST_F(MathHelpersTest, LinearInterpolate)
			{
				EXPECT_EQ(0.0f, Math::LinearInterpolate(0.0f, 2.0f, 0.0f));
				EXPECT_EQ(2.0f, Math::LinearInterpolate(0.0f, 2.0f, 1.0f));
				EXPECT_EQ(1.0f, Math::LinearInterpolate(0.0f, 2.0f, 0.5f));
			}
		}
	}
}
