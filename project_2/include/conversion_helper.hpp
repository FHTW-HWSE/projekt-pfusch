#pragma once

#include <stdlib.h>
#include <errno.h>
#include <string>

#include "result.hpp"
#include "uuid.hpp"

namespace Helper
{
	auto str_to_int_strict(const std::string &str) noexcept -> cpp::result<int, std::errc>;

	auto str_to_int(const std::string &str) noexcept -> cpp::result<int, std::errc>;

	auto str_to_uuid(const std::string &str) noexcept -> cpp::result<uuids::uuid, std::errc>;

	std::string id_to_string(const uuids::uuid &id);
}