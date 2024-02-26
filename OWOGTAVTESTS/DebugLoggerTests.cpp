#include "CppUnitTest.h"
#include "Debug.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(DebugLoggerTests)
	{
	public:
		TEST_METHOD(Check_logger_exists)
		{
			Assert::IsTrue(!Debug::Exists());
		}
	};
}