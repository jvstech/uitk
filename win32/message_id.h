#if !defined (JVS_UITK_WIN32_MESSAGE_ID_H_)
#define JVS_UITK_WIN32_MESSAGE_ID_H_

#include <windows.h>
#include "jvs/uitk/base/string.h"
#include "jvs/uitk/base/value_wrapper.h"

namespace jvs 
{
namespace uitk
{
namespace win32
{

class MessageId : public virtual ValueWrapper<UINT>
{
private:
  int id_;
  std::string name_;

public:

  MessageId()
    : id_(WM_USER),
    name_("WM_USER")
  {
  }

  MessageId(int message, const std::string& messageName)
    : id_(message),
    name_(messageName)
  {
  }

  MessageId(const MessageId& src)
    : id_(src.id_),
    name_(src.name_)
  {
  }

  virtual ~MessageId()
  {
  }

  UINT GetValue() const override
  {
    return this->id_;
  }

  const std::string& name() const
  {
    return this->name_;
  }

  operator std::string() const
  {
    return this->name_;
  }

};

} // namespace win32
} // namespace uitk
} // namespace jvs

// used to generate a MessageId with name from just the WM_ macro
#define MsgId(message) jvs::uitk::win32::MessageId(message, #message)

#endif