#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "../FeelDamage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(RecoilTests)
	{
	public:
		FeelDamage CreateSut(sharedPtr<OWOGame::OWO> device = nullptr, sharedPtr<PlayerBody> body = nullptr)
		{
			sharedPtr<OWO> mock = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<PlayerBody> mockBody = body == nullptr ? CreateNewUnique(MockBody, MockBody(MusclesGroup({ Muscle::Arm_L() }))) : body;
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
	}
}