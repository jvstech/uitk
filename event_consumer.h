
#if !defined (JVS_UITK_EVENT_CONSUMER_H_)
#define JVS_UITK_EVENT_CONSUMER_H_

#include <jvs/uitk/event_arguments.h>

namespace jvs
{

template <typename ProviderT, typename ArgumentT>
class EventProvider;

template <typename ProviderT, typename ArgumentT>
class EventConsumer
{
public:

  virtual ~EventConsumer()
  {
  }

  template <typename EventProviderT>
  EventConsumer<ProviderT, ArgumentT>& AddTo(EventProviderT& eventProvider)
  {
    eventProvider.AddEventConsumer(*this);
    return *this;
  }

  // must be equality comparable
  virtual bool operator==(const EventConsumer<ProviderT, ArgumentT>&) = 0;
  
private:

  friend class EventProvider<ProviderT, ArgumentT>;

  virtual void RaiseEvent(ProviderT&, ArgumentT&) = 0;

  virtual void OnAttached(ProviderT&)
  {
    // to be overridden only if needed
  }
};

}

#endif