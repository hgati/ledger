#include "BasicAmount.h"
#include "ledger.h"

using namespace ledger;

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(BasicAmountTestCase, "numerics");

void BasicAmountTestCase::setUp() {}
void BasicAmountTestCase::tearDown() {}

void BasicAmountTestCase::testConstructors()
{
  amount_t x0;
  amount_t x1(123456L);
  amount_t x2(123456UL);
  amount_t x4(true);
  amount_t x5("123456");
  amount_t x6("123.456");
  amount_t x7(std::string("123456"));
  amount_t x8(std::string("123.456"));
  amount_t x10(x6);
  amount_t x11(x8);

  assertEqual(amount_t(0L), x0);
  assertEqual(x2, x1);
  assertEqual(x5, x1);
  assertEqual(x7, x1);
  assertEqual(x6, x8);
  assertEqual(x10, x6);
  assertEqual(x11, x10);
  assertEqual(amount_t(1L), x4);
}

void BasicAmountTestCase::testNegation()
{
  amount_t x0;
  amount_t x1(-123456L);
  amount_t x5("-123456");
  amount_t x6("-123.456");
  amount_t x7(std::string("-123456"));
  amount_t x8(std::string("-123.456"));
  amount_t x9(- x6);

  assertEqual(amount_t(0L), x0);
  assertEqual(x5, x1);
  assertEqual(x7, x1);
  assertEqual(x6, x8);
  assertEqual(- x6, x9);
  assertEqual(x6.negated(), x9);

  amount_t x10(x9);
  x10.negate();

  assertEqual(x6, x10);
}

void BasicAmountTestCase::testAssignment()
{
  amount_t x0;
  amount_t x1  = 123456L;
  amount_t x2  = 123456UL;
  amount_t x4  = true;
  amount_t x5  = "123456";
  amount_t x6  = "123.456";
  amount_t x7  = std::string("123456");
  amount_t x8  = std::string("123.456");
  amount_t x9  = x6;
  amount_t x10 = amount_t(x6);

  assertEqual(amount_t(0L), x0);
  assertEqual(x2, x1);
  assertEqual(x5, x1);
  assertEqual(x7, x1);
  assertEqual(x8, x6);
  assertEqual(x10, x6);
  assertEqual(amount_t(1L), x4);
  assertEqual(x10, x9);

  x0  = amount_t();
  x1  = 123456L;
  x2  = 123456UL;
  x4  = true;
  x5  = "123456";
  x6  = "123.456";
  x7  = std::string("123456");
  x8  = std::string("123.456");
  x9  = x6;
  x10 = amount_t(x6);

  assertEqual(amount_t(0L), x0);
  assertEqual(x2, x1);
  assertEqual(x5, x1);
  assertEqual(x7, x1);
  assertEqual(x8, x6);
  assertEqual(x10, x6);
  assertEqual(amount_t(1L), x4);
  assertEqual(x10, x9);
}

void BasicAmountTestCase::testEquality()
{
  amount_t x1(123456L);
  amount_t x2(456789L);
  amount_t x3(333333L);
  amount_t x5("123456.0");

  CPPUNIT_ASSERT(x1 == 123456L);
  CPPUNIT_ASSERT(x1 != x2);
  CPPUNIT_ASSERT(x1 == (x2 - x3));
  CPPUNIT_ASSERT(x1 == x5);
}

void BasicAmountTestCase::testIntegerAddition()
{
  amount_t x1(123L);
  amount_t y1(456L);

  assertEqual(amount_t(579L), x1 + y1);
  assertEqual(amount_t(579L), x1 + 456L);
  assertEqual(amount_t(579L), 456L + x1);

  x1 += amount_t(456L);
  assertEqual(amount_t(579L), x1);
  x1 += 456L;
  assertEqual(amount_t(1035L), x1);

  amount_t x3(true);
  amount_t y3(true);

  assertEqual(amount_t(2L), x3 + y3);
  assertEqual(amount_t(2L), x3 + true);

  amount_t x4("123456789123456789123456789");

  assertEqual(amount_t("246913578246913578246913578"), x4 + x4);
}

