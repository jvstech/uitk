//  TODO: Move constructor/assignment operator
//  TODO: max/min sizes
//  TODO: ATL removal (custom thunks + CBT hook)
//  TODO: Drag-and-drop functionality
//  TODO: Flicker-free sizing (WmPaint handling all the drawing and text),
//    see http://msdn.microsoft.com/en-us/library/windows/desktop/dd162760(v=vs.85).aspx
//  TODO: Graphics/device contexts (graphics) - possibly DirectX?
//    see http://nsdn.microsoft.com/en-us/library/windows/desktop/dd370971%28v=vs.85%29.aspx
//  TODO: locale info
//  TODO: Automatic focus traversal on tab by default
//  TODO: Figure out a way to get distance settings to work without a parent

#if !defined (JVS_UITK_WIN32_COMPONENT_H_)
#define JVS_UITK_WIN32_COMPONENT_H_

#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers

#define USE_ATL

#if defined (USE_ATL)
# include <atlbase.h>
# include <atldef.h>
# include <atlwin.h>
#endif

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <memory>
#include <map>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>

#include "jvs/uitk/win32/component_wndproc.h"
#include <jvs/base/types.h>
#include <jvs/uitk/win32/types.h>
#include "component_msghandler.h"
#include "font.h"
#include "graphics.h"
#include <jvs/uitk/event_arguments.h>
#include "component_creation_parameters.h"
#include "keyboard.h"
#include "gdi_object_deleter.h"
#include <jvs/uitk/component_states.h>
#include <jvs/uitk/background_mode.h>
#include "mouse_event_arguments.h"
#include "mouse_button.h"
#include <jvs/uitk/bounds_changed.h>
#include <jvs/uitk/null_deleter.h>
#include "brush.h"
#include "rectangle.h"
#include <jvs/uitk/win32/point.h>
#include "cursor.h"
#include <jvs/uitk/event_provider.h>
#include "message_arguments.h"
#include <jvs/uitk/anchor_styles.h>
#include <jvs/uitk/smart_ptr_compare.h>
#include "default_layout.h"

#include <jvs/debugkit/debugkit.h>




namespace jvs
{
namespace uitk
{
namespace win32
{


#ifdef USE_ATL
typedef CWindowImplBaseT<CWindow, CControlWinTraits> ComponentBase;
#else
// TODO: typedef to custom protected thunk class
class ComponentBase { };
#endif

class Component;

using ComponentEventProvider = EventProvider<Component, MessageArguments>;

class Component :
  // TODO: custom thunk base
  public virtual ComponentBase,
  // TODO: public virtual ValueWrapper<HWND>, // when ATL is removed; this will 
  // make it easier to make components copyable.
  protected virtual MessageHandler,
  public virtual ComponentEventProvider
{
private:
  // non-copyable for now
  Component(const Component&) { } /*C++11: = delete*/;

public:
  // typedefs
  typedef std::shared_ptr<Component> OwnedComponent;
  typedef std::vector<OwnedComponent> OwnedComponentCollection;

private:
  // name of the component
  std::string name_{Component::GenerateName()};
  // components owned by this one
  OwnedComponentCollection components_{};
  // the component that owns this one
  mutable Component* parent_{nullptr};
  // index of this component in its parent's child list
  int index_{-1};
  // left coordinate
  int x_;
  // top coordinate
  int y_;
  // width of the component
  int width_;
  // height of the component
  int height_;
  // width of the user-interactive area
  int client_width_;
  // height of the user-interactive area
  int client_height_;
  // text displayed for this component
  std::string text_;
  std::wstring text_buffer_;
  // color of the component background
  Color background_color_;
  // brush used for coloring the component background
  Brush background_brush_;
  // color of the component foreground
  Color foreground_color_;
  // font used to render text on the component
  Font font_;
  // properties that define how the component is initially created
  ComponentCreationParameters creation_parameters_;
  // style of background for the component
  BackgroundMode background_mode_;
  // mouse cursor displayed when over the component
  Cursor cursor_;
  // Anchor settings
  AnchorStyles anchor_;
  // Anchor distance info
  Rectangle anchor_delta_;
  // Layout engine
  std::shared_ptr<LayoutEngine<Component>> layout_;
  bool subclassed_window_; // TODO //
  UINT window_state_;
  TRACKMOUSEEVENT track_mouse_event_;

  static UINT WM_MOUSEENTER;
  static UINT WM_REDIRECTMSG;
  // stores components that have been created but don't have a parent component
  static Component HoldingComponent;
  // holds the list of all created components
  static std::set<OwnedComponent> CreatedComponents;
  static int ComponentCount;

public:

  Component()
    : window_state_(0),
    // I was originally using RECTs here to store the size and location
    // but it became too unwieldy. It's easier to recalculate sizes
    // and locations with individual ints using position updates.
    x_(0),
    y_(0),
    width_(0),
    height_(0),
    client_width_(0),
    client_height_(0),
    background_color_(::GetSysColor(COLOR_WINDOW)),
    foreground_color_(::GetSysColor(COLOR_WINDOWTEXT)),
    font_(Font::Default),
    background_brush_(),
    creation_parameters_(),
    background_mode_(BackgroundMode::Transparent),
    cursor_(Cursor::Default),
    subclassed_window_(false),
    anchor_(AnchorStyles::Left | AnchorStyles::Top),
    layout_(new DefaultLayout<Component>())
  {
    this->setState(ComponentStates::Visible, true);
    this->setState(ComponentStates::Enabled, true);
    // set up the message handler
    this->creation_parameters_.WindowProc = StartWindowProc;
  }

  Component(Component&& src)
    : name_(std::move(src.name_)),
    window_state_(src.window_state_),
    components_(std::move(src.components_)),
    parent_(src.parent_),
    index_(src.index_),
    x_(src.x_),
    y_(src.y_),
    width_(src.width_),
    height_(src.height_),
    client_width_(src.client_width_),
    client_height_(src.client_height_),
    background_color_(src.background_color_),
    foreground_color_(src.foreground_color_),
    font_(std::move(src.font_)),
    background_brush_(std::move(src.background_brush_)),
    creation_parameters_(std::move(src.creation_parameters_)),
    background_mode_(src.background_mode_),
    cursor_(std::move(src.cursor_)),
    subclassed_window_(src.subclassed_window_),
    anchor_(src.anchor_),
    layout_(std::move(src.layout_))
  {
    // TODO: Update when ATL is removed
    src.m_hWnd = nullptr;
  }

  virtual ~Component()
  {
    if (this->IsCreated())
    {
      if (this->subclassed_window_)
      {
        // TODO: replace with non-ATL version
        this->UnsubclassWindow(FALSE);
      }

      ::DestroyWindow(*this);
    }
  }

  Component& operator=(Component && src)
  {
    this->name_ = std::move(src.name_);
    this->window_state_ = src.window_state_;
    this->components_ = std::move(src.components_);
    this->parent_ = src.parent_;
    this->index_ = src.index_;
    this->x_ = src.x_;
    this->y_ = src.y_;
    this->width_ = src.width_;
    this->height_ = src.height_;
    this->client_width_ = src.client_width_;
    this->client_height_ = src.client_height_;
    this->background_color_ = src.background_color_;
    this->foreground_color_ = src.foreground_color_;
    this->font_ = std::move(src.font_);
    this->background_brush_ = std::move(src.background_brush_);
    this->creation_parameters_ = std::move(src.creation_parameters_);
    this->background_mode_ = src.background_mode_;
    this->cursor_ = std::move(src.cursor_);
    this->subclassed_window_ = src.subclassed_window_;
    this->anchor_ = src.anchor_;
    this->layout_ = std::move(src.layout_);
    // prevent destruction of window
    src.m_hWnd = nullptr;
    return *this;
  }

  /// <summary> Adds a component to this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="component">  [in] The component to add. </param>
  /// <returns> *this </returns>
  virtual Component& Add(Component& component)
  {
    this->components_.push_back(OwnedComponent(&component, jvs::NullDeleter()));
    this->updateChildIndex(component);
    return *this;
  }

  /// <summary> Adds a component to this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="component">  [in] The component to add. </param>
  /// <returns> *this </returns>
  virtual Component& Add(OwnedComponent& component)
  {
    this->components_.push_back(component);
    this->updateChildIndex(*component);
    return *this;
  }

  /// <summary> Adds a newly created component to this component and takes
  ///           ownership of it. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="component">  [in] Pointer to the component to add. </param>
  /// <returns> *this </returns>
  virtual Component& Add(Component* component)
  {
    return this->Add(OwnedComponent(component));
  }

  /// <summary> Adds a component to this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="component">  [in] The component to add. </param>
  /// <returns> The added component </returns>

  virtual Component& AddAndReturn(OwnedComponent& component)
  {
    this->Add(component);
    return *(component.get());
  }

  /// <summary> Adds a component to this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="component">  [in] The component to add to this one. </param>
  /// <returns> The added component </returns>
  virtual Component& AddAndReturn(Component* component)
  {
    this->Add(component);
    return *component;
  }

  /// <summary> Adds this component to the given parent component </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="parent"> [in] The parent component. </param>
  /// <returns> *this </returns>
  virtual Component& AddTo(Component& parent)
  {
    parent.Add(*this);
    return *this;
  }

  /// <summary> Gets the anchor style. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Anchor style. </returns>
  AnchorStyles anchor() const
  {
    return this->anchor_;
  }

  /// <summary> Gets the anchor style. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="r">  [out] Anchor style. </param>
  /// <returns> *this </returns>
  Component& anchor(AnchorStyles& r)
  {
    r = this->anchor();
    return *this;
  }

  /// <summary> Sets the anchor style. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="anchor"> Anchor style to set. </param>
  /// <returns> *this </returns>
  Component& set_anchor(AnchorStyles anchor)
  {
    this->anchor_ = anchor;
    // TODO: this->doLayout();
    return *this;
  }

  /// <summary> Gets the background color. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Background color. </returns>
  Color background_color() const
  {
    return this->background_color_;
  }

  /// <summary> Gets the background color. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="backColor">  [out] Background color. </param>
  /// <returns> *this </returns>
  Component& background_color(Color& backColor)
  {
    backColor = this->background_color();
    return *this;
  }

  /// <summary> Sets the background color. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="backColor">  The new background color </param>
  /// <returns> *this </returns>
  Component& set_background_color(const Color& backColor)
  {
    // check to make sure the background brush has been created
    if (this->background_brush_ == 0)
    {
      this->background_brush_.Assign(this->background_color_);
    }

    // If the new background color is the same as the current one, there is no
    // need to do anything else.
    if (backColor != this->background_color_)
    {
      this->background_color_ = backColor;
      this->background_brush_.Assign(this->background_color_);
      if (this->IsCreated())
      {
        ::InvalidateRect(*this, nullptr, TRUE);
      }
    }

    return *this;
  }

  /// <summary> Gets the background brush. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Background brush </returns>
  Brush background_brush() const
  {
    return this->background_brush_;
  }

  /// <summary> Gets the background brush. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="backBrush">  [out] Background brush. </param>
  /// <returns> *this </returns>
  Component& background_brush(Brush& backBrush)
  {
    backBrush = this->background_brush();
    return *this;
  }

  /// <summary> Gets the background mode. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Background mode. </returns>
  BackgroundMode background_mode() const
  {
    return this->background_mode_;
  }

  /// <summary> Gets the background mode. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="backMode"> [out] Background mode. </param>
  /// <returns> *this </returns>
  Component& background_mode(BackgroundMode& backMode)
  {
    backMode = this->background_mode();
    return *this;
  }

  /// <summary> Sets the background mode. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="backMode"> New background mode. </param>
  /// <returns> *this </returns>
  Component& set_background_mode(BackgroundMode backMode)
  {
    this->background_mode_ = backMode;
    return *this;
  }

  // The "bottom" and "right" methods use the same stylistic approach as other
  // field accessors and mutators because they used to be stored as fields 
  // themselves. Updating the naming style for these methods is trivial but 
  // unnecessary.

  /// <summary> Gets the bottom location. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Bottom location. </returns>
  int bottom() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->y_ + this->height_);
  }

