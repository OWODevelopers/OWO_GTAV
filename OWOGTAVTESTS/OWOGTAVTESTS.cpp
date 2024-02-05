#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "../sdfgh.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//1.Si la vida del personaje baja se env�a sensaci�n.
//2.La barra de escudo y de vida se tratan como una sola.
//3.La sensaci�n se env�a a unos m�sculos diferentes seg�n punto de impacto.
//4.La intensidad del m�sculo cambia seg�n la vida restada
//5.Actualizar la vida m�xima si la vida actual (o escudo) sube en lugar de bajar.
//6.Cambiar la sensaci�n a enviar dependiendo del tipo de da�o.

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