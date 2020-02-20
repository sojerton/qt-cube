#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(3, 3);

  // Set widget up
  MainWindow *widget = new MainWindow;
  widget->setFormat(format);

  QMainWindow w;
  w.setCentralWidget(widget);
  w.resize(QSize(800, 600));
  w.show();

  return a.exec();
}
