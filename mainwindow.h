#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "change.h"

class QExposeEvent;
class QOpenGLShaderProgram;

class MainWindow : public QOpenGLWidget,
               protected QOpenGLFunctions
{
  Q_OBJECT

// OpenGL Events
public:
  MainWindow();
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
protected slots:
  void teardownGL();
  void update();
protected:
  void paintSerif();
  void mousePressEvent ( QMouseEvent * event );
  void mouseMoveEvent ( QMouseEvent * event );
  void wheelEvent(QWheelEvent *event);
private:
  QPoint lastPos;
  // OpenGL State Information
  QOpenGLBuffer m_vertex, p_vertex;
  QOpenGLVertexArrayObject m_object, p_object;
  QOpenGLShaderProgram *m_program, *p_program;

  // Shader Information
  int u_modelToWorld;
  int u_worldToView;
  QMatrix4x4 m_projection;
  Transform3D m_transform;
};


#endif // MAINWINDOW_H
