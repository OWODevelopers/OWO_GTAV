#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "../FeelDamage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//6.Cambiar la sensaci�n a enviar dependiendo del tipo de da�o.

namespace OWOGTAVTESTS
{
	TEST_CLASS(OWOGTAVTESTS)
	{
	public:
		FeelDamage CreateSut(sharedPtr<OWOGame::OWO> device = nullptr, sharedPtr<PlayerBody> body = nullptr) 
		{
			sharedPtr<OWO> mock = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<PlayerBody> mockBody = body == nullptr ? CreateNewUnique(MockBody, MockBody(MusclesGroup({Muscle::Arm_L()}))) : body;
			return FeelDamage(mock, mockBody);
		}
		
		TEST_METHOD(FeelDamage_WhenHealthIs_BelowPreviousHealth)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = CreateSut(mock);

			sut.Execute(100);
			sut.Execute(90);

			Assert::IsTrue(mock->DidFeelAnything());
		}

		TEST_METHOD(DontFeelHealing)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = CreateSut(mock);

			sut.Execute(100);
			sut.Execute(200);

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(UpdateLastHealth)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = CreateSut(mock);

			sut.Execute(90);
			sut.Execute(100);
			sut.Execute(95);

			Assert::IsTrue(mock->DidFeelAnything());
		}

		TEST_METHOD(DontFeelNoDamage)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = CreateSut(mock);

			sut.Execute(45);
			sut.Execute(45);

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(FeelOnRightMuscle)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockBody> body = CreateNewUnique(MockBody, MockBody(MusclesGroup({Muscle::Abdominal_R()})));
			auto sut = CreateSut(mock, body);

			sut.Execute(100);
			sut.Execute(99);

			Assert::IsTrue(mock->DidFeelIn(Muscle::Abdominal_R().WithIntensity(20)));
		}

		TEST_METHOD(Feel_AtHigherIntensity_ThanLowest)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockBody> body = CreateNewUnique(MockBody, MockBody(MusclesGroup({ Muscle::Abdominal_R() })));
			auto sut = CreateSut(mock, body);

			sut.Execute(100);
			sut.Execute(50);

			Assert::IsFalse(mock->DidFeelIn(Muscle::Abdominal_R().WithIntensity(20)));
		}

		TEST_METHOD(Feel_Based_On_damageType)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockBody> body = CreateNewUnique(MockBody, MockBody(MusclesGroup({ Muscle::Abdominal_R() })));
			auto sut = CreateSut(mock, body);
			body->damageSensation = SensationsFactory::Create(20);

			sut.Execute(100);
			sut.Execute(50);

			Assert::IsTrue(mock->DidFeelWithoutMuscles(SensationsFactory::Create(20)));
		}
	};
}