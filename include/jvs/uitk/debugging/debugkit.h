
#if !defined (JVS_DEBUG_DEBUGKIT_H_)
#define JVS_DEBUG_DEBUGKIT_H_

#if defined (DEBUG)
#define USE_DEBUGKIT
#endif

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <typeinfo>

#include "jvs/uitk/base/string.h"

#if defined JVS_WINDOWS
#	if !defined (WIN32_LEAN_AND_MEAN)
#		define WIN32_LEAN_AND_MEAN
#		include <Windows.h>
#		undef WIN32_LEAN_AND_MEAN
#	else
#		include <Windows.h>
#	endif
#endif

namespace jvs
{
namespace debug
{

static bool Win32UseConsole = false;
static std::string LogFile = "";
static std::stack<std::string> CallStack = std::stack<std::string>();

#if defined USE_DEBUGKIT
class DebugStream : public std::ostream
{
private:
  class DebugStreamBuf : public std::stringbuf
  {
  private:
    std::string logFile_;

  public:
    DebugStreamBuf(void)
    {
    }

    ~DebugStreamBuf()
    {
      std::stringbuf::pubsync();
    }

    int sync()
    {
#if defined USE_DEBUGKIT
#	if defined WIN32
      if (!LogFile.empty())
      {
        std::ofstream outfile(LogFile.c_str(), std::ios::app);
        outfile << std::stringbuf::str();
        std::stringbuf::str("");
        outfile.close();
        return 0;
      }

      if (!Win32UseConsole)
      {
        ::OutputDebugStringW(Widen(std::stringbuf::str()).c_str());
        std::stringbuf::str("");
        return 0;
      }

      HANDLE hStdErr = ::GetStdHandle(STD_ERROR_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO screenbuf;
      ::GetConsoleScreenBufferInfo(hStdErr, &screenbuf);
      ::SetConsoleTextAttribute(hStdErr, FOREGROUND_BLUE);
      std::cerr << std::stringbuf::str();
      ::SetConsoleTextAttribute(hStdErr, screenbuf.wAttributes);
      std::stringbuf::str("");
      return !std::cerr;
#	else
      std::cerr << std::stringbuf::str();
      std::stringbuf::str("");
      return !std::cerr;
#	endif
#endif

      return !std::cerr;
    }
  };

public:
  DebugStream(void)
    : std::ostream(new DebugStreamBuf())
  {
  }

  ~DebugStream()
  {
    delete rdbuf();
  }
};

static DebugStream cdbg{};

class DebugOutputHelper
{
public:
  DebugOutputHelper(void)
  {

  }

  ~DebugOutputHelper(void)
  {
    jvs::debug::cdbg << std::endl;
  }

  template <typename ArgT>
  void operator()(const ArgT& object)
  {
    jvs::debug::cdbg << object;
  }

  template <typename ArgT, typename... OtherArgsT>
  void operator()(const ArgT& object, OtherArgsT... otherArgs)
  {
    this->operator()(object);
    if (sizeof...(otherArgs) > 0)
    {
      this->operator()(otherArgs...);
    }
  }
};

class DebugTrace
{
public:
  static int Depth;

  DebugTrace(void)
  {
  }

  DebugTrace(const std::string& signature, const std::string& file,
    uint32_t line)
  {
    this->Trace(signature, file, line);;
  }

  void Trace(const std::string& signature, const std::string& file,
    uint32_t line)
  {
    cdbg << std::string(DebugTrace::Depth, '|') << "> " << signature
      << " (" << file << ":" << line << ")" << std::endl;
    DebugTrace::Depth++;
  }

  void Trace(const std::string& signature, const std::string& file,
    std::uint32_t line, std::stringstream& argStream)
  {
    cdbg << std::string(DebugTrace::Depth, '|') << "> " << signature << "("
      << argStream.str() << ") (" << file << ":" << line << ")"
      << std::endl;
  }

  template <typename ArgT, typename... ArgsT>
  void Trace(const std::string& signature, const std::string& file,
    std::uint32_t line, std::stringstream& argStream, ArgT arg, ArgsT... args)
  {
    argStream << ", " << arg;
    this->Trace(signature, file, line, argStream, args...);
  }

  template <typename ArgT, typename... ArgsT>
  void Trace(const std::string& signature, const std::string& file,
    std::uint32_t line, ArgT arg, ArgsT... args)
  {
    std::stringstream s;
    s << arg;
    this->Trace(signature, file, line, s, args...);
    DebugTrace::Depth++;
  }

  void TraceIf(bool condition, const std::string& signature, const std::string& file,
    uint32_t line)
  {
    if (condition)
    {
      this->Trace(signature, file, line);
    }
  }

