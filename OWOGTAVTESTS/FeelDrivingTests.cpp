#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "../FeelDriving.h"
#include "../MockVehicle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(FeelDrivingTests)
	{
	public:

		TEST_METHOD(Fell_velocity_whiledriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = FeelDriving(mock, doc);

			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(FeelSomething_WhenDriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = FeelDriving(mock, doc);

			doc->DriveAt(100);

			sut.Execute();

			Assert::IsTrue(mock->DidFeelAnything());
		}
	};
}