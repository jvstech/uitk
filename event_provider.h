
#if !defined (JVS_UITK_EVENT_PROVIDER_H_)
#define JVS_UITK_EVENT_PROVIDER_H_

#include <set>
#include <algorithm>
#include <initializer_list>

#include <jvs/uitk/event_consumer.h>
#include "null_deleter.h"

namespace jvs
{

template <typename ProviderT, typename ArgumentT>
class EventProvider
{
public:
  typedef ProviderT ProviderType;
  typedef ArgumentT ArgumentType;
  typedef EventConsumer<ProviderT, ArgumentT> ConsumerType;

private:
  // Implemented as a set<shared_ptr<>> because 1) it's usually not a good idea 
  // to put naked pointers in STL containers, 2) it makes it easier for the 
  // event consumers to be compared, and 3) we don't always take ownership of 
  // the added event consumers.
  std::set<std::shared_ptr<ConsumerType>> consumers_;

public:

  virtual ~EventProvider()
  {
  }

  virtual EventProvider<ProviderT, ArgumentType>& AddEventConsumer
    (ConsumerType& eventConsumer)
  {
    std::shared_ptr<ConsumerType> c(&eventConsumer, jvs::NullDeleter());
    this->consumers_.insert(c);
    eventConsumer.OnAttached(this->GetProvider());
    return *this;
  }

  virtual EventProvider<ProviderT, ArgumentType>& AddEventConsumer
    (std::shared_ptr<ConsumerType>& eventConsumer)
  {
    this->consumers_.insert(eventConsumer);
    eventConsumer->OnAttached(this->GetProvider());
    return *this;
  }

  virtual EventProvider<ProviderT, ArgumentType>& RemoveEventConsumer
    (std::shared_ptr<ConsumerType>& eventConsumer)
  {
    auto consumer = this->consumers_.find(eventConsumer);
    if (consumer != this->consumers_.end())
    {
      this->consumers_.erase(consumer);
    }

    return *this;
  }

  EventProvider& operator<<(std::shared_ptr<
    EventConsumer<ProviderT, ArgumentType>
  > eventConsumer)
  {
    this->AddEventConsumer(eventConsumer);
    return *this;
  }

protected:
  virtual typename std::vector<ConsumerType>::size_type GetConsumerCount() 
    const
  {
    return this->consumers_.size();
  }

  virtual void ProcessEvent(ProviderType& provider, ArgumentType& args)
  {
    for (auto& consumer : this->consumers_)
    {
      consumer->RaiseEvent(provider, args);
    }
  }

  virtual ProviderType& GetProvider() = 0;
  
};

}

#endif