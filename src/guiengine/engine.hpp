//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2009 Marianne Gagnon
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


/*
+---------+
+ Widgets +
+---------+

_______________________________________________________
Internal constant       Name in XML files
_______________________________________________________
 
WTYPE_RIBBON            "ribbon", "buttonbar", "tabs"
appears an horizontal bar containing elements laid in a row, each being and icon and/or a label
the "ribbon" subcategory will behave a bit like a radio button group, i.e. one element must selected.
events are triggered as soon as a choice is selected (can be simply by hovering).
the "buttonbar" subcategory treats children buttons as action buttons, which means they can't have a
'selected' state, only focused or not (i.e. there is no selection that remains if you leave this area).
events are triggered only on enter/fire.
the "tabs" subcategory will show a tab bar. behaviour is same as normal ribbon, only looks are different.
Orientation of tabs (up or down) is automatically inferred from on-screen position
Ribbon widgets are of spawn type (<ribbon> ... </ribbon>) and may contain icon-buttons or buttons as children.
Property PROP_SQUARE can be set to tell the engine if the ribbon's contents are rectangular or not (this will
affect the type of highlighting used)
 * Note : all elements within a ribbon must have an 'ID' property

WTYPE_SPINNER           "spinner", "gauge"
A spinner component (lets you choose numbers). Sprecify PROP_MIN_VALUE and PROP_MAX_VALUE to have control
over values (default will be from 0 to 10). You can specify an icon; then, include a sprintf format string
like %i in the name, and at runtime the current number will be inserted into the given name to find the
right file for each possible value the spinner can take. It may also display arbitrary text instead of
numbers, though this cannot be achieve in the XML file; use the ->addLabel(...) method in code to do this.
It can also display arbitrary text containing the value; just define the PROP_TEXT property to contain
the text you want, including a format string %i where the value should appear.
The "gauge" variant behaves similarly, but a fill band shows how close to the max the value is.


WTYPE_BUTTON            "button"
A plain text buttons.

WTYPE_ICON_BUTTON       "icon-button", "icon"
A component with an image, and optional text to go under it. The "icon" variant will have no border and will not
be clickable. PROP_ICON is mandatory for this component.
There are three ways to place the texture within the allocated space; the default (and only way currently accessible
through xml files) is to scale the texture to fit, while preserving its aspect ratio; other methods, currently only
accessible through C++ code, are to stretch the texture to fill the area without caring for aspect ratio, and another
to respect an aspect ratio other than the texture's (useful for track screenshots, which are 4:3 compressed to fit
in a power-of-two 256x256 texture)

WTYPE_CHECKBOX          "checkbox"
A checkbox. Not used at the moment.

WTYPE_LABEL             "label" "header"
A plain label. Supports properties PROP_WORD_WRAP and PROP_TEXT_ALIGN.
The "Header" variant uses a bigger and more colourful font.

WTYPE_SPACER            "spacer"
Some blank space; not visible on screen.

WTYPE_DIV               "div", "box"
A container. Does not do much on itself, but is useful to lay out children automatically. Divs can be nested.
Supports property PROP_LAYOUT. Of spawn type (<div>...</div>, place children within)
 "box" is a variant that acts exactly the same but is visible on-screen

WTYPE_DYNAMIC_RIBBON       "ribbon_grid", "scrollable_ribbon", "scrollable_toolbar"
Builds upon the basic Ribbon to be more dynamic (dynamics contents, possibly with scrolling, possibly multi-line)
NOT of spawn type (<ribbon_grid .../>), contents must be programmatically set at runtime.
Property PROP_SQUARE can be set to tell the engine if the ribbon's contents are rectangular or icons (this will
affect the type of highlighting used).
PROP_CHILD_WIDTH and PROP_CHILD_HEIGHT are mandatory (so at least aspect ratio of elements that will later be
added is known) An interesting aspect of PROP_CHILD_WIDTH and PROP_CHILD_HEIGHT is that you can use them to
show textures to any aspect ratio you want (so you can e.g. save textures to a power-of-two size like 256x256,
but then show it in 4:3 ratio).
Supports an optional label at the bottom if PROP_LABELS_LOCATION is set (see more on PROP_LABELS_LOCATION below).
The "scrollable_ribbon" and "scrollable_toolbar" subtypes are single-line
scrollable ribbons. The difference between both is that 'scrollable_ribbon' always has a value selected (like in
a combo box, or radio buttons), while 'scrollable_toolbar' is a scrollable list of buttons that can be pressed to
trigger actions.
 
WTYPE_MODEL_VIEW        "model"
Displays a model. Currently incomplete. Contents must be set programmatically.

WTYPE_LIST              "list"
Displays a list. Currently incomplete. Contents must be set programmatically.

+------------+
+ Properties +
+------------+

_______________________________________________________
Internal constant       Name in XML files
_______________________________________________________

PROP_ID                 "id"
gives a unique internal name to each object using this property. It will be
used in events callbacks to determine what action occurred. Can be omitted
on components that do not trigger events (e.g. labels)

PROP_TEXT               "text"
gives text (a label) to the widget where supported. Ribbon-grids give a special meaning
to this parameter, see ribbon-grid docs above.

PROP_ICON               "icon"
give an icon to the widget. Property contents is the path to the file, by default relative
relative to the /data directory of STK (several methods of IconButtonWidget and DynamicRibbon
can enable you to use absolute paths if you wish).

PROP_TEXT_ALIGN         "text_align"
used exclusively by label components. Value can be "right" or "center" (left used if not specified).
 
PROP_WORD_WRAP          "word_wrap"
used exclusively by label components. Value can be "true" to indicate that long text should spawn on
multiple lines.

PROP_MIN_VALUE          "min_value"
PROP_MAX_VALUE          "max_value"
used to specify a minimum and maximum value for numeric widgets (c.f. spinner)

PROP_X                  "x"
PROP_Y                  "y"
sets the position (location) of a widget, relative to its parent (container <div> or screen if none).
A plain number will be interpreted as an aabsolute position in pixels. A '%' sign may be added to the
given number to mean that the location is specified in terms of a percentage of parent size (parent size
means the parent <div> or the whole screen if none). A negative value can also be passed to start coordinate
from right and/or bottom, instead of starting from top-left corner as usual.
Note that in many cases, it is not necessary to manually a position. Div layouts will often manage that
for you (see PROP_LAYOUT). Other widgets will also automativally manage the position and size of their children,
for instance ribbons.

PROP_WIDTH              "width"
PROP_HEIGHT             "height"
give dimensions to the widget. A plain number will be interpreted as an aabsolute position in pixels.
A '%' sign may be added to the given number to mean that the size is specified in terms of a percentage
of parent size (parent size means the parent <div> or the whole screen if none).
Note that in many cases, it is not necessary to manually a size. Div layouts will often manage that
for you (see PROP_LAYOUT). In addition, sizes are automatically calculated for widgets made of icons
and/or text like labels and plain icons. Other widgets will also automativally manage the position and
size of their children, for instance ribbons.

PROP_MAX_WIDTH          "max_width"
PROP_MAX_HEIGHT         "max_height"
The maximum size a widget can take; especially useful when using percentages and proportions.
 
PROP_CHILD_WIDTH        "child_width"
PROP_CHILD_HEIGHT       "child_height"
Used exclusively by the ribbon grid widget. See docs for this widget above.

PROP_GROW_WITH_TEXT     "grow_with_text"
Reserved, but currently unimplemented and unused.

PROP_LAYOUT             "layout"
Valid on 'div' containers. Value can be "horizontal-row" or "vertical-row". This means x and y coordinates
of all children will automatically be calculated at runtime, so they are laid in a row. Width and height can
be set absolutely as usual, but can also be determined dynamically according to available screen space. Also
see PROP_ALIGN and PROP_PROPORTION to known more about controlling layouts. Note that all components within a
layed-out div will ignore all x/y coordinates you may give them as parameter.

PROP_ALIGN              "align"
For widgets located inside a vertical-row layout div : Changes how the x coord of the widget is determined.
 value can be "left", "center" or "right".
For widgets located inside a horizontal-row layout div : Changes how the y coord of the widget is determined.
 value can be "top", "center" or "bottom".

PROP_PROPORTION         "proportion"
Helps  determining widget size dynamically (according to available screen space) in layed-out divs. In a
vertical row layout, proportion sets the height of the item. In an horizontal row, it sets the width of
the item. Proportions are always evaluated relative to the proportions of other widgets in the same div.
If one div contains 4 widgets, and their proportions are 1-2-1-1, it means the second must take twice as
much space as the 3 others. In this case, 10-20-10-10 would do the exact same effect. 1-1-1-1 would mean
all take 1/4 of the available space. Note that it is allowed to mix absolute widget sizes and proportions;
in this case, widgets with absolute size are evaluated first, and the dynamically-sized ones split the
remaining space according to their proportions.

PROP_SQUARE             "square_items"
Valid on Ribbons or RibbonGrids. Can be "true" (omitting it means "false"). Indicates whether the contents
use rectangular icons as opposed to "round" icons (this will affect the type of focus/highlighting used)

PROP_EXTEND_LABEL       "extend_label"
How many pixels the label is allowed to expand beyond the boundaries of the widget itself. Currently only
allowed on icon widgets.
 
PROP_LABELS_LOCATION    "label_location"
Currently only used by dynamic ribbons. Decides where the label is. Value can be "each", "bottom", or "none"
(if ommitted, "none" is the default). "each" means that every item has its own label. "bottom" means there
is a single label for all at the bottom, that displays the name of the current item.
 
PROP_MAX_ROWS           "max_rows"
Currently used for ribbon grids only. Indicates the maximum amount of rows this ribbon can have.
 
+--------------------------+
+ Using the Engine in Code +
+--------------------------+

The first thing to do is to derive a class of your own from AbstractStateManager. There are a few callbacks
you will need to override. Once it's done, you have all AbstractStateManager methods ready to be used to
push/pop/set menus on the screen stack.
Once you have instanciated your state manager class, call GUIEngine::init and pass it as argument.
One of the most important callbacks is 'eventCallback', which will be called everytime sometimes happens.
Events are generally a widget state change. In this case, a pointer to the said widget is passed along its
name, so you get its new state and/or act. There are two special events, passed with a NULL widget, and which
bear the anmes "init" and "tearDown", called respectively when a screen is being made visible and when it's
being left, allowing for setup/clean-up.
 
*/

