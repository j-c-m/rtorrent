#include "test/helpers/test_fixture.h"

class TestEncryptionConfig : public test_fixture {
  CPPUNIT_TEST_SUITE(TestEncryptionConfig);
  CPPUNIT_TEST(test_default_policy);
  CPPUNIT_TEST(test_granular_round_trip);
  CPPUNIT_TEST_SUITE_END();

public:
  void test_default_policy();
  void test_granular_round_trip();
};