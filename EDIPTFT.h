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

#include <Arduino.h>

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
    /*! \brief Delete display
     *
     * Delete display contents (all pixels off)
     */
    void clear();

    /*! \brief Invert display
     *
     * Invert display contents (invert all pixels)
     */
    void invert();

    void setDisplayColor(char fg, char bg);
    void fillDisplayColor(char bg);

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
    void defineInstrument(char no, int x1, int y1, char image, char angle, char sv, char ev);
    void updateInstrument(char no, char val);
    void redrawInstrument(char no);
    void deleteInstrument(char no, char n1, char n2);

    // Text
    void setTextColor(char fg, char bg);
    void setTextFont(char font);
    void setTextAngle(char angle);
    void drawText(int x1, int y1, char justification,char* text);

    // Rectangle and Line
    void setLineColor(char fg, char bg);
    void setLineThick(char x, char y);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawRect(int x1, int y1, int x2, int y2);
    void drawRectf(int x1, int y1, int x2, int y2, char color);

    // Touch keys
    void defineTouchKey(int x1, int y1, int x2, int y2, char down, char up, char* text);
    void defineTouchSwitch(int x1, int y1, int x2, int y2, char down, char up, char* text);
    void setTouchSwitch(char code,char value);
    void setTouchkeyColors(char n1, char n2, char n3, char s1, char s2, char s3);
    void setTouchkeyFont(char font);
    void setTouchkeyLabelColors(char nf,char sf);
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
    void callMacro(uint nr);
    void callTouchMacro(uint nr);
    void callMenuMacro(uint nr);

    /*! \brief Send *open* signal after a Menu open request has been sent from TFT.
     *
     *  If a touch menu is not set to open automatically the TFT sends a
     *  request 'ESC T 0'. This function sends 'ESC N T 2' to open the menu.
     */
    void openTouchMenu();

  private:
    boolean _smallprotocol;
    unsigned char bytesAvailable();
    void waitBytesAvailable();
    void sendByte(char data);
    void sendSmall(char* data, char len);
    void sendSmallDC2(char* data, char len);
};
#endif