void BasicAmountTestCase::testFractionalAddition()
{
  amount_t x1("123.123");
  amount_t y1("456.456");

  assertEqual(amount_t("579.579"), x1 + y1);
  assertEqual(amount_t("579.579"), x1 + amount_t("456.456"));
  assertEqual(amount_t("579.579"), amount_t("456.456") + x1);

  x1 += amount_t("456.456");
  assertEqual(amount_t("579.579"), x1);
  x1 += amount_t("456.456");
  assertEqual(amount_t("1036.035"), x1);
  x1 += 456L;
  assertEqual(amount_t("1492.035"), x1);

  amount_t x2("123456789123456789.123456789123456789");

  assertEqual(amount_t("246913578246913578.246913578246913578"), x2 + x2);
}

void BasicAmountTestCase::testIntegerSubtraction()
{
  amount_t x1(123L);
  amount_t y1(456L);

  assertEqual(amount_t(333L), y1 - x1);
  assertEqual(amount_t(-333L), x1 - y1);
  assertEqual(amount_t(23L), x1 - 100L);
  assertEqual(amount_t(-23L), 100L - x1);

  x1 -= amount_t(456L);
  assertEqual(amount_t(-333L), x1);
  x1 -= 456L;
  assertEqual(amount_t(-789L), x1);

  amount_t x3(true);
  amount_t y3(true);

  assertEqual(amount_t(false), x3 - y3);

  amount_t x4("123456789123456789123456789");
  amount_t y4("8238725986235986");

  assertEqual(amount_t("123456789115218063137220803"), x4 - y4);
  assertEqual(amount_t("-123456789115218063137220803"), y4 - x4);
}

void BasicAmountTestCase::testFractionalSubtraction()
{
  amount_t x1("123.123");
  amount_t y1("456.456");

  assertEqual(amount_t("-333.333"), x1 - y1);
  assertEqual(amount_t("333.333"), y1 - x1);

  x1 -= amount_t("456.456");
  assertEqual(amount_t("-333.333"), x1);
  x1 -= amount_t("456.456");
  assertEqual(amount_t("-789.789"), x1);
  x1 -= 456L;
  assertEqual(amount_t("-1245.789"), x1);

  amount_t x2("123456789123456789.123456789123456789");
  amount_t y2("9872345982459.248974239578");

  assertEqual(amount_t("123446916777474329.874482549545456789"), x2 - y2);
  assertEqual(amount_t("-123446916777474329.874482549545456789"), y2 - x2);
}

void BasicAmountTestCase::testIntegerMultiplication()
{
  amount_t x1(123L);
  amount_t y1(456L);

  assertEqual(amount_t(0L), x1 * 0L);
  assertEqual(amount_t(0L), amount_t(0L) * x1);
  assertEqual(amount_t(0L), 0L * x1);
  assertEqual(x1, x1 * 1L);
  assertEqual(x1, amount_t(1L) * x1);
  assertEqual(x1, 1L * x1);
  assertEqual(- x1, x1 * -1L);
  assertEqual(- x1, amount_t(-1L) * x1);
  assertEqual(- x1, -1L * x1);
  assertEqual(amount_t(56088L), x1 * y1);
  assertEqual(amount_t(56088L), y1 * x1);
  assertEqual(amount_t(56088L), x1 * 456L);
  assertEqual(amount_t(56088L), amount_t(456L) * x1);
  assertEqual(amount_t(56088L), 456L * x1);

  x1 *= amount_t(123L);
  assertEqual(amount_t(15129L), x1);
  x1 *= 123L;
  assertEqual(amount_t(1860867L), x1);

  amount_t x3(true);
  amount_t y3(true);

  assertEqual(amount_t(true), x3 * y3);

  amount_t x4("123456789123456789123456789");

  assertEqual(amount_t("15241578780673678546105778281054720515622620750190521"),
	      x4 * x4);
}