#ifndef HEADER_ENGINE_HPP
#define HEADER_ENGINE_HPP

#include <irrlicht.h>
#include <string>

#include "guiengine/abstract_state_manager.hpp"
#include "guiengine/widgets.hpp"
#include "utils/ptr_vector.hpp"

namespace GUIEngine
{    
    class Screen;
    class CutScene;
    class Widget;
    
    /** Returns the widget currently focused by given player, or NULL if none.
        Do NOT use irrLicht's GUI focus facilities; it's too limited for our
        needs, so we use ours. (i.e. always call these functions are never those
        in IGUIEnvironment) */
    Widget* getFocusForPlayer(const int playerID);

    /** Focuses nothing for given player (removes any selection for this player).
     Do NOT use irrLicht's GUI focus facilities; it's too limited for our
     needs, so we use ours. (i.e. always call these functions are never those
     in IGUIEnvironment) */
    void focusNothingForPlayer(const int playerID);

    /** Returns whether given the widget is currently focused by given player.
     Do NOT use irrLicht's GUI focus facilities; it's too limited for our
     needs, so we use ours. (i.e. always call these functions are never those
     in IGUIEnvironment) */
    bool isFocusedForPlayer(const Widget*w, const int playerID);
    
    // In an attempt to make getters as fast as possible by possibly allowing inlining
    // These fields should never be accessed outside of the GUI engine.
    namespace Private
    {
        extern irr::gui::IGUIEnvironment* g_env;
        extern Skin* g_skin;
        extern irr::gui::IGUIFont* g_font;
        extern irr::gui::IGUIFont* g_title_font;

