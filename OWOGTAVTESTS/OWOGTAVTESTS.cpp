#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "../sdfgh.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//1.Si la vida del personaje baja se envía sensación.
//2.La barra de escudo y de vida se tratan como una sola.
//3.La sensación se envía a unos músculos diferentes según punto de impacto.
//4.La intensidad del músculo cambia según la vida restada
//5.Actualizar la vida máxima si la vida actual (o escudo) sube en lugar de bajar.
//6.Cambiar la sensación a enviar dependiendo del tipo de daño.

namespace OWOGTAVTESTS
{
	TEST_CLASS(OWOGTAVTESTS)
	{
	public:
		
		TEST_METHOD(FeelDamage)
		{
			sharedPtr<HapticDevice> mock = CreateNewUnique(HapticDevice, HapticDevice());
			auto sut = sdfgh(mock);

			sut.Execute(100);
			sut.Execute(90);

			Assert::IsTrue(mock->Received != nullptr);
		}

		TEST_METHOD(DontFeelHealing)
		{
			sharedPtr<HapticDevice> mock = CreateNewUnique(HapticDevice, HapticDevice());
			auto sut = sdfgh(mock);

			sut.Execute(100);
			sut.Execute(200);

			Assert::IsTrue(mock->Received == nullptr);
		}

	};
}