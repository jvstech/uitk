
#if !defined (JVS_UITK_WIN32_WINDOWMSGHANDLERS_H_)
#define JVS_UITK_WIN32_WINDOWMSGHANDLERS_H_

#include <unordered_map>
#include <windows.h>
#include "message_id.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

  class MessageHandler
  {
  public:
  static const std::unordered_map<UInt, MessageId> KnownMessagesIds;

  private:
  static std::unordered_map<UInt, MessageId> getKnownMessageIds()
    {
    std::unordered_map<UInt, MessageId> ret{};
      ret[WM_ACTIVATE] = MsgId(WM_ACTIVATE);
      ret[WM_ACTIVATEAPP] = MsgId(WM_ACTIVATEAPP);
      ret[WM_AFXFIRST] = MsgId(WM_AFXFIRST);
      ret[WM_AFXLAST] = MsgId(WM_AFXLAST);
      ret[WM_APP] = MsgId(WM_APP);
      ret[WM_APPCOMMAND] = MsgId(WM_APPCOMMAND);
      ret[WM_ASKCBFORMATNAME] = MsgId(WM_ASKCBFORMATNAME);
      ret[WM_CANCELJOURNAL] = MsgId(WM_CANCELJOURNAL);
      ret[WM_CANCELMODE] = MsgId(WM_CANCELMODE);
      ret[WM_CAPTURECHANGED] = MsgId(WM_CAPTURECHANGED);
      ret[WM_CHANGECBCHAIN] = MsgId(WM_CHANGECBCHAIN);
      ret[WM_CHANGEUISTATE] = MsgId(WM_CHANGEUISTATE);
      ret[WM_CHAR] = MsgId(WM_CHAR);
      ret[WM_CHARTOITEM] = MsgId(WM_CHARTOITEM);
      ret[WM_CHILDACTIVATE] = MsgId(WM_CHILDACTIVATE);
      ret[WM_CLEAR] = MsgId(WM_CLEAR);
      ret[WM_CLIPBOARDUPDATE] = MsgId(WM_CLIPBOARDUPDATE);
      ret[WM_CLOSE] = MsgId(WM_CLOSE);
      ret[WM_COMMAND] = MsgId(WM_COMMAND);
      ret[WM_COMMNOTIFY] = MsgId(WM_COMMNOTIFY);
      ret[WM_COMPACTING] = MsgId(WM_COMPACTING);
      ret[WM_COMPAREITEM] = MsgId(WM_COMPAREITEM);
      ret[WM_CONTEXTMENU] = MsgId(WM_CONTEXTMENU);
      ret[WM_COPY] = MsgId(WM_COPY);
      ret[WM_COPYDATA] = MsgId(WM_COPYDATA);
      ret[WM_CREATE] = MsgId(WM_CREATE);
      ret[WM_CTLCOLORBTN] = MsgId(WM_CTLCOLORBTN);
      ret[WM_CTLCOLORDLG] = MsgId(WM_CTLCOLORDLG);
      ret[WM_CTLCOLOREDIT] = MsgId(WM_CTLCOLOREDIT);
      ret[WM_CTLCOLORLISTBOX] = MsgId(WM_CTLCOLORLISTBOX);
      ret[WM_CTLCOLORMSGBOX] = MsgId(WM_CTLCOLORMSGBOX);
      ret[WM_CTLCOLORSCROLLBAR] = MsgId(WM_CTLCOLORSCROLLBAR);
      ret[WM_CTLCOLORSTATIC] = MsgId(WM_CTLCOLORSTATIC);
      ret[WM_CUT] = MsgId(WM_CUT);
      ret[WM_DEADCHAR] = MsgId(WM_DEADCHAR);
      ret[WM_DELETEITEM] = MsgId(WM_DELETEITEM);
      ret[WM_DESTROY] = MsgId(WM_DESTROY);
      ret[WM_DESTROYCLIPBOARD] = MsgId(WM_DESTROYCLIPBOARD);
      ret[WM_DEVICECHANGE] = MsgId(WM_DEVICECHANGE);
      ret[WM_DEVMODECHANGE] = MsgId(WM_DEVMODECHANGE);
      ret[WM_DISPLAYCHANGE] = MsgId(WM_DISPLAYCHANGE);
      ret[WM_DRAWCLIPBOARD] = MsgId(WM_DRAWCLIPBOARD);
      ret[WM_DRAWITEM] = MsgId(WM_DRAWITEM);
      ret[WM_DROPFILES] = MsgId(WM_DROPFILES);
      ret[WM_DWMCOLORIZATIONCOLORCHANGED] = MsgId(WM_DWMCOLORIZATIONCOLORCHANGED);
      ret[WM_DWMCOMPOSITIONCHANGED] = MsgId(WM_DWMCOMPOSITIONCHANGED);
      ret[WM_DWMNCRENDERINGCHANGED] = MsgId(WM_DWMNCRENDERINGCHANGED);
      ret[WM_DWMSENDICONICLIVEPREVIEWBITMAP] = MsgId(WM_DWMSENDICONICLIVEPREVIEWBITMAP);
      ret[WM_DWMSENDICONICTHUMBNAIL] = MsgId(WM_DWMSENDICONICTHUMBNAIL);
      ret[WM_DWMWINDOWMAXIMIZEDCHANGE] = MsgId(WM_DWMWINDOWMAXIMIZEDCHANGE);
      ret[WM_ENABLE] = MsgId(WM_ENABLE);
      ret[WM_ENDSESSION] = MsgId(WM_ENDSESSION);
      ret[WM_ENTERIDLE] = MsgId(WM_ENTERIDLE);
      ret[WM_ENTERMENULOOP] = MsgId(WM_ENTERMENULOOP);
      ret[WM_ENTERSIZEMOVE] = MsgId(WM_ENTERSIZEMOVE);
      ret[WM_ERASEBKGND] = MsgId(WM_ERASEBKGND);
      ret[WM_EXITMENULOOP] = MsgId(WM_EXITMENULOOP);
      ret[WM_EXITSIZEMOVE] = MsgId(WM_EXITSIZEMOVE);
      ret[WM_FONTCHANGE] = MsgId(WM_FONTCHANGE);
      ret[WM_GESTURE] = MsgId(WM_GESTURE);
      ret[WM_GESTURENOTIFY] = MsgId(WM_GESTURENOTIFY);
      ret[WM_GETDLGCODE] = MsgId(WM_GETDLGCODE);
      ret[WM_GETFONT] = MsgId(WM_GETFONT);
      ret[WM_GETHOTKEY] = MsgId(WM_GETHOTKEY);
      ret[WM_GETICON] = MsgId(WM_GETICON);
      ret[WM_GETMINMAXINFO] = MsgId(WM_GETMINMAXINFO);
      ret[WM_GETOBJECT] = MsgId(WM_GETOBJECT);
      ret[WM_GETTEXT] = MsgId(WM_GETTEXT);
      ret[WM_GETTEXTLENGTH] = MsgId(WM_GETTEXTLENGTH);
      ret[WM_GETTITLEBARINFOEX] = MsgId(WM_GETTITLEBARINFOEX);
      ret[WM_HANDHELDFIRST] = MsgId(WM_HANDHELDFIRST);
      ret[WM_HANDHELDLAST] = MsgId(WM_HANDHELDLAST);
      ret[WM_HELP] = MsgId(WM_HELP);
      ret[WM_HOTKEY] = MsgId(WM_HOTKEY);
      ret[WM_HSCROLL] = MsgId(WM_HSCROLL);
      ret[WM_HSCROLLCLIPBOARD] = MsgId(WM_HSCROLLCLIPBOARD);
      ret[WM_ICONERASEBKGND] = MsgId(WM_ICONERASEBKGND);
      ret[WM_IME_CHAR] = MsgId(WM_IME_CHAR);
      ret[WM_IME_COMPOSITION] = MsgId(WM_IME_COMPOSITION);
      ret[WM_IME_COMPOSITIONFULL] = MsgId(WM_IME_COMPOSITIONFULL);
      ret[WM_IME_CONTROL] = MsgId(WM_IME_CONTROL);
      ret[WM_IME_ENDCOMPOSITION] = MsgId(WM_IME_ENDCOMPOSITION);
      ret[WM_IME_KEYDOWN] = MsgId(WM_IME_KEYDOWN);
      ret[WM_IME_KEYUP] = MsgId(WM_IME_KEYUP);
      ret[WM_IME_NOTIFY] = MsgId(WM_IME_NOTIFY);
      ret[WM_IME_REQUEST] = MsgId(WM_IME_REQUEST);
      ret[WM_IME_SELECT] = MsgId(WM_IME_SELECT);
      ret[WM_IME_SETCONTEXT] = MsgId(WM_IME_SETCONTEXT);
      ret[WM_IME_STARTCOMPOSITION] = MsgId(WM_IME_STARTCOMPOSITION);
      ret[WM_INITDIALOG] = MsgId(WM_INITDIALOG);
      ret[WM_INITMENU] = MsgId(WM_INITMENU);
      ret[WM_INITMENUPOPUP] = MsgId(WM_INITMENUPOPUP);
      ret[WM_INPUT] = MsgId(WM_INPUT);
      ret[WM_INPUTLANGCHANGE] = MsgId(WM_INPUTLANGCHANGE);
      ret[WM_INPUTLANGCHANGEREQUEST] = MsgId(WM_INPUTLANGCHANGEREQUEST);
      ret[WM_INPUT_DEVICE_CHANGE] = MsgId(WM_INPUT_DEVICE_CHANGE);
      ret[WM_KEYDOWN] = MsgId(WM_KEYDOWN);
      ret[WM_KEYUP] = MsgId(WM_KEYUP);
      ret[WM_KILLFOCUS] = MsgId(WM_KILLFOCUS);
      ret[WM_LBUTTONDBLCLK] = MsgId(WM_LBUTTONDBLCLK);
      ret[WM_LBUTTONDOWN] = MsgId(WM_LBUTTONDOWN);
      ret[WM_LBUTTONUP] = MsgId(WM_LBUTTONUP);
      ret[WM_MBUTTONDBLCLK] = MsgId(WM_MBUTTONDBLCLK);
      ret[WM_MBUTTONDOWN] = MsgId(WM_MBUTTONDOWN);
      ret[WM_MBUTTONUP] = MsgId(WM_MBUTTONUP);
      ret[WM_MDIACTIVATE] = MsgId(WM_MDIACTIVATE);
      ret[WM_MDICASCADE] = MsgId(WM_MDICASCADE);
      ret[WM_MDICREATE] = MsgId(WM_MDICREATE);
      ret[WM_MDIDESTROY] = MsgId(WM_MDIDESTROY);
      ret[WM_MDIGETACTIVE] = MsgId(WM_MDIGETACTIVE);
      ret[WM_MDIICONARRANGE] = MsgId(WM_MDIICONARRANGE);
      ret[WM_MDIMAXIMIZE] = MsgId(WM_MDIMAXIMIZE);
      ret[WM_MDINEXT] = MsgId(WM_MDINEXT);
      ret[WM_MDIREFRESHMENU] = MsgId(WM_MDIREFRESHMENU);
      ret[WM_MDIRESTORE] = MsgId(WM_MDIRESTORE);
      ret[WM_MDISETMENU] = MsgId(WM_MDISETMENU);
      ret[WM_MDITILE] = MsgId(WM_MDITILE);
      ret[WM_MEASUREITEM] = MsgId(WM_MEASUREITEM);
      ret[WM_MENUCHAR] = MsgId(WM_MENUCHAR);
      ret[WM_MENUCOMMAND] = MsgId(WM_MENUCOMMAND);
      ret[WM_MENUDRAG] = MsgId(WM_MENUDRAG);
      ret[WM_MENUGETOBJECT] = MsgId(WM_MENUGETOBJECT);
      ret[WM_MENURBUTTONUP] = MsgId(WM_MENURBUTTONUP);
      ret[WM_MENUSELECT] = MsgId(WM_MENUSELECT);
      ret[WM_MOUSEACTIVATE] = MsgId(WM_MOUSEACTIVATE);
      ret[WM_MOUSEHOVER] = MsgId(WM_MOUSEHOVER);
      ret[WM_MOUSEHWHEEL] = MsgId(WM_MOUSEHWHEEL);
      ret[WM_MOUSELEAVE] = MsgId(WM_MOUSELEAVE);
      ret[WM_MOUSEMOVE] = MsgId(WM_MOUSEMOVE);
      ret[WM_MOUSEWHEEL] = MsgId(WM_MOUSEWHEEL);
      ret[WM_MOVE] = MsgId(WM_MOVE);
      ret[WM_MOVING] = MsgId(WM_MOVING);
      ret[WM_NCACTIVATE] = MsgId(WM_NCACTIVATE);
      ret[WM_NCCALCSIZE] = MsgId(WM_NCCALCSIZE);
      ret[WM_NCCREATE] = MsgId(WM_NCCREATE);
      ret[WM_NCDESTROY] = MsgId(WM_NCDESTROY);
      ret[WM_NCHITTEST] = MsgId(WM_NCHITTEST);
      ret[WM_NCLBUTTONDBLCLK] = MsgId(WM_NCLBUTTONDBLCLK);
      ret[WM_NCLBUTTONDOWN] = MsgId(WM_NCLBUTTONDOWN);
      ret[WM_NCLBUTTONUP] = MsgId(WM_NCLBUTTONUP);
      ret[WM_NCMBUTTONDBLCLK] = MsgId(WM_NCMBUTTONDBLCLK);
      ret[WM_NCMBUTTONDOWN] = MsgId(WM_NCMBUTTONDOWN);
      ret[WM_NCMBUTTONUP] = MsgId(WM_NCMBUTTONUP);
      ret[WM_NCMOUSEHOVER] = MsgId(WM_NCMOUSEHOVER);
      ret[WM_NCMOUSELEAVE] = MsgId(WM_NCMOUSELEAVE);
      ret[WM_NCMOUSEMOVE] = MsgId(WM_NCMOUSEMOVE);
      ret[WM_NCPAINT] = MsgId(WM_NCPAINT);
      ret[WM_NCRBUTTONDBLCLK] = MsgId(WM_NCRBUTTONDBLCLK);
      ret[WM_NCRBUTTONDOWN] = MsgId(WM_NCRBUTTONDOWN);
      ret[WM_NCRBUTTONUP] = MsgId(WM_NCRBUTTONUP);
      ret[WM_NCXBUTTONDBLCLK] = MsgId(WM_NCXBUTTONDBLCLK);
      ret[WM_NCXBUTTONDOWN] = MsgId(WM_NCXBUTTONDOWN);
      ret[WM_NCXBUTTONUP] = MsgId(WM_NCXBUTTONUP);
      ret[WM_NEXTDLGCTL] = MsgId(WM_NEXTDLGCTL);
      ret[WM_NEXTMENU] = MsgId(WM_NEXTMENU);
      ret[WM_NOTIFY] = MsgId(WM_NOTIFY);
      ret[WM_NOTIFYFORMAT] = MsgId(WM_NOTIFYFORMAT);
      ret[WM_NULL] = MsgId(WM_NULL);
      ret[WM_PAINT] = MsgId(WM_PAINT);
      ret[WM_PAINTCLIPBOARD] = MsgId(WM_PAINTCLIPBOARD);
      ret[WM_PAINTICON] = MsgId(WM_PAINTICON);
      ret[WM_PALETTECHANGED] = MsgId(WM_PALETTECHANGED);
      ret[WM_PALETTEISCHANGING] = MsgId(WM_PALETTEISCHANGING);
      ret[WM_PARENTNOTIFY] = MsgId(WM_PARENTNOTIFY);
      ret[WM_PASTE] = MsgId(WM_PASTE);
      ret[WM_PENWINFIRST] = MsgId(WM_PENWINFIRST);
      ret[WM_PENWINLAST] = MsgId(WM_PENWINLAST);
      ret[WM_POWER] = MsgId(WM_POWER);
      ret[WM_POWERBROADCAST] = MsgId(WM_POWERBROADCAST);
      ret[WM_PRINT] = MsgId(WM_PRINT);
      ret[WM_PRINTCLIENT] = MsgId(WM_PRINTCLIENT);
      ret[WM_QUERYDRAGICON] = MsgId(WM_QUERYDRAGICON);
      ret[WM_QUERYENDSESSION] = MsgId(WM_QUERYENDSESSION);
      ret[WM_QUERYNEWPALETTE] = MsgId(WM_QUERYNEWPALETTE);
      ret[WM_QUERYOPEN] = MsgId(WM_QUERYOPEN);
      ret[WM_QUERYUISTATE] = MsgId(WM_QUERYUISTATE);
      ret[WM_QUEUESYNC] = MsgId(WM_QUEUESYNC);
      ret[WM_QUIT] = MsgId(WM_QUIT);
      ret[WM_RBUTTONDBLCLK] = MsgId(WM_RBUTTONDBLCLK);
      ret[WM_RBUTTONDOWN] = MsgId(WM_RBUTTONDOWN);
      ret[WM_RBUTTONUP] = MsgId(WM_RBUTTONUP);
      ret[WM_RENDERALLFORMATS] = MsgId(WM_RENDERALLFORMATS);
      ret[WM_RENDERFORMAT] = MsgId(WM_RENDERFORMAT);
      ret[WM_SETCURSOR] = MsgId(WM_SETCURSOR);
      ret[WM_SETFOCUS] = MsgId(WM_SETFOCUS);
      ret[WM_SETFONT] = MsgId(WM_SETFONT);
      ret[WM_SETHOTKEY] = MsgId(WM_SETHOTKEY);
      ret[WM_SETICON] = MsgId(WM_SETICON);
      ret[WM_SETREDRAW] = MsgId(WM_SETREDRAW);
      ret[WM_SETTEXT] = MsgId(WM_SETTEXT);
      ret[WM_SETTINGCHANGE] = MsgId(WM_SETTINGCHANGE);
      ret[WM_SHOWWINDOW] = MsgId(WM_SHOWWINDOW);
      ret[WM_SIZE] = MsgId(WM_SIZE);
      ret[WM_SIZECLIPBOARD] = MsgId(WM_SIZECLIPBOARD);
      ret[WM_SIZING] = MsgId(WM_SIZING);
      ret[WM_SPOOLERSTATUS] = MsgId(WM_SPOOLERSTATUS);
      ret[WM_STYLECHANGED] = MsgId(WM_STYLECHANGED);
      ret[WM_STYLECHANGING] = MsgId(WM_STYLECHANGING);
      ret[WM_SYNCPAINT] = MsgId(WM_SYNCPAINT);
      ret[WM_SYSCHAR] = MsgId(WM_SYSCHAR);
      ret[WM_SYSCOLORCHANGE] = MsgId(WM_SYSCOLORCHANGE);
      ret[WM_SYSCOMMAND] = MsgId(WM_SYSCOMMAND);
      ret[WM_SYSDEADCHAR] = MsgId(WM_SYSDEADCHAR);
      ret[WM_SYSKEYDOWN] = MsgId(WM_SYSKEYDOWN);
      ret[WM_SYSKEYUP] = MsgId(WM_SYSKEYUP);
      ret[WM_TABLET_FIRST] = MsgId(WM_TABLET_FIRST);
      ret[WM_TABLET_LAST] = MsgId(WM_TABLET_LAST);
      ret[WM_TCARD] = MsgId(WM_TCARD);
      ret[WM_THEMECHANGED] = MsgId(WM_THEMECHANGED);
      ret[WM_TIMECHANGE] = MsgId(WM_TIMECHANGE);
      ret[WM_TIMER] = MsgId(WM_TIMER);
      ret[WM_TOUCH] = MsgId(WM_TOUCH);
      ret[WM_UNDO] = MsgId(WM_UNDO);
      ret[WM_UNICHAR] = MsgId(WM_UNICHAR);
      ret[WM_UNINITMENUPOPUP] = MsgId(WM_UNINITMENUPOPUP);
      ret[WM_UPDATEUISTATE] = MsgId(WM_UPDATEUISTATE);
      ret[WM_USER] = MsgId(WM_USER);
      ret[WM_USERCHANGED] = MsgId(WM_USERCHANGED);
      ret[WM_VKEYTOITEM] = MsgId(WM_VKEYTOITEM);
      ret[WM_VSCROLL] = MsgId(WM_VSCROLL);
      ret[WM_VSCROLLCLIPBOARD] = MsgId(WM_VSCROLLCLIPBOARD);
      ret[WM_WINDOWPOSCHANGED] = MsgId(WM_WINDOWPOSCHANGED);
      ret[WM_WINDOWPOSCHANGING] = MsgId(WM_WINDOWPOSCHANGING);
      ret[WM_WTSSESSION_CHANGE] = MsgId(WM_WTSSESSION_CHANGE);
      ret[WM_XBUTTONDBLCLK] = MsgId(WM_XBUTTONDBLCLK);
      ret[WM_XBUTTONDOWN] = MsgId(WM_XBUTTONDOWN);
      ret[WM_XBUTTONUP] = MsgId(WM_XBUTTONUP);
      return ret;
    }

  protected:

    // Default window message handlers - these are here for ease of overrides
    // // // // // // // // // // // // // // // // // // // // // // // // /

  inline virtual LResult WmActivate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmActivateApp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmAfxFirst(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmAfxLast(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmApp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmAppCommand(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmAskCbFormatName(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCancelJournal(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCancelMode(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCaptureChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmChangeCbChain(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmChangeUiState(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCharToItem(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmChildActivate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmClear(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmClipboardUpdate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmClose(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCommand(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCommNotify(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCompacting(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCompareItem(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmContextmenu(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCopy(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCopyData(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCreate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorBtn(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorDlg(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorEdit(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorListbox(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorMsgbox(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorScrollbar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCtlColorStatic(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmCut(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDeadChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDeleteItem(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDestroy(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDestroyClipboard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDeviceChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDevModeChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDisplayChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDrawClipboard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDrawItem(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDropFiles(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDwmColorizationColorChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDwmCompositionChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDwmNcRenderingChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDwmSendIconicLivePreviewBitmap(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDwmSendIconicThumbnail(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmDwmWindowMaximizedChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmEnable(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmEndSession(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmEnterIdle(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmEnterMenuLoop(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmEnterSizeMove(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmEraseBkgnd(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmExitMenuLoop(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmExitSizeMove(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmFontChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGesture(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGestureNotify(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetDlgCode(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetFont(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetHotkey(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetIcon(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetMinMaxInfo(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetObject(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetText(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetTextLength(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmGetTitlebarInfoEx(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmHandheldFirst(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmHandheldLast(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmHelp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmHotkey(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmHscroll(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmHscrollClipboard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmIconEraseBkgnd(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeComposition(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeCompositionFull(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeControl(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeEndComposition(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeKeyDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeKeyLast(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeKeyUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeNotify(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeRequest(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeSelect(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeSetContext(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmImeStartComposition(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInitDialog(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInitMenu(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInitMenuPopup(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInput(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInputLangChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInputLangChangeRequest(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmInputDeviceChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmKeyDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmKeyUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmKillFocus(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmLButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmLButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmLButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiActivate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiCascade(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdicreate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiDestroy(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiGetActive(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiIconArrange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiMaximize(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiNext(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiRefreshMenu(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiRestore(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiSetMenu(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMdiTile(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMeasureItem(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMenuChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMenuCommand(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMenuDrag(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMenuGetObject(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMenuRButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMenuSelect(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMouseActivate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMouseHover(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMouseHwheel(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMouseLeave(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMouseMove(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMouseWheel(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMove(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmMoving(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcActivate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcCalcSize(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcCreate(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcDestroy(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcHitTest(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcLButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcLButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcLButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcMButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcMButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcMButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcMouseHover(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcMouseLeave(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcMouseMove(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcPaint(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcRButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcRButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcRButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcXButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcXButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNcXButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNextDlgCtl(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNextMenu(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNotify(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNotifyFormat(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmNull(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPaint(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPaintClipboard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPaintIcon(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPaletteChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPaletteIsChanging(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmParentNotify(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPaste(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPenWinFirst(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPenWinLast(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPower(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPowerBroadcast(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPrint(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmPrintClient(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQueryDragIcon(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQueryEndSession(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQueryNewPalette(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQueryOpen(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQueryUiState(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQueueSync(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmQuit(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmRButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmRButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmRButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmRenderAllFormats(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmRenderFormat(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetCursor(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetFocus(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetFont(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetHotkey(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetIcon(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetRedraw(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSetText(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSettingChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmShowWindow(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSizeClipboard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSize(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSizing(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSpoolerStatus(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmStyleChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmStyleChanging(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSyncPaint(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSysChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSysColorChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSysCommand(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSysDeadChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSysKeyDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmSysKeyUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmTabletFirst(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmTabletLast(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmTCard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmThemeChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmTimeChange(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmTimer(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmTouch(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmUndo(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmUniChar(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmUnInitMenuPopup(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmUpdateUiState(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmUser(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmUserchanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmVkeyToItem(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmVscroll(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmVscrollClipboard(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmWindowPosChanged(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmWindowPosChanging(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmWtsSession_Change(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmXButtonDblClk(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmXButtonDown(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult WmXButtonUp(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }
  inline virtual LResult Message(LResult defaultResult, MSG& msg, bool& handled) { return defaultResult; }

  LResult RouteMessage(LResult defaultResult, MSG& msg, bool& handled)
    {
    LResult lresult = 0;

      switch (msg.message)
      {
      case WM_ACTIVATE:
        
        lresult = this->WmActivate(defaultResult, msg, handled);
        break;

      case WM_ACTIVATEAPP:
        
        lresult = this->WmActivateApp(defaultResult, msg, handled);
        break;

      case WM_AFXFIRST:
        
        lresult = this->WmAfxFirst(defaultResult, msg, handled);
        break;

      case WM_AFXLAST:
        
        lresult = this->WmAfxLast(defaultResult, msg, handled);
        break;

      case WM_APP:
        
        lresult = this->WmApp(defaultResult, msg, handled);
        break;

      case WM_APPCOMMAND:
        
        lresult = this->WmAppCommand(defaultResult, msg, handled);
        break;

      case WM_ASKCBFORMATNAME:
        
        lresult = this->WmAskCbFormatName(defaultResult, msg, handled);
        break;

      case WM_CANCELJOURNAL:
        
        lresult = this->WmCancelJournal(defaultResult, msg, handled);
        break;

      case WM_CANCELMODE:
        
        lresult = this->WmCancelMode(defaultResult, msg, handled);
        break;

      case WM_CAPTURECHANGED:
        
        lresult = this->WmCaptureChanged(defaultResult, msg, handled);
        break;

      case WM_CHANGECBCHAIN:
        
        lresult = this->WmChangeCbChain(defaultResult, msg, handled);
        break;

      case WM_CHANGEUISTATE:
        
        lresult = this->WmChangeUiState(defaultResult, msg, handled);
        break;

      case WM_CHAR:
        
        lresult = this->WmChar(defaultResult, msg, handled);
        break;

      case WM_CHARTOITEM:
        
        lresult = this->WmCharToItem(defaultResult, msg, handled);
        break;

      case WM_CHILDACTIVATE:
        
        lresult = this->WmChildActivate(defaultResult, msg, handled);
        break;

      case WM_CLEAR:
        
        lresult = this->WmClear(defaultResult, msg, handled);
        break;

      case WM_CLIPBOARDUPDATE:
        
        lresult = this->WmClipboardUpdate(defaultResult, msg, handled);
        break;

      case WM_CLOSE:
        
        lresult = this->WmClose(defaultResult, msg, handled);
        break;

      case WM_COMMAND:
        
        lresult = this->WmCommand(defaultResult, msg, handled);
        break;

      case WM_COMMNOTIFY:
        
        lresult = this->WmCommNotify(defaultResult, msg, handled);
        break;

      case WM_COMPACTING:
        
        lresult = this->WmCompacting(defaultResult, msg, handled);
        break;

      case WM_COMPAREITEM:
        
        lresult = this->WmCompareItem(defaultResult, msg, handled);
        break;

      case WM_CONTEXTMENU:
        
        lresult = this->WmContextmenu(defaultResult, msg, handled);
        break;

      case WM_COPY:
        
        lresult = this->WmCopy(defaultResult, msg, handled);
        break;

      case WM_COPYDATA:
        
        lresult = this->WmCopyData(defaultResult, msg, handled);
        break;

      case WM_CREATE:
        
        lresult = this->WmCreate(defaultResult, msg, handled);
        break;

      case WM_CTLCOLORBTN:
        
        lresult = this->WmCtlColorBtn(defaultResult, msg, handled);
        break;

      case WM_CTLCOLORDLG:
        
        lresult = this->WmCtlColorDlg(defaultResult, msg, handled);
        break;

      case WM_CTLCOLOREDIT:
        
        lresult = this->WmCtlColorEdit(defaultResult, msg, handled);
        break;

      case WM_CTLCOLORLISTBOX:
        
        lresult = this->WmCtlColorListbox(defaultResult, msg, handled);
        break;

      case WM_CTLCOLORMSGBOX:
        
        lresult = this->WmCtlColorMsgbox(defaultResult, msg, handled);
        break;

      case WM_CTLCOLORSCROLLBAR:
        
        lresult = this->WmCtlColorScrollbar(defaultResult, msg, handled);
        break;

      case WM_CTLCOLORSTATIC:
        
        lresult = this->WmCtlColorStatic(defaultResult, msg, handled);
        break;

      case WM_CUT:
        
        lresult = this->WmCut(defaultResult, msg, handled);
        break;

      case WM_DEADCHAR:
        
        lresult = this->WmDeadChar(defaultResult, msg, handled);
        break;

      case WM_DELETEITEM:
        
        lresult = this->WmDeleteItem(defaultResult, msg, handled);
        break;

      case WM_DESTROY:
        
        lresult = this->WmDestroy(defaultResult, msg, handled);
        break;

      case WM_DESTROYCLIPBOARD:
        
        lresult = this->WmDestroyClipboard(defaultResult, msg, handled);
        break;

      case WM_DEVICECHANGE:
        
        lresult = this->WmDeviceChange(defaultResult, msg, handled);
        break;

      case WM_DEVMODECHANGE:
        
        lresult = this->WmDevModeChange(defaultResult, msg, handled);
        break;

      case WM_DISPLAYCHANGE:
        
        lresult = this->WmDisplayChange(defaultResult, msg, handled);
        break;

      case WM_DRAWCLIPBOARD:
        
        lresult = this->WmDrawClipboard(defaultResult, msg, handled);
        break;

      case WM_DRAWITEM:
        
        lresult = this->WmDrawItem(defaultResult, msg, handled);
        break;

      case WM_DROPFILES:
        
        lresult = this->WmDropFiles(defaultResult, msg, handled);
        break;

      case WM_DWMCOLORIZATIONCOLORCHANGED:
        
        lresult = this->WmDwmColorizationColorChanged(defaultResult, msg, handled);
        break;

      case WM_DWMCOMPOSITIONCHANGED:
        
        lresult = this->WmDwmCompositionChanged(defaultResult, msg, handled);
        break;

      case WM_DWMNCRENDERINGCHANGED:
        
        lresult = this->WmDwmNcRenderingChanged(defaultResult, msg, handled);
        break;

      case WM_DWMSENDICONICLIVEPREVIEWBITMAP:
        
        lresult = this->WmDwmSendIconicLivePreviewBitmap(defaultResult, msg, handled);
        break;

      case WM_DWMSENDICONICTHUMBNAIL:
        
        lresult = this->WmDwmSendIconicThumbnail(defaultResult, msg, handled);
        break;

      case WM_DWMWINDOWMAXIMIZEDCHANGE:
        
        lresult = this->WmDwmWindowMaximizedChange(defaultResult, msg, handled);
        break;

      case WM_ENABLE:
        
        lresult = this->WmEnable(defaultResult, msg, handled);
        break;

      case WM_ENDSESSION:
        
        lresult = this->WmEndSession(defaultResult, msg, handled);
        break;

      case WM_ENTERIDLE:
        
        lresult = this->WmEnterIdle(defaultResult, msg, handled);
        break;

      case WM_ENTERMENULOOP:
        
        lresult = this->WmEnterMenuLoop(defaultResult, msg, handled);
        break;

      case WM_ENTERSIZEMOVE:
        
        lresult = this->WmEnterSizeMove(defaultResult, msg, handled);
        break;

      case WM_ERASEBKGND:
        
        lresult = this->WmEraseBkgnd(defaultResult, msg, handled);
        break;

      case WM_EXITMENULOOP:
        
        lresult = this->WmExitMenuLoop(defaultResult, msg, handled);
        break;

      case WM_EXITSIZEMOVE:
        
        lresult = this->WmExitSizeMove(defaultResult, msg, handled);
        break;

      case WM_FONTCHANGE:
        
        lresult = this->WmFontChange(defaultResult, msg, handled);
        break;

      case WM_GESTURE:
        
        lresult = this->WmGesture(defaultResult, msg, handled);
        break;

      case WM_GESTURENOTIFY:
        
        lresult = this->WmGestureNotify(defaultResult, msg, handled);
        break;

      case WM_GETDLGCODE:
        
        lresult = this->WmGetDlgCode(defaultResult, msg, handled);
        break;

      case WM_GETFONT:
        
        lresult = this->WmGetFont(defaultResult, msg, handled);
        break;

      case WM_GETHOTKEY:
        
        lresult = this->WmGetHotkey(defaultResult, msg, handled);
        break;

      case WM_GETICON:
        
        lresult = this->WmGetIcon(defaultResult, msg, handled);
        break;

      case WM_GETMINMAXINFO:
        
        lresult = this->WmGetMinMaxInfo(defaultResult, msg, handled);
        break;

      case WM_GETOBJECT:
        
        lresult = this->WmGetObject(defaultResult, msg, handled);
        break;

      case WM_GETTEXT:
        
        lresult = this->WmGetText(defaultResult, msg, handled);
        break;

      case WM_GETTEXTLENGTH:
        
        lresult = this->WmGetTextLength(defaultResult, msg, handled);
        break;

      case WM_GETTITLEBARINFOEX:
        
        lresult = this->WmGetTitlebarInfoEx(defaultResult, msg, handled);
        break;

      case WM_HANDHELDFIRST:
        
        lresult = this->WmHandheldFirst(defaultResult, msg, handled);
        break;

      case WM_HANDHELDLAST:
        
        lresult = this->WmHandheldLast(defaultResult, msg, handled);
        break;

      case WM_HELP:
        
        lresult = this->WmHelp(defaultResult, msg, handled);
        break;

      case WM_HOTKEY:
        
        lresult = this->WmHotkey(defaultResult, msg, handled);
        break;

      case WM_HSCROLL:
        
        lresult = this->WmHscroll(defaultResult, msg, handled);
        break;

      case WM_HSCROLLCLIPBOARD:
        
        lresult = this->WmHscrollClipboard(defaultResult, msg, handled);
        break;

      case WM_ICONERASEBKGND:
        
        lresult = this->WmIconEraseBkgnd(defaultResult, msg, handled);
        break;

      case WM_IME_CHAR:
        
        lresult = this->WmImeChar(defaultResult, msg, handled);
        break;

      case WM_IME_COMPOSITION:
        
        lresult = this->WmImeComposition(defaultResult, msg, handled);
        break;

      case WM_IME_COMPOSITIONFULL:
        
        lresult = this->WmImeCompositionFull(defaultResult, msg, handled);
        break;

      case WM_IME_CONTROL:
        
        lresult = this->WmImeControl(defaultResult, msg, handled);
        break;

      case WM_IME_ENDCOMPOSITION:
        
        lresult = this->WmImeEndComposition(defaultResult, msg, handled);
        break;

      case WM_IME_KEYDOWN:
        
        lresult = this->WmImeKeyDown(defaultResult, msg, handled);
        break;

      case WM_IME_KEYUP:
        
        lresult = this->WmImeKeyUp(defaultResult, msg, handled);
        break;

      case WM_IME_NOTIFY:
        
        lresult = this->WmImeNotify(defaultResult, msg, handled);
        break;

      case WM_IME_REQUEST:
        
        lresult = this->WmImeRequest(defaultResult, msg, handled);
        break;

      case WM_IME_SELECT:
        
        lresult = this->WmImeSelect(defaultResult, msg, handled);
        break;

      case WM_IME_SETCONTEXT:
        
        lresult = this->WmImeSetContext(defaultResult, msg, handled);
        break;

      case WM_IME_STARTCOMPOSITION:
        
        lresult = this->WmImeStartComposition(defaultResult, msg, handled);
        break;

      case WM_INITDIALOG:
        
        lresult = this->WmInitDialog(defaultResult, msg, handled);
        break;

      case WM_INITMENU:
        
        lresult = this->WmInitMenu(defaultResult, msg, handled);
        break;

      case WM_INITMENUPOPUP:
        
        lresult = this->WmInitMenuPopup(defaultResult, msg, handled);
        break;

      case WM_INPUT:
        
        lresult = this->WmInput(defaultResult, msg, handled);
        break;

      case WM_INPUTLANGCHANGE:
        
        lresult = this->WmInputLangChange(defaultResult, msg, handled);
        break;

      case WM_INPUTLANGCHANGEREQUEST:
        
        lresult = this->WmInputLangChangeRequest(defaultResult, msg, handled);
        break;

      case WM_INPUT_DEVICE_CHANGE:
        
        lresult = this->WmInputDeviceChange(defaultResult, msg, handled);
        break;

      case WM_KEYDOWN:
        
        lresult = this->WmKeyDown(defaultResult, msg, handled);
        break;

      case WM_KEYUP:
        
        lresult = this->WmKeyUp(defaultResult, msg, handled);
        break;

      case WM_KILLFOCUS:
        
        lresult = this->WmKillFocus(defaultResult, msg, handled);
        break;

      case WM_LBUTTONDBLCLK:
        
        lresult = this->WmLButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_LBUTTONDOWN:
        
        lresult = this->WmLButtonDown(defaultResult, msg, handled);
        break;

      case WM_LBUTTONUP:
        
        lresult = this->WmLButtonUp(defaultResult, msg, handled);
        break;

      case WM_MBUTTONDBLCLK:
        
        lresult = this->WmMButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_MBUTTONDOWN:
        
        lresult = this->WmMButtonDown(defaultResult, msg, handled);
        break;

      case WM_MBUTTONUP:
        
        lresult = this->WmMButtonUp(defaultResult, msg, handled);
        break;

      case WM_MDIACTIVATE:
        
        lresult = this->WmMdiActivate(defaultResult, msg, handled);
        break;

      case WM_MDICASCADE:
        
        lresult = this->WmMdiCascade(defaultResult, msg, handled);
        break;

      case WM_MDICREATE:
        
        lresult = this->WmMdicreate(defaultResult, msg, handled);
        break;

      case WM_MDIDESTROY:
        
        lresult = this->WmMdiDestroy(defaultResult, msg, handled);
        break;

      case WM_MDIGETACTIVE:
        
        lresult = this->WmMdiGetActive(defaultResult, msg, handled);
        break;

      case WM_MDIICONARRANGE:
        
        lresult = this->WmMdiIconArrange(defaultResult, msg, handled);
        break;

      case WM_MDIMAXIMIZE:
        
        lresult = this->WmMdiMaximize(defaultResult, msg, handled);
        break;

      case WM_MDINEXT:
        
        lresult = this->WmMdiNext(defaultResult, msg, handled);
        break;

      case WM_MDIREFRESHMENU:
        
        lresult = this->WmMdiRefreshMenu(defaultResult, msg, handled);
        break;

      case WM_MDIRESTORE:
        
        lresult = this->WmMdiRestore(defaultResult, msg, handled);
        break;

      case WM_MDISETMENU:
        
        lresult = this->WmMdiSetMenu(defaultResult, msg, handled);
        break;

      case WM_MDITILE:
        
        lresult = this->WmMdiTile(defaultResult, msg, handled);
        break;

      case WM_MEASUREITEM:
        
        lresult = this->WmMeasureItem(defaultResult, msg, handled);
        break;

      case WM_MENUCHAR:
        
        lresult = this->WmMenuChar(defaultResult, msg, handled);
        break;

      case WM_MENUCOMMAND:
        
        lresult = this->WmMenuCommand(defaultResult, msg, handled);
        break;

      case WM_MENUDRAG:
        
        lresult = this->WmMenuDrag(defaultResult, msg, handled);
        break;

      case WM_MENUGETOBJECT:
        
        lresult = this->WmMenuGetObject(defaultResult, msg, handled);
        break;

      case WM_MENURBUTTONUP:
        
        lresult = this->WmMenuRButtonUp(defaultResult, msg, handled);
        break;

      case WM_MENUSELECT:
        
        lresult = this->WmMenuSelect(defaultResult, msg, handled);
        break;

      case WM_MOUSEACTIVATE:
        
        lresult = this->WmMouseActivate(defaultResult, msg, handled);
        break;

      case WM_MOUSEHOVER:
        
        lresult = this->WmMouseHover(defaultResult, msg, handled);
        break;

      case WM_MOUSEHWHEEL:
        
        lresult = this->WmMouseHwheel(defaultResult, msg, handled);
        break;

      case WM_MOUSELEAVE:
        
        lresult = this->WmMouseLeave(defaultResult, msg, handled);
        break;

      case WM_MOUSEMOVE:
        
        lresult = this->WmMouseMove(defaultResult, msg, handled);
        break;

      case WM_MOUSEWHEEL:
        
        lresult = this->WmMouseWheel(defaultResult, msg, handled);
        break;

      case WM_MOVE:
        
        lresult = this->WmMove(defaultResult, msg, handled);
        break;

      case WM_MOVING:
        
        lresult = this->WmMoving(defaultResult, msg, handled);
        break;

      case WM_NCACTIVATE:
        
        lresult = this->WmNcActivate(defaultResult, msg, handled);
        break;

      case WM_NCCALCSIZE:
        
        lresult = this->WmNcCalcSize(defaultResult, msg, handled);
        break;

      case WM_NCCREATE:
        
        lresult = this->WmNcCreate(defaultResult, msg, handled);
        break;

      case WM_NCDESTROY:
        
        lresult = this->WmNcDestroy(defaultResult, msg, handled);
        break;

      case WM_NCHITTEST:
        
        lresult = this->WmNcHitTest(defaultResult, msg, handled);
        break;

      case WM_NCLBUTTONDBLCLK:
        
        lresult = this->WmNcLButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_NCLBUTTONDOWN:
        
        lresult = this->WmNcLButtonDown(defaultResult, msg, handled);
        break;

      case WM_NCLBUTTONUP:
        
        lresult = this->WmNcLButtonUp(defaultResult, msg, handled);
        break;

      case WM_NCMBUTTONDBLCLK:
        
        lresult = this->WmNcMButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_NCMBUTTONDOWN:
        
        lresult = this->WmNcMButtonDown(defaultResult, msg, handled);
        break;

      case WM_NCMBUTTONUP:
        
        lresult = this->WmNcMButtonUp(defaultResult, msg, handled);
        break;

      case WM_NCMOUSEHOVER:
        
        lresult = this->WmNcMouseHover(defaultResult, msg, handled);
        break;

      case WM_NCMOUSELEAVE:
        
        lresult = this->WmNcMouseLeave(defaultResult, msg, handled);
        break;

      case WM_NCMOUSEMOVE:
        
        lresult = this->WmNcMouseMove(defaultResult, msg, handled);
        break;

      case WM_NCPAINT:
        
        lresult = this->WmNcPaint(defaultResult, msg, handled);
        break;

      case WM_NCRBUTTONDBLCLK:
        
        lresult = this->WmNcRButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_NCRBUTTONDOWN:
        
        lresult = this->WmNcRButtonDown(defaultResult, msg, handled);
        break;

      case WM_NCRBUTTONUP:
        
        lresult = this->WmNcRButtonUp(defaultResult, msg, handled);
        break;

      case WM_NCXBUTTONDBLCLK:
        
        lresult = this->WmNcXButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_NCXBUTTONDOWN:
        
        lresult = this->WmNcXButtonDown(defaultResult, msg, handled);
        break;

      case WM_NCXBUTTONUP:
        
        lresult = this->WmNcXButtonUp(defaultResult, msg, handled);
        break;

      case WM_NEXTDLGCTL:
        
        lresult = this->WmNextDlgCtl(defaultResult, msg, handled);
        break;

      case WM_NEXTMENU:
        
        lresult = this->WmNextMenu(defaultResult, msg, handled);
        break;

      case WM_NOTIFY:
        
        lresult = this->WmNotify(defaultResult, msg, handled);
        break;

      case WM_NOTIFYFORMAT:
        
        lresult = this->WmNotifyFormat(defaultResult, msg, handled);
        break;

      case WM_NULL:
        
        lresult = this->WmNull(defaultResult, msg, handled);
        break;

      case WM_PAINT:
        
        lresult = this->WmPaint(defaultResult, msg, handled);
        break;

      case WM_PAINTCLIPBOARD:
        
        lresult = this->WmPaintClipboard(defaultResult, msg, handled);
        break;

      case WM_PAINTICON:
        
        lresult = this->WmPaintIcon(defaultResult, msg, handled);
        break;

      case WM_PALETTECHANGED:
        
        lresult = this->WmPaletteChanged(defaultResult, msg, handled);
        break;

      case WM_PALETTEISCHANGING:
        
        lresult = this->WmPaletteIsChanging(defaultResult, msg, handled);
        break;

      case WM_PARENTNOTIFY:
        
        lresult = this->WmParentNotify(defaultResult, msg, handled);
        break;

      case WM_PASTE:
        
        lresult = this->WmPaste(defaultResult, msg, handled);
        break;

      case WM_PENWINFIRST:
        
        lresult = this->WmPenWinFirst(defaultResult, msg, handled);
        break;

      case WM_PENWINLAST:
        
        lresult = this->WmPenWinLast(defaultResult, msg, handled);
        break;

      case WM_POWER:
        
        lresult = this->WmPower(defaultResult, msg, handled);
        break;

      case WM_POWERBROADCAST:
        
        lresult = this->WmPowerBroadcast(defaultResult, msg, handled);
        break;

      case WM_PRINT:
        
        lresult = this->WmPrint(defaultResult, msg, handled);
        break;

      case WM_PRINTCLIENT:
        
        lresult = this->WmPrintClient(defaultResult, msg, handled);
        break;

      case WM_QUERYDRAGICON:
        
        lresult = this->WmQueryDragIcon(defaultResult, msg, handled);
        break;

      case WM_QUERYENDSESSION:
        
        lresult = this->WmQueryEndSession(defaultResult, msg, handled);
        break;

      case WM_QUERYNEWPALETTE:
        
        lresult = this->WmQueryNewPalette(defaultResult, msg, handled);
        break;

      case WM_QUERYOPEN:
        
        lresult = this->WmQueryOpen(defaultResult, msg, handled);
        break;

      case WM_QUERYUISTATE:
        
        lresult = this->WmQueryUiState(defaultResult, msg, handled);
        break;

      case WM_QUEUESYNC:
        
        lresult = this->WmQueueSync(defaultResult, msg, handled);
        break;

      case WM_QUIT:
        
        lresult = this->WmQuit(defaultResult, msg, handled);
        break;

      case WM_RBUTTONDBLCLK:
        
        lresult = this->WmRButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_RBUTTONDOWN:
        
        lresult = this->WmRButtonDown(defaultResult, msg, handled);
        break;

      case WM_RBUTTONUP:
        
        lresult = this->WmRButtonUp(defaultResult, msg, handled);
        break;

      case WM_RENDERALLFORMATS:
        
        lresult = this->WmRenderAllFormats(defaultResult, msg, handled);
        break;

      case WM_RENDERFORMAT:
        
        lresult = this->WmRenderFormat(defaultResult, msg, handled);
        break;

      case WM_SETCURSOR:
        
        lresult = this->WmSetCursor(defaultResult, msg, handled);
        break;

      case WM_SETFOCUS:
        
        lresult = this->WmSetFocus(defaultResult, msg, handled);
        break;

      case WM_SETFONT:
        
        lresult = this->WmSetFont(defaultResult, msg, handled);
        break;

      case WM_SETHOTKEY:
        
        lresult = this->WmSetHotkey(defaultResult, msg, handled);
        break;

      case WM_SETICON:
        
        lresult = this->WmSetIcon(defaultResult, msg, handled);
        break;

      case WM_SETREDRAW:
        
        lresult = this->WmSetRedraw(defaultResult, msg, handled);
        break;

      case WM_SETTEXT:
        
        lresult = this->WmSetText(defaultResult, msg, handled);
        break;

      case WM_SETTINGCHANGE:
        
        lresult = this->WmSettingChange(defaultResult, msg, handled);
        break;

      case WM_SHOWWINDOW:
        
        lresult = this->WmShowWindow(defaultResult, msg, handled);
        break;

      case WM_SIZE:
        
        lresult = this->WmSize(defaultResult, msg, handled);
        break;

      case WM_SIZECLIPBOARD:
        
        lresult = this->WmSizeClipboard(defaultResult, msg, handled);
        break;

      case WM_SIZING:
        
        lresult = this->WmSizing(defaultResult, msg, handled);
        break;

      case WM_SPOOLERSTATUS:
        
        lresult = this->WmSpoolerStatus(defaultResult, msg, handled);
        break;

      case WM_STYLECHANGED:
        
        lresult = this->WmStyleChanged(defaultResult, msg, handled);
        break;

      case WM_STYLECHANGING:
        
        lresult = this->WmStyleChanging(defaultResult, msg, handled);
        break;

      case WM_SYNCPAINT:
        
        lresult = this->WmSyncPaint(defaultResult, msg, handled);
        break;

      case WM_SYSCHAR:
        
        lresult = this->WmSysChar(defaultResult, msg, handled);
        break;

      case WM_SYSCOLORCHANGE:
        
        lresult = this->WmSysColorChange(defaultResult, msg, handled);
        break;

      case WM_SYSCOMMAND:
        
        lresult = this->WmSysCommand(defaultResult, msg, handled);
        break;

      case WM_SYSDEADCHAR:
        
        lresult = this->WmSysDeadChar(defaultResult, msg, handled);
        break;

      case WM_SYSKEYDOWN:
        
        lresult = this->WmSysKeyDown(defaultResult, msg, handled);
        break;

      case WM_SYSKEYUP:
        
        lresult = this->WmSysKeyUp(defaultResult, msg, handled);
        break;

      case WM_TABLET_FIRST:
        
        lresult = this->WmTabletFirst(defaultResult, msg, handled);
        break;

      case WM_TABLET_LAST:
        
        lresult = this->WmTabletLast(defaultResult, msg, handled);
        break;

      case WM_TCARD:
        
        lresult = this->WmTCard(defaultResult, msg, handled);
        break;

      case WM_THEMECHANGED:
        
        lresult = this->WmThemeChanged(defaultResult, msg, handled);
        break;

      case WM_TIMECHANGE:
        
        lresult = this->WmTimeChange(defaultResult, msg, handled);
        break;

      case WM_TIMER:
        
        lresult = this->WmTimer(defaultResult, msg, handled);
        break;

      case WM_TOUCH:
        
        lresult = this->WmTouch(defaultResult, msg, handled);
        break;

      case WM_UNDO:
        
        lresult = this->WmUndo(defaultResult, msg, handled);
        break;

      case WM_UNICHAR:
        
        lresult = this->WmUniChar(defaultResult, msg, handled);
        break;

      case WM_UNINITMENUPOPUP:
        
        lresult = this->WmUnInitMenuPopup(defaultResult, msg, handled);
        break;

      case WM_UPDATEUISTATE:
        
        lresult = this->WmUpdateUiState(defaultResult, msg, handled);
        break;

      case WM_USER:
        
        lresult = this->WmUser(defaultResult, msg, handled);
        break;

      case WM_USERCHANGED:
        
        lresult = this->WmUserchanged(defaultResult, msg, handled);
        break;

      case WM_VKEYTOITEM:
        
        lresult = this->WmVkeyToItem(defaultResult, msg, handled);
        break;

      case WM_VSCROLL:
        
        lresult = this->WmVscroll(defaultResult, msg, handled);
        break;

      case WM_VSCROLLCLIPBOARD:
        
        lresult = this->WmVscrollClipboard(defaultResult, msg, handled);
        break;

      case WM_WINDOWPOSCHANGED:
        
        lresult = this->WmWindowPosChanged(defaultResult, msg, handled);
        break;

      case WM_WINDOWPOSCHANGING:
        
        lresult = this->WmWindowPosChanging(defaultResult, msg, handled);
        break;

      case WM_WTSSESSION_CHANGE:
        
        lresult = this->WmWtsSession_Change(defaultResult, msg, handled);
        break;

      case WM_XBUTTONDBLCLK:
        
        lresult = this->WmXButtonDblClk(defaultResult, msg, handled);
        break;

      case WM_XBUTTONDOWN:
        
        lresult = this->WmXButtonDown(defaultResult, msg, handled);
        break;

      case WM_XBUTTONUP:
        
        lresult = this->WmXButtonUp(defaultResult, msg, handled);
        break;

      default:
        lresult = this->Message(defaultResult, msg, handled);
        break;
      }

      return lresult;
    }


  };

const std::unordered_map<UInt, MessageId> MessageHandler::KnownMessagesIds =
    MessageHandler::getKnownMessageIds();

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif