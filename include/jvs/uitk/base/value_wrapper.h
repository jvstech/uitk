#if !defined (JVS_BASE_VALUE_WRAPPER_H_)
#define JVS_BASE_VALUE_WRAPPER_H_

namespace jvs
{

template <typename WrappedT>
class ValueWrapper
{
public:
  // typedefs
  typedef WrappedT WrappedType;
  typedef ValueWrapper<WrappedType> ValueWrapperType;

public:
  virtual WrappedType GetValue(void) const = 0;

  operator WrappedType(void) const
  {
    return this->GetValue();
  }

  virtual bool operator==(WrappedType item)
  {
    return (this->GetValue() == item);
  }

  virtual bool operator==(const ValueWrapper<WrappedType>& item)
  {
    return (this->GetValue() == item.GetValue());
  }

  virtual bool operator!=(WrappedType item)
  {
    return (!(this->GetValue() == item));
  }

  virtual bool operator!=(const ValueWrapperType& item)
  {
    return (!(this->GetValue() == item.GetValue()));
  }

  virtual bool operator<(WrappedType item)
  {
    return (this->GetValue() < item);
  }

  virtual bool operator<(const ValueWrapperType& item)
  {
    return (this->GetValue() < item.GetValue());
  }
}; // class ValueWrapper

template <typename WrappedT>
class HostedValueWrapper : public ValueWrapper<WrappedT>
{
public:
  // typedefs
  typedef HostedValueWrapper<WrappedType> HostedValueWrapperType;

private:
  WrappedType value_;

public:

  HostedValueWrapper(void)
    : value_()
  {
  }

  HostedValueWrapper(const HostedValueWrapper& src)
    : value_(src.value_)
  {
  }

  HostedValueWrapper(HostedValueWrapper&& src)
    : value_(std::move(src.value_))
  {
  }

  HostedValueWrapper(WrappedType value)
    : value_(value)
  {
  }

  virtual ~HostedValueWrapper(void)
  {
  }

  virtual WrappedType GetValue(void) const override
  {
    return this->value_;
  }

protected:
  HostedValueWrapper& SetValue(WrappedType new_value_value)
  {
    this->value_ = new_value_value;
    return *this;
  }
}; // class HostedValueWrapper

} // namespace jvs

#endif
