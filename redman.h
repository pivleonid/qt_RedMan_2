#ifndef REDMAN_H
#define REDMAN_H

#define Stand_state 0
#define Left_State  1
#define Right_State 2
#define Jump_Left   3
#define Jump_Right  4
#define Cower_Down  5
#define Cower_Up    6

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

#include <windows.h>

class RedMan : public QObject, public QGraphicsItem
{
Q_OBJECT
public:
    explicit RedMan(QObject *parent = 0);
    ~RedMan();

private:
    //эти два метода необходимо переопределить
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mapToParent_jump(int n);
public slots:
//слот соеденить с игровым таймером программы
//слот опроса клавиши и действия
void slotTimerMan();
void slotKey_sprites();

private:
// состояние фигурки: влево, вправо...
int state_man;
// итерация спрайтов
int sprites_count;
// счетчик прыжков
int jump_count;


QPixmap* left_jump;
QPixmap* left_down;
QPixmap* left_run;
QPixmap* left_right;
QPixmap* right_jump;
QPixmap* right_down;
QPixmap* right_run;
QPixmap* right_left;
//
QPixmap* cat_left;
QPixmap* cat_right;

QTimer* timer_sprites;
};

#endif // REDMAN_H
