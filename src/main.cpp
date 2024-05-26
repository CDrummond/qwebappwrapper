/*
 * QWebAppWrapper
 *
 * Copyright (c) 2022 Craig Drummond <craig.p.drummond@gmail.com>
 *
 * ----
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "mainwindow.h"
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtWebEngineCore/QWebEngineProfile>
#else
#include <QtWebEngineWidgets/QWebEngineProfile>
#endif
#include <QtWidgets/QApplication>

static const QLatin1String constUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36");

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName(PROJECT_NAME);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCommandLineParser parser;

    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({{"a", "appname"}, QApplication::translate("main", "Set application name."), "appname", "QtWA"});
    parser.addOption({{"c", "cachesize"}, QApplication::translate("main", "Max size of cache (Mb)."), "cachesize", "50"});
    parser.addOption({{"d", "dark"}, QApplication::translate("main", "Use dark theme.")});
    parser.addOption({{"z", "zoom"}, QApplication::translate("main", "Initial zoom scale (e.g. 1.5).")});
    parser.process(app);

    if (parser.isSet("dark")) {
        app.setProperty("KDE_COLOR_SCHEME_PATH", "/usr/share/color-schemes/BreezeDark.colors");
        app.setStyleSheet("QToolTip{background-color:#121212;color:#eee}");
    }

    QString appName = parser.value("appname");
    unsigned int maxCacheSize = parser.isSet("cachesize") ? parser.value("cachesize").toUInt() : 50;
    qreal zoom = parser.isSet("zoom") ? parser.value("zoom").toFloat() : 1.0;

    QWebEngineProfile::defaultProfile()->setHttpCacheMaximumSize(maxCacheSize*1024*1024);
    QWebEngineProfile::defaultProfile()->setHttpUserAgent(constUserAgent);

    if (!appName.isEmpty()) {
        app.setApplicationName(appName);
        app.setOrganizationName(appName);
    }

    const QStringList args = parser.positionalArguments();

    if (args.length()!=1) {
        qWarning() << QApplication::translate("main", "Must specify one, and only one, URL");
        return -1;
    }

    MainWindow mw(args.at(0), zoom);
    mw.show();
    return app.exec();
}
