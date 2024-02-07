#include "CppUnitTest.h"
#include "HapticDevice.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include "MockInventory.h"
#include "../FeelRecoil.h"
#include "../SensationOfWeapons.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OWOGTAVTESTS
{
	TEST_CLASS(RecoilTests)
	{
	public:		

		FeelRecoil CreateSut(sharedPtr<MockDevice> device = nullptr, sharedPtr<MockInventory> inventory = nullptr, std::vector<SensationOfWeapons> sensations = {})
		{
			sharedPtr<MockDevice> mockDevice = device == nullptr ? CreateNewUnique(MockDevice, MockDevice()) : device;
			sharedPtr<MockInventory> mockInventory = inventory == nullptr ? CreateNewUnique(MockInventory, MockInventory()) : inventory;
			std::vector<SensationOfWeapons> gwregv = sensations.size() == 0 ? std::vector<SensationOfWeapons>{SensationOfWeapons({ 0 }, SensationsFactory::Create()->ToString())} : sensations;

			return FeelRecoil(mockDevice, mockInventory, gwregv);
		}

		TEST_METHOD(FeelRecoil_WhenShooting)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			sut.Execute();
			inventory->Shoot();
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

			inventory->Reload(10);
			sut.Execute();
			inventory->Reload(15);
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(ResetAmmo_OnWeaponChange_WithLessAmmo)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			inventory->Equip(0);
			inventory->Reload(10);
			sut.Execute();
			inventory->Equip(1);
			inventory->Reload(5);
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}

		TEST_METHOD(ChangeSensation_BasedOn_Weapon) 
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory, { SensationOfWeapons({ 20 }, SensationsFactory::Create(10)->ToString())});

			inventory->Equip(20);
			sut.Execute();
			inventory->Shoot() ;
			sut.Execute();

			Assert::IsTrue(mock->DidFeelWithoutMuscles(SensationsFactory::Create(10)));
		}

		TEST_METHOD(SetPriority_ToRecoilSensation)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			sut.Execute();
			inventory->Shoot();
			sut.Execute();

			Assert::AreEqual(FeelRecoil::Priority, mock->WhatFelt->GetPriority());
		}

		TEST_METHOD(Send_NotImplemented_Sensation)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			inventory->Equip(1234);
			sut.Execute();
			inventory->Shoot();
			sut.Execute();

			Assert::IsTrue(mock->DidFeelWithoutMuscles(SensationsParser::Parse("12")));
		}

		TEST_METHOD(Feel_DifferentRecoil)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory, { SensationOfWeapons({ 0 }, ""), SensationOfWeapons({10}, SensationsFactory::Create(33)->ToString())});

			inventory->Equip(10);
			sut.Execute();
			inventory->Shoot();
			sut.Execute();

			Assert::IsTrue(mock->DidFeelWithoutMuscles(SensationsFactory::Create(33)));
		}

		TEST_METHOD(DoNotFeel_IfNotHoldingWeapon)
		{
			sharedPtr<MockDevice> mock = CreateNewUnique(MockDevice, MockDevice());
			sharedPtr<MockInventory> inventory = CreateNewUnique(MockInventory, MockInventory());
			auto sut = CreateSut(mock, inventory);

			sut.Execute();
			inventory->StoreWeapon();
			inventory->Shoot();
			sut.Execute();

			Assert::IsFalse(mock->DidFeelAnything());
		}
	};
}