  /// <summary> Gets the bottom location </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="b">  [out] Bottom location. </param>
  /// <returns> *this </returns>
  Component& bottom(int& b)
  {
    b = this->bottom();
    return *this;
  }

  /// <summary> Sets the bottom location by changing this component's height.
  ///           </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="bottom"> New bottom location. </param>
  /// <returns> *this </returns>
  Component& set_bottom(int bottom)
  {
    TRACEIN_THIS_ARGS(bottom);
    this->setBounds(0, 0, 0, bottom - this->y_, BoundsChanged::Height);
    return *this;
  }

  /// <summary> Get this distance from the bottom of this component to the 
  ///           bottom of its parent component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> The distance from the bottom of this component to the bottom of
  ///           its parent component. </returns>
  int bottom_distance() const
  {
    TRACEIN;
    if (this->parent_ == nullptr)
    {
      // TODO: possibly return the distance from the bottom of the screen to the
      // bottom of this component
      return 0;
    }

    return this->parent_->client_height() - this->bottom();
  }

  /// <summary> Get this distance from the bottom of this component to the 
  ///           bottom of its parent component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="bottomDistance"> [out] The distance from the bottom of this 
  ///                               component to the bottom of its parent
  ///                               component. </param>
  /// <returns> *this </returns>
  Component& bottom_distance(int& bottomDistance)
  {
    bottomDistance = this->bottom_distance();
    return *this;
  }

  /// <summary> Sets distance from the bottom of this component to the bottom of
  ///           its parent component by changing this component's height. 
  ///           </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="bottomDistance"> The distance from the bottom of this 
  ///                               component to the bottom of its parent 
  ///                               component. </param>
  /// <returns> *this </returns>
  Component& set_bottom_distance(int bottomDistance)
  {
    if (this->parent_ != nullptr)
    {
      this->setBounds(0, 0, 0,
        this->parent_->client_height_ - this->y_ - bottomDistance,
        BoundsChanged::Height);
    }
    else
    {
      // TODO: possibly change the height of this component to match the 
      // distance from its bottom to the bottom of the screen.
    }

    return *this;
  }

  /// <summary> Gets the bounds of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Bounds of this component. </returns>
  Rectangle bounds() const
  {
    RECT r = { this->x_, this->y_, this->x_ + this->width_,
      this->y_ + this->height_ };
    return r;
  }

  /// <summary> Gets the bounds of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="bounds"> [out] Bounds of this component. </param>
  /// <returns> *this </returns>
  Component& bounds(Rectangle& bounds)
  {
    bounds = this->bounds();
    return *this;
  }

  /// <summary> Gets the bounds of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="left">   [out] Left location. </param>
  /// <param name="top">    [out] Top location. </param>
  /// <param name="right">  [out] Right location. </param>
  /// <param name="bottom"> [out] Bottom location. </param>
  /// <returns> *this </returns>
  Component& bounds(int& left, int& top, int& right, int& bottom)
  {
    RECT r = this->bounds();
    left = r.left;
    top = r.top;
    right = r.right;
    bottom = r.bottom;
    return *this;
  }

  /// <summary> Sets the bounds of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="x">      New x coordinate. </param>
  /// <param name="y">      New y coordinate. </param>
  /// <param name="width">  New width. </param>
  /// <param name="height"> New height. </param>
  /// <returns> *this </returns>
  Component& set_bounds(int x, int y, int width, int height)
  {
    this->setBounds(x, y, width, height, BoundsChanged::All);
    return *this;
  }

  /// <summary> Sets the bounds of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="bounds"> New bounds of this component. </param>
  /// <returns> *this </returns>
  Component& set_bounds(Rectangle bounds)
  {
    this->set_bounds(bounds.x, bounds.y, bounds.width(),
      bounds.height());
    return *this;
  }

  virtual Component& CenterHorizontally()
  {
    if (this->parent_ == nullptr)
    {
      return *this;
    }

    this->set_left((this->parent()->client_width() / 2) - (this->width() / 2));
    return *this;
  }

  virtual Component& CenterVertically()
  {
    if (this->parent_ == nullptr)
    {
      return *this;
    }

    this->set_top((this->parent()->client_height() / 2) - (this->height() / 2));
    return *this;
  }

  /// <summary> Gets the child components of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> A list of components parented by this component. </returns>
  const OwnedComponentCollection& components() const
  {
    return this->components_;
  }

