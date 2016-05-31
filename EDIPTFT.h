//
// Library for controlling Electronic Assembly eDIPTFT displays
//
//      Copyright (c) 2013 Stefan Gofferje. All rights reserved.
//
//      This library is free software; you can redistribute it and/or
//      modify it under the terms of the GNU Lesser General Public
//      License as published by the Free Software Foundation; either
//      version 2.1 of the License, or (at your option) any later
//      version.
//
//      This library is distributed in the hope that it will be
//      useful, but WITHOUT ANY WARRANTY; without even the implied
//      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//      PURPOSE.  See the GNU Lesser General Public License for more
//      details.
//
//      You should have received a copy of the GNU Lesser General
//      Public License along with this library; if not, write to the
//      Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
//      Boston, MA 02110-1301 USA
//

#ifndef EDIPTFT_h
#define EDIPTFT_h

// handle Arduino and Spark/Particle environments
#if defined (SPARK)
  #include "application.h"
#else
  #if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
  #else
    #include "WProgram.h"
  #endif
  // includes only needed for Arduino platform go here
#endif

//Devices
#define EDIP128 1
#define EDIP160 1
#define EDIP240 1
#define EDIP320 2

//Set your device
#define DEVICE EDIP240
#define COORD_SIZE DEVICE  //Byte count for coordinates
#define SERIAL_DEV Serial2

#define EA_BLACK 1
#define EA_BLUE 2
#define EA_RED 3
#define EA_GREEN 4
#define EA_PURPLE 5
#define EA_CYAN 6
#define EA_YELLOW 7
#define EA_WHITE 8
#define EA_DARKGREY 9
#define EA_ORANGE 10
#define EA_LILA 11
#define EA_DARKPURPLE 12
#define EA_MINT 13
#define EA_GRASSGREEN 14
#define EA_LIGHTBLUE 15
#define EA_LIGHTGREY 16

// Fonts
#define EA_FONT8X8 0
#define EA_FONT4X6 1
#define EA_FONT6X8 2
#define EA_FONT7X12 3
#define EA_GENEVA10 4
#define EA_CHICAGO14 5
#define EA_SWISS30B 6
#define EA_BIGZIF57 7

#define NAK 0x15
#define ACK 0x06
#define ESC 0x1B

#define uint unsigned int

class EDIPTFT {
  public:
    EDIPTFT(boolean smallprotocol=true);

    void begin(long baud=115200);

    // helper functions
    char readByte();
    char waitandreadByte();
    unsigned char datainBuffer();
    int readBuffer(char* data);
    void smallProtoSelect(char address);
    void smallProtoDeselect(char address);
    void sendData(char* data, char len);

    // Basic display functions
    /*! \brief Clear display
     *
     * Clear display contents (all pixels off) and remove touch areas
     */
    void clear();

    /*! \brief Delete display
     *
     * Delete display contents (all pixels off). Touch areas are still active.
     */
    void deleteDisplay();

    /*! \brief Invert display
     *
     * Invert display contents (invert all pixels)
     */
    void invert();

    void setDisplayColor(char fg, char bg);

    void fillDisplayColor(char bg);


    /*! \brief Display illumination on/duration
     *
     * Terminal display illumination is switched off if \a on is zero, on if \a on is 1, switch on for n 1/10 seconds otherwise
     *
     * \param on determine display illumination state
     */
    void displayIllumination(unsigned char on);

    /*! \brief Display illumination level
     *
     * Terminal display illumination is set to specified \a level (0 .. 255)
     *
     * \param level determine display illumination level (0 .. 255)
     */
    void setDisplayIlluminationLevel(unsigned char level);

    /*! \brief Acoustic confirmation of touch operations
     *
     * Sound buzzer on touch operation if \a on is true
     *
     * \param on determine if buzzer should confirm touch operations
     */
    void setTouchBuzzer(boolean on);
    
