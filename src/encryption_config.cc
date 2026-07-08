#include "config.h"

#include "encryption_config.h"

#include <torrent/runtime/network_config.h>
#include <torrent/runtime/runtime.h>
#include <torrent/utils/option_strings.h>

#include "command_helpers.h"
#include "globals.h"

namespace encryption_config {
namespace {

Policy
current_policy() {
  return torrent::runtime::network_config()->encryption_policy();
}

} // namespace

Policy
default_policy() {
  Policy policy;
  policy.handshake = Policy::Mode::allow;
  policy.stream    = Policy::Mode::allow;
  return policy;
}

std::string
mode_to_string(Policy::Mode value) {
  return torrent::option_to_str_or_throw(torrent::OPTION_ENCRYPTION_MODE,
                                         static_cast<unsigned int>(value));
}

void
apply_mode_value(Policy& policy, Policy::Mode Policy::*field, const std::string& value) {
  policy.*field = static_cast<Policy::Mode>(
    torrent::option_find_string_str(torrent::OPTION_ENCRYPTION_MODE, value));
}

std::string
summary_string(const Policy& policy) {
  return "handshake=" + mode_to_string(policy.handshake)
       + " stream=" + mode_to_string(policy.stream);
}

void
apply_policy(const Policy& policy) {
  torrent::runtime::network_config()->set_encryption_policy(policy);
}

torrent::Object
apply_handshake_set(const std::string& value) {
  Policy policy = current_policy();
  apply_mode_value(policy, &Policy::handshake, value);
  apply_policy(policy);
  return torrent::Object();
}

torrent::Object
apply_stream_set(const std::string& value) {
  Policy policy = current_policy();
  apply_mode_value(policy, &Policy::stream, value);
  apply_policy(policy);
  return torrent::Object();
}

void
initialize_commands() {
  apply_policy(default_policy());

  CMD2_ANY("protocol.encryption", [](auto, auto) { return summary_string(current_policy()); });

  CMD2_ANY("protocol.encryption.handshake", [](auto, auto) { return mode_to_string(current_policy().handshake); });
  CMD2_ANY_STRING_V("protocol.encryption.handshake.set", [](auto, auto& str) { return apply_handshake_set(str); });

  CMD2_ANY("protocol.encryption.stream", [](auto, auto) { return mode_to_string(current_policy().stream); });
  CMD2_ANY_STRING_V("protocol.encryption.stream.set", [](auto, auto& str) { return apply_stream_set(str); });

  rpc::rpc.mark_safe("protocol.encryption");
  rpc::rpc.mark_safe("protocol.encryption.handshake");
  rpc::rpc.mark_safe("protocol.encryption.handshake.set");
  rpc::rpc.mark_safe("protocol.encryption.stream");
  rpc::rpc.mark_safe("protocol.encryption.stream.set");
}

} // namespace encryption_config