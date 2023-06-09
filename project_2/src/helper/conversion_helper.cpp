#include <stdlib.h>
#include <errno.h>
#include <string>
#include <sstream>
#include <chrono>

#include "conversion_helper.hpp"

#include "result.hpp"
#include "uuid.hpp"

namespace Helper
{
	static auto str_to_int_internal(const char *first_c, char **last_c) noexcept -> cpp::result<int, std::errc>
	{
		errno = 0;
		const auto result = std::strtol(first_c, last_c, 10);

		if (errno != 0)
		{
			// Returns an error value
			return cpp::fail(static_cast<std::errc>(errno));
		}

		return result;
	}

	auto str_to_int_strict(const std::string &str) noexcept -> cpp::result<int, std::errc>
	{
		auto *last_entry = static_cast<char *>(nullptr);
		auto *first_entry = str.c_str();

		auto result = str_to_int_internal(first_entry, &last_entry);

		if(result.has_error()){
			return cpp::fail(result.error());
		}

		if (*last_entry != '\0')
		{
			return cpp::fail(static_cast<std::errc>(EINVAL));
		}

		// Returns a value
		return result.value();
	}

	auto str_to_int(const std::string &str) noexcept -> cpp::result<int, std::errc>
	{
		auto *last_entry = static_cast<char *>(nullptr);
		auto *first_entry = str.c_str();

		return str_to_int_internal(first_entry, &last_entry);
	}

	auto str_to_uuid(const std::string &str) noexcept -> cpp::result<uuids::uuid, std::errc>
	{
		auto *last_entry = static_cast<char *>(nullptr);
		auto *first_entry = str.c_str();

		errno = 0;

		auto id_result = uuids::uuid::from_string(str);

		if (id_result.has_value())
		{
			return id_result.value();
		}
		else
		{
			return cpp::fail(static_cast<std::errc>(EINVAL));
		}
	}

	std::string id_to_string(const uuids::uuid &id)
	{
		return uuids::to_string(id);
	}

	std::string tm_to_Ymd(const std::tm &tm){
		char buffer[15];
        size_t format = strftime(buffer, 15, "%Y-%m-%d", &tm);

		return std::string(buffer);
	}

	std::tm Ymd_to_tm(const std::string &str){
		struct tm tm;
		const char* c_str = str.c_str();
		auto last = strptime(c_str, "%Y-%m-%d", &tm);
		return tm;
	}

	std::string time_t_to_string(const time_t &time)
	{
		std::ostringstream oss;
		oss << time;
		return oss.str();
	}

	std::string time_t_to_readable_string(const time_t &time)
	{
		if(time == 0)
		{
			return "open";
		}

		std::tm local = *std::localtime(&time);

		char buffer[255];
        size_t format = strftime(buffer, 15, "%Y-%m-%d %H:%M", &local);

		return buffer;

	}

	time_t string_to_time_t(const std::string str)
	{
		std::istringstream stream( str );
		time_t t;
		stream >> t;
		return t;
	}

	time_t get_time_now()
	{
		auto now = std::chrono::system_clock::now();
		return std::chrono::system_clock::to_time_t(now);
	}

}