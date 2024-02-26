#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../SensationsCollection.h"
#include "../Debug.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(AuthTests)
	{
	public:
		TEST_METHOD(Generate_auth)
		{
			auto auth = SensationsCollection::Auth()->ToString();
			Assert::IsTrue(true);
		}
	};
}