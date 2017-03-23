#include "redman.h"

static void mapToParent_jump(int n);

RedMan::RedMan(QObject *parent) :
    QObject(parent), QGraphicsItem()
{


 state_man = Stand_state; //планирую под это состояние ввести анимацию
 sprites_count = 960; //нулевой отсчет спрайтов
 left_jump  = new QPixmap(":jump_left.png");
 left_down  = new QPixmap(":Left_down.png");
 left_run   = new QPixmap(":left_run.png");
 left_right = new QPixmap(":Left_to_right.png");
 right_jump = new QPixmap(":right_up.png");
 right_down = new QPixmap(":right_down.png");
 right_run  = new QPixmap(":right_run.png");
 right_left = new QPixmap(":right_to_left.png");
 //
 cat_left = new QPixmap(":cat_left.png");
 cat_right = new QPixmap(":cat_right.png");
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
        setPos(mapToParent(-5, 0));
        sprites_count -= 120;
        if (sprites_count <= 0){
            sprites_count = 960;
            timer_sprites->stop();
            }
            break;
    case Right_State:
        setPos(mapToParent(5, 0));
        sprites_count += 120;
        if (sprites_count >= 960){
            sprites_count = 0;
            timer_sprites->stop();
            }
            break;
    case Jump_Left:
       // setPos(mapToParent(-8, 0));
        mapToParent_jump(jump_count);
        jump_count++;
        sprites_count += 77;
        if (sprites_count >= 847){
            sprites_count = 0;
            jump_count = 0;
            timer_sprites->stop();
            }
            break;
    case Jump_Right:
        setPos(mapToParent(8, 0));
        sprites_count += 76.27;
        if (sprites_count >= 839){
            sprites_count = 0;
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
        painter->drawPixmap(-60,-60, *cat_left ,sprites_count ,120 /*или -120*/ , 120, 120);
    if(state_man == Right_State )
        painter->drawPixmap(-50,-50,  *cat_right,sprites_count ,120 , 120, 120);
    if(state_man == Jump_Left )
        painter->drawPixmap(-50,-50,  *left_jump,sprites_count ,0 , 77, 99);
    if(state_man == Jump_Right )
        painter->drawPixmap(-50,-50,  *right_jump,sprites_count ,0 , 77, 95);
    if(state_man == Stand_state )
        painter->drawPixmap(-50,-50,  *cat_right,sprites_count ,0 , 120, 120);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

 RedMan::~RedMan(){

}

 void RedMan:: mapToParent_jump(int n){


     switch(n){
     case 0:
         setPos(mapToParent(-1, 1));
     case 1:
         setPos(mapToParent(-1, 1));
     case 2:
         setPos(mapToParent(-1, 1));
     case 3:
         setPos(mapToParent(-1, 1));
     case 4:
         setPos(mapToParent(-1, 1));
     case 5:
         setPos(mapToParent(-1, 1));
     case 6:
         setPos(mapToParent(-1, -1));
     case 7:
         setPos(mapToParent(-1, -1));
     case 8:
         setPos(mapToParent(-1, -1));
     case 9:
         setPos(mapToParent(-1, -1));
     case 10:
         setPos(mapToParent(-1, -2));
     }

 }
