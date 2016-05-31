
A library for controlling Electronic Assembly eDIPTFT displays.

Copyright (c) 2013 Stefan Gofferje. All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later
version.

This library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General
Public License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA 02110-1301 USA

## Features

* draw text, lines, rectangles
* define touch areas
* define radio touch groups
* define menus
* call macros, touch macros and menu macros
* draw bargraphs and define them as touch areas

## Usage

    #include <ediptft.h>

    EDIPTFT tft = EDIPTFT();

    void main() {
        tft.begin(115200);  // start display communication
        tft.clear();  // clear display
        tft.setTextFont(EA_GENEVA10);  // set a text font
        tft.drawText(100, 30, 'C', "Hello World");  // draw some text
    }

