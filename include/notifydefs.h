#ifndef NOTIFYDEFS_H
#define NOTIFYDEFS_H

#include <QString>

const int NOTIFY_WIDTH     = 300;
const int NOTIFY_HEIGHT    = 70;
const int NOTIFY_SPACING   = 2;
const int NOTIFY_FONT_POINTSIZE = 10;
const double NOTIFY_MAX_OPACITY = 0.9;
const int NOTIFY_ANIMATION_DURATION = 200;
const int NOTIFY_ROOT_HOFFSET = 2;
const int NOTIFY_ROOT_VOFFSET = 2;
const int NOTIFY_MAX_VISIBLE  = 5;

const QString NOTIFY_INFOSTYLE  =
    "QWidget {"
    "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 \"#37a0e3\", stop: 1 \"#217fba\");"
    "   border-radius: 2px;"
    "   color: white;"
    "}"
    "QWidget QLabel{"
    "   color: white;"
    "   border: none;"
    "}";

const QString NOTIFY_WARNINGSTYLE  =
    "QWidget {"
    "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 \"#efd22a\", stop: 1 \"#d5bb24\");"
    "   border-radius: 2px;"
    "   color: \"#333323\";"
    "}"
    "QWidget QLabel{"
    "   color: \"#333323\";"
    "   border: none;"
    "}";

const QString NOTIFY_CRITICALSTYLE  =
    "QWidget {"
    "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 \"#e33737\", stop: 1 \"#ba2020\");"
    "   border-radius: 2px;"
    "   color: white;"
    "}"
    "QWidget QLabel{"
    "   color: white;"
    "   border: none;"
    "}";

#endif
