#include "config.h"

#include "test/src/test_encryption_config.h"

#include <torrent/runtime/encryption_policy.h>

#include "encryption_config.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestEncryptionConfig);

void
TestEncryptionConfig::test_default_policy() {
  const auto policy = encryption_config::default_policy();

  CPPUNIT_ASSERT(policy.handshake == encryption_config::Policy::Mode::allow);
  CPPUNIT_ASSERT(policy.stream == encryption_config::Policy::Mode::allow);

  CPPUNIT_ASSERT_EQUAL(std::string("handshake=allow stream=allow"),
                       encryption_config::summary_string(policy));
}

void
TestEncryptionConfig::test_granular_round_trip() {
  auto round_trip_handshake = [](const std::string& value) {
    encryption_config::Policy policy;
    encryption_config::apply_mode_value(policy, &encryption_config::Policy::handshake, value);
    return encryption_config::mode_to_string(policy.handshake);
  };

  CPPUNIT_ASSERT_EQUAL(std::string("deny"), round_trip_handshake("deny"));
  CPPUNIT_ASSERT_EQUAL(std::string("allow"), round_trip_handshake("allow"));
  CPPUNIT_ASSERT_EQUAL(std::string("prefer"), round_trip_handshake("prefer"));
  CPPUNIT_ASSERT_EQUAL(std::string("require"), round_trip_handshake("require"));

  auto round_trip_stream = [](const std::string& value) {
    encryption_config::Policy policy;
    encryption_config::apply_mode_value(policy, &encryption_config::Policy::stream, value);
    return encryption_config::mode_to_string(policy.stream);
  };

  CPPUNIT_ASSERT_EQUAL(std::string("deny"), round_trip_stream("deny"));
  CPPUNIT_ASSERT_EQUAL(std::string("allow"), round_trip_stream("allow"));
  CPPUNIT_ASSERT_EQUAL(std::string("prefer"), round_trip_stream("prefer"));
  CPPUNIT_ASSERT_EQUAL(std::string("require"), round_trip_stream("require"));
}