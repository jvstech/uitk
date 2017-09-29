
#if !defined (JVS_UITK_WIN32_FOCUS_EVENT_ARGUMENTS_H_)
#define JVS_UITK_WIN32_FOCUS_EVENT_ARGUMENTS_H_

#include "component.h"
#include "jvs/uitk/event_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32

{

struct FocusEventArguments : BasicEventArguments
{

  Component* OppositeComponent;

  FocusEventArguments()
    : OppositeComponent(nullptr)
  {
  }

  FocusEventArguments(Component* oppositeComponent)
    : OppositeComponent(oppositeComponent)
  {
  }

  ~FocusEventArguments()
  {
  }
};

}}}

#endif