    /*! \brief Sound buzzer
     *
     * Sound buzzer for \a duration 1/10th seconds
     *
     * \param duration 1/10th seconds (0: off, 1: on, 2..255: on for 1/10th seconds)
     */
    void soundBuzzer(unsigned char duration);
    
    /*! \brief Output port
     *
     * Set output port \a port to \a value
     *
     * \param port  Port bit to modify (1..5/1..7); if set to 0, second parameter is bitmask to set
     * \param value 0: reset; 1: set; 2: toggle; if port is 0 this is the bitmask instead
     */
    void setOutputPort(unsigned char port, unsigned char value);


    /*! \brief Terminal on
     *
     * Terminal display is switched on if \a on is true
     *
     * \param on determine if terminal is switched on
     */
    void terminalOn(boolean on);

    /*! \brief Load internal image
     *
     * Load internal image with the \a nr (0..255) from the *EEPROM* memory to
     * \a x1, \a y1
     *
     * \param x1 x position of image on the display
     * \param y1 y position of image on the display
     * \param nr number of the image on the *EEPROM*
     */
    void loadImage(int x1, int y1, int nr);

    /*! \brief Cursor on/off
     *
     * Switch cursor on/off
     *
     * \param on `n1=0`: cursor is invisible, `n1=1`: cursor flashes
     */
    void cursorOn(boolean on);

    /*! \brief Position cursor
     *
     * origin upper-left corner `(1, 1)`
     *
     * \param col new cursor column
     * \param row new cursor row
     */
    void setCursor(char col, char row);

    // Bargraph
    /*! \brief Define bargraph
     *
     * Define bargraph to form the rectangle enclosing the
     * bargraph. \a sv and \a ev are the values for `0%` and `100%`.
     *
     * \param dir direction ('L'eft, 'R'ight, 'O'up, 'U'down)
     * \param no bargraph number `1..32`
     * \param x1 upper left x coordinate
     * \param y1 upper left y coordinate
     * \param x2 lower right x coordinate
     * \param y2 lower right y coordinate
     * \param sv start value (0%)
     * \param ev end value (100%)

     * \param type set the style of the bargraph:\n
     *             `type=0`: pattern bar, \a mst=bar pattern,\n
     *             `type=1`: pattern bar in rectangle, \a mst=bar pattern,\n
     *             `type=2`: pattern line, \a mst=line width,\n
     *             `type=3`: pattern line in rectangle, \a mst=line width
     *
     * \param mst additional parameter for type specification
     */
    void defineBargraph(char dir, char no, int x1, int y1, int x2, int y2,
                        byte sv, byte ev, char type, char mst);

    /*! \brief Update bargraph
     *
     * Set and draw the bargraph *no* to the new *value*
     *
     * \param no number of the bargraph `1..32`
     * \param val new value of the bargraph
     */
    void updateBargraph(char no, char val);

    void setBargraphColor(char no, char fg, char bg, char fr);

    /*! \brief Set bargraph by touch
     *
     * The bargraph with number *no* is defined for input by touch panel
     *
     * \param no number of the bargraph `1..32`
     */
    void makeBargraphTouch(char no);

    void linkBargraphLight(char no);

    /*! \brief Delete bargraph
     *
     * The definition of the bargraph with number *no* becomes invalid. If the
     * bargraph was defined as input with touch, the touchfield will also be
     * deleted.
     *
     * \param no number of the bargraph `1..32`
     * \param n1 additional parameter\n
     *           `n1=0`: bargraph remains visible\n
     *           `n1=1`: bargraph is deleted
     */
    void deleteBargraph(char no, char n1);

    // Instrument
    void defineInstrument(char no, int x1, int y1, char image,
                          char angle, char sv, char ev);
    void updateInstrument(char no, char val);
    void redrawInstrument(char no);
    void deleteInstrument(char no, char n1, char n2);

    // Text
    void setTextColor(char fg, char bg);