  /// <summary> Gets the client area height of this component. 
  ///           </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Client area height of this component. </returns>
  virtual int client_height() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->client_height_);
  }

  /// <summary> Gets the client area height of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="clientHeight"> [out] Client area height of this 
  ///                             component. </param>
  /// <returns> *this </returns>
  Component& client_height(int& clientHeight)
  {
    clientHeight = this->client_height();
    return *this;
  }

  /// <summary> Sets client area height of this component. NOTE: This will 
  ///           resize the entire component; not just the client area. 
  ///           </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="height"> New client area height. </param>
  /// <returns> *this </returns>
  Component& set_client_height(int height)
  {
    RECT r = { 0, 0, this->client_width_, height };
    this->updateFromClientSize(r);
    return *this;
  }

  /// <summary> Gets the client rectangle of this component. </summary>
  /// <remarks> Jsmith, 3/23/2014. </remarks>
  /// <returns> Client rectangle of this component. </returns>
  Rectangle client_rectangle() const
  {
    RECT ret = { 0, 0, this->client_width_, this->client_height_ };
    return ret;
  }

  /// <summary> Gets the client rectangle of this component. </summary>
  /// <remarks> Jsmith, 3/23/2014. </remarks>
  /// <param name="clientRect"> [out] Client rectangle of this component. 
  ///                           </param>
  /// <returns> *this </returns>
  Component& client_rectangle(Rectangle& clientRect)
  {
    clientRect = this->client_rectangle();
    return *this;
  }

  /// <summary> Gets the client area size of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Client area size of this component. </returns>
  Point client_size() const
  {
    POINT ret = { this->client_width_, this->client_height_ };
    return ret;
  }

  /// <summary> Gets the client area size of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="clientSize"> [out] Size of the client area. </param>
  /// <returns> *this </returns>
  Component& client_size(Point& clientSize)
  {
    clientSize = this->client_size();
    return *this;
  }

  /// <summary> Gets the client area size of this component. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="width">  [out] Client area width. </param>
  /// <param name="height"> [out] Client area height. </param>
  /// <returns> *this </returns>
  Component& client_size(int& width, int& height)
  {
    POINT ret = this->client_size();
    width = ret.x;
    height = ret.y;
    return *this;
  }

  /// <summary> Sets the client area size of this component. NOTE: This will
  ///           resize the entire component; not just the client area. 
  ///           </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="clientSize"> New client area size. </param>
  /// <returns> *this </returns>
  virtual Component& set_client_size(Point clientSize)
  {
    return this->set_client_size(clientSize.x, clientSize.y);
  }

  /// <summary> Sets the client area size of this component. NOTE: This will
  ///           resize the entire component; not just the client area. 
  ///           </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="width">  New client area width. </param>
  /// <param name="height"> New client area height. </param>
  /// <returns> *this </returns>
  virtual Component& set_client_size(int width, int height)
  {
    TRACEIN_THIS_ARGS(width, height);
    RECT r = { 0, 0, width, height };
    this->updateFromClientSize(r);
    return *this;
  }

  /// <summary> Gets the client area width. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <returns> Client area width. </returns>
  virtual int client_width() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->client_width_);
  }

  /// <summary> Gets the client area width. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="clientWidth">  [out] Client area width. </param>
  /// <returns> *this </returns>
  Component& client_width(int& clientWidth)
  {
    clientWidth = this->client_width();
    return *this;
  }

  /// <summary> Sets the client area width. NOTE: This will resize the entire 
  ///           component; not just the client area. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="width">  The width. </param>
  /// <returns> *this </returns>
  virtual Component& set_client_width(int width)
  {
    TRACEIN_THIS_ARGS(width);
    RECT r = { 0, 0, width, this->client_height_ };
    this->updateFromClientSize(r);
    return *this;
  }

  /// <summary> Gets the child component at the given coordinates. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="x">  X coordinate relative to this component. </param>
  /// <param name="y">  Y coordinate relative to this component. </param>
  /// <returns> Child component found at the given coordinate or *this if no
  ///           child component is found. </returns>
  Component& ComponentAt(int x, int y)
  {
    for (OwnedComponent & child : this->components_)
    {
      if ((x >= child->x_ && x <= (child->x_ + child->width_))
        && (y >= child->y_ && y <= (child->y_ + child->height_)))
      {
        return *child;
      }
    }

    return *this;
  }

  /// <summary> Gets the child component at the given coordinates. </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="point">  Point relative to this component. </param>
  /// <returns> Child component found at the given coordinate or *this if no
  ///           child component is found. </returns>
  Component& ComponentAt(Point point)
  {
    return this->ComponentAt(point.x, point.y);
  }

  /// <summary> Searches for child components in this components. I will update 
  ///           it later to search recursively. For now... no... </summary>
  /// <remarks> Jsmith, 12/22/2013. </remarks>
  /// <param name="component">  [in] If non-null, the child component to search 
  ///                           for. </param>
  /// <param name="recursive">  (Optional) Search recursively? Currently 
  ///                           ignored. </param>
  /// <returns> true if the component is a child to this one, false if not. 
  ///           </returns>
  bool Contains(Component* component, bool recursive = false) const
  {
    if (component == nullptr)
    {
      return false;
    }

    if (!this->IsCreated())
    {
      if (this->components_.empty())
      {
        return false;
      }

      // If this component hasn't been created yet, the only thing we can do is
      // search the current child component collection.
      return (std::find_if
        (
        this->components_.begin(),
        this->components_.end(),
        SmartPtrComparerer<Component>(component))
        ) != this->components_.end();
    }

    HWND currentHandle = ::FindWindowEx(*this, nullptr, nullptr, nullptr);
    if (currentHandle == static_cast<HWND>(*component))
    {
      return true;
    }

    while (currentHandle != NULL)
    {
      currentHandle = ::FindWindowEx(*this, currentHandle, nullptr, nullptr);
      if (currentHandle == static_cast<HWND>(*component))
      {
        return true;
      }
    }

    return false;
  }

  /// <summary> Query if this component contains the given point. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="x">  X coordinate. </param>
  /// <param name="y">  Y coordinate. </param>
  /// <returns> true if the point is within the bounds of this control, false 
  ///           if not. </returns>
  bool Contains(int x, int y)
  {
    // TODO: make X and Y screen coordinates and determine if those screen 
    // coordinates are covered by this component.
    return ((x >= 0 && x <= this->client_width_)
      && (y >= 0 && y <= this->client_height_));
  }

  /// <summary> Query if this object contains the given point. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="point">  Point to test for containment. </param>
  /// <returns> true if the point is within the bounds of this control, false 
  ///           if not. </returns>
  bool Contains(Point point)
  {
    return this->Contains(point.x, point.y);
  }

  /// <summary> Gets the cursor displayed when the mouse is over this 
  ///           component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Cursor displayed when the mouse is over this component. 
  ///           </returns>
  Cursor cursor() const
  {
    return this->cursor_;
  }

  /// <summary> Gets the cursor displayed when the mouse is over this 
  ///           component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="cursor"> [out] Cursor displayed when the mouse is over this 
  ///                       component. </param>
  /// <returns> *this </returns>
  Component& cursor(Cursor& cursor)
  {
    cursor = this->cursor();
    return *this;
  }

  /// <summary> Sets cursor to display when the mouse is over this component. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="c">  Cursor to display when the mouse is over this component. 
  ///                   </param>
  /// <returns> *this </returns>
  Component& set_cursor(const Cursor& c)
  {
    bool cursorChanged = false;
    if (c != this->cursor_)
    {
      this->cursor_ = c;
      cursorChanged = true;
    }

    if (this->IsCreated())
    {
      Point p;
      ::GetCursorPos(&p);
      Rectangle r;
      ::GetWindowRect(*this, &r);
      if (r.Contains(p) || ::GetCapture() == *this)
      {
        ::SendMessage(*this, WM_SETCURSOR,
          reinterpret_cast<WPARAM>(this->handle()), HTCLIENT);
      }

    }

    if (cursorChanged)
    {
      // TODO: OnCursorChanged maybe?
    }

    return *this;
  }

  /// <summary> Query whether or not this component is enabled. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> true if it enabled, false if not. </returns>
  bool enabled() const
  {
    return this->getState(ComponentStates::Enabled);
  }

  /// <summary> Query whether or not this component is enabled. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="e">  [out] true if it enabled, false if not. </param>
  /// <returns> *this </returns>
  Component& enabled(bool& e)
  {
    e = this->enabled();
    return *this;
  }

  /// <summary> Enables or disables this component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="enabled">  true to enable, false to disable. </param>
  /// <returns> *this </returns>
  Component& set_enabled(bool enabled)
  {
    ::EnableWindow(*this, enabled);
  }

  /// <summary> Sets cursor focus to this component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& Focus()
  {
    TRACEIN_THIS;
    this->ensureComponentIsCreated();
    ::SetFocus(*this);
    return *this;
  }

  /// <summary> Gets the font. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Font. </returns>
  Font font() const
  {
    return this->font_;
  }

  /// <summary> Gets the font. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="f">  [out] Font. </param>
  /// <returns> *this </returns>
  Component& font(Font& f)
  {
    f = this->font();
    return *this;
  }

  /// <summary> Sets the font. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="f">  Font to set. </param>
  /// <returns> *this </returns>
  Component& set_font(Font f)
  {
    if (this->IsCreated())
    {
      // Send a WM_SETFONT message to the component. Its message handler will
      // update the font internally.
      ::SendMessage(*this, WM_SETFONT,
        reinterpret_cast<WPARAM>(f.handle()), MAKELPARAM(TRUE, 0));
    }
    else
    {
      this->font_ = f;
    }

    return *this;
  }

  /// <summary> Gets the foreground color. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Foreground color. </returns>
  Color foreground_color() const
  {
    return this->foreground_color_;
  }

  /// <summary> Gets the foreground color. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="color">  [out] Foreground color. </param>
  /// <returns> *this </returns>
  Component& foreground_color(Color& color)
  {
    color = this->foreground_color_;
    return *this;
  }

  /// <summary> Sets the foreground color. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="color">  New foreground color. </param>
  /// <returns> *this </returns>
  Component& set_foreground_color(const Color& color)
  {
    this->foreground_color_ = color;
    if (this->IsCreated())
    {
      ::InvalidateRect(*this, nullptr, TRUE);
    }

    return *this;
  }

  /// <summary> Gets the native window handle if the component has been 
  ///           created. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Handle (HWND) to the created component; null (0) if the
  ///           component has not been created. </returns>
  WindowHandle handle() const
  {
    // TODO: update this when ATL is removed
    return this->m_hWnd;
  }

  /// <summary> Gets the native window handle if the component has been 
  ///           created. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="h">  [out] Handle (HWND) to the created component; null (0) 
  ///                   if the component has not been created. </param>
  /// <returns> *this </returns>
  Component& handle(WindowHandle& h)
  {
    h = this->handle();
    return *this;
  }

  /// <summary> Gets the height. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Height. </returns>
  int height() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->height_);
  }

  /// <summary> Gets the height. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="h">  [out] Height. </param>
  /// <returns> *this </returns>
  Component& height(int& h)
  {
    h = this->height();
    return *this;
  }

  /// <summary> Sets the height. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="h">  Height. </param>
  /// <returns> *this </returns>
  Component& set_height(int h)
  {
    TRACEIN_THIS_ARGS(h);
    this->setBounds(this->x_, this->y_, this->width_, h, BoundsChanged::Height);
    return *this;
  }

  /// <summary> Makes the component invisible. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& Hide()
  {
    this->set_visible(false);
    return *this;
  }

  /// <summary> Query if this component has been created by the system. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> true if created, false if not. </returns>
  bool IsCreated() const
  {
    return (this->handle() != nullptr);
  }

  /// <summary> Query if this component is focused. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> true if focused, false if not. </returns>
  virtual bool IsFocused() const
  {
    return (this->IsCreated() && (::GetFocus() == *this));
  }

  /// <summary> Query if this component is a top-level window. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> true if top level, false if not. </returns>
  bool IsTopLevel() const
  {
    TRACEIN_THIS;
    if (this->IsCreated())
    {
      RETURN_TRACE(
        (((::GetWindowLongPtr(*this, GWL_STYLE) & WS_CHILD) != WS_CHILD)
         && ::GetParent(*this) == nullptr)
      );
    }

    RETURN_TRACE(((this->creation_parameters_.WindowStyles & WS_CHILD) != WS_CHILD));
  }

  /// <summary> Gets the left position. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Left position. </returns>
  int left() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->x_);
  }

  /// <summary> Gets the left position. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="x">  [out] Left position. </param>
  /// <returns> *this </returns>
  Component& left(int& x)
  {
    x = this->left();
    return *this;
  }

  /// <summary> Sets the left position. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="x">  New left position. </param>
  /// <returns> *this </returns>
  Component& set_left(int x)
  {
    TRACEIN_THIS_ARGS(x);
    this->setBounds(x, this->y_, this->width_, this->height_,
                    BoundsChanged::X);
    return *this;
  }

  /// <summary> Resizes this component down to the minimum size needed to 
  ///           display all of its child components. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="paddingRight">   (Optional) the right-side padding amount in 
  ///                               pixels. </param>
  /// <param name="paddingBottom">  (Optional) the bottom-side padding amount 
  ///                               in pixels. </param>
  /// <returns> *this </returns>
  virtual Component& Pack(int paddingRight = 10, int paddingBottom = 10)
  {
    TRACEIN_THIS_ARGS(paddingRight, paddingBottom);

    int maxRight = 0, maxBottom = 0;
    std::for_each(this->components_.begin(), this->components_.end(),
                  [&](OwnedComponent & child)
    {
      // It doesn't make a lot of sense to pack down using invisible components
      // for boundaries.
      if (child->visible())
      {
        int right = child->right();
        int bottom = child->bottom();
        maxRight = (std::max)(right, maxRight);
        maxBottom = (std::max)(bottom, maxBottom);
      }
    });

    DBGOUT("Client-edge right: ", maxRight, " (plus ", paddingRight,
           " padding)");
    DBGOUT("Client-edge bottom: ", maxBottom, " (plus ", paddingBottom,
           " padding)");
    this->layout_->Suspend();
    this->set_client_size(maxRight + paddingRight, maxBottom + paddingBottom);
    this->layout_->Resume();
    return *this;
  }

  /// <summary> Gets the top location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Top location. </returns>
  int top() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->y_);
  }

  /// <summary> Gets the top location </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="y">  [out] Top location. </param>
  /// <returns> *this </returns>
  Component& top(int& y)
  {
    y = this->top();
    return *this;
  }

  /// <summary> Sets the top location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="y">  New top location. </param>
  /// <returns> *this </returns>
  Component& set_top(int y)
  {
    TRACEIN_THIS_ARGS(y);
    this->setBounds(0, y, 0, 0, BoundsChanged::Y);
    return *this;
  }

  /// <summary> Gets the location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Location. </returns>
  Point location() const
  {
    TRACEIN_THIS;
    POINT ret = { this->x_, this->y_ };
    DBGOUT("[Return: x=", ret.x, ", y=", ret.y, "]");
    return ret;
  }

  /// <summary> Gets the location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="loc">  [out] Location. </param>
  /// <returns> *this </returns>
  Component& location(Point& loc)
  {
    loc = this->location();
    return *this;
  }

  /// <summary> Gets the location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="x">  [out] X coordinate. </param>
  /// <param name="y">  [out] Y coordinate. </param>
  /// <returns> *this </returns>
  Component& location(int& x, int& y)
  {
    POINT r = this->location();
    x = r.x;
    y = r.y;
    return *this;
  }

  /// <summary> Sets the location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="x">  New x coordinate. </param>
  /// <param name="y">  New y coordinate. </param>
  /// <returns> *this </returns>
  Component& set_location(int x, int y)
  {
    TRACEIN_THIS_ARGS(x, y);

    this->setBounds(x, y, 0, 0, BoundsChanged::Location);
    return *this;
  }

  /// <summary> Sets the location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="loc">  New location. </param>
  /// <returns> *this </returns>
  Component& set_location(Point loc)
  {
    TRACEIN_THIS_ARGS(loc.x, loc.y);
    this->setBounds(loc.x, loc.y, 0, 0, BoundsChanged::Location);
    return *this;
  }

  /// <summary> Move to the back of the z-order. This has no effect on 
  ///           components that have not been created. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& MoveToBack()
  {
    if (this->IsCreated())
    {
      ::SetWindowPos(*this, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }

    return *this;
  }

  /// <summary> Move to the front of the z-order. This has no effect on
  ///           components that have not been created. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& MoveToFront()
  {
    if (this->IsCreated())
    {
      ::SetWindowPos(*this, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }

    return *this;
  }

  /// <summary> Gets the internal name. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Name of the component. </returns>
  std::string name() const
  {
    return this->name_;
  }

  /// <summary> Gets the internal name. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="componentName">  [out] Name of the component. </param>
  /// <returns> *this </returns>
  Component& name(std::string& componentName)
  {
    componentName = this->name_;
    return *this;
  }

  /// <summary> Sets the internal name. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="componentName">  Name of the component. </param>
  /// <returns> *this </returns>
  Component& set_name(const std::string& componentName)
  {
    this->name_ = componentName;
    return *this;
  }

  /// <summary> Gets the parent. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> null if no parent, else the parent Component*. </returns>
  Component* parent() const
  {
    return this->parent_;
  }

  /// <summary> Gets the parent. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="p">  [out] null if no parent, else the parent Component*. 
  ///                   </param>
  /// <returns> *this </returns>

  Component& parent(Component*& p)
  {
    p = this->parent_;
    return *this;
  }

  /// <summary> Sets the parent. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="p">  [in] New parent Component*. Can be null. </param>
  /// <returns> *this </returns>
  Component& set_parent(Component* p)
  {
    if (this->parent_ != nullptr)
    {
      p->Add(*this);
    }
    else
    {
      p->Remove(*this);
    }

    return *this;
  }

  /// <summary> Removes the given child component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="component">  [in] Component to remove. </param>
  /// <returns> *this </returns>
  Component& Remove(Component& component)
  {
    this->RemoveAndReturn(component);
    return *this;
  }

  /// <summary> Removes the given child component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="component">  [in] Component to remove. </param>
  /// <returns> Removed component </returns>
  Component& RemoveAndReturn(Component& component)
  {
    component.setParentComponent(nullptr);
    auto winPtr = std::find_if(this->components_.begin(),
      this->components_.end(), SmartPtrComparerer<Component>(&component));
    if (winPtr != this->components_.end())
    {
      this->components_.erase(winPtr);
    }

    component.AssignParent(nullptr);
    this->updateChildIndicies();
    return component;
  }

  /// <summary> Repaints the entire component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& Repaint()
  {
    if (this->ensureComponentIsCreated())
    {
      ::InvalidateRect(*this, nullptr, TRUE);
    }

    return *this;
  }

  /// <summary> Repaints a portion of the component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="r">  Area of the component to repaint. </param>
  /// <returns> *this </returns>
  Component& Repaint(Rectangle r)
  {
    if (this->ensureComponentIsCreated())
    {
      ::InvalidateRect(*this, &r, TRUE);
    }

    return *this;
  }

  /// <summary> Repaints a portion of the component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="x">      X coordinate to start painting. </param>
  /// <param name="y">      Y coordinate to start painting. </param>
  /// <param name="width">  Width of the repaint area. </param>
  /// <param name="height"> Height of the repaint area. </param>
  /// <returns> *this </returns>
  Component& Repaint(int x, int y, int width, int height)
  {
    return this->Repaint(Rectangle(x, y, width, height));
  }

  /// <summary> Gets the right location. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Right location. </returns>
  int right() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->x_ + this->width_);
  }

  /// <summary> Gets the right location </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="r">  [out] Right location. </param>
  /// <returns> *this </returns>
  Component& right(int& r)
  {
    r = this->right();
    return *this;
  }

  /// <summary> Sets the right location by changing the component's width. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="r">  New right location. </param>
  /// <returns> *this </returns>
  Component& set_right(int r)
  {
    TRACEIN_THIS_ARGS(r);
    this->setBounds(0, 0, r - this->x_, 0, BoundsChanged::Width);
    return *this;
  }

  /// <summary> Gets the distance from the right location of this component to 
  ///           the right location of its parent component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Distance from the right location of this component to the right 
  ///           location of its parent component. </returns>
  int right_distance() const
  {
    if (this->parent_ == nullptr)
    {
      return 0;
    }

    return (this->parent_->client_width_ - this->right());
  }

  /// <summary> Gets the distance from the right location of this component to 
  ///           the right location of its parent component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="rightDistance">  [out] Distance from the right location of 
  ///                               this component to the right location of its 
  ///                               parent component. </param>
  /// <returns> *this </returns>
  Component& right_distance(int& rightDistance)
  {
    rightDistance = this->right_distance();
    return *this;
  }

  /// <summary> Sets the distance from the right location of this component to
  ///           the right location of its parent component by changing the 
  ///           width of this component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="rightDistance">  New right distance. </param>
  /// <returns> *this </returns>
  Component& set_right_distance(int rightDistance)
  {
    if (this->parent_ != nullptr)
    {
      this->setBounds(0, 0,
        this->parent_->client_width_ - this->x_ - rightDistance, 0, 
        BoundsChanged::Width);
    }

    return *this;
  }

  /// <summary> Makes this component visible. NOTE: This will force the 
  ///           component to be created if it has not yet been. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& Show()
  {
    this->set_visible(true);
    return *this;
  }

  /// <summary> Gets the size. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Size. </returns>
  Point size() const
  {
    TRACEIN_THIS;
    POINT ret = { this->width(), this->height() };
    DBGOUT("[Return: x=", ret.x, ", y=", ret.y, "]");
    return ret;
  }

  /// <summary> Gets the size. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="s">  [out] Size. </param>
  /// <returns> *this </returns>
  Component& size(Point& s)
  {
    s = this->size();
    return *this;
  }

  /// <summary> Gets the size. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="w">  [out] Width. </param>
  /// <param name="h">  [out] Height. </param>
  /// <returns> *this </returns>
  Component& size(int& w, int& h)
  {
    POINT p = this->size();
    w = p.x;
    h = p.y;
    return *this;
  }

  /// <summary> Sets the size. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="s">  New size. </param>
  /// <returns> *this </returns>

  Component& set_size(Point s)
  {
    return this->set_size(s.x, s.y);
  }

  /// <summary> Sets the size. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="w">  New width. </param>
  /// <param name="h">  New height. </param>
  /// <returns> *this </returns>
  Component& set_size(int w, int h)
  {
    TRACEIN_THIS_ARGS(w, h);
    this->setBounds(0, 0, w, h, BoundsChanged::Size);
    return *this;
  }

  /// <summary> Gets the text. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Text. </returns>
  std::string text() const
  {
    if (!this->IsCreated())
    {
      return this->text_;
    }

    std::wstring buf(::GetWindowTextLengthW(*this) + 1, 0);
    int size = ::GetWindowTextW(*this, &buf[0], static_cast<int>(buf.size()));
    buf.resize(size);
    return jvs::Narrow(buf);
  }

  /// <summary> Gets the text </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="s">  [out] Text. </param>
  /// <returns> *this </returns>
  Component& text(std::string& s)
  {
    if (!this->IsCreated())
    {
      s = this->text_;
      return *this;
    }

    std::wstring buf(::GetWindowTextLengthW(*this) + 1, 0);
    int size = ::GetWindowTextW(*this, &buf[0], static_cast<int>(buf.size()));
    buf.resize(size);
    s = jvs::Narrow(buf);
    return *this;
  }

  /// <summary> Sets the text. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="s">  New text. </param>
  /// <returns> *this </returns>
  Component& set_text(const std::string& s)
  {
    if (this->IsCreated())
    {
      ::SetWindowTextW(*this, jvs::Widen(s).c_str());
      // SetWindowText raises a WM_SETTEXT message; no need for
      // further processing
      return *this;
    }

    this->text_ = s;
    this->text_buffer_ = jvs::Widen(this->text_);
    return *this;
  }

  /// <summary> Transfers focus to the next component in the focus order. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& TransferFocus()
  {
    this->transferFocus(1);
    return *this;
  }

  /// <summary> Transfers focus to the previous component in the focus order. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> *this </returns>
  Component& TransferFocusBackward()
  {
    this->transferFocus(-1);
    return *this;
  }

  /// <summary> Gets the visibility of this component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> true if visible, false if not. </returns>
  bool visible() const
  {
    if (!this->IsCreated())
    {
      return this->getState(ComponentStates::Visible);
    }

    return (::IsWindowVisible(*this) == TRUE);
  }

  /// <summary> Gets the visibility of this component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="v">  [out] true if visible, false if not. </param>
  /// <returns> *this </returns>
  Component& visible(bool& v)
  {
    v = this->visible();
    return *this;
  }

  /// <summary> Sets the visibility of this component. NOTE: If the component 
  ///           has not been created and the visibility is set to true, this 
  ///           will force the creation of the component. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="v">  true to make the component visible, false to make the 
  ///                   component invisible. </param>
  /// <returns> *this </returns>
  Component& set_visible(bool v)
  {
    this->setState(ComponentStates::Visible, v);
    if (this->getState(ComponentStates::Visible))
    {
      if (this->ensureComponentIsCreated())
      {
        ::ShowWindow(*this, SW_SHOW);
      }
    }
    else
    {
      if (this->IsCreated())
      {
        ::ShowWindow(*this, SW_HIDE);
      }
    }

    return *this;
  }

  /// <summary> Gets the width. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Width. </returns>
  int width() const
  {
    TRACEIN_THIS;
    RETURN_TRACE(this->width_);
  }

  /// <summary> Gets the width. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="w">  [out] Width. </param>
  /// <returns> *this </returns>
  Component& width(int& w)
  {
    w = this->width();
    return *this;
  }

  /// <summary> Sets the width. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <param name="w">  New width. </param>
  /// <returns> *this </returns>
  Component& set_width(int w)
  {
    TRACEIN_THIS_ARGS(w);
    this->setBounds(0, 0, w, 0, BoundsChanged::Width);
    this->updateAnchorDelta();
    return *this;
  }

  /// <summary> Gets the set of all the created components across the 
  ///           application. </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  /// <returns> Set of all the created components across the application. 
  ///           </returns>
  static const std::set<OwnedComponent>& GetCreatedComponents()
  {
    return Component::CreatedComponents;
  }

protected:

  // used to (eventually) adjust the properties of the child window to become
  // similar to that of the parent window (enabled state, font, visibility,
  // etc.)
  virtual void AssignParent(Component* parent)
  {
    this->parent_ = parent;
  }

  // Modified version of CWindowImpl::Create...
  virtual WindowHandle CreateComponent()
  {
    TRACEIN_THIS;

    // For reference:

    // typedef struct tagWNDCLASSEXW {
    //  UINT        cbSize;
    //  UINT        style;
    //  WNDPROC     lpfnWndProc;
    //  int         cbClsExtra;
    //  int         cbWndExtra;
    //  HINSTANCE   hInstance;
    //  HICON       hIcon;
    //  HCURSOR     hCursor;
    //  HBRUSH      hbrBackground;
    //  LPCWSTR     lpszMenuName;
    //  LPCWSTR     lpszClassName;
    //  HICON       hIconSm;
    //  WNDCLASSEXW, *PWNDCLASSEXW, NEAR *NPWNDCLASSEXW, FAR *LPWNDCLASSEXW;

    //  #define DECLARE_WND_CLASS_EX(WndClassName, style, bkgnd) \
    //  static ATL::CWndClassInfo& GetWndClassInfo() \
    //  { \
    //    static ATL::CWndClassInfo wc = \
    //    { \
    //      { sizeof(WNDCLASSEX), style, StartWindowProc, \
    //        0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName, NULL }, \
    //      NULL, NULL, IDC_ARROW, TRUE, 0, _T("") \
    //    }; \
    //    return wc; \
    //  }

    //  #define DECLARE_WND_SUPERCLASS(WndClassName, OrigWndClassName) \
    //  static ATL::CWndClassInfo& GetWndClassInfo() \
    //  { \
    //    static ATL::CWndClassInfo wc = \
    //    { \
    //      { sizeof(WNDCLASSEX), 0, StartWindowProc, \
    //        0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
    //      OrigWndClassName, NULL, NULL, TRUE, 0, _T("") \
    //    }; \
    //    return wc; \
    //  }
    //

    WindowHandle ret = *this;
    if (!this->IsCreated())
    {
      ATOM atom;
      WindowHandle parentHandle = (this->parent_ == nullptr) ? nullptr
                          : static_cast<HWND>(*this->parent_);
      ATL::_U_MENUorID MenuOrID = 0U;
      LPVOID lpCreateParam = NULL;

      ATL::CWndClassInfo atlClsInfo;

      // We're about to register this window class with the system; let derived 
      // components know so they can set anything different that needs to be 
      // set.
      auto createParams = this->GetCreationParameters();
      this->OnRegistering(createParams);
      if (!createParams.UseSystemClass)
      {
        atlClsInfo = createParams;
        // TODO: use jvs::uitk::win32::ComponentWndProc
        atlClsInfo.m_wc.lpfnWndProc = StartWindowProc;
        atom = atlClsInfo.Register(&m_pfnSuperWindowProc);
        //atom = this->registerComponent(createParams);
      }
      else
      {
        if (createParams.class_name() != createParams.base_class_name())
        {
          createParams.set_class_name(createParams.base_class_name());
        }

        atom = static_cast<ATOM>(::GetClassInfoExW(::GetModuleHandleW(nullptr),
          createParams.class_name_buffer().c_str(), &atlClsInfo.m_wc));
      }

      // Update the local cursor object (if necessary)
      if (this->cursor_.type() == CursorType::Default)
      {
        this->cursor_ = Cursor(atlClsInfo.m_wc.hCursor);
      }

      // Let derived components know registration is complete.
      this->OnRegistered(createParams);
      // We now move on to actual window creation
      DWORD dwStyle = createParams.WindowStyles;
      DWORD dwExStyle = createParams.WindowExStyles;
      // If the window isn't enabled, set the WS_DISABLED style.
      if (((dwStyle & WS_DISABLED) != WS_DISABLED)
          && (!(this->getState(ComponentStates::Enabled))))
      {
        dwStyle |= WS_DISABLED;
      }

      // If the window isn't visible and the style has WS_VISIBLE, remove it.
      if (((dwStyle & WS_VISIBLE) != 0)
          && (!(this->getState(ComponentStates::Visible))))
      {
        dwStyle &= ~WS_VISIBLE;
      }

      // Can't create a top-level child window, so we fix that RIGHT HERE by
      // parking the window to be created in the application-wide holding
      // component.
      if (((dwStyle & WS_CHILD) != 0) && (parentHandle == NULL))
      {
        if (this == &Component::HoldingComponent)
        {
          dwStyle &= ~WS_CHILD;
        }
        else
        {
          parentHandle = Component::GetHoldingHandle();
        }
      }

      if (createParams.UseSystemClass)
      {
        // Manually create the system-based window without the use
        // of ATL and then subclass it
        if (MenuOrID.m_hMenu == NULL && (dwStyle & WS_CHILD))
        {
          MenuOrID.m_hMenu = reinterpret_cast<HMENU>(
                               reinterpret_cast<UINT_PTR>(this)
                             );
        }

        // We're about to create the window; let derived components know for
        // last minute modififcations.
        this->OnCreating();
        ret = ::CreateWindowExW(
          dwExStyle, 
          MAKEINTATOM(atom), 
          jvs::Widen(this->text_).c_str(), 
          dwStyle, 
          this->x_, 
          this->y_, 
          this->width_,
          this->height_, 
          parentHandle, 
          MenuOrID.m_hMenu, 
          //_AtlBaseModule.GetModuleInstance(), 
          ::GetModuleHandleW(nullptr),
          lpCreateParam);
        if (ret == nullptr)
        {
          auto errCode = ::GetLastError();
          DBGOUT("Error: ", debug::ErrorToMessage(errCode));
          _ASSERT(ret != nullptr);
        }

        this->subclassed_window_ = true;
        // TODO: replace with non-ATL function
        this->SubclassWindow(ret);
      }
      else
      {
        // We're about to create the window; let derived components know for
        // last minute modififcations.
        this->OnCreating();
        RECT r = { this->x_, this->y_, this->right(), this->bottom() };
        ret = ComponentBase::Create(parentHandle, r, 
          this->text_buffer_.c_str(), dwStyle, dwExStyle, MenuOrID, atom, 
          lpCreateParam);
      }

      if (ret == nullptr)
      {
        auto errCode = ::GetLastError();
        DBGOUT("Error: ", debug::ErrorToMessage(errCode));
        _ASSERT(ret != NULL);
      }

      // add this component to the list of created components
      Component::CreatedComponents.insert(OwnedComponent(this,
        jvs::NullDeleter()));
      // Window has been created
      this->OnCreated();
    }

    this->updateBounds();
    this->setState(ComponentStates::MouseEnterPending, true);
    this->unhookMouse();
    // set the font
    ::SendMessage(*this, WM_SETFONT, 
      reinterpret_cast<WPARAM>(static_cast<FontHandle>(this->font_)),
      MAKELPARAM(TRUE, 0));
    // create the child components
    for (OwnedComponent & itr : this->components_)
    {
      Component& window = *itr;
      if (window.IsCreated())
      {
        window.setParentComponent(this);
      }

      window.CreateComponent();
    }

    // show the component if necessary
    if (this->getState(ComponentStates::Visible))
    {
      // SW_SHOWNORMAL (1) - Activates and displays a window. If the window is
      // minimized or maximized, the system restores it to its original size and
      // position. An application should specify this flag when displaying the
      // window for the first time.
      ::ShowWindow(*this, SW_SHOWNORMAL);
      this->OnFirstShown();
    }

    return ret;
  }

  virtual ComponentCreationParameters GetCreationParameters() const
  {
    return this->creation_parameters_;
  }

  virtual Point GetDefaultSize() const
  {
    return Point::Zero;
  }

  // used by the EventProvider class
  Component& GetProvider() override
  {
    return *this;
  }

  // meant to be overridden by derived classes
  virtual bool HasMenu() const
  {
    return false;
  }

  // meant to be called by the constructors of derived components
  void Initialize()
  {
    // set up default sizes
    this->setDefaultSizes();
  }

  // Event activators
  virtual void OnCreating() { };
  virtual void OnCreated() { };
  virtual void OnPaint(bool& handled) { }
  virtual void OnRegistering(ComponentCreationParameters& createParams)  { }
  virtual void OnRegistered(const ComponentCreationParameters& createParams) { }
  virtual void OnFirstShown() { }

  // Window message handlers
  // // // // // // // // //

  virtual LRESULT WmCtlColorEdit(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    handled = true;
    return this->colorControl(msg.message,
                              reinterpret_cast<HDC>(msg.wParam),
                              reinterpret_cast<HWND>(msg.lParam));
  }

  virtual LRESULT WmCtlColorListbox(LRESULT defaultResult, MSG& msg,
                                    bool& handled)
  {
    handled = true;
    return this->colorControl(msg.message,
                              reinterpret_cast<HDC>(msg.wParam),
                              reinterpret_cast<HWND>(msg.lParam));
  }

  virtual LRESULT WmCtlColorStatic(LRESULT defaultResult, MSG& msg,
                                   bool& handled)
  {
    handled = true;
    return this->colorControl(msg.message,
                              reinterpret_cast<HDC>(msg.wParam),
                              reinterpret_cast<HWND>(msg.lParam));
  }

  virtual LRESULT WmEraseBkgnd(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    //HDC hdcWindow = reinterpret_cast<HDC>(msg.wParam);
    //HDC hdcMem = ::CreateCompatibleDC(hdcWindow);
    //HBITMAP bmMem = ::CreateCompatibleBitmap(hdcWindow, this->width_,
    //                this->height_);
    //::SelectObject(hdcMem, bmMem);

    //RECT r;
    //::GetClientRect(*this, &r);
    //::FillRect(hdcMem, &r, this->background_brush_);
    //::BitBlt(hdcWindow, 0, 0, this->width_, this->height_, hdcMem, 0, 0,
    //         SRCCOPY);
    //::DeleteObject(bmMem);
    //::DeleteDC(hdcMem);
    //::InvalidateRect(*this, nullptr, FALSE);

    // FIXME: this is causing flickering *sometimes*... not sure why
    this->drawBackground();
    handled = true;
    return 1;
  }

  virtual LRESULT WmEnable(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    this->setState(ComponentStates::Enabled,
                   (static_cast<BOOL>(msg.wParam) == TRUE ? true : false));
    return 0;
  }

  // Original WM_PAINT code:
  // 
  // virtual LRESULT WmPaint(LRESULT defaultResult, MSG& msg, bool& handled)
  // {
  //  PAINTSTRUCT ps;
  //  HDC hdcWindow;
  //  Rectangle clip;
  //  bool dispose = false;
  //  if (msg.wParam == NULL)
  //  {
  //    hdcWindow = ::BeginPaint(*this, &ps);
  //    clip = ps.rcPaint;
  //    dispose = true;
  //  }
  //  else
  //  {
  //     hdcWindow = reinterpret_cast<HDC>(msg.wParam);
  //     clip.set_size(this->client_width_, this->client_height_);
  //  }

  //  // Create the back-buffer DC
  //  HDC hdcMem = ::CreateCompatibleDC(hdcWindow);
  //  // Duplicate the component's image
  //  HBITMAP bmMem = ::CreateCompatibleBitmap(hdcWindow, this->width_,
  //    this->height_);
  //  // Copy the bitmap in to the back-buffer
  //  auto hOld = ::SelectObject(hdcMem, bmMem);
  //  ::FillRect(hdcMem, &clip, this->background_brush_);
  //  // Update only the clipped portion
  //  ::BitBlt(hdcWindow, clip.left, clip.top, clip.width(),
  //    clip.height(), hdcMem, clip.left, clip.top, SRCCOPY);
  //  ::SelectObject(hdcMem, hOld);
  //  // Cleanup
  //  ::DeleteObject(bmMem);
  //  ::DeleteDC(hdcMem);
  //  if (dispose)
  //  {
  //  ::EndPaint(*this, &ps);
  //  }

  //  handled = true;
  //  return defaultResult;
  // }

  virtual LRESULT WmMove(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    TRACEIN_THIS;

    this->updateBounds();
    return 0;
  }

  virtual LRESULT WmSetCursor(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    if (reinterpret_cast<HWND>(msg.wParam) == this->handle()
        && LOWORD(msg.lParam) == HTCLIENT)
    {
      ::SetCursor(this->cursor_);
      handled = true;
      return 1;
    }

    return 0;
  }

  virtual LRESULT WmSetFont(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    // Font is being updated; change it internally
    if (msg.wParam == NULL)
    {
      this->font_ = Font::Default;
    }
    else
    {
      //if (this->font_.handle() != reinterpret_cast<FontHandle>(msg.wParam))
      //{
        this->font_ = Font(reinterpret_cast<FontHandle>(msg.wParam));
      //}
    }

    return defaultResult;
  }

  virtual LRESULT WmSetText(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    // Text is being updated; change it internally
    this->text_ = jvs::Narrow(reinterpret_cast<const wchar_t*>(msg.lParam));
    return 0;
  }

  virtual LRESULT WmWindowPosChanged(LRESULT defaultResult, MSG& msg,
                                     bool& handled)
  {
    TRACEIN_THIS;
    this->DefWindowProc(msg.message, msg.wParam, msg.lParam);
    this->updateBounds();
    handled = true;
    return 0;
  }

  virtual BOOL ProcessWindowMessage(HWND hwnd, UINT uint, WPARAM wparam,
    LPARAM lparam, LRESULT &lresult, DWORD dwMsgMapID) override
  {
    static POINT mousePos;
    ::GetCursorPos(&mousePos);
    MSG msg = { hwnd, uint, wparam, lparam, 
      static_cast<DWord>(std::chrono::high_resolution_clock::now()
        .time_since_epoch().count()), mousePos };
    bool handled = false;

    if (uint == WM_MOUSEENTER)
    {
      // ee: this->OnMouseEnter();
      bool handledIgnored;  // ignored
      win32::LResult resultIgnored;  // ignored
      MessageArguments e(msg, handledIgnored, resultIgnored);
      this->ProcessEvent(*this, e);
      lresult = 0;
      return TRUE;
    }
    else
    {
      lresult = MessageHandler::RouteMessage(lresult, msg, handled);
      MessageArguments e(msg, handled, reinterpret_cast<LResult&>(lresult));
      this->ProcessEvent(*this, e);

      lresult = e.Result;
      handled = e.Handled;
    }

    return handled;
  }

  virtual void PaintBackgroundColor()
  {
    PAINTSTRUCT ps;
    HDC hdcWindow = ::BeginPaint(*this, &ps);
    HDC hdcMem = ::CreateCompatibleDC(hdcWindow);
    HBITMAP bmMem = ::CreateCompatibleBitmap(hdcWindow, this->width_,
                    this->height_);
    ::SelectObject(hdcMem, bmMem);
    // This class automatically handles the background
    // drawing for any other component
    if (this->background_brush_ == 0)
    {
      this->background_brush_.Assign(this->background_color_);
    }

    ::FillRect(hdcMem, &ps.rcPaint, this->background_brush_);
    ::BitBlt(hdcWindow, 0, 0, this->width_, this->height_, hdcMem, 0, 0,
             SRCCOPY);
    ::DeleteObject(bmMem);
    ::DeleteDC(hdcMem);
    ::EndPaint(*this, &ps);
  }

private:

  Component& setBounds(int x, int y, int width, int height,
                       BoundsChanged boundsChanged)
  {
    TRACEIN_THIS_ARGS(x, y, width, height, static_cast<int>(boundsChanged));

    if ((boundsChanged & BoundsChanged::X) == BoundsChanged::None)
    {
      x = this->x_;
    }

    if ((boundsChanged & BoundsChanged::Y) == BoundsChanged::None)
    {
      y = this->y_;
    }

    if ((boundsChanged & BoundsChanged::Width) == BoundsChanged::None)
    {
      width = this->width_;
    }

    if ((boundsChanged & BoundsChanged::Height) == BoundsChanged::None)
    {
      height = this->height_;
    }

    // TODO:
    // if (boundsChanged != BoundsChanged::None)
    // {
    //   this->layout_->DoLayout();
    // }

    if (!this->IsCreated())
    {
      this->updateBounds(x, y, width, height);
    }
    else
    {
      if ((boundsChanged & BoundsChanged::Location) != BoundsChanged::None)
      {
        this->updateNativeLocation(x, y);
      }

      if ((boundsChanged & BoundsChanged::Size) != BoundsChanged::None)
      {
        this->updateNativeSize(width, height);
      }
    }

    return *this;
  }

  void setDefaultSizes()
  {
    auto defaultSize = this->GetDefaultSize();
    this->width_ = defaultSize.x;
    this->height_ = defaultSize.y;
    auto createParams = this->GetCreationParameters();
    if (this->width_ != 0 && this->height_ != 0)
    {
      Rectangle r = Rectangle::CreateFromBounds(0, 0, 0, 0);
      ::AdjustWindowRectEx(&r, createParams.WindowStyles, false,
        createParams.WindowExStyles);
      this->client_width_ = this->width_ - r.width();
      this->client_height_ = this->height_ - r.height();
    }
  }

  void setParentComponent(Component* newParent)
  {
    if (this->IsCreated())
    {
      HWND parent = ::GetParent(*this);
      bool topLevel = this->IsTopLevel();
      // check to see if the newParent pointer is null and, if it isn't, check
      // to see if the handle value of newParent is null (which should only be
      // the case if the component hasn't been created)
      bool newParentIsValid = (newParent != nullptr && *newParent != nullptr);
      if (newParent != nullptr) // null reference check
      {
        if (parent != *newParent || (parent == nullptr && !topLevel))
        {
          // TODO: update top-level window styles or re-create the component;
          // These things could take a top-level window and make it a child
          // which is why we perform a new top-level check below.
          if (!(this->IsTopLevel()))
          {
            if (!newParentIsValid)
            {
              Component::HoldComponent(this);
            }
            else
            {
              ::SetParent(*this, *newParent);
              if (this->parent_ != nullptr)
              {
                // TODO: update child Z-order
              }
            }
          }
        }
      }
      else if ((!newParentIsValid && parent == nullptr) && topLevel)
      {
        ::SetParent(*this, nullptr);
      }
    }
  }

  LRESULT colorControl(UINT origMsg, HDC hdc, HWND window)
  {
    if (window == *this)
    {
      // NOTE: If controls stop showing their visual styles, this
      // would be the place.
      if (this->background_brush_ == 0)
      {
        this->background_brush_.Assign(this->background_color_);
        DBGOUT("background_brush_ was null, reset to ",
               this->background_brush_.GetValue());
      }

      ::SetBkMode(hdc, static_cast<int>(this->background_mode_));
      ::SetBkColor(hdc, this->background_color_);
      ::SetTextColor(hdc, this->foreground_color_);
      return reinterpret_cast<LRESULT>(this->background_brush_.GetValue());
    }

    // this message isn't meant for us (it's meant for one of the child
    // components); forward it to the real component
    return ::SendMessage(window, origMsg, reinterpret_cast<WPARAM>(hdc),
                         reinterpret_cast<LPARAM>(window));
  }

  // This will be used at some point...
  void drawBackground()
  {
    this->drawBackground(Rectangle(0, 0, this->client_width_, 
      this->client_height_));
  }

  void drawBackground(const Rectangle& rect)
  {
    if (this->background_color_ != Color::Empty)
    {
      Graphics g(*this);
      g.FillRectangle(this->background_brush_, rect);
    }
  }

  void hookMouse()
  {
    if (WM_MOUSEENTER == -1)
    {
      WM_MOUSEENTER =
        ::RegisterWindowMessageW(L"UITKWindowMouseEnter");
    }

    if (this->IsCreated()
        && (!(this->getState(ComponentStates::TrackingMouse))))
    {
      this->setState(ComponentStates::TrackingMouse, true);
      track_mouse_event_.cbSize = sizeof(TRACKMOUSEEVENT);
      track_mouse_event_.dwHoverTime = 100;
      track_mouse_event_.dwFlags = TME_LEAVE | TME_HOVER;
      track_mouse_event_.hwndTrack = *this;
      ::TrackMouseEvent(&track_mouse_event_);
    }
  }

  void unhookMouse()
  {
    this->setState(ComponentStates::TrackingMouse, false);
  }

  bool getState(ComponentStates state) const
  {
    return ((this->window_state_ & static_cast<uint32_t>(state)) != 0);
  }

  void setState(ComponentStates state, bool value)
  {
    this->window_state_ = value ?
                         (this->window_state_ | static_cast<uint32_t>(state))
                         : (this->window_state_ & ~static_cast<uint32_t>(state));
  }

  bool ensureComponentIsCreated()
  {
    bool ret = this->IsCreated();
    if (!ret)
    {
      this->CreateComponent();
    }

    return ret;
  }

  Atom registerComponent(const ComponentCreationParameters& createParams)
  {
    WNDCLASSEXW wndcls = static_cast<WNDCLASSEXW>(createParams);
    if (!createParams.base_class_name().empty())
    {
      if (!::GetClassInfoExW(nullptr,
        createParams.base_class_name_buffer().c_str(), &wndcls))
      {
        if (!::GetClassInfoExW(::GetModuleHandleW(nullptr),
          createParams.base_class_name_buffer().c_str(), &wndcls))
        {
          // TODO: indicate failure to read base window class information
          return 0;
        }
      }

      auto defWndProc = wndcls.lpfnWndProc;
      wndcls.lpfnWndProc = createParams.WindowProc;
      wndcls.style &= ~CS_GLOBALCLASS;
    }

    
    //template <class T>
    //ATLINLINE ATOM AtlModuleRegisterWndClassInfoT(
    //  _In_ _ATL_BASE_MODULE* pBaseModule,
    //  _In_ _ATL_WIN_MODULE* pWinModule,
    //  _Inout_updates_(1) typename T::_ATL_WNDCLASSINFO* p,
    //  _In_ WNDPROC* pProc,
    //  _Inout_ T)
    //{
    //  if (pBaseModule == NULL || pWinModule == NULL || p == NULL || pProc == NULL)
    //  {
    //    ATLTRACE(atlTraceWindowing, 0, _T("ERROR : Invalid Arguments to AtlModuleRegisterWndClassInfoT\n"));
    //    ATLASSERT(0);
    //    return 0;
    //  }

    //  if (p->m_atom == 0)
    //  {
    //    ATL::CComCritSecLock<ATL::CComCriticalSection> lock(pWinModule->m_csWindowCreate, false);
    //    if (FAILED(lock.Lock()))
    //    {
    //      ATLTRACE(atlTraceWindowing, 0, _T("ERROR : Unable to lock critical section in AtlModuleRegisterWndClassInfoT\n"));
    //      ATLASSERT(0);
    //      return 0;
    //    }
    //    if (p->m_atom == 0)
    //    {
    //      if (p->m_lpszOrigName != NULL)
    //      {
    
    //        ATLASSERT(pProc != NULL);
    //        typename T::PCXSTR lpsz = p->m_wc.lpszClassName;
    //        WNDPROC proc = p->m_wc.lpfnWndProc;

    //        typename T::WNDCLASSEX wc;
    //        wc.cbSize = sizeof(T::WNDCLASSEX);
    //        // Try global class
    //        if (!T::GetClassInfoEx(NULL, p->m_lpszOrigName, &wc))
    //        {
    //          // try process local
    //          if (!T::GetClassInfoEx(pBaseModule->m_hInst, p->m_lpszOrigName, &wc))
    //          {
    //            ATLTRACE(atlTraceWindowing, 0, _T("ERROR : Could not obtain Window Class information for %Ts\n"), p->m_lpszOrigName);
    //            return 0;
    //          }
    //        }
    //        p->m_wc = wc;
    //        p->pWndProc = p->m_wc.lpfnWndProc;
    //        p->m_wc.lpszClassName = lpsz;
    //        p->m_wc.lpfnWndProc = proc;
    //      }
    //      else
    //      {
    //        p->m_wc.hCursor = T::LoadCursor(p->m_bSystemCursor ? NULL : pBaseModule->m_hInstResource,
    //          p->m_lpszCursorID);
    //      }

    //      p->m_wc.hInstance = pBaseModule->m_hInst;
    //      p->m_wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes
    //      if (p->m_wc.lpszClassName == NULL)
    //      {
    //        T::FormatWindowClassName(p->m_szAutoName, _countof(p->m_szAutoName), &p->m_wc);
    //        p->m_wc.lpszClassName = p->m_szAutoName;
    //      }
    //      typename T::WNDCLASSEX wcTemp;
    //      wcTemp = p->m_wc;
    //      p->m_atom = static_cast<ATOM>(T::GetClassInfoEx(p->m_wc.hInstance, p->m_wc.lpszClassName, &wcTemp));
    //      if (p->m_atom == 0)
    //      {
    //        p->m_atom = T::RegisterClassEx(pWinModule, &p->m_wc);
    //      }
    //    }
    //  }

    //  if (p->m_lpszOrigName != NULL)
    //  {
    //    ATLASSERT(pProc != NULL);
    //    ATLASSERT(p->pWndProc != NULL);
    //    *pProc = p->pWndProc;
    //  }
    //  return p->m_atom;
    //}
  }

  void transferFocus(int direction)
  {
    if (this->parent_ == nullptr)
    {
      // No parent? No reason to transfer focus.
      return;
    }

    assert(!(this->parent_->components_.empty())); // should never fail
    if (this->parent_->components_.size() == 1)
    {
      // we are the only component at the current layer in the
      // hierarchy. We're done here.
      return;
    }

    int maxIndex = static_cast<int>(this->parent_->components_.size());
    int nextIndex = this->index_ + (direction >= 0 ? 1 : -1);
    // clamp the index between 0 and maxIndex
    if (nextIndex > maxIndex)
    {
      nextIndex = 0;
    }
    else if (nextIndex < 0)
    {
      nextIndex = maxIndex;
    }

    this->parent_->components_[nextIndex]->Focus();
  }

  void updateBounds()
  {
    TRACEIN_THIS;

    Point originalSize = this->client_size();
    RECT r;
    ::GetClientRect(*this, &r);
    int clientWidth = r.right;
    int clientHeight = r.bottom;
    BREAK_IF(clientWidth < 0 || clientHeight < 0);
    ::GetWindowRect(*this, &r);
    if (!this->IsTopLevel())
    {
      ::MapWindowPoints(nullptr, ::GetParent(*this),
                        reinterpret_cast<LPPOINT>(&r), 2);
    }

    if (!this->components_.empty())
    {
      Point newSize(clientWidth, clientHeight);
      this->layout_->DoLayout(*this, originalSize, newSize);
    }

    this->updateBounds(r.left, r.top, r.right - r.left,
                       r.bottom - r.top, clientWidth, clientHeight);
  }

  // this should be the *only* method that updates the size and location
  // member variables
  void updateBounds(int left, int top, int width, int height,
                    int clientWidth, int clientHeight)
  {
    TRACEIN_THIS_ARGS(left, top, width, height, clientWidth,
                      clientHeight);
    bool sizeChanged = this->width_ != width || 
      this->height_ != height ||
      this->client_width_ != clientWidth || 
      this->client_height_ != clientHeight;
    bool locChanged = this->x_ != left || this->y_ != top;
    this->x_ = left;
    this->y_ = top;
    this->width_ = width;
    this->height_ = height;
    this->client_width_ = clientWidth;
    this->client_height_ = clientHeight;
    if (sizeChanged)
    {
      ::InvalidateRect(*this, nullptr, TRUE);
    }
  }

  void updateBounds(int x, int y, int width, int height)
  {
    TRACEIN_THIS_ARGS(x, y, width, height);
    RECT r = {0};
    auto createParams = this->GetCreationParameters();
    ::AdjustWindowRectEx(&r, createParams.WindowStyles, false,
      createParams.WindowExStyles);
    int clientWidth = width - (r.right - r.left);
    int clientHeight = height - (r.bottom - r.top);
    this->updateBounds(x, y, width, height, clientWidth, clientHeight);
  }

  // resets the index values of each child
  void updateChildIndicies()
  {
    for (OwnedComponentCollection::size_type i = 0;
      i < this->components_.size(); ++i)
    {
      this->components_[i]->index_ = static_cast<int>(i);
    }
  }

  void updateChildIndex(Component& component)
  {
    component.index_ = static_cast<int>(this->components_.size() - 1);
    try
    {
      HWND prevParent = reinterpret_cast<HWND>(component.parent_);
      try
      {
        component.AssignParent(this);
      }
      catch (...)
      {
      }

      if (prevParent != reinterpret_cast<HWND>(component.parent_))
      {
        component.setParentComponent(this);
        if (component.visible() && !component.IsCreated())
        {
          component.CreateComponent();
        }
      }
    }
    catch (const std::runtime_error& ex)
    {
      DBGOUT("Caught error: ", ex.what());
    }
  }

  void updateFromClientSize(RECT &clientrect)
  {
    TRACEIN_THIS_ARGS(clientrect.left, clientrect.top, clientrect.right,
      clientrect.bottom);
    auto createParams = this->GetCreationParameters();
    ::AdjustWindowRectEx(&clientrect, createParams.WindowStyles,
      this->HasMenu(), createParams.WindowExStyles);
    this->set_size(clientrect.right - clientrect.left,
      clientrect.bottom - clientrect.top);
  }

  void updateAnchorDelta()
  {
    if (this->parent_ != nullptr)
    {
      this->anchor_delta_.left = this->x_;
      this->anchor_delta_.top = this->y_;
      this->anchor_delta_.right = this->right_distance();
      this->anchor_delta_.bottom = this->bottom_distance();
      Rectangle parentClientRect = this->parent_->client_rectangle();
      int parentWidth = this->parent_->client_width_;
      int parentHeight = this->parent_->client_height_;
      // parentClientRect.x and parentClientRect.y should always be 0 so the
      // below offsetting code shouldn't change anything.
      this->anchor_delta_.left -= parentClientRect.x;
      this->anchor_delta_.top -= parentClientRect.y;
      this->anchor_delta_.right -= parentClientRect.x;
      this->anchor_delta_.bottom -= parentClientRect.y;
      // The anchor deltas are *added* to the control bounds values to set them
      // to the appropriate sizes when their parent is resized. For example:
      //  * textBox1 is anchored to the right
      //  * textBox1.left = 15
      //  * textBox1.right = 315 (making the width 300)
      //  * frame1.client_width = 500
      // This makes textBox1's right anchor delta -185:
      //    textBox1.anchor_delta_right = textBox1.right - frame1.client_width
      //                                = 315 - 500
      //                                = -185
      // When frame1 is resized horizontally to, for example, 465:
      //    textBox1.right = frame1.client_width + textBox1.anchor_delta_right;
      //                   = 465 + -185
      //                   = 280
      if (IsAnchored(this->anchor_, AnchorStyles::Right))
      {
        this->anchor_delta_.right -= parentWidth;
        if (!IsAnchored(this->anchor_, AnchorStyles::Left))
        {
          this->anchor_delta_.left -= parentWidth;
        }
      }
      else if (!IsAnchored(this->anchor_, AnchorStyles::Left))
      {
        this->anchor_delta_.right -= (parentWidth / 2);
        this->anchor_delta_.left -= (parentWidth / 2);
      }

      if (IsAnchored(this->anchor_, AnchorStyles::Bottom))
      {
        this->anchor_delta_.bottom -= parentHeight;
        if (!IsAnchored(this->anchor_, AnchorStyles::Top))
        {
          this->anchor_delta_.top -= parentHeight;
        }
      }
      else if (!IsAnchored(this->anchor_, AnchorStyles::Top))
      {
        this->anchor_delta_.bottom -= (parentHeight / 2);
        this->anchor_delta_.top -= (parentHeight / 2);
      }
    }
  }

  void updateNativeLocation(int x, int y)
  {
    TRACEIN_THIS_ARGS(x, y);
    ::SetWindowPos(*this, nullptr, x, y, 0, 0,
                   SWP_NOZORDER | SWP_NOSIZE);
  }

  void updateNativeSize(int width, int height)
  {
    TRACEIN_THIS_ARGS(width, height);
    ::SetWindowPos(*this, nullptr, 0, 0, width, height,
                   SWP_NOMOVE | SWP_NOZORDER);
  }

  static void HoldComponent(Component* window)
  {
    if (!HoldingComponent.IsCreated())
    {
      HoldingComponent.set_visible(false);
      HoldingComponent.CreateComponent();
    }

    ::SetParent(*window, HoldingComponent);
  }

  static HWND GetHoldingHandle()
  {
    if (!HoldingComponent.IsCreated())
    {
      HoldingComponent.set_visible(false);
      HoldingComponent.CreateComponent();
    }

    return HoldingComponent;
  }

  static std::string GenerateName()
  {
    std::stringstream s;
    s << "Component" << ++Component::ComponentCount;
    return s.str();
  }
};

Component Component::HoldingComponent;
UINT Component::WM_MOUSEENTER = -1;
UINT Component::WM_REDIRECTMSG =
  ::RegisterWindowMessage(TEXT("JutWindowMsgRedirect"));
int Component::ComponentCount = 0;
std::set<Component::OwnedComponent> Component::CreatedComponents;

}
}
}

#endif
