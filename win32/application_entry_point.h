#if !defined (INCLUDE_GUARD_H_)
#define INCLUDE_GUARD_H_

#if defined (_MSC_VER)
#pragma once
#endif

#include <vector>
#include <Windows.h>
#include <jvs/base/string.h>

namespace jvs
{
typedef const std::vector<jvs::String>& ArgList;
}

int Main(jvs::ArgList args);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCommandLine, int nShowCmd)
{
  int numArgs = 0;
  auto commandLineArgs = jvs::String(::GetCommandLine());
  std::vector<jvs::String> args;
  auto argList = ::CommandLineToArgvW(commandLineArgs.c_str(), &numArgs);
  for (int i = 0; i < numArgs; ++i)
  {
    args.push_back(jvs::String(argList[i]));
  }

  return Main(args);

}

#endif