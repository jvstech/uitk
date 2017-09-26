
#if !defined (JVS_UITK_WIN32_WIN32ERROR_H_)
#define JVS_UITK_WIN32_WIN32ERROR_H_

#include <stdexcept>
#include <Windows.h>
#include "jvs/uitk/win32/types.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class Win32Error : public std::runtime_error
{
private:
  DWord errCode_;

public:
  Win32Error(DWord errCode)
    : std::runtime_error(Win32Error::getMessageFromCode(errCode)),
		errCode_(errCode)
	{
	}

  virtual ~Win32Error()
	{
	}

private:
  static std::string getMessageFromCode(DWord errCode) 
	{
    std::string ret;
    wchar_t* errorText{nullptr};
    ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER 
			| FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
			errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
      reinterpret_cast<wchar_t*>(&errorText), 0, nullptr);
		if (nullptr != errorText)
		{
      ret = jvs::Narrow(errorText);
			::LocalFree(errorText);
			errorText = nullptr;
		}
		else
		{
      ret = std::string("Unknown error (Code: 0x")
        + jvs::GetHex(errCode) + std::string(")");
		}

		return ret;
	}
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif