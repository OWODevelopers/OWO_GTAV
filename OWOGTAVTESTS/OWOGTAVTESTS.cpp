#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(OWOGTAVTESTS)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			uniquePtr<OWO> owo = CreateNewUnique(OWO, HapticDevice());

			owo->AutoConnect();
			owo->ChangeUpdateFrequency(12);
			owo->Configure(GameAuth::Parse("", "0"));
			owo->Connect({});
			owo->Disconnect();
			owo->DiscoveredApps();
			owo->Scan(15);
			owo->State();
			owo->Send(SensationsFactory::Create());
			owo->Stop();
			owo->UpdateStatus(20);
		}
	};
}
