#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockBody.h"
#include "../FeelDriving.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(FeelDrivingTests)
	{
	public:

		TEST_METHOD(Fell_velocity_whiledriving)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = FeelDriving(mock);

			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}
	};
}