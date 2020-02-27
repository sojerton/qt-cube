#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QExposeEvent>
#include <QPainter>
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

// Front Primitive
#define PRIM_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
// Back Primitive
#define PRIM_BTR Vertex( QVector3D( 0.5f,  0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BTL Vertex( QVector3D(-0.5f,  0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BBL Vertex( QVector3D(-0.5f, -0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BBR Vertex( QVector3D( 0.5f, -0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )

// Serifs long
#define ONE Vertex( QVector3D(0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define N_ONE Vertex( QVector3D(0.5f,  0.5f,  0.45f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define TWO Vertex( QVector3D(0.5f,  0.5f,  0.3f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define N_TWO Vertex( QVector3D(0.5f,  0.5f,  0.25f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define THREE Vertex( QVector3D(0.5f,  0.5f,  0.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_THREE Vertex( QVector3D(0.5f,  0.5f,  0.05f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define FOUR Vertex( QVector3D(0.5f,  0.5f,  -0.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_FOUR Vertex( QVector3D(0.5f,  0.5f,  -0.15f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define FIVE Vertex( QVector3D(0.5f,  0.5f,  -0.3f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_FIVE Vertex( QVector3D(0.5f,  0.5f,  -0.35f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define SIX Vertex( QVector3D(0.5f,  0.5f,  -0.5f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_SIX Vertex( QVector3D(0.5f,  0.5f,  -0.55f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define SEVEN Vertex( QVector3D(0.5f,  0.5f,  -0.7f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_SEVEN Vertex( QVector3D(0.5f,  0.5f,  -0.75f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define EIGHN Vertex( QVector3D(0.5f,  0.5f,  -0.9f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_EIGHN Vertex( QVector3D(0.5f,  0.5f,  -0.95f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define NINE Vertex( QVector3D(0.5f,  0.5f,  -1.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_NINE Vertex( QVector3D(0.5f,  0.5f,  -1.15f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define TEN Vertex( QVector3D(0.5f,  0.5f,  -1.3f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_TEN Vertex( QVector3D(0.5f,  0.5f,  -1.35f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define LOOP Vertex( QVector3D(0.5f,  0.5f,  -1.5f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_LOOP Vertex( QVector3D(0.5f,  0.5f,  -1.55f), QVector3D( 0.0f, 1.0f, 0.0f )  )

// Create serifs
static const Vertex sg_vertexes_serif[] = {
    ONE, N_ONE, TWO, N_TWO, THREE, N_THREE,
    FOUR, N_FOUR, FIVE, N_FIVE, SIX, N_SIX,
    SEVEN, N_SEVEN, EIGHN, N_EIGHN, NINE, N_NINE,
    TEN, N_TEN, LOOP, N_LOOP
};

// Create figure
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
// Create primitive
static const Vertex sg_vertexes_prim[] = {
    PRIM_FTR, PRIM_FTL, PRIM_FBL,
    PRIM_FBR, PRIM_FTR, PRIM_BTR,
    PRIM_BTL, PRIM_FTL, PRIM_BTL,
    PRIM_BBL, PRIM_FBL, PRIM_BBL,
    PRIM_BBR, PRIM_FBR, PRIM_BBR,
    PRIM_BTR
};

#undef ONE
#undef N_ONE
#undef TWO
#undef N_TWO
#undef THREE
#undef N_THREE
#undef FOUR
#undef N_FOUR
#undef FIVE
#undef N_FIVE
#undef SIX
#undef N_SIX
#undef SEVEN
#undef N_SEVEN
#undef EIGHN
#undef N_EIGHN
#undef NINE
#undef N_NINE
#undef TEN
#undef N_TEN
#undef LOOP
#undef N_LOOP

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
    s_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());

    glDrawArrays(GL_LINES, 0, sizeof(sg_vertexes_serif) / sizeof(sg_vertexes_serif[0]));
    s_object.release();
  }
  s_program->release();

  paintSerif();

}
    // Painting serif
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
    } else if (event->buttons() & Qt::LeftButton && (dx < 0)) {
        m_transform.rotate(-2.0f, QVector3D(0.0f, 0.4f, 0.0f));
    }
    if (event->buttons() & Qt::LeftButton && (dy > 0)) {
        m_transform.rotate(2.0f, QVector3D(0.4f, 0.0f, 0.0f));
    } else if (event->buttons() & Qt::LeftButton && (dy < 0)) {
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
