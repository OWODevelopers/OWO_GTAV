#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "FeelDriving.h"
#include "MockVehicle.h"
#include "VehicleEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(VehicleEngineTests)
	{
	public:

		TEST_METHOD(DontFeel_Below_MinVelocity)
		{
			Assert::AreEqual(0, VehicleCalculator(3, 100, 20, 40, 0, 90).IntensityAt(2));
		}

		TEST_METHOD(Feel_MinIntensity)
		{
			Assert::AreEqual(1, VehicleCalculator(6, 100, 1, 40, 0, 90).IntensityAt(6));
		}

		TEST_METHOD(Feel_Intensity_InBetween)
		{
			Assert::AreEqual(30, VehicleCalculator(0, 50, 20, 40, 0, 90).IntensityAt(25));
			Assert::AreEqual(60, VehicleCalculator(10, 20, 40, 80, 0, 90).IntensityAt(15));
		}

		TEST_METHOD(Limit_AtMaxIntensity)
		{
			Assert::AreEqual(80, VehicleCalculator(10, 100, 0, 80, 0, 90).IntensityAt(120));
		}
	};
}