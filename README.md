uitk
====

Native Windows desktop user interface header-only library

The original goal of this project was to create a user interface library with the following specifications:

  1. Ease-of-use equal to that of WinForms and AWT
  2. Usage of modern C++ idioms and code (currently makes heavy use of C++11 language and library features; avoids macros
     and naming prefixes so the code doesn't look anything like MFC or wxWidgets)
  3. Does not rely on other 3rd party libraries such as Qt\*
  4. Is header-only to avoid needing to link to static or shared/dynamic libraries thus allowing use with multiple 
     compilers easily (downside: compile time is increased somewhat)

\* Right now, point 3 misses the mark. The code relies on ATL to provide thunk-based window procedures as well as some window 
class registration and creation. The number one goal right now is to remove the reliance on ATL. Instead of thunks, the 
window procedure handling code will be migrated to storing the pointer to the window object in extra WNDCLASSEX memory and accessing it through GetWindowLongPtr(). For subclassed windows, I haven't thought of a good solution yet. Originally, the pointer was going to accessed via GetProp/SetProp with window property atoms.

I decided to publish the code now for three reasons:

  1. I have become paranoid about my local backups and this code is really important to me. If I were to somehow get a
     power surge that were to, say, fry all of the hard drives in my house, I'd be hosed. As unlikely of an event as this
     is, I'd rather be covered in such an event.
  2. If something were to happen to me, nobody would have access to my code. I want this project to continue as it appears 
     there are no alternatives to this out in the public. Every one else uses Qt, wxWidgets, or MFC. There have been 
     several attempts to do the same thing; they all either never really went anywhere (eGUI, SmartWin++) or refused to 
     adapt to modern C++ (Ultimate++, wxWidgets).
  3. I want other people to have access to this code, even if it isn't complete yet.

It's important to note that this *is not* a cross-platform toolkit. It's *exclusively* native to Windows. I have no 
plans or desires to make this cross platform as it would simply bloat the code base. This toolkit strives to solve only 
the four specifications listed above using native Windows drawing capabilities.

Other than that, here is a list of goals and milestones:

  * Remove the reliance on ATL (primary goal, will be the next milestone)
  * Refactor the code and comments to match a single code style; right now, it's *mostly* based on Google's C++ style 
    guide, but I don't agree with many of Google's style recommendations. Some of the code is formatted one way, some 
    is formatted another way. This all needs to be made uniform.
  * Make sure existing comments and documentation are up to par. More comments need to be added, I'm sure.
  * Make sure component layouts are handled properly (this should be done soon)
  * Create the rest of the control classes; currently, only labels, non-rich text boxes, buttons, and list box 
    exist. The immediate ones I can think of that need to be created: tab controls, combo box, list view control, 
    progress bar, tree control, status bar, and rich text box.
  * Use flicker-free painting
  
I can't think of anything else that needs to be done yet.