    /*! \brief Set font
     *
     * Set font with the number *font*
     *
     * \param font font number `font=0..15`, use font defines here
     */
    void setTextFont(char font);

    /*! \brief Set text angle
     *
     * Set text output angle
     *
     * \param angle text output angle\n
                    `angle=0`: 0°
                    `angle=1`: 90°
     */
    void setTextAngle(char angle);

    /*! \brief Draw text on display
     *
     * Draw a *text* on screen. Several lines are separated by the character `|`
     * ($7C).
     * * place text between `~`: characters flash on/off
     * * place text between `@`: characters flash inversely
     * * use `\\` as to escape special characters
     *
     * \param x1: x coordinate
     * \param y1: y coordinate
     * \param justification set text justification to `L`(eft), `R`(ight),
     *                      `C`(enter)
     * \param text text to draw on display
     */
    void drawText(int x1, int y1, char justification, const char* text);

    // Rectangle and Line
    void setLineColor(char fg, char bg);

    /*! \brief Point size/line thickness
     *
     * \param x x-point size (1..15)
     * \param y y-point size (1..15)
     */
    void setLineThick(char x, char y);

    /*! \brief Draw straight line
     *
     * Draw straight line from point *x1*, *y1* to point *x2*, *y2*
     */
    void drawLine(int x1, int y1, int x2, int y2);

    /*! \brief Draw rectangle
     *
     * Draw four straight lines as a rectangle from *x1*, *y1* to *x2*, *y2*
     */
    void drawRect(int x1, int y1, int x2, int y2);

    void drawRectf(int x1, int y1, int x2, int y2, char color);
    
    /*! \brief Clear rectangle
     *
     * Clear rectangle from *x1*, *y1* to *x2*, *y2*
     */
    void clearRect(int x1, int y1, int x2, int y2);

    /*! \brief Invert rectangle
     *
     * Invert rectangle from *x1*, *y1* to *x2*, *y2*
     */
    void invertRect(int x1, int y1, int x2, int y2);

    /*! \brief Fill rectangle
     *
     * Fill rectangle from *x1*, *y1* to *x2*, *y2*
     */
    void fillRect(int x1, int y1, int x2, int y2);
    void fillRectp(int x1, int y1, int x2, int y2, char pattern);
    

    // Touch keys

    /*! \brief Define touch key
     *
     * Key remains pressed as long as there is contact. The area from *x1*, *y1*
     * to *x2*, *y2* is drawn with actual border and defined as a key.
     * The label is drawn with the current touch font. The first character
     * determines the alignment of the text (`L`(eft), `R`(ight), `C`(enter)).
     * Multiline texts are separated by the character `|`.
     *
     * \param down return/touchmacro (1-255) if pressed
     * \param up return/touchmacro (1-255) if released
     * \param text label of the touch key
     */
    void defineTouchKey(int x1, int y1, int x2, int y2,
                        char down, char up, const char* text);

    /*! \brief Define touch switch
     *
     * Status of the switch toggles after each contact. The area from *x1*, *y1*
     * to *x2*, *y2* is drawn with actual border and defined as a key.
     * The label is drawn with the current touch font. The first character
     * determines the alignment of the text (`L`(eft), `R`(ight), `C`(enter)).
     * Multiline texts are separated by the character `|`.
     *
     * \param down return/touchmacro (1-255) if pressed
     * \param up return/touchmacro (1-255) if released
     * \param text label of the touch key
     */
    void defineTouchSwitch(int x1, int y1, int x2, int y2,
                           char down, char up, const char* text);

    /*! \brief Define touch switch with image
     *
     * Status of the switch toggles after each contact. Image number *img* is
     * loaded to *x*, *y* and defined as a switch.
     * The label is drawn with the current touch font. The first character
     * determines the alignment of the text (`L`(eft), `R`(ight), `C`(enter)).
     * Multiline texts are separated by the character `|`.
     *
     * \param down return/touchmacro (1-255) if pressed
     * \param up return/touchmacro (1-255) if released
     * \param text label of the touch switch
     */
    void defineTouchSwitch(int x, int y, int img, char downcode,
                           char upcode, const char* text);

