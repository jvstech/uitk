#if !defined (JVS_STRING_H_)
#define JVS_STRING_H_

#include <codecvt>
#include <locale>
#include <string>

namespace jvs
{

std::string Narrow(const std::wstring& wstr)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
  return convert.to_bytes(wstr);
}
std::wstring Widen(const std::string& str)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
  return convert.from_bytes(str);
}

template <typename NumberT>
static std::string GetHex(NumberT number)
{
  std::stringstream ret;
  ret << std::hex << number;
  return ret.str();
}

} // namespace jvs 

#endif
