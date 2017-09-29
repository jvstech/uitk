
#if !defined (JVS_UITK_EVENT_ARGUMENTS_H_)
#define JVS_UITK_EVENT_ARGUMENTS_H_

namespace jvs
{

struct BasicEventArguments
{
  static const BasicEventArguments Empty;
};

template <typename ArgT>
class EventArguments : public BasicEventArguments
{
public:

  typedef ArgT ArgumentType;

  EventArguments(ArgT argument)
    : arg_(argument)
  {
  }

  virtual ~EventArguments()
  {
  }

  virtual ArgT get_Value() const
  {
    return this->arg_;
  }

  virtual void set_Value(ArgumentType value)
  {
    this->arg_ = value;
  }

private:
  ArgumentType arg_;
}; /* class EventArguments */

const BasicEventArguments BasicEventArguments::Empty = BasicEventArguments();
} // namespace jvs
#endif