
#if !defined _TEXTBOX_H_INCLUDED
#define _TEXTBOX_H_INCLUDED

#include "component.h"

namespace jvs
{
namespace uitk
{
namespace win32
{
  class TextBox :	public Component
  {
  public:

    TextBox(void)
      : Component()
    {
      this->Initialize();
      this->set_size(100, this->font().GetHeight() + 3);
    }

    virtual ~TextBox(void)
    {
    }

  protected:

    virtual void OnRegistering(ComponentCreationParameters& createParams)
    {
      createParams.BaseClassName = WC_EDIT;
      createParams.WindowStyles |= ES_AUTOHSCROLL | ES_AUTOVSCROLL; 
      createParams.WindowExStyles |= WS_EX_CLIENTEDGE;
      createParams.BackgroundBrush = this->background_brush();
    }

  };

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif