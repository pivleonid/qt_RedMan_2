#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();   /// Инициализируем графическую сцену

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500); /// Устанавливаем область графической сцены
    timer = new QTimer();

    redman = new RedMan();
    scene->addItem(redman);
    redman->setPos( 0, 0);
    connect(timer, &QTimer::timeout,redman, &RedMan::slotTimerMan);
    timer->start(10);

    scene->addLine(-500,60,500,60,QPen(Qt::black));

//
    m_player = new QMediaPlayer(this);          // Инициализация плеера
    m_playlist = new QMediaPlaylist(m_player);  // Инициализация плейлиста

    m_player->setPlaylist(m_playlist);          // Установка плейлиста в аудио плеер
    m_playlist->addMedia(QUrl("qrc:/sprites/understand.wav"));       // Добавление трека в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // Зацикливание трека

}

MainWindow::~MainWindow()
{
    delete ui;
}
