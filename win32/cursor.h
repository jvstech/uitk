
#if !defined (JVS_UITK_WIN32_CURSOR_H_)
#define JVS_UITK_WIN32_CURSOR_H_

#include <Windows.h>

#include "jvs/uitk/base/string.h"
#include "jvs/uitk/base/value_wrapper.h"
#include "jvs/uitk/win32/types.h"

#include "cursor_type.h"

#include "jvs/uitk/debugging/debugkit.h"

namespace jvs
{
namespace uitk
{
namespace win32

{

class Cursor : public ValueWrapper<CursorHandle>
{
private:
  CursorType type_{CursorType::Default};
  std::string name_{};
  CursorHandle cursor_{nullptr};
  std::wstring resource_id_{};

public:
  
  static const Cursor Crosshair;
  static const Cursor Default;
  static const Cursor EastResize;
  static const Cursor Hand;
  static const Cursor Help;
  static const Cursor Move;
  static const Cursor No;
  static const Cursor NorthResize;
  static const Cursor NorthEastResize;
  static const Cursor NorthWestResize;
  static const Cursor SouthResize;
  static const Cursor SouthEastResize;
  static const Cursor SouthWestResize;
  static const Cursor Starting;
  static const Cursor Text;
  static const Cursor Up;
  static const Cursor WestResize;
  static const Cursor Wait;

  Cursor()
  {
    this->loadCursor();
  }

  Cursor(CursorType cursorType)
    : type_{cursorType}
  {
    if (this->type_ == CursorType::Custom)
    {
      this->type_ = CursorType::Default;
    }

    this->loadCursor();
  }

  Cursor(const std::string& name)
    : type_(CursorType::Custom),
    name_(name)
  {
    this->loadCursor();
  }

  Cursor(CursorHandle handle)
    : type_(CursorType::Default),
    cursor_(Cursor::copyHandle(handle))
  {
  }

  Cursor(const Cursor& cursor)
    : type_(cursor.type_),
    name_(cursor.name_),
    cursor_(Cursor::copyHandle(cursor.cursor_))
  {
    // TODO: handle custom created cursors in the future...
  }

  Cursor& operator= (const Cursor& src)
  {
    this->type_ = src.type_;
    this->name_ = src.name_;
    this->cursor_ = Cursor::copyHandle(src.cursor_);
    return *this;
  }

  CursorType type() const
  {
    return this->type_;
  }

  std::string name() const
  {
    if (this->type_ != CursorType::Custom)
    {
      return "";
    }

    return this->name_;
  }

  HCURSOR GetValue() const override
  {
    return this->cursor_;
  }

  const char* GetInternalResourceId() const
  {
    if (this->type_ != CursorType::Custom)
    {
      return jvs::Narrow(
        MAKEINTRESOURCEW(static_cast<int>(this->type_))).c_str();
    }

    return this->name_.c_str();
  }

  static Cursor FromResourceId(const std::string& resourceId)
  {

    if (resourceId.length() < sizeof(int))
    {
      return Cursor(resourceId);
    }

    int typeId = 0;
    std::memcpy(&typeId, &resourceId[0], sizeof(int));
    if (typeId == static_cast<int>(CursorType::Crosshair)
      || typeId == static_cast<int>(CursorType::Arrow)
      || typeId == static_cast<int>(CursorType::EastResize)
      || typeId == static_cast<int>(CursorType::Hand)
      || typeId == static_cast<int>(CursorType::Help)
      || typeId == static_cast<int>(CursorType::Move)
      || typeId == static_cast<int>(CursorType::No)
      || typeId == static_cast<int>(CursorType::NorthEastResize)
      || typeId == static_cast<int>(CursorType::NorthResize)
      || typeId == static_cast<int>(CursorType::NorthWestResize)
      || typeId == static_cast<int>(CursorType::Starting)
      || typeId == static_cast<int>(CursorType::Text)
      || typeId == static_cast<int>(CursorType::Up)
      || typeId == static_cast<int>(CursorType::Wait)
      )
    {
      return Cursor(static_cast<CursorType>(typeId));
    }
    
    return Cursor(resourceId);
  }

private:
  void loadCursor()
  {
    if (this->type_ != CursorType::Custom)
    {
      this->cursor_ = ::LoadCursorW(nullptr,
        MAKEINTRESOURCEW(static_cast<int>(this->type_)));
    }
    else
    {
      this->cursor_ = ::LoadCursorW(::GetModuleHandleW(nullptr),
        jvs::Widen(this->name_).c_str());
    }
  }

  static CursorHandle copyHandle(CursorHandle cursorHandle)
  {
    return static_cast<CursorHandle>(::CopyIcon(
      static_cast<IconHandle>(cursorHandle)));
  }

};

const Cursor Cursor::Crosshair = Cursor(CursorType::Crosshair);
const Cursor Cursor::Default = Cursor();
const Cursor Cursor::EastResize = Cursor(CursorType::EastResize);
const Cursor Cursor::Hand = Cursor(CursorType::Hand);
const Cursor Cursor::Help = Cursor(CursorType::Help);
const Cursor Cursor::Move = Cursor(CursorType::Move);
const Cursor Cursor::No = Cursor(CursorType::No);
const Cursor Cursor::NorthResize = Cursor(CursorType::NorthResize);
const Cursor Cursor::NorthEastResize = Cursor(CursorType::NorthEastResize);
const Cursor Cursor::NorthWestResize = Cursor(CursorType::NorthWestResize);
const Cursor Cursor::SouthResize = Cursor::NorthResize;
const Cursor Cursor::SouthEastResize = Cursor::NorthWestResize;
const Cursor Cursor::SouthWestResize = Cursor::NorthEastResize;
const Cursor Cursor::Starting = Cursor(CursorType::Starting);
const Cursor Cursor::Text = Cursor(CursorType::Text);
const Cursor Cursor::Up = Cursor(CursorType::Up);
const Cursor Cursor::WestResize = Cursor::EastResize;
const Cursor Cursor::Wait = Cursor(CursorType::Wait);

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif