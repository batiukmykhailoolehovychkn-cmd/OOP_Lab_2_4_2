#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP_Lab_2_4_2/Money.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestOOPLab242
{
	TEST_CLASS(UnitTestOOPLab242)
	{
    public:
        TEST_METHOD(TestTotalSum)
        {
            Money wallet;
            wallet.addNote(N_100, 2); // 200
            wallet.addNote(N_50, 1);  // 50

            Assert::AreEqual(250L, wallet.getTotalSum());
        }

        TEST_METHOD(TestStringInitializationAndAddition)
        {
            Money w1("100:1,10:5"); // 150
            Money w2("50:2");       // 100

            Money w3 = w1 + w2;     // 250

            Assert::AreEqual(250L, w3.getTotalSum());
        }

        TEST_METHOD(TestEqualityOperator)
        {
            Money w1("100:1"); // 100
            Money w2("50:2");  // 100
            Money w3("20:1");  // 20

            Assert::IsTrue(w1 == w2);
            Assert::IsFalse(w1 == w3);
        }
    };
}