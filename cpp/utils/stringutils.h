#pragma once

#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

std::string string_replace(std::string subject, const std::string& search, const std::string& replace);
std::vector<std::string> string_split(const std::string& text, const std::string& delims = " \t\n\v\f\r,");
std::vector<std::string> string_split_lines(const std::string& text);

std::string& string_left_trim(std::string& s, const char* t = " \t\n\r\f\v");
std::string& string_right_trim(std::string& s, const char* t = " \t\n\r\f\v");
std::string& string_trim(std::string& s, const char* t = " \t\n\r\f\v");

inline std::wstring string_to_wstring(const std::string& str) { return std::wstring(str.begin(), str.end()); }

std::string string_to_lower(const std::string& str);

unsigned int murmur_hash_inverse(unsigned int h, unsigned int seed);
uint64_t murmur_hash_64(const void * key, uint32_t len, uint64_t seed);
uint32_t murmur_hash(const void * key, int len, uint32_t seed);

template<typename T>
std::string string_from_value(const T &t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

template<typename T>
std::string string_from_value(const T &t, int precision) {
    std::ostringstream oss;
    oss << std::setprecision(precision) << t;
    return oss.str();
}
template<typename T>
T string_to_value(const std::string& s) {
    std::istringstream stream(s);
    T t;
    stream >> t;
    return t;
}

