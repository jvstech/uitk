
#if !defined (JVS_UITK_WIN32_WINDOWMSGHANDLERS_H_)
#define JVS_UITK_WIN32_WINDOWMSGHANDLERS_H_

#include <map>
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
    static const std::map<UINT, MessageId> KnownMessagesIds;

  private:
    static std::map<UINT, MessageId> getKnownMessageIds(void)
    {
      std::map<UINT, MessageId> ret;
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

    inline virtual LRESULT WmActivate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmActivateApp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmAfxFirst(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmAfxLast(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmApp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmAppCommand(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmAskCbFormatName(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCancelJournal(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCancelMode(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCaptureChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmChangeCbChain(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmChangeUiState(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCharToItem(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmChildActivate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmClear(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmClipboardUpdate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmClose(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCommand(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCommNotify(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCompacting(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCompareItem(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmContextmenu(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCopy(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCopyData(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCreate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorBtn(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorDlg(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorEdit(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorListbox(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorMsgbox(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorScrollbar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCtlColorStatic(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmCut(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDeadChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDeleteItem(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDestroy(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDestroyClipboard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDeviceChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDevModeChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDisplayChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDrawClipboard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDrawItem(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDropFiles(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDwmColorizationColorChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDwmCompositionChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDwmNcRenderingChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDwmSendIconicLivePreviewBitmap(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDwmSendIconicThumbnail(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmDwmWindowMaximizedChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmEnable(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmEndSession(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmEnterIdle(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmEnterMenuLoop(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmEnterSizeMove(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmEraseBkgnd(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmExitMenuLoop(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmExitSizeMove(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmFontChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGesture(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGestureNotify(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetDlgCode(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetFont(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetHotkey(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetIcon(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetMinMaxInfo(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetObject(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetText(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetTextLength(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmGetTitlebarInfoEx(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmHandheldFirst(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmHandheldLast(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmHelp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmHotkey(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmHscroll(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmHscrollClipboard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmIconEraseBkgnd(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeComposition(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeCompositionFull(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeControl(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeEndComposition(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeKeyDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeKeyLast(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeKeyUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeNotify(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeRequest(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeSelect(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeSetContext(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmImeStartComposition(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInitDialog(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInitMenu(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInitMenuPopup(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInput(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInputLangChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInputLangChangeRequest(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmInputDeviceChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmKeyDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmKeyUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmKillFocus(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmLButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmLButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmLButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiActivate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiCascade(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdicreate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiDestroy(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiGetActive(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiIconArrange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiMaximize(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiNext(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiRefreshMenu(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiRestore(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiSetMenu(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMdiTile(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMeasureItem(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMenuChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMenuCommand(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMenuDrag(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMenuGetObject(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMenuRButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMenuSelect(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMouseActivate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMouseHover(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMouseHwheel(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMouseLeave(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMouseMove(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMouseWheel(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMove(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmMoving(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcActivate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcCalcSize(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcCreate(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcDestroy(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcHitTest(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcLButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcLButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcLButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcMButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcMButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcMButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcMouseHover(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcMouseLeave(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcMouseMove(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcPaint(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcRButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcRButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcRButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcXButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcXButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNcXButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNextDlgCtl(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNextMenu(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNotify(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNotifyFormat(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmNull(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPaint(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPaintClipboard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPaintIcon(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPaletteChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPaletteIsChanging(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmParentNotify(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPaste(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPenWinFirst(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPenWinLast(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPower(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPowerBroadcast(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPrint(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmPrintClient(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQueryDragIcon(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQueryEndSession(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQueryNewPalette(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQueryOpen(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQueryUiState(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQueueSync(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmQuit(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmRButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmRButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmRButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmRenderAllFormats(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmRenderFormat(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetCursor(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetFocus(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetFont(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetHotkey(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetIcon(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetRedraw(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSetText(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSettingChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmShowWindow(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSizeClipboard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSize(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSizing(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSpoolerStatus(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmStyleChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmStyleChanging(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSyncPaint(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSysChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSysColorChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSysCommand(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSysDeadChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSysKeyDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmSysKeyUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmTabletFirst(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmTabletLast(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmTCard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmThemeChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmTimeChange(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmTimer(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmTouch(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmUndo(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmUniChar(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmUnInitMenuPopup(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmUpdateUiState(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmUser(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmUserchanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmVkeyToItem(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmVscroll(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmVscrollClipboard(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmWindowPosChanged(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmWindowPosChanging(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmWtsSession_Change(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmXButtonDblClk(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmXButtonDown(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT WmXButtonUp(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }
    inline virtual LRESULT Message(LRESULT defaultResult, MSG& msg, bool& handled) { return defaultResult; }

    LRESULT RouteMessage(LRESULT defaultResult, MSG& msg, bool& handled) 
    {
      LRESULT lresult = 0;

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

  const std::map<UINT, MessageId> MessageHandler::KnownMessagesIds = 
    MessageHandler::getKnownMessageIds();

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif