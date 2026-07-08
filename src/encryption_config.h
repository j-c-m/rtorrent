#ifndef RTORRENT_ENCRYPTION_CONFIG_H
#define RTORRENT_ENCRYPTION_CONFIG_H

#include <cstdint>
#include <string>

#include <torrent/runtime/encryption_policy.h>
#include <torrent/object.h>

namespace encryption_config {

using Policy = torrent::EncryptionPolicy;

Policy              default_policy();

std::string         mode_to_string(Policy::Mode value);
void                apply_mode_value(Policy& policy, Policy::Mode Policy::*field, const std::string& value);

std::string         summary_string(const Policy& policy);

void                apply_policy(const Policy& policy);
torrent::Object     apply_handshake_set(const std::string& value);
torrent::Object     apply_stream_set(const std::string& value);

void                initialize_commands();

} // namespace encryption_config

#endif