void BasicAmountTestCase::testFractionalMultiplication()
{
  amount_t x1("123.123");
  amount_t y1("456.456");

  assertEqual(amount_t(0L), x1 * 0L);
  assertEqual(amount_t(0L), amount_t(0L) * x1);
  assertEqual(amount_t(0L), 0L * x1);
  assertEqual(x1, x1 * 1L);
  assertEqual(x1, amount_t(1L) * x1);
  assertEqual(x1, 1L * x1);
  assertEqual(- x1, x1 * -1L);
  assertEqual(- x1, amount_t(-1L) * x1);
  assertEqual(- x1, -1L * x1);
  assertEqual(amount_t("56200.232088"), x1 * y1);
  assertEqual(amount_t("56200.232088"), y1 * x1);
  assertEqual(amount_t("56200.232088"), x1 * amount_t("456.456"));
  assertEqual(amount_t("56200.232088"), amount_t("456.456") * x1);

  x1 *= amount_t("123.123");
  assertEqual(amount_t("15159.273129"), x1);
  x1 *= amount_t("123.123");
  assertEqual(amount_t("1866455.185461867"), x1);
  x1 *= 123L;
  assertEqual(amount_t("229573987.811809641"), x1);

  amount_t x2("123456789123456789.123456789123456789");

  assertEqual(amount_t("15241578780673678546105778311537878.046486820281054720515622620750190521"),
	      x2 * x2);
}

void BasicAmountTestCase::testIntegerDivision()
{
  amount_t x1(123L);
  amount_t y1(456L);

  assertThrow(x1 / 0L, amount_error *);
  assertEqual(amount_t(0L), amount_t(0L) / x1);
  assertEqual(amount_t(0L), 0L / x1);
  assertEqual(x1, x1 / 1L);
  assertEqual(amount_t("0.008130"), amount_t(1L) / x1);
  assertEqual(amount_t("0.008130"), 1L / x1);
  assertEqual(- x1, x1 / -1L);
  assertEqual(- amount_t("0.008130"), amount_t(-1L) / x1);
  assertEqual(- amount_t("0.008130"), -1L / x1);
  assertEqual(amount_t("0.269736"), x1 / y1);
  assertEqual(amount_t("3.707317"), y1 / x1);
  assertEqual(amount_t("0.269736"), x1 / 456L);
  assertEqual(amount_t("3.707317"), amount_t(456L) / x1);
  assertEqual(amount_t("3.707317"), 456L / x1);

  x1 /= amount_t(456L);
  assertEqual(amount_t("0.269736"), x1);
  x1 /= 456L;
  assertEqual(amount_t("0.000591526315789473"), x1);

  amount_t x4("123456789123456789123456789");
  amount_t y4("56");

  assertEqual(amount_t(1L), x4 / x4);
  assertEqual(amount_t("2204585520061728377204585.517857"), x4 / y4);
}

void BasicAmountTestCase::testFractionalDivision()
{
  amount_t x1("123.123");
  amount_t y1("456.456");

  assertThrow(x1 / 0L, amount_error *);
  assertEqual(amount_t("0.00812195"), amount_t("1.0") / x1);
  assertEqual(x1, x1 / amount_t("1.0"));
  assertEqual(amount_t("0.00812195"), amount_t("1.0") / x1);
  assertEqual(- x1, x1 / amount_t("-1.0"));
  assertEqual(- amount_t("0.00812195"), amount_t("-1.0") / x1);
  assertEqual(amount_t("0.269736842105"), x1 / y1);
  assertEqual(amount_t("3.707317073170"), y1 / x1);
  assertEqual(amount_t("0.269736842105"), x1 / amount_t("456.456"));
  assertEqual(amount_t("3.707317073170"), amount_t("456.456") / x1);

  x1 /= amount_t("456.456");
  assertEqual(amount_t("0.269736842105"), x1);
  x1 /= amount_t("456.456");
  assertEqual(amount_t("0.0005909372252856792330476541"), x1);
  x1 /= 456L;
  assertEqual(amount_t("0.00000129591496773175270405187302631578947368421052631578947368421"), x1);

  amount_t x4("1234567891234567.89123456789");
  amount_t y4("56.789");

  assertEqual(amount_t("1.0"), x4 / x4);
  assertEqual(amount_t("21739560323910.7554497273748437197344556164"),
	      x4 / y4);
}

// round
// conversion
// truth tests
// test for real zero
// comparison operators
// sign check
// abs
// reduce
// printing to a string buffer
