Introduction
============

Simple QWebEngine wrapper for web-apps. Usage:

```
qwebappwrapper http://APP_URL --qwindowtitle TitleOfWindow --qwindowicon /path/to/icon.png --appname AppName
```

building
--------
1. sudo apt install cmake g++ qtwebengine5-dev
2. mkdir build
3. cd build
4. cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release
5. make
6. sudo make install


Example apps
------------
This contains example Linuux `.desktop` files for LMS and WhatsApp. In the
source tarball these are `cmake templates` that will be installed into `PREFIX/share/qwebappwrapper/apps`

To make an app usable, simply copy (or sym link) the `.desktop` file to `PREFIX/share/applications/`
NOTE: You will probably need to edit `LMS.desktop` to contain the correct
IP/hostname of your LMS server.

If the `/usr/local` is the install prefix, then `WhatsApp.desktop` would be
created as follows:

```
[Desktop Entry]
Version=1.0
Name=WhatsApp
Comment=WhatsApp Web
Exec=/usr/local/bin/qwebappwrapper --qwindowtitle WhatsApp --qwindowicon /usr/local/share/qwebappwrapper/icons/whatsapp.png --appname WhatsApp https://web.whatsapp.com/
Terminal=false
Type=Application
Icon=/usr/local/share/qwebappwrapper/icons/whatsapp.png
StartupWMClass=WhatsApp
StartupNotify=true
```

Python
------
By default a binary is created, but this needs the Qt, etc, development
libraries. Alternatively you can use the Python3 implementation located in the
`python` sub-folder.
