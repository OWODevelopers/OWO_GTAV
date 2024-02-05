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
			inventory->ammo--;
			sut.Execute();

			Assert::IsTrue(mock->DidFeelAnything());
		}

		TEST_METHOD(DontFeelRecoil_WhenNotShooting) 
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = FeelRecoil(mock, inventory);

			sut.Execute();
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(DoNotFeel_Reload) 
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = FeelRecoil(mock, inventory);

			inventory->ammo = 10;
			sut.Execute();
			inventory->ammo = 15;
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(ResetAmmo_OnWeaponChange_WithLessAmmo)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = FeelRecoil(mock, inventory);

			inventory->currentWeapon = 0;
			inventory->ammo = 10;
			sut.Execute();
			inventory->currentWeapon = 1;
			inventory->ammo = 5;
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());

		}
	};
}