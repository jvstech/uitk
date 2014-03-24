
#if !defined (JVS_UITK_WIN32_WIN32ERROR_H_)
#define JVS_UITK_WIN32_WIN32ERROR_H_

#include <stdexcept>
#include <Windows.h>
#include <jvs/base/types.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

class Win32Error : public std::runtime_error
{
private:
	DWORD errCode_;

public:
	Win32Error(DWORD errCode)
		: std::runtime_error(Win32Error::getMessageFromCode(errCode).AsAscii()),
		errCode_(errCode)
	{
	}

	virtual ~Win32Error(void)
	{
	} // dtor */

private:
	static String getMessageFromCode(DWORD errCode) 
	{
		String ret;
		LPTSTR errorText = nullptr;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER 
			| FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
			errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			reinterpret_cast<LPTSTR>(&errorText), 0, nullptr);
		if (nullptr != errorText)
		{
			ret = errorText;
			::LocalFree(errorText);
			errorText = nullptr;
		} // if (nullptr != errorText) */
		else
		{
			ret = String("Unknown error (Code: 0x") 
				+ String::GetHex(errCode) + String(")");
		} // else [if (nullptr != errorText)] */

		return ret;
	} // getMessageFromCode */


}; /* class Win32Error */

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif