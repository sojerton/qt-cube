#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QOpenGLShaderProgram>
#include <QExposeEvent>
#include <QPainter>
#include <QPair>
#include "vectors.h"

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/

MainWindow::MainWindow()
{
  m_transform.translate(0.0f, 0.0f, -5.0f);
  s_transform.translate(0.0f, 0.0f, -5.0f);
}

void MainWindow::initializeGL()
{
  // Initialize OpenGL
  initializeOpenGLFunctions();
  connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

  // Set global information
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Application-specific initialization
  {
    // Create Shader
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    m_program->link();
    m_program->bind();

    // Cache Uniform Locations
    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToView = m_program->uniformLocation("worldToView");

    // Create Buffer
    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

    // Create Vertex Array Object
    m_object.create();
    m_object.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT,  Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    // Release
    m_object.release();
    m_vertex.release();
    m_program->release();

    // Create Shader for primitive
    p_program = new QOpenGLShaderProgram();
    p_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    p_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    p_program->link();
    p_program->bind();

    // Cache Uniform Locations
    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToView = m_program->uniformLocation("worldToView");

    // Create Buffer
    p_vertex.create();
    p_vertex.bind();
    p_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    p_vertex.allocate(sg_vertexes_prim, sizeof(sg_vertexes_prim));

    // Create Vertex Array Object
    p_object.create();
    p_object.bind();
    p_program->enableAttributeArray(0);
    p_program->enableAttributeArray(1);
    p_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    p_program->setAttributeBuffer(1, GL_FLOAT,  Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
    // Release
    p_object.release();
    p_vertex.release();
    p_program->release();
    // Create Shader for serif
    s_program = new QOpenGLShaderProgram();
    s_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    s_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    s_program->link();
    s_program->bind();
    // Cache Uniform Locations
    u_modelToWorld = m_program->uniformLocation("modelToWorld");
    u_worldToView = m_program->uniformLocation("worldToView");
    // Create Buffer
    s_vertex.create();
    s_vertex.bind();
    s_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    s_vertex.allocate(sg_vertexes_serif, sizeof (sg_vertexes_serif));

    // Create Vertex Array Object
    s_object.create();
    s_object.bind();
    s_program->enableAttributeArray(0);
    s_program->enableAttributeArray(1);
    s_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    s_program->setAttributeBuffer(1, GL_FLOAT,  Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

//    s_program->disableAttributeArray(0);
//    s_vertex.allocate(sg_vertexes_serif, sizeof (sg_vertexes_serif));
//    s_program->enableAttributeArray(0);
//    s_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

    // Release
    s_object.release();
    s_vertex.release();
    s_program->release();
  }
}

void MainWindow::resizeGL(int width, int height)
{
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void MainWindow::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);

  // Render using shader
  m_program->bind();
  m_program->setUniformValue(u_worldToView, m_projection);
  {
    m_object.bind();
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    m_object.release();
  }
  m_program->release();
  // Render primitive using shader
  p_program->bind();
  p_program->setUniformValue(u_worldToView, m_projection);
  {
    p_object.bind();
    p_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
    glDrawArrays(GL_LINE_LOOP, 0, sizeof(sg_vertexes_prim) / sizeof(sg_vertexes_prim[0]));
    p_object.release();
  }
  p_program->release();
  // Render serif using shader
  s_program->bind();
  s_program->setUniformValue(u_worldToView, m_projection);
  {
    s_object.bind();
    s_program->setUniformValue(u_modelToWorld, s_transform.toMatrix());
        //glDrawArrays(GL_LINES, 0, sizeof(sg_vertexes_serif));

         s_transform.setTranslation(QVector3D(0.5f, 0.5f, 0.5f));
         glDrawArrays(GL_LINES, 0, sizeof(sg_vertexes_serif));
        //s_transform.setTranslation(-0.5f, 0.0f, 0.0f);
//         glDrawArrays(GL_LINES, 0, sizeof(sg_vertexes_serif));
//        s_transform.setTranslation(0.0f, 0.5f, 0.0f);
//         glDrawArrays(GL_LINES, 0, sizeof(sg_vertexes_serif));
//        s_transform.setTranslation(0.5f, 0.0f, 0.0f);
        //s_transform.setRotation(2.0f, QVector3D(0.0f, 0.4f, 0.0f));
    s_object.release();
  }
  s_program->release();

  s_program->bind();
  s_program->setUniformValue(u_worldToView, m_projection);
  {
    s_object.bind();
    s_program->setUniformValue(u_modelToWorld, s_transform.toMatrix());
        glDrawArrays(GL_LINES, 0, sizeof(sg_vertexes_serif));
    s_object.release();
  }
  s_program->release();

}
/*TODO text painting/////////////////////

void MainWindow::paintSerif(){
    QPainter painter(this);
    painter.beginNativePainting();

    glDisable(GL_CULL_FACE);
    painter.setPen(Qt::green);
    painter.drawLine(QPointF(Vertex::positionOffset(), Vertex::positionOffset()),
                     QPointF(Vertex::positionOffset()+50, Vertex::positionOffset()+50));
    glEnable(GL_CULL_FACE);

    painter.endNativePainting();
}
*/
void MainWindow::teardownGL()
{
  // Actually destroy our OpenGL information
  m_object.destroy();
  m_vertex.destroy();
  delete m_program;
  p_object.destroy();
  p_vertex.destroy();
  delete p_program;
  s_object.destroy();
  s_vertex.destroy();
  delete s_program;
}

void MainWindow::update()
{
  QOpenGLWidget::update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Update last cursor position
    lastPos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Mouse move axis
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    // Rotate by mouse move
    if (event->buttons() & Qt::LeftButton && (dx > 0)) {
        m_transform.rotate(2.0f, QVector3D(0.0f, 0.4f, 0.0f));
        s_transform.rotate(2.0f, QVector3D(0.0f, 0.4f, 0.0f));
    } else if (event->buttons() & Qt::LeftButton && (dx < 0)) {
        m_transform.rotate(-2.0f, QVector3D(0.0f, 0.4f, 0.0f));
        s_transform.rotate(-2.0f, QVector3D(0.0f, 0.4f, 0.0f));
    }
    if (event->buttons() & Qt::LeftButton && (dy > 0)) {
        m_transform.rotate(2.0f, QVector3D(0.4f, 0.0f, 0.0f));
        s_transform.rotate(2.0f, QVector3D(0.4f, 0.0f, 0.0f));
    } else if (event->buttons() & Qt::LeftButton && (dy < 0)) {
        m_transform.rotate(-2.0f, QVector3D(0.4f, 0.0f, 0.0f));
        s_transform.rotate(-2.0f, QVector3D(0.4f, 0.0f, 0.0f));
    }
    lastPos = event->pos();
}

void MainWindow::wheelEvent(QWheelEvent *event){
    // Scaling cube
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if (event->orientation() == Qt::Vertical) {
        m_transform.grow(numSteps);
        s_transform.grow(numSteps);
    }
    event->accept();
}
