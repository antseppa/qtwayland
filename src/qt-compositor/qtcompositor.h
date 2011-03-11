/****************************************************************************
**
** This file is part of QtCompositor**
**
** Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact:  Nokia Corporation qt-info@nokia.com
**
** You may use this file under the terms of the BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
** Redistributions of source code must retain the above copyright
** notice, this list of conditions and the following disclaimer.
**
** Redistributions in binary form must reproduce the above copyright
** notice, this list of conditions and the following disclaimer in the
** documentation and/or other materials provided with the distribution.
**
** Neither the name of Nokia Corporation and its Subsidiary(-ies) nor the
** names of its contributors may be used to endorse or promote products
** derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#ifndef QTCOMP_H
#define QTCOMP_H

#include <QObject>
#include <QImage>
#include <QRect>

#ifdef QT_COMPOSITOR_WAYLAND_GL
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

class QWidget;

namespace Wayland
{
    class Compositor;
}

class WaylandCompositor
{
public:
    WaylandCompositor(QWidget *topLevelWidget = 0);
    virtual ~WaylandCompositor();

    void sendMousePressEvent(uint winId, int x, int y, Qt::MouseButton button);
    void sendMouseReleaseEvent(uint winId, int x, int y, Qt::MouseButton button);
    void sendMouseMoveEvent(uint winId, int x, int y);

    void sendKeyPressEvent(uint winId, uint code);
    void sendKeyReleaseEvent(uint winId, uint code);

    void frameFinished();

    void setInputFocus(uint winId);

    void setDirectRenderWinId(uint winId);
    uint directRenderWinId() const;

    QWidget *topLevelWidget()const;

    bool hasImage(uint winId) const;
    const QImage image(uint winId) const;

#ifdef QT_COMPOSITOR_WAYLAND_GL
    bool hasTexture(uint winId) const;
    GLuint textureId(uint winId) const;
#endif

    virtual void surfaceCreated(uint winId) = 0;
    virtual void surfaceDestroyed(uint winId) = 0;
    virtual void surfaceMapped(uint winId, const QRect &rect) = 0;
    virtual void surfaceDamaged(uint winId, const QRect &rect) = 0;

private:
    Wayland::Compositor *m_compositor;
    QWidget  *m_toplevel_widget;

};

#endif // QTCOMP_H