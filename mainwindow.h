#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <redman.h>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene  *scene;     /// Объявляем графическую сцену
    RedMan          *redman;  /// и треугольник
    QTimer          *timer;
    QMediaPlayer   *m_player;
    QMediaPlaylist *m_playlist;
};

#endif // MAINWINDOW_H
