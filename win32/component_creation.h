
#if !defined (JVS_UITK_WIN32_COMPONENT_CREATION_H_)
#define JVS_UITK_WIN32_COMPONENT_CREATION_H_

#include <mutex>

#include <Windows.h>

#include "component_creation_parameters.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

// assists in the registration and creation of components (classes)
class ComponentCreation
{
public:
  static std::mutex CriticalMutex;

  static ATOM Register(ComponentCreationParameters& p)
  {
    if (p.atom() == 0)
    {
      if (!CriticalMutex.try_lock())
      {

      }
    }
  }
};

}
}
}

#endif