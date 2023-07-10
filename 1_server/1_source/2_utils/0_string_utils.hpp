//字符串操作类
#pragma once 
#include <spdlog/fmt/fmt.h>
#include <string>
#include <vector>

#define MAX_MSG_LEN 1024
class string_utils
{
public:
    template<typename... Args>
    static char* format_to(char* buffer, const char* fmt, const Args& ...args)
    {
        char* s = fmt::format_to(buffer, fmt, args...);
        s[0] = '\0';
        return s;
    }
    template<typename... Args>
    static std::string format(const char* fmt, const Args& ...args)
    {
        std::string ret = fmt::format(fmt, args...);
        return ret;
    }

	
	static size_t strncpy(char* dest, const char* src, size_t len = 0)
	{
		if (dest == nullptr || src == nullptr)
			return -1;
		len = (len == 0) ? strlen(src) : len;
		memcpy(dest, src, len);
		dest[len] = '\0';
		return len;
	}

};