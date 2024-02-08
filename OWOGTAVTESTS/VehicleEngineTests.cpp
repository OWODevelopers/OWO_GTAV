#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "FeelDriving.h"
#include "MockVehicle.h"
#include "IntensityLerp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(IntensityLerpTests)
	{
	public:

		TEST_METHOD(DontFeel_Below_MinVelocity)
		{
			Assert::AreEqual(0, IntensityLerp(3, 100, 20, 40).IntensityAt(2));
		}

		TEST_METHOD(Feel_MinIntensity)
		{
			Assert::AreEqual(1, IntensityLerp(6, 100, 1, 40).IntensityAt(6));
		}

		TEST_METHOD(Feel_Intensity_InBetween)
		{
			Assert::AreEqual(30, IntensityLerp(0, 50, 20, 40).IntensityAt(25));
			Assert::AreEqual(60, IntensityLerp(10, 20, 40, 80).IntensityAt(15));
		}

		TEST_METHOD(Limit_AtMaxIntensity)
		{
			Assert::AreEqual(80, IntensityLerp(10, 100, 0, 80).IntensityAt(120));
		}
	};
}