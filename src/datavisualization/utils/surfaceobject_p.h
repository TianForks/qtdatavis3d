/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef SURFACEOBJECT_P_H
#define SURFACEOBJECT_P_H

#include "datavisualizationglobal_p.h"
#include "abstractobjecthelper_p.h"
#include "qsurfacedataproxy.h"

#include <QOpenGLFunctions>
#include <QRect>

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

class SurfaceObject : public AbstractObjectHelper
{
public:
    SurfaceObject();
    ~SurfaceObject();

    void setUpData(const QSurfaceDataArray &dataArray, const QRect &space, GLfloat yRange,
                   GLfloat yMin, bool changeGeometry);
    void setUpSmoothData(const QSurfaceDataArray &dataArray, const QRect &space, GLfloat yRange,
                         GLfloat yMin, bool changeGeometry);
    void updateCoarseRows(const QSurfaceDataArray &dataArray, int startRow,
                          int endRow, GLfloat yRange, GLfloat yMin);
    void updateSmoothRows(const QSurfaceDataArray &dataArray, int startRow,
                          int endRow, GLfloat yRange, GLfloat yMin);
    void createSmoothIndices(int x, int y, int endX, int endY);
    void createCoarseIndices(int x, int y, int columns, int rows);
    void createSmoothGridlineIndices(int x, int y, int endX, int endY);
    void createCoarseGridlineIndices(int x, int y, int endX, int endY);
    GLuint gridElementBuf();
    GLuint gridIndexCount();
    QVector3D vertexAt(int column, int row);

private:
    QVector3D normal(const QVector3D &a, const QVector3D &b, const QVector3D &c);
    void createBuffers(const QVector<QVector3D> &vertices, const QVector<QVector2D> &uvs,
                       const QVector<QVector3D> &normals, const GLint *indices,
                       bool changeGeometry);

private:
    enum SurfaceType {
        SurfaceSmooth,
        SurfaceFlat
    };
    int m_surfaceType;
    int m_columns;
    int m_rows;
    GLuint m_gridElementbuffer;
    GLuint m_gridIndexCount;
    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_normals;
};

QT_DATAVISUALIZATION_END_NAMESPACE
#endif // SURFACEOBJECT_P_H