    /*! \brief Set touch switch
     *
     * Set the status of the touch switch with the return code *code*
     * to *value*.
     *
     * \param code Return code of the switch
     * \param value `value=0`: OFF, `value=1`: ON
     */
    void setTouchSwitch(char code,char value);

    void setTouchkeyColors(char n1, char n2, char n3,
                           char s1, char s2, char s3);

    /*! \brief Label font
     *
     * Apply font with number *font* for touch key labels
     */
    void setTouchkeyFont(char font);

    void setTouchkeyLabelColors(char nf,char sf);

    /*! \brief Radio group for switches
     *
     * `group=0`: newly defined switches don't belong to a group
     * `group=1..255`: newly defined switches are assigned to the group with
     *                 the given number
     * Only one switch in a group is active at once. All others are deactivated.
     * For switches only the *down code* is applicable. The *up code* will be
     * ignored.
     */
    void setTouchGroup(char group);

    /*! \brief Delete toch area by up- or downcode
     *
     *  The touch area with the return code is removed from the touch query
     *
     *  \param code the code of the touch area (code=0: all touch areas)
     *  \param n1 n1==0: the area remains visible on the display,
     *            n1==1: the area is deleted
     */
    void removeTouchArea(char code,char n1);

    // Macro Calls
    /*! \brief Run macro
     *
     * Call the (normal) macro with number *nr* (max. 7 levels).
     */
    void callMacro(uint nr);

    /*! \brief Run touch macro
     *
     * Call touch macro with number *nr* (max. 7 levels)
     */
    void callTouchMacro(uint nr);

    /*! \brief Run menu macro
     *
     * Call menu macro with number *nr* (max. 7 levels)
     */
    void callMenuMacro(uint nr);

    /*! \brief Define touch key with menu function
     *
     * Define the area from *x1*, *y1* to *x2*, *y2*  as a menu key.
     * The first character determines the direction in which the menu opens (R=right,L=left,O=up,U=down)
     * The second character determines the alignment of the touch text (C=center,L=left-,R=right justified)
     * The menu items are separated by the character '|' ($7C,dec:124) (e.g. "UCkey|item1|item2|item3".
     * The key text is written with the current touch font and the menu items are written with the current menu font. The background of the menu is saved automatically.
     * \param downcode `1-255` return/touchmacro if pressed
     * \param upcode `1-255` return/touchmacro if released
     * \param mnucode return/menumacro+(item nr - 1) after selection of a
     *                menu item
     * \param text string with the key text and menu items
     */
    void defineTouchMenu(int x1, int y1, int x2, int y2,
                         char downcode, char upcode, char mnucode,
                         const char *text);

    /*! \brief Send *open* signal after a Menu open request has been sent from TFT.
     *
     *  If a touch menu is not set to open automatically the TFT sends a
     *  request 'ESC T 0'. This function sends 'ESC N T 2' to open the menu.
     */
    void openTouchMenu();

    /*! \brief Set menu font
     *
     * Set font with number *font* (`0..15`) for menu display
     */
    void setMenuFont(char font);

    /*! \brief enable/disable touchmenu automation
     *
     * if val==true touch menu opens automatically, if val==false touchmenu
     * doesn' t open automatically, instead a request is sent to the
     * host computer, which can then open the menu with openTouchMenu()
     */
    void setTouchMenuAutomation(bool val);

  private:
    boolean _smallprotocol;
    unsigned char bytesAvailable();
    void waitBytesAvailable();
    void sendByte(char data);
    void sendSmall(char* data, char len);
    void sendSmallDC2(char* data, char len);
};
#endif
