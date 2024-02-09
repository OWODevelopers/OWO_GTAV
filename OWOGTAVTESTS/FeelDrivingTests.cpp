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
	TEST_CLASS(FeelDrivingTests)
	{
	public:

		FeelDriving CreateSut(sharedPtr<MockDevice> device = nullptr, sharedPtr<MockVehicle> vehicle = nullptr, sharedPtr <IntensityLerp> engine = nullptr)
		{
			sharedPtr<MockDevice> finalDevice = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<MockVehicle> doc = vehicle == nullptr ? CreateNewUnique(MockVehicle, MockVehicle()) : vehicle;
			auto finalEngine = engine == nullptr ? IntensityLerp(0, 100, 0, 40) : *engine;

			return FeelDriving(finalDevice, doc, finalEngine, IntensityLerp(10, 60, 40, 90));
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

		TEST_METHOD(StopFeeling_AfterExitingVehicle)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->ExitTheVehicle();
			doc->DriveAt(100);
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(ResetLastVelocity_AfterLeavingVehicle)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(100);
			sut.Execute();
			doc->ExitTheVehicle();
			doc->DriveAt(0);
			sut.Execute();
			doc->EnterTheVehicle();
			sut.Execute();


			Assert::AreEqual(1, mock->HowManyFelt());
		}

		TEST_METHOD(Feel_RightArm_OnSteeringRight) {
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(80);
			doc->TurnRight(10);
			sut.Execute();

			Assert::IsTrue(mock->DidFeelIn(OWOGame::Muscle::Arm_R()));
		}

		TEST_METHOD(Feel_LeftArm_OnSteeringLeft) {
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockVehicle> doc = CreateNewUnique(MockVehicle, MockVehicle());
			auto sut = CreateSut(mock, doc);

			doc->DriveAt(80);
			doc->TurnLeft(10);
			sut.Execute();

			Assert::IsTrue(mock->DidFeelIn(OWOGame::Muscle::Arm_L()));
		}

		TEST_METHOD(Muscles_Sum) {

			Assert::AreEqual(Muscle::Pectoral_R().WithIntensity(30).ToString(), (Muscle::Pectoral_R().WithIntensity(20) + Muscle::Pectoral_R().WithIntensity(10)).ToString());
			Assert::AreEqual(MusclesGroup::All().ToString(), (MusclesGroup::Front() + MusclesGroup::Back()).ToString());
			Assert::AreEqual(MusclesGroup::Front().WithIntensity(80).ToString(), (MusclesGroup::Front().WithIntensity(30) + MusclesGroup::Front().WithIntensity(50)).ToString());
			Assert::AreEqual(MusclesGroup(
				{
					Muscle::Pectoral_R().WithIntensity(50), 
					Muscle::Pectoral_L().WithIntensity(30)
				}
			).ToString(), 
				(
					MusclesGroup(
						{ 
							Muscle::Pectoral_R().WithIntensity(50), 
							Muscle::Pectoral_L().WithIntensity(10) 
						}) 
					+ MusclesGroup(
						{ 
							Muscle::Pectoral_L().WithIntensity(20) 
						})).ToString());
		}
	};
}