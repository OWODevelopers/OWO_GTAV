#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockInventory.h"
#include "../FeelRecoil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(RecoilTests)
	{
	public:		

		TEST_METHOD(FeelRecoil_WhenShooting)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = FeelRecoil(mock, inventory);

			sut.Execute();

			Assert::IsTrue(mock->DidFeelAnything());
		}
	};
}