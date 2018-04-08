export module Maia.Utilities.Math;

namespace Maia
{
	namespace Utilities
	{
		namespace Math
		{
			export template <class Vector, class Scalar>
			inline Vector LinearInterpolate(const Vector& a, const Vector& b, Scalar percentage)
			{
				return (Scalar(1) - percentage) * a + percentage * b;
			}
		}
	}
}
