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

#include "mainwindow.h"
#include "webenginepage.h"
#include <QtCore/QSettings>
#include <QtCore/QSize>
#include <QtCore/QTimer>
#include <QtCore/QUrl>
#include <QtGui/QKeySequence>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtWebEngineCore/QWebEngineProfile>
#else
#include <QtWebEngineWidgets/QWebEngineProfile>
#endif
#include <QtWebEngineWidgets/QWebEngineView>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtGui/QAction>
#else
#include <QtWidgets/QAction>
#endif

MainWindow::MainWindow(const QString &url, qreal defaultZoom)
    : QMainWindow(nullptr) {
    QSettings settings;
    web = new QWebEngineView(this);
    page = new WebEnginePage(web);
    web->setPage(page);
    web->load(QUrl(url));
    web->setContextMenuPolicy(Qt::NoContextMenu);
    connect(web, &QWebEngineView::titleChanged, this, &QMainWindow::setWindowTitle);
    setCentralWidget(web);

    if (settings.contains("windowGeometry")) {
        restoreGeometry(settings.value("windowGeometry").toByteArray());
    } else {
        resize(800, 600);
    }
    if (settings.contains("state")) {
        restoreState(settings.value("state").toByteArray());
    }
    web->setZoomFactor(settings.contains("zoom") ? settings.value("zoom").toReal() : defaultZoom);

    QAction *reloadAct = new QAction(this);
    reloadAct->setShortcut(QKeySequence::Refresh);
    connect(reloadAct, &QAction::triggered, this, &MainWindow::reload);
    addAction(reloadAct);

    QAction *zoomInAct = new QAction(this);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);
    addAction(zoomInAct);

    QAction *zoomOutAct = new QAction(this);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);
    addAction(zoomOutAct);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings;
    settings.setValue("windowGeometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.setValue("zoom", web->zoomFactor());
    QMainWindow::closeEvent(event);
}

void MainWindow::reload() {
    web->stop();
    QWebEngineProfile::defaultProfile()->clearHttpCache();
    QTimer::singleShot(500, web, &QWebEngineView::reload);
}

void MainWindow::zoomIn() {
    qreal zoom = page->zoomFactor();
    if (zoom<=4.75) {
        zoom+= 0.25;
        page->setZoomFactor(zoom);
    }
}

void MainWindow::zoomOut() {
    qreal zoom = page->zoomFactor();
    if (zoom>=0.5) {
        zoom-= 0.25;
        page->setZoomFactor(zoom);
    }
}
