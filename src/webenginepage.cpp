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

#include "webenginepage.h"
#include <QtGui/QDesktopServices>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtWebEngineCore/QWebEngineProfile>
#else
#include <QtWebEngineWidgets/QWebEngineProfile>
#endif

WebEnginePage::WebEnginePage(QObject *parent)
    : QWebEnginePage(QWebEngineProfile::defaultProfile(), parent) {
    QObject::connect(this, &QWebEnginePage::featurePermissionRequested,
                     [&] (const QUrl &origin, QWebEnginePage::Feature feature) {
                         if (feature != QWebEnginePage::Notifications)
                             return;
                         this->setFeaturePermission(origin, feature, QWebEnginePage::PermissionGrantedByUser);
                     });
}

bool WebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) {
    if (QWebEnginePage::NavigationTypeLinkClicked==type) {
        QDesktopServices::openUrl(url);
        return false;
    }
    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}
