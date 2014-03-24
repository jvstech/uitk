
#if !defined (JVS_UITK_WIN32_LABEL_H_)
#define JVS_UITK_WIN32_LABEL_H_

#include "color.h"
#include "component.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class Label : public Component
{
private:
  bool autoSize_;

public:

  static Color DefaultBackgroundColor;
  static Color DefaultForegroundColor;

  Label(void) 
    : Component(), 
    autoSize_(true)
  {
    this->set_background_color(Label::DefaultBackgroundColor);
    this->set_foreground_color(Label::DefaultForegroundColor);
    this->Initialize();
  }

  virtual ~Label(void)
  {
  }

  virtual bool get_AutoSize(void) const
  {
    return autoSize_;
  }

  virtual Label& set_AutoSize(bool value)
  {
    this->autoSize_ = value;
    if (Component::IsCreated() && this->autoSize_)
    {
      return this->Pack();
    }

    return *this;
  }

  virtual Label& Pack(int paddingRight = 0, int paddingBottom = 0) override
  {
    if (Component::IsCreated())
    {
      Graphics c(*this);
      Rectangle textSize(c.MeasureText(this->text(), this->font()));
      // Rectangle textSize(c.MeasureText(this->text()));
      c.Reset();
      this->set_size(textSize.width(), textSize.height());
    }

    return *this;
  }

  virtual Label& set_text(const String& text)
  {
    Component::set_text(text);
    if (this->autoSize_)
    {
      return this->Pack();
    }

    return *this;
  } // set_text */

protected:

  virtual ComponentCreationParameters GetCreationParameters(void) const override
  {
    auto ret = Component::GetCreationParameters();
    ret.BaseClassName = "Static";
    return ret;
  }

  virtual void OnCreated(void)
  {
    if (this->autoSize_)
    {
      this->Pack();
    }
  }

private:
  // irtual LRESULT WmWindowPosChanged(LRESULT defaultResult, MSG& msg, 
  //	bool& handled)
  // 
  //	auto ret = Component::WmWindowPosChanged(defaultResult, msg, handled);
  //	auto* wp = reinterpret_cast<const WINDOWPOS*>(msg.lParam);
  //	if ((wp->flags & SWP_HIDEWINDOW) == 0)
  //	{
  //		if ((wp->flags & SWP_SHOWWINDOW) != 0)
  //		{
  //			// label is being displayed
  //			if (this->autoSize_)
  //			{
  //				this->Pack();
  //			}
  //		}
  //	}

  //	return ret;
  // 

}; /* class Label */

// static initializers
Color Label::DefaultBackgroundColor = ::GetSysColor(COLOR_3DFACE);
Color Label::DefaultForegroundColor = ::GetSysColor(COLOR_WINDOWTEXT);

// / used to quickly place a label on a control without caring about
// / if it changes or not
// truct StaticLabel : Directive
// 
//	jvs::String Text;
//	Point Location;
//
//	StaticLabel(const std::string& text, const Point::CoordinateType x,
//		const Point::CoordinateType y)
//		: Text(text.begin(), text.end()),
//		Location(x, y)
//	{
//	}
//
//	StaticLabel(const std::wstring& text, const Point::CoordinateType x,
//		const Point::CoordinateType y)
//		: Text(text.begin(), text.end()),
//		Location(x, y)
//	{
//	}
//
//	StaticLabel(const std::string& text, const Point& location)
//		: Text(text.begin(), text.end()),
//		Location(location)
//	{
//	}
//
//	StaticLabel(const std::wstring& text, const Point& location)
//		: Text(text.begin(), text.end()),
//		Location(location)
//	{
//	}
//
//	void operator()(Component& c)
//	{
//		Label* label = new Label();
//		label
//			->set_AutoSize(true)
//			.set_text(Text)
//			.set_Location(Location.x, Location.y)
//			;
//
//		c.Add(label);
//	} // operator() */
// ;

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif