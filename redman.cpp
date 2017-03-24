#include "redman.h"



RedMan::RedMan(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

jump_count = 0;
 state_man = Stand_state; //планирую под это состояние ввести анимацию
 sprites_count = 0; //нулевой отсчет спрайтов
 //
 cat_left = new QPixmap(":/sprites/cat_left.png");
 cat_right = new QPixmap(":/sprites/cat_right.png");

 timer_sprites = new QTimer;
 connect(timer_sprites,&QTimer::timeout, this, &RedMan::slotKey_sprites);
}


void RedMan::slotTimerMan(){
    if(timer_sprites->isActive() == false){
        if(GetAsyncKeyState(VK_LEFT) ){
            state_man = Left_State;
            timer_sprites->start(25);
            return;

        }
        if(GetAsyncKeyState(VK_UP) ){
            if(state_man == Left_State)
            state_man = Jump_Left;
            if(state_man == Right_State)
            state_man = Jump_Right;
            timer_sprites->start(25);
            return;
        }
        if(GetAsyncKeyState(VK_RIGHT) ){
            state_man = Right_State;
            timer_sprites->start(25);
            return;
        }

        state_man = Stand_state;
        timer_sprites->start(25);
    }
}

void RedMan::slotKey_sprites(){
    switch(state_man){
    case Left_State:
        setPos(mapToParent(-15, 0));
        sprites_count -= 120;
        if (sprites_count <= 0){
            sprites_count = 960;
            timer_sprites->stop();
            }
            break;
    case Right_State:
        setPos(mapToParent(15, 0));
        sprites_count += 120;
        if (sprites_count >= 960){
            sprites_count = 0;
            timer_sprites->stop();
            }
            break;
    case Jump_Left:
        mapToParent_jump(jump_count);
        jump_count++;
        sprites_count -= 120;
        if (sprites_count <= 120){
            sprites_count = 960;
            jump_count = 0;
            timer_sprites->stop();
            }
            break;
    case Jump_Right:
        mapToParent_jump(jump_count);
        sprites_count += 120;
         jump_count++;
        if (sprites_count >= 840){
            sprites_count = 0;
             jump_count= 0 ;
            timer_sprites->stop();
            }
            break;
    case Stand_state:
        update();
        sprites_count += 120;
        if (sprites_count >= 960){
            sprites_count = 0;
            timer_sprites->stop();
        }
        break;
    }
}

QRectF RedMan::boundingRect() const{
    return QRectF(-60,-60,120,120);
}

void RedMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    /* В отрисовщике графического объекта отрисовываем спрайт
     * Разберём все параметры данной функции
     * Первых два аргумента - это координат X и Y куда помещается QPixmap
     * Третий аргумент - это указатель на QPixmap
     * 4 и 5 аргументы - Координаты в В изображении QPixmap, откуда будет отображаться изображение
     * Задавая координату X с помощью перемнной currentFrame мы будем как бы передвигать камеру
     * по спрайту
     * и последние два аргумента - это ширина и высота отображаем части изображение, то есть кадра
     * */
    if(state_man == Left_State )
        painter->drawPixmap(-60,-60, *cat_left ,sprites_count ,120 , 120, 120);
    if(state_man == Right_State )
        painter->drawPixmap(-60,-60,  *cat_right,sprites_count ,120 , 120, 120);
    if(state_man == Jump_Left )
        painter->drawPixmap(-60,-60,  *cat_left,sprites_count ,360 , 120, 120);
    if(state_man == Jump_Right )
        painter->drawPixmap(-60,-60,  *cat_right,sprites_count ,360 , 120, 120);
    if(state_man == Stand_state )
        painter->drawPixmap(-60,-60,  *cat_right,sprites_count ,0 , 120, 120);
//огриничения
    if(this->x() - 10 < -500){
        this->setX(-490);       // слева
    }
    if(this->x() + 10 > 500){
        this->setX(490);        // справа
    }

    if(this->y() - 10 < -500){
        this->setY(-490);       // сверху
    }
    if(this->y() + 10 > 500){
        this->setY(490);        // снизу
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

 RedMan::~RedMan(){

}

 void RedMan:: mapToParent_jump(int n){

 if (state_man == Jump_Left){
        switch(n){
     case 0:
         setPos(mapToParent(-20, 0));
         break;
     case 1:
         setPos(mapToParent(-20 ,-20 ));
          break;
     case 2:
         setPos(mapToParent(-20, -20));
          break;
     case 3:
         setPos(mapToParent(-20, -20));
          break;
     case 4:
         setPos(mapToParent(-20, 20));
          break;
     case 5:
         setPos(mapToParent(-20, 20));
          break;
     case 6:
         setPos(mapToParent(-20, 20));
     }

 }
 if (state_man == Jump_Right){
     switch(n){
     case 0:
         setPos(mapToParent(20, 0));
         break;
     case 1:
         setPos(mapToParent(20 ,-20 ));
          break;
     case 2:
         setPos(mapToParent(20, -20));
          break;
     case 3:
         setPos(mapToParent(20, -20));
          break;
     case 4:
         setPos(mapToParent(20, 20));
          break;
     case 5:
         setPos(mapToParent(20, 20));
          break;
     case 6:
         setPos(mapToParent(20, 20));
     }

 }
}