        extern IrrlichtDevice* g_device;
        extern irr::video::IVideoDriver* g_driver;
        extern Screen* g_current_screen;
        extern AbstractStateManager* g_state_manager;
        extern Widget* g_focus_for_player[MAX_PLAYER_COUNT];
    }
    
    inline IrrlichtDevice*            getDevice()        { return Private::g_device;         }
    inline irr::gui::IGUIEnvironment* getGUIEnv()        { return Private::g_env;            }
    inline irr::video::IVideoDriver*  getDriver()        { return Private::g_driver;         }
    inline irr::gui::IGUIFont*        getFont()          { return Private::g_font;           }
    inline irr::gui::IGUIFont*        getTitleFont()     { return Private::g_title_font;     }
    inline Screen*                    getCurrentScreen() { return Private::g_current_screen; }
    inline AbstractStateManager*      getStateManager()  { return Private::g_state_manager;  }
    inline Skin*                      getSkin()          { return Private::g_skin;           }

    /** Returns the height of the font in pixels */
    int   getFontHeight();
    
    float getLatestDt();
    
    /** Add a cutscene to the list of screens known by the gui engine */
    void addScreenToList(Screen* screen);
    
    // Widgets that need to be notified at every frame can add themselves there
    extern ptr_vector<Widget, REF> needsUpdate;
    
    void init(irr::IrrlichtDevice* device, irr::video::IVideoDriver* driver, AbstractStateManager* state_manager);
    void cleanUp();
    
    /** Low-level mean to change current screen. Use a state manager instead to get higher-level functionnality. */
    void switchToScreen(const char* );
    void clear();
    void cleanForGame();
    
    void reshowCurrentScreen();
    
    void render(float dt);
    
    void transmitEvent(Widget* widget, std::string& name, const int playerID);
    
    Widget* getWidget(const char* name);
    Widget* getWidget(const int id);
}

#endif
