#include "../OWOAPI/Domain/Muscle.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio;

namespace OWOGame 
{
	static class OWOAssert {
	public:
		static void AreEqual(Muscle first, Muscle second) 
		{
			if (first == second) CppUnitTestFramework::Assert::IsTrue(true);

			CppUnitTestFramework::Assert::AreEqual(first.ToString(), second.ToString());
		}
	};
}