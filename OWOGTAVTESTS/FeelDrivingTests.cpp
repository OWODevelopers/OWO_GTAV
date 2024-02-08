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
	TEST_CLASS(FeelDrivingTests)
	{
	public:

		FeelDriving CreateSut(sharedPtr<MockDevice> device = nullptr, sharedPtr<MockVehicle> vehicle = nullptr, sharedPtr <VehicleCalculator> engine = nullptr)
		{
			sharedPtr<MockDevice> finalDevice = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<MockVehicle> doc = vehicle == nullptr ? CreateNewUnique(MockVehicle, MockVehicle()) : vehicle;
			auto finalEngine = engine == nullptr ? VehicleCalculator(0, 100, 0, 40, 0, 90) : *engine;

			return FeelDriving(finalDevice, doc, finalEngine);
		}

		TEST_METHOD(FeelNothing_WheNotDriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = CreateSut(mock);

			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(FeelSomething_WhenDriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);

			sut.Execute();

			Assert::IsTrue(mock->DidFeelAnything());
		}

		TEST_METHOD(Feel_MaxVelocity_Intensity)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			sut.Execute();

			Assert::AreEqual(40, mock->IntensityOfLastFelt());
		}

		TEST_METHOD(FeelVelocity_At_BackMuscles)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			sut.Execute();

			Assert::IsTrue(mock->DidFeelInEvery(MusclesGroup::Back()));
		}

		TEST_METHOD(Feel_At_FrontMuscles_WhileDriving_Backwards)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			doc->DriveBackwards();
			sut.Execute();

			Assert::IsTrue(mock->DidFeelInEvery(MusclesGroup::Front()));
		}

		TEST_METHOD(Feel_Collision_WhileDriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			sut.Execute();
			doc->DriveAt(50);
			sut.Execute();

			Assert::IsTrue(mock->DidFeelInEvery(MusclesGroup::All()));
		}

		TEST_METHOD(FeelCollisionOnce)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			sut.Execute();
			doc->DriveAt(0);
			sut.Execute();
			sut.Execute();

			Assert::AreEqual(2, mock->HowManyFelt());
		}

		TEST_METHOD(FeelCollisionAtMaxIntensity)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			sut.Execute();
			doc->DriveAt(0);
			sut.Execute();

			Assert::AreEqual(90, mock->IntensityOfLastFelt());
		}
	};
}