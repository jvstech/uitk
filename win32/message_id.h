
#if !defined (JVS_UITK_WIN32_MESSAGE_ID_H_)
#define JVS_UITK_WIN32_MESSAGE_ID_H_

#include <windows.h>
#include <jvs/base/types.h>
#include <jvs/base/value_wrapper.h>

namespace jvs { namespace uitk { namespace win32
{

class MessageId : public virtual ValueWrapper<UINT>
{
private:
  int message_id_;
  String message_name_;

public:

  MessageId(void)
    : message_id_(WM_USER),
    message_name_("WM_USER")
  {
  }

  MessageId(int message, const String& messageName)
    : message_id_(message),
    message_name_(messageName)
  {
  }

  MessageId(const MessageId& src)
    : message_id_(src.message_id_),
    message_name_(src.message_name_)
  {
  }

  virtual ~MessageId(void)
  {
  }

  UINT get_Value(void) const
  {
    return this->message_id_;
  }

  const String& get_Name(void) const
  {
    return this->message_name_;
  }

  operator String(void) const
  {
    return this->message_name_;
  }

};

} // namespace win32
} // namespace uitk
} // namespace jvs

// used to generate a MessageId with name from just the WM_ macro
#define MsgId(message) jvs::uitk::win32::MessageId(message, #message)

#endif