  void TraceIf(bool condition, const std::string& signature,
    const std::string& file,
    std::uint32_t line, std::stringstream& argStream)
  {
    if (condition)
    {
      this->Trace(signature, file, line, argStream);
    }
  }

  template <typename ArgT, typename... ArgsT>
  void TraceIf(bool condition, const std::string& signature,
    const std::string& file,
    std::uint32_t line, std::stringstream& argStream, ArgT arg, ArgsT... args)
  {
    if (condition)
    {
      this->Trace(signature, file, line, argStream, args...);
    }
  }

  template <typename ArgT, typename... ArgsT>
  void TraceIf(bool condition, const std::string& signature,
    const std::string& file,
    std::uint32_t line, ArgT arg, ArgsT... args)
  {
    if (condition)
    {
      this->Trace(signature, file, line, arg, args...);
    }
  }

  ~DebugTrace(void)
  {
    --DebugTrace::Depth;
  }
};

int DebugTrace::Depth = 0;

std::string ErrorToMessage(DWORD errCode)
{
  wchar_t* pMsg = nullptr;
  ::FormatMessageW(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |
    FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,
    errCode,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    reinterpret_cast<wchar_t*>(&pMsg),
    1,
    NULL);
  std::string ret(Narrow(pMsg));
  ::LocalFree(pMsg);
  return ret;
}

void Break(void)
{
  ::DebugBreak();
}

#endif

} // namespace debug
} // namespace jvs


#if defined (USE_DEBUGKIT)
# define DBGOUT(...) \
    jvs::debug::DebugOutputHelper()( \
    std::string(jvs::debug::DebugTrace::Depth, '|'), "  ", __VA_ARGS__)

# define BREAK_IF(condition) \
    if (condition) { ::DebugBreak(); }

# if !defined (DISABLE_TRACE)
#   define TRACEIN_IF(condition) \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.TraceIf(condition, __FUNCTION__, __FILE__, \
        __LINE__);

#   define TRACEIN \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.Trace(__FUNCTION__, __FILE__, __LINE__);

#   define TRACEIN_THIS_IF(condition) \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.TraceIf(condition, \
        (typeid(*this).name() + \
        std::string(" - ") + \
        std::string(__FUNCTION__)), __FILE__, __LINE__)

#   define TRACEIN_THIS \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.Trace((typeid(*this).name() + \
        std::string(" - ") + \
        std::string(__FUNCTION__)), __FILE__, __LINE__)

#   define TRACEIN_ARGS_IF(condition, ...) \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.TraceIf(condition, __FUNCTION__, __FILE__, \
        __LINE__, __VA_ARGS__)

#   define TRACEIN_ARGS(...) \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.Trace(__FUNCTION__, __FILE__, __LINE__, \
        __VA_ARGS__)

#   define TRACEIN_THIS_ARGS_IF(condition, ...) \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.TraceIf(condition, \
        (typeid(*this).name() + \
        std::string(" - ") + \
        std::string(__FUNCTION__)), __FILE__, __LINE__, __VA_ARGS__)

#   define TRACEIN_THIS_ARGS(...) \
      jvs::debug::DebugTrace dk__trace{}; \
      dk__trace.Trace((typeid(*this).name() + \
        std::string(" - ") + \
        std::string(__FUNCTION__)), __FILE__, __LINE__, __VA_ARGS__)

#   define RETURN_TRACE(retval) \
      auto dk__ret = retval; \
      DBGOUT("[Return: ", dk__ret, "]"); \
      return dk__ret;

#   define RETURN_TRACE_IF(condition, retval) \
      auto dk__ret = retval; \
      if (condition) \
      { \
        DBGOUT("[Return: ", dk__ret, "]"); \
      } \
      return dk__ret;
# else
#   define TRACEIN
#   define TRACEIN_IF(condition)
#   define TRACEIN_THIS
#   define TRACEIN_THIS_IF(condition)
#   define TRACEIN_ARGS(...)
#   define TRACEIN_ARGS_IF(condition, ...)
#   define TRACEIN_THIS_ARGS(...)
#   define TRACEIN_THIS_ARGS_IF(condition, ...)
#   define RETURN_TRACE(retval) return retval
#   define RETURN_TRACE_IF(condition, retval) return retval
# endif
#else
# define TRACEIN
# define TRACEIN_IF(condition)
# define TRACEIN_THIS
# define TRACEIN_THIS_IF(condition)
# define TRACEIN_ARGS(...)
# define TRACEIN_ARGS_IF(condition, ...)
# define TRACEIN_THIS_ARGS(...)
# define TRACEIN_THIS_ARGS_IF(condition, ...)
# define DBGOUT(...)
# define RETURN_TRACE(retval) return retval
# define RETURN_TRACE_IF(condition, retval) return retval
# define BREAK_IF(condition)
#endif

#endif
