#if !defined (JVS_BASE_ENVIRONMENT_H_)
#define JVS_BASE_ENVIRONMENT_H_

#include <cstdlib>
#include <map>
#include <string>
#include <sstream>

#if !defined (_WIN32)
#include <unistd.h>
extern "C"
{
  extern char** environ;
}
#else
#include <windows.h>
#endif

namespace jvs
{

struct Environment
{
  using EnvironmentMap = std::map<std::string, std::string>;
  static EnvironmentMap Variables;

private:
  static EnvironmentMap loadVariables(void)
  {
    EnvironmentMap ret;
    int count = 0;
    
    while (environ[count] != nullptr)
    {
      std::stringstream key;
      std::stringstream value;
      char* i = environ[count];

      for (; *i != '='; ++i)
      {
        key << *i;
      }

      ++i;
      for (; *i != '\0'; ++i)
      {
        value << *i;
      }

      ret[key.str()] = value.str();
      ++count;
    }

    return std::move(ret);
  }
};

Environment::EnvironmentMap Environment::Variables =
  Environment::loadVariables();

} // namespace jvs

#endif