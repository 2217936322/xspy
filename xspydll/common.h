#pragma once
#include <string>

//see afxtrace.cpp ������һ�ָ��ݺ���WIN64_XXXX��û�ж��壬���л���ķ������൱�ں��ﶨ���
// from http://stackoverflow.com/questions/2664703/macros-in-macros-c
#include <boost/preprocessor/control/if.hpp>
#define PP_CHECK_N(x, n, ...) n
#define PP_CHECK(...) PP_CHECK_N(__VA_ARGS__, 0,)
#ifdef _WIN64
#define WIN64_XXXX ~, 1,
#endif
#define FAKE_POINTER_FORMAT \
    BOOST_PP_IF(PP_CHECK(WIN64_XXXX), "%#p", "0x%08x")
// ������ֱָ������%p����Ż��0����LONG_PTR����ָ�����ͣ������ʱ��ǰ�治���0

#define BOOST_FORMAT boost::str(boost::format

std::string GetMods(LPCVOID addr);
std::string GetCodes(PVOID addr);