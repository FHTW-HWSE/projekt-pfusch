#pragma once

#include <stdlib.h>
#include <errno.h>
#include <string>
#include <ctime>

#include "result.hpp"
#include "uuid.hpp"

namespace Helper
{
	auto str_to_int_strict(const std::string &str) noexcept -> cpp::result<int, std::errc>;

	auto str_to_int(const std::string &str) noexcept -> cpp::result<int, std::errc>;

	auto str_to_uuid(const std::string &str) noexcept -> cpp::result<uuids::uuid, std::errc>;

	std::string id_to_string(const uuids::uuid &id);

	std::string tm_to_Ymd(const std::tm &tm);

	std::tm Ymd_to_tm(const std::string &str);

	std::string time_t_to_string(const time_t &time);

	time_t string_to_time_t(const std::string str);

	time_t get_time_now();

	std::string time_t_to_readable_string(const time_t &time);
}