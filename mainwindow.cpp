#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QExposeEvent>
#include "vertex.h"

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )

// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )

// Front Verticies
#define PRIM_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )

// Back Verticies
#define PRIM_BTR Vertex( QVector3D( 0.5f,  0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BTL Vertex( QVector3D(-0.5f,  0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BBL Vertex( QVector3D(-0.5f, -0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BBR Vertex( QVector3D( 0.5f, -0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )

// Create a colored cube
static const Vertex sg_vertexes[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};
// Create a colored cube
static const Vertex sg_vertexes_prim[] = {
  // Face 1 (Front)
    PRIM_FTR, PRIM_FTL, PRIM_FBL,
    PRIM_FBR, PRIM_FTR, PRIM_BTR,
    PRIM_BTL, PRIM_FTL, PRIM_BTL,
    PRIM_BBL, PRIM_FBL, PRIM_BBL,
    PRIM_BBR, PRIM_FBR, PRIM_BBR,
    PRIM_BTR
};
#undef PRIM_BBR
#undef PRIM_BBL
#undef PRIM_BTL
#undef PRIM_BTR
#undef PRIM_FBR
#undef PRIM_FBL
#undef PRIM_FTL
#undef PRIM_FTR

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR
#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/


MainWindow::MainWindow()
{
  m_transform.translate(0.0f, 0.0f, -5.0f);
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

    // Create Shader
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
  // Render 2 using shader
  p_program->bind();
  p_program->setUniformValue(u_worldToView, m_projection);
  {
    p_object.bind();
    p_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
    glDrawArrays(GL_LINE_LOOP, 0, sizeof(sg_vertexes_prim) / sizeof(sg_vertexes_prim[0]));
    p_object.release();
  }
  p_program->release();
}

void MainWindow::teardownGL()
{
  // Actually destroy our OpenGL information
  m_object.destroy();
  m_vertex.destroy();
  delete m_program;
  p_object.destroy();
  p_vertex.destroy();
  delete p_program;
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
    // Rotate cube by mouse move
    if (event->buttons() & Qt::LeftButton & (dx > 0)) {
        m_transform.rotate(2.0f, QVector3D(0.0f, 0.4f, 0.0f));
    } else if (event->buttons() & Qt::LeftButton & (dx < 0)) {
        m_transform.rotate(-2.0f, QVector3D(0.0f, 0.4f, 0.0f));
    } else if (event->buttons() & Qt::LeftButton & (dy > 0)) {
        m_transform.rotate(2.0f, QVector3D(0.4f, 0.0f, 0.0f));
    } else if (event->buttons() & Qt::LeftButton & (dy < 0)) {
        m_transform.rotate(-2.0f, QVector3D(0.4f, 0.0f, 0.0f));
    }
    lastPos = event->pos();
}

void MainWindow::wheelEvent(QWheelEvent *event){
    // Scaling cube
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if (event->orientation() == Qt::Vertical) {
        m_transform.grow(numSteps);
    }
    event->accept();
}
