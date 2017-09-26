#if !defined (INCLUDE_GUARD_H_)
#define INCLUDE_GUARD_H_

#if defined (_MSC_VER)
#pragma once
#endif

#include <string>
#include <vector>
#include <Windows.h>
#include "jvs/base/string.h"

namespace jvs
{
using ArgList = const std::vector<std::string>&;
}

int Main(jvs::ArgList args);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCommandLine, int nShowCmd)
{
  int numArgs = 0;
  auto commandLineArgs = std::wstring(::GetCommandLineW());
  std::vector<std::string> args{};
  auto argList = ::CommandLineToArgvW(commandLineArgs.c_str(), &numArgs);
  args.reserve(numArgs);
  for (int i = 0; i < numArgs; ++i)
  {
    args.push_back(jvs::Narrow(argList[i]));
  }

  return Main(args);

}

#endif