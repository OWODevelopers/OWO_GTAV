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

		FeelRecoil CreateSut(sharedPtr<MockDevice> device = nullptr, sharedPtr<MockInventory> inventory = nullptr) 
		{
			sharedPtr<MockDevice> mock = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<MockInventory> mockInventory = inventory == nullptr ? CreateNewUnique(MockInventory, MockInventory()) : inventory;
			return FeelRecoil(mock, mockInventory);
		}

		TEST_METHOD(FeelRecoil_WhenShooting)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			sut.Execute();
			inventory->ammo--;
			sut.Execute();

			Assert::IsTrue(mock->DidFeelAnything());
		}

		TEST_METHOD(DontFeelRecoil_WhenNotShooting) 
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			auto sut = CreateSut(mock);

			sut.Execute();
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(DoNotFeel_Reload) 
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

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
			auto sut = CreateSut(mock, inventory);

			inventory->currentWeapon = 0;
			inventory->ammo = 10;
			sut.Execute();
			inventory->currentWeapon = 1;
			inventory->ammo = 5;
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(ChangeSensation_BasedOn_Weapon) 
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			inventory->toBeFelt = SensationsFactory::Create(10)->WithMuscles({ Muscle::Pectoral_R()});
			sut.Execute();
			inventory->ammo--;
			sut.Execute();

			Assert::IsTrue(mock->DidFeelWithoutMuscles(SensationsFactory::Create(10)));
		}
	};
}