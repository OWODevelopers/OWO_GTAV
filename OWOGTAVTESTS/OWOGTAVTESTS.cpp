#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "../sdfgh.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//4.La intensidad del músculo cambia según la vida restada
//5.Actualizar la vida máxima si la vida actual (o escudo) sube en lugar de bajar.
//6.Cambiar la sensación a enviar dependiendo del tipo de daño.

namespace OWOGTAVTESTS
{
	TEST_CLASS(OWOGTAVTESTS)
	{
	public:
		sdfgh Createasdfasfads(sharedPtr<OWOGame::OWO> device = nullptr, sharedPtr<PlayerBody> body = nullptr) 
		{
			sharedPtr<OWO> mock = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<PlayerBody> mockBody = body == nullptr ? CreateNewUnique(MockBody, MockBody(MusclesGroup({Muscle::Arm_L()}))) : body;
			return sdfgh(mock, mockBody);
		}
		
		TEST_METHOD(FeelDamage)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = Createasdfasfads(mock);

			sut.Execute(100);
			sut.Execute(90);

			Assert::IsTrue(mock->Received != nullptr);
		}

		TEST_METHOD(DontFeelHealing)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = Createasdfasfads(mock);

			sut.Execute(100);
			sut.Execute(200);

			Assert::IsTrue(mock->Received == nullptr);
		}

		TEST_METHOD(UpdateLastHealth)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = Createasdfasfads(mock);

			sut.Execute(90);
			sut.Execute(100);
			sut.Execute(95);

			Assert::IsTrue(mock->Received != nullptr);
		}

		TEST_METHOD(DontFeelNoDamage)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = Createasdfasfads(mock);

			sut.Execute(45);
			sut.Execute(45);

			Assert::IsTrue(mock->Received == nullptr);
		}

		TEST_METHOD(FeelOnRightMuscle)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockBody> body = CreateNewUnique(MockBody, MockBody(MusclesGroup({Muscle::Abdominal_R()})));
			auto sut = sdfgh(mock, body);

			sut.Execute(100);
			sut.Execute(99);

			Assert::IsTrue(mock->DidFeel(Muscle::Abdominal_R().WithIntensity(20)));
		}

	};
}