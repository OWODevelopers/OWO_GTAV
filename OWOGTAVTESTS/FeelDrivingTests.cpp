#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "../FeelDriving.h"
#include "../MockVehicle.h"
#include "../VehicleEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(FeelDrivingTests)
	{
	public:

		TEST_METHOD(FeelNothing_WheNotDriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto engine = VehicleEngine(0, 100, 0, 40);

			auto sut = FeelDriving(mock, doc, engine);

			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(FeelSomething_WhenDriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto engine = VehicleEngine(0, 100, 0, 40);

			auto sut = FeelDriving(mock, doc, engine);

			doc->DriveAt(100);

			sut.Execute();

			Assert::IsTrue(mock->DidFeelAnything());
		}

		TEST_METHOD(Feel_MaxVelocity_Intensity)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());

			auto engine = VehicleEngine(0, 100, 0, 40);
			auto sut = FeelDriving(mock, doc, engine);

			doc->DriveAt(100);
			sut.Execute();

			Assert::AreEqual(40, mock->IntensityOfLastFelt());
		}

		TEST_METHOD(DontFeel_Below_MinVelocity)
		{
			Assert::AreEqual(0, VehicleEngine(3, 100, 20, 40).IntensityAt(2));
		}

		TEST_METHOD(Feel_MinIntensity)
		{
			Assert::AreEqual(1, VehicleEngine(6, 100, 1, 40).IntensityAt(6));
		}

		TEST_METHOD(Feel_Intensity_InBetween)
		{
			Assert::AreEqual(30, VehicleEngine(0, 50, 20, 40).IntensityAt(25));
			Assert::AreEqual(60, VehicleEngine(10, 20, 40, 80).IntensityAt(15));
		}

		TEST_METHOD(Limit_AtMaxIntensity)
		{
			Assert::AreEqual(80, VehicleEngine(10, 100, 0, 80).IntensityAt(120));
		}
	};
}