#include "jvs/uitk/uitk.h"
#include "jvs/uitk/win32/application_entry_point.h"

namespace ui = jvs::uitk::win32;
using jvs::uitk::win32::Frame;
using jvs::uitk::win32::Label;
using jvs::uitk::win32::TextBox;
using jvs::uitk::win32::List;
using jvs::uitk::win32::Button;
using jvs::uitk::DockPosition;
using jvs::uitk::AnchorStyles;

int Main(jvs::ArgList args)
{
  Frame mainFrame{};

  auto& itemLabel = 
    mainFrame << ui::AddNewComponent<Label>("Item:", DockPosition::None, 8, 8);
  auto& itemTextBox =
    mainFrame << ui::AddNewComponent<TextBox>(itemLabel, "", DockPosition::Right);
  itemTextBox
    .set_left(itemTextBox.left() + 8)
    .set_right_distance(8)
    .set_anchor(AnchorStyles::Left | AnchorStyles::Top | AnchorStyles::Right)
    ;
  auto& itemList = 
    mainFrame << ui::AddNewComponent<List>(itemTextBox, "", DockPosition::Bottom);
  itemList
    .set_top(itemList.top() + 8)
    .set_left(8)
    .set_right_distance(8)
    .set_height(100)
    .set_anchor(AnchorStyles::All)
    ;

  auto& addItemButton =
    mainFrame << ui::AddNewComponent<Button>(itemList, "&Add", DockPosition::Bottom);
  addItemButton
    .set_width(50)
    .set_height(20)
    .CenterHorizontally()
    .set_anchor(AnchorStyles::Bottom);
    ;
  //addItemButton.set_top(itemList.bottom() + 8);
  //addItemButton.set_anchor(AnchorStyles::Bottom);

  mainFrame
    .set_text("Item List")
    .set_visible(true)
    .Pack()
    .CenterWindow()
    ;

  ui::FrameEventConsumer mainEventConsumer{};
  mainEventConsumer.Closed << [](auto&&, auto&&) { ::PostQuitMessage(0); };
  mainFrame.AddEventConsumer(mainEventConsumer);
  ui::SimpleMessageLoop::Run();
  return 0;
}