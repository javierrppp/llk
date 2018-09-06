#include "startinterface.h"
#include "handler.h"
#include "windows.h"
#include <stdlib.h>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QSound>
#include <QList>
#include <QColor>

startInterface::startInterface()
{
    this->setSceneRect(0, 0, 800, 800);
    handler* hand = handler::getInstance();
    //canvas
    this->opache_canvas = new llkcanvas("main_canvas",0, 0, 800, 800);
    this->opache_canvas->setOpacity(0.01);
    this->addItem(opache_canvas);

    //start interface buttons
    this->start_btn = new llkButton("start", QString::fromLocal8Bit("开     始"));
    this->start_btn->setPos(300,400);
    this->search_btn = new llkButton("search", QString::fromLocal8Bit("排     行"));
    this->search_btn->setPos(300,500);
    this->exit_btn = new llkButton("exit", QString::fromLocal8Bit("退     出"));
    this->exit_btn->setPos(300,600);
    this->title = new QGraphicsPixmapItem;
    this->title->setPixmap(QPixmap(":/system/img/title.png"));
    this->title->setPos(100,150);

    //setting buttons
    this->settings = new assemble("settings", ":/system/img/", -2, -2, 75, 75);
    this->settings->setPos(730,20);
    this->settings->setZValue(5);
    this->settings_canvas = new llkcanvas("settings", 100, 200, 600, 500);
    this->settings_canvas->setOpacity(0.9);
    this->settings_canvas->setColor(new QColor(255, 255, 255));
    this->settings_canvas->hide();
    this->settings_canvas->setZValue(5);
    this->volumn_img = new assemble("volumn", ":/system/img/", -10, -10, 140, 140);
    this->volumn_img->setPos(260, 300);
    this->volumn_img->setParentItem(settings_canvas);
    this->ban_volumn_img  = new assemble("ban_volumn", ":/system/img/", -10, -10, 140, 140);
    this->ban_volumn_img->setPos(260, 300);
    this->ban_volumn_img->setParentItem(settings_canvas);
    this->ban_volumn_img->hide();
    this->arrow_img = new assemble("arrow", ":/system/img/", -10, -10, 90, 70);
    this->arrow_img->setPos(62,176);
    this->arrow_img->setParentItem(settings_canvas);
    this->home = new assemble("home", ":/system/img/", -10, -10, 140, 140);
    this->home->setPos(430, 300);
    this->home->setParentItem(settings_canvas);
    connect(hand, SIGNAL(modifyVolumn(bool)), this, SLOT(modifyVolumn(bool)));

    //game over

    this->game_over_canvas = new llkcanvas("settings", 220, 300, 360, 200);
    this->game_over_canvas->setOpacity(0.9);
    this->game_over_canvas->setColor(new QColor(255, 255, 255));
    this->game_over_canvas->hide();
    this->game_over_canvas->setZValue(4);
    this->play_again = new assemble("play_again", ":/system/img/", -10, -10, 80, 80);
    this->play_again->setParentItem(game_over_canvas);
    this->play_again->setPos(435,420);
    this->game_home1 = new assemble("game_home", ":/system/img/", -10, -10, 80, 80);
    this->game_home1->setParentItem(game_over_canvas);
    this->game_home1->setPos(290,420);
    this->game_home1->setData(2, QVariant(1));
    this->game_over_text = new llkText(QString::fromLocal8Bit("通 关 失 败 ！"));
    this->game_over_text->setColor(new QColor(98, 81, 88));
    this->game_over_text->setSize(28);
    this->game_over_text->setPos(300, 390);
    this->game_over_text->setParentItem(game_over_canvas);

    //game pass

    this->game_pass_canvas = new llkcanvas("settings", 220, 300, 360, 200);
    this->game_pass_canvas->setOpacity(0.9);
    this->game_pass_canvas->setColor(new QColor(255, 255, 255));
    this->game_pass_canvas->hide();
    this->game_pass_canvas->setZValue(4);
    this->next_checkpoint = new assemble("next_checkpoint", ":/system/img/", -10, -10, 80, 80);
    this->next_checkpoint->setParentItem(game_pass_canvas);
    this->next_checkpoint->setPos(435,420);
    this->game_home2 = new assemble("game_home", ":/system/img/", -10, -10, 80, 80);
    this->game_home2->setParentItem(game_pass_canvas);
    this->game_home2->setPos(290,420);
    this->game_home2->setData(2, QVariant(2));
    this->game_pass_text = new llkText(QString::fromLocal8Bit("恭 喜 通 关 ！"));
    this->game_pass_text->setColor(new QColor(98, 81, 88));
    this->game_pass_text->setSize(28);
    this->game_pass_text->setPos(300, 390);
    this->game_pass_text->setParentItem(game_pass_canvas);


    connect(hand, SIGNAL(playAgain()), this, SLOT(playAgain()));
    connect(hand, SIGNAL(toNextCheckpoint()), this, SLOT(toNextCheckpoint()));

    //after start game
    this->time = 60;
    this->score = 0;
    this->grade = 6;
    this->order1_tips = -1;
    this->order2_tips = -1;
    this->disapearTimes = new QTimer;
    this->game_canvas = new llkcanvas("game", 0, 0, 800, 800);
    this->game_canvas->hide();
    connect(hand, SIGNAL(selectOrder(int)), this, SLOT(judgeAndUpdate(int)));
    this->selected_square = -1;
    this->route = new llkRoute;
    this->route->hide();
    this->route->setParentItem(game_canvas);
    this->time_text = new llkText(QString::fromLocal8Bit(("时间：60")));
    this->time_text->setPos(100, 70);
    this->time_text->setParentItem(game_canvas);
    this->score_text = new llkText(QString::fromLocal8Bit(("得分：0")));
    this->score_text->setPos(550, 70);
    this->score_text->setParentItem(game_canvas);
    this->grade_text = new llkText(QString::fromLocal8Bit(("关卡：01")));
    this->grade_text->setPos(325, 70);
    this->grade_text->setParentItem(game_canvas);
    this->refresh = new assemble("refresh", ":/system/img/", -10, -10, 80, 80);
    this->refresh->setPos(720,175);
    this->refresh->setParentItem(game_canvas);
    this->refresh_disabled = new assemble("refresh_disabled", ":/system/img/", -10, -10, 80, 80, false);
    this->refresh_disabled->setPos(720,175);
    this->refresh_disabled->setParentItem(game_canvas);
    this->refresh_disabled->hide();
    this->tip = new assemble("tip", ":/system/img/", -10, -10, 80, 80);
    this->tip->setPos(720,375);
    this->tip->setParentItem(game_canvas);
    this->tip_disabled = new assemble("tip_disabled", ":/system/img/", -10, -10, 80, 80, false);
    this->tip_disabled->setPos(720,375);
    this->tip_disabled->setParentItem(game_canvas);
    this->tip_disabled->hide();
    this->boom = new assemble("boom", ":/system/img/", -10, -10, 80, 80);
    this->boom->setPos(720,575);
    this->boom->setParentItem(game_canvas);
    this->boom->setData(1, QVariant(false)); //false代表未点击
    this->boom_disabled = new assemble("boom_disabled", ":/system/img/", -10, -10, 80, 80, false);
    this->boom_disabled->setPos(720,575);
    this->boom_disabled->setParentItem(game_canvas);
    this->boom_disabled->hide();
    this->setGameStart(false);
    connect(hand, SIGNAL(refresh(bool)), this, SLOT(shuffle(bool)));
    connect(hand, SIGNAL(findAPair()), this, SLOT(findAPairThenTips()));
    connect(hand, SIGNAL(boom(bool)), this, SLOT(boom_judge(bool)));
    connect(this->disapearTimes, SIGNAL(timeout()), this, SLOT(disapearSquares()));

    //system
    this->ptimer = new QTimer;
    this->bgm = new QSound(QCoreApplication::applicationDirPath() + "/audio/bgm.wav");
    this->setMusicOn(true);
    connect(this->ptimer, SIGNAL(timeout()), this, SLOT(gameUpdate()));
    connect(hand, SIGNAL(playSound(QString)), this, SLOT(playSound(QString)));
    connect(hand, SIGNAL(toHomepage(int)), this, SLOT(toHomepage(int)));

    initStartInterface();
}

void startInterface::setStartInterface()
{
    this->start_btn->show();
    this->search_btn->show();
    this->exit_btn->show();
    this->title->show();
}

void startInterface::initStartInterface()
{
    //homepage
    this->addItem(start_btn);
    this->addItem(search_btn);
    this->addItem(exit_btn);
    this->addItem(title);
    this->addItem(settings);
    //settings
    this->addItem(settings_canvas);
//    this->addItem(volumn_img);
//    this->addItem(ban_volumn_img);
//    this->addItem(arrow_img);
    //game over
    this->addItem(game_over_canvas);
//    this->addItem(game_over_text);
//    this->addItem(game_home1);
//    this->addItem(play_again);
    //game pass
    this->addItem(game_pass_canvas);
//    this->addItem(game_pass_text);
//    this->addItem(next_checkpoint);
//    this->addItem(game_home2);
    //play interface
    this->addItem(game_canvas);
//    this->addItem(time_text);
//    this->addItem(score_text);
//    this->addItem(refresh);
//    this->addItem(refresh_disabled);
//    this->addItem(tip);
//    this->addItem(tip_disabled);
//    this->addItem(boom);
//    this->addItem(boom_disabled);

    setStartInterface();
}

void startInterface::toHomepage(int from)
{
    this->game_canvas->hide();
    setStartInterface();
    if(from == 0)
        this->removeSettingButtons();
    else if(from == 1)
        this->game_over_canvas->hide();
    else if(from == 2)
        this->game_pass_canvas->hide();
    if(this->isGameStart())
        resetGameScene();
    this->setGameStart(false);
}

void startInterface::removeStartButtons()
{
    this->start_btn->hide();
    this->search_btn->hide();
    this->exit_btn->hide();
    this->title->hide();
}

void startInterface::setSettingInterface()
{
    this->settings_canvas->show();
    this->start_btn->setAcceptHoverEvents(false);
    this->search_btn->setAcceptHoverEvents(false);
    this->exit_btn->setAcceptHoverEvents(false);
}

void startInterface::removeSettingButtons()
{
    this->settings_canvas->hide();
    this->start_btn->setAcceptHoverEvents(true);
    this->search_btn->setAcceptHoverEvents(true);
    this->exit_btn->setAcceptHoverEvents(true);
}

void startInterface::start()
{
    this->game_canvas->show();
    if(isMusicOn())
    {
        QSound::play(QCoreApplication::applicationDirPath() + "/audio/ready_go.wav");
        this->bgm->setLoops(QSound::Infinite);
        this->bgm->play();
    }
    this->ptimer->start(1000);

    removeStartButtons();
    this->setGameStart(true);
    resetSquareArray();
    setSquares();
}

void startInterface::resetGameScene()
{
    qDebug() << "hear";
    for(int i = 0; i < 64; i++)
    {
        this->removeItem(this->square[i]);
        this->square[i] = 0;
    }
    resetSquareArray();
    this->refresh->show();
    this->refresh_disabled->hide();
    this->tip->show();
    this->tip_disabled->hide();
    this->boom->show();
    this->boom_disabled->hide();
    if(!this->isGameStart())
    {
        this->grade = 1;
        this->score = 0;
        updateScore(0);
    }
    remainOrders.clear();
}

void startInterface::playAgain()
{
    resetGameScene();
    if(isMusicOn())
        QSound::play(QCoreApplication::applicationDirPath() + "/audio/ready_go.wav");
    this->game_over_canvas->hide();
    this->ptimer->start(1000);
    this->setGameStart(true);
    setSquares();
}

void startInterface::resetSquareArray()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            this->squareArray[i][j] = 1;
        }
    }
}

void startInterface::setSquares()
{
    int square_num = 64;
    this->time = 100;
    this->time_text->setText(QString::fromLocal8Bit(("时间：100")));
    this->remain_square_num = square_num;
    QList<int> squareIndex;
    while(squareIndex.count() < square_num)
    {
        int index = rand() % 20;
        if(squareIndex.count(index) < 2 * (int(square_num / 40) + 1))
        {
            squareIndex.append(index);
            squareIndex.append(index);
        }
    }
    for(int i = 0; i < square_num; i++)
    {
        int num = squareIndex.count();
        int index = rand() % num;
        int square_index = squareIndex.at(index) + 1;
        squareIndex.removeAt(index);
        QString square_path = getPath(square_index);
        this->square[i] = new llkSqure(square_index, i);
        this->square[i]->setPos(70 + i/8*this->square[i]->boundingRect().width(),115 + i%8*this->square[i]->boundingRect().height());
        this->square[i]->setPixmap(QPixmap(square_path));
        this->square[i]->setI(i / 8);
        this->square[i]->setJ(i % 8);
        this->addItem(this->square[i]);
        this->remainOrders.append(i);
        this->square[i]->setParentItem(game_canvas);
    }
}

void startInterface::search()
{
    qDebug() << "search!!!";
}

void startInterface::exit()
{
    QApplication* app;
    app->exit(0);
}

void startInterface::judgeAndUpdate(int order)
{
    showSqaureArray();
    int order_index = this->square[order]->data(0).toInt();
    qDebug() << "judge:order->" << QString::number(order) + " i and j:" + QString::number(this->square[order]->getI()) + " " + QString::number(this->square[order]->getJ());
    if(this->isGameStart() == false) return;
    if(this->boom->data(1).toInt() == true)
    {
        boomSquares(order);
        return;
    }
    if(order1_tips != -1 && order2_tips != -1)
    {
        if(order != order1_tips && order != order2_tips)
        {
            int tip1_index = this->square[order1_tips]->data(0).toInt();
            this->square[order1_tips]->setPixmap(QPixmap(getPath(tip1_index)));
            int tip2_index = this->square[order2_tips]->data(0).toInt();
            this->square[order2_tips]->setPixmap(QPixmap(getPath(tip2_index)));
        }
    }
    if(selected_square == -1){
        selected_square = order;
        this->square[selected_square]->setPixmap(QPixmap(getPath(order_index, 1)));
    }else
    {
        if(selected_square == order)
        {
            this->square[order]->setPixmap(QPixmap(getPath(order_index)));
            this->selected_square = -1;
        }else
        {
            if(this->square[selected_square]->data(0).toInt() == this->square[order]->data(0).toInt())
            {
                if(checkIfCanBePair(selected_square, order))
                {
                    //this->removeItem(this->square[selected_square]);
                    //this->removeItem(this->square[order]);
                    int selected_index = this->square[selected_square]->data(0).toInt();
                    this->square[selected_square]->setPixmap(QPixmap(getPath(selected_index)));
                    this->route->update();
                    this->route->show();
                    this->disapearTimes->start(200);
                    int x = 0, y = 0;
                    x = this->square[selected_square]->getI();
                    y = this->square[selected_square]->getJ();
                    this->squareArray[y][x] = 0;
                    x = this->square[order]->getI();
                    y = this->square[order]->getJ();
                    this->squareArray[y][x] = 0;

                    this->remain_square_num -= 2;
                    this->remainOrders.removeOne(selected_square);
                    this->remainOrders.removeOne(order);
                    updateScore(2);
                    this->selected_square = -1;

                    if(remain_square_num == 0)
                        gameOver(true);
                    else
                    {
                        playSound(QCoreApplication::applicationDirPath() + "/audio/bePair.wav");
                        return;
                    }
                }
                else
                {
                    int selected_index = this->square[selected_square]->data(0).toInt();
                    this->square[selected_square]->setPixmap(QPixmap(getPath(selected_index)));
                    selected_square = order;
                    this->square[order]->setPixmap(QPixmap(getPath(order_index, 1)));
                }
            }
            else
            {
                int selected_index = this->square[selected_square]->data(0).toInt();
                this->square[selected_square]->setPixmap(QPixmap(getPath(selected_index)));
                this->square[order]->setPixmap(QPixmap(getPath(order_index, 1)));
                this->selected_square = order;
            }
        }
    }
    playSound(QCoreApplication::applicationDirPath() + "/audio/select_square.wav");
}

void startInterface::shuffle(bool used)
{
    qDebug() << "shuffle...";
    if(this->isGameStart() == false) return;
    if(order1_tips != -1 && order2_tips != -1)
    {
        int tip1_index = this->square[order1_tips]->data(0).toInt();
        this->square[order1_tips]->setPixmap(QPixmap(getPath(tip1_index)));
        int tip2_index = this->square[order2_tips]->data(0).toInt();
        this->square[order2_tips]->setPixmap(QPixmap(getPath(tip2_index)));
    }
    if(used)
    {
        this->refresh->hide();
        this->refresh_disabled->show();
    }
    QList<int> orders = remainOrders;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(this->squareArray[j][i] == 1)
            {
                //qDebug() << "i:" + QString::number(i) + " j:" + QString::number(j);
                int num = orders.count();
                int order_index = rand() % num;
                int index = orders.at(order_index);
                orders.removeAt(order_index);
                //qDebug() << "order_index:" + QString::number(order_index) + " index:" + QString::number(index) + " remain_num:" + QString::number(orders.count());
                this->square[index]->setPos(70 + i*this->square[index]->boundingRect().width(),115 + j*this->square[index]->boundingRect().height());
                this->square[index]->setI(i);
                this->square[index]->setJ(j);
            }
        }
    }
}

int startInterface::findOrderByIJ(int i, int j)
{
    int order = -1;
    for(int o : remainOrders)
    {
        if(this->square[o]->getI() == i && this->square[o]->getJ() == j)
        {
            order = o;
            break;
        }
    }
    if(order == -1)
        qDebug() << "find error";
    return order;
}

void startInterface::gameUpdate()
{
    if(this->time == 0)
    {
        gameOver(false);
        return;
    }
    this->time--;
    QString t = QString("%1").arg(this->time, 2, 10, QChar('0'));
    this->time_text->setText(QString::fromLocal8Bit("时间：") + t);
    this->game_canvas->update();
    this->time_text->update();
}

void startInterface::findAPairThenTips()
{
    if(this->isGameStart() == false) return;
    this->tip->hide();
    this->tip_disabled->show();
    int order1 = -1, order2 = -1;
    findAPair(order1, order2);
    if(order1 == -1 || order2 == -1) return;
    this->order1_tips = order1;
    this->order2_tips = order2;
    int order1_index = this->square[order1_tips]->data(0).toInt();
    int order2_index = this->square[order2_tips]->data(0).toInt();
    this->square[order1_tips]->setPixmap(QPixmap(getPath(order1_index, 2)));
    this->square[order2_tips]->setPixmap(QPixmap(getPath(order2_index, 2)));
}

void startInterface::findAPair(int& order1, int& order2)
{
    for(int o1 : remainOrders)
    {
        for(int o2 : remainOrders)
        {
            if(o1 != o2)
            {
                if(this->square[o1]->data(0).toInt() == this->square[o2]->data(0).toInt() && checkIfCanBePair(o1, o2))
                {
                    order1 = o1;
                    order2 = o2;
                    return ;
                }
            }
        }
    }
}

void startInterface::findIfThereIsAPair()
{
    int o1 = -1;
    int o2 = -1;
    findAPair(o1, o2);
    if(o1 == -1 || o2 == -1)
    {
        shuffle(false);
    }
}

void startInterface::gameOver(bool success)
{
    this->ptimer->stop();
    if(success) {
        qDebug() << "success";
        playSound(QCoreApplication::applicationDirPath() + "/audio/success.wav");
        updateScore(this->time / 2);
        this->game_pass_canvas->show();
        //this->setGameStart(false);
    }

    else
    {
        qDebug() << "failed";
        playSound(QCoreApplication::applicationDirPath() + "/audio/failed.wav");
        this->game_over_canvas->show();
        this->setGameStart(false);
    }
}

void startInterface::updateScore(int score)
{
    this->score += score;
    this->score_text->setText(QString::fromLocal8Bit("得分：") + QString::number(this->score));
    this->game_canvas->update();
    this->score_text->update();
}

QString startInterface::getPath(int index, int type)
{
    QString m;
    if(type == 0) m = "init";
    if(type == 1) m = "selected";
    if(type == 2) m = "tips";
    QString path = ":/square/pokemon/" + m + "/img/pokemon/" + m + "/" + QString::number(index) + ".png";
    return path;
}

void startInterface::showSqaureArray()
{
    for(int i = 0; i < 8; i++)
    {
        QString l = "";
        for(int j = 0; j < 8; j++)
        {
            l += QString::number(this->squareArray[i][j]) + " ";
        }
        qDebug() << l;
    }
    qDebug() << "";
}

bool startInterface::checkIfCanBePair(int order1, int order2)
{
    int real_x1, real_y1, real_x2, real_y2;
    int item_hight = this->square[0]->boundingRect().height();
    int item_width = this->square[0]->boundingRect().width();
    real_x1 = this->square[order1]->pos().x() + item_width / 2;
    real_y1 = this->square[order1]->pos().y() + item_hight / 2;
    real_x2 = this->square[order2]->pos().x() + item_width / 2;
    real_y2 = this->square[order2]->pos().y() + item_hight / 2;
    int x1, x2, y1, y2;
    x1 = this->square[order1]->getI();
    y1 = this->square[order1]->getJ();
    x2 = this->square[order2]->getI();
    y2 = this->square[order2]->getJ();
    qDebug() << "x1:" + QString::number(x1);
    qDebug() << "y1:" + QString::number(y1);
    qDebug() << "x2:" + QString::number(x2);
    qDebug() << "y2:" + QString::number(y2);
    bool can_be_pair = false;
    QList<int> order1_l;
    QList<int> order2_l;
    int left_x, right_x;
    if(x1 < x2) {left_x = x1; right_x = x2;}
    else {left_x = x2; right_x = x1;}
    for(int i = y1; i < 8; i++)
    {
        if(i == y1 || this->squareArray[i][x1] == 0)
            order1_l.append(i);
        else
            break;
    }
    for(int i = y1 - 1; i >=0; i--)
    {
        if(this->squareArray[i][x1] == 0)
            order1_l.append(i);
        else
            break;
    }
    for(int j = y2; j < 8; j++)
    {
        if(j == y2 || this->squareArray[j][x2] == 0)
            order2_l.append(j);
        else
            break;
    }
    for(int j = y2 - 1; j >= 0; j--)
    {
        if(this->squareArray[j][x2] == 0)
            order2_l.append(j);
        else
            break;
    }
    for(int l : order1_l)
    {
        if(order2_l.contains(l))
        {
            bool can = true;
            for(int k = left_x + 1; k < right_x; k++)
            {
                if(this->squareArray[l][k] == 1)
                {
                    can = false;
                    break;
                }
            }
            if(can || (l == 0 || l == 7))
            {
                int num = 0;
                if(l == y1) num = real_y1;
                if(l == y2) num = real_y2;
                if(num == 0)
                    num = y1 < y2 ? real_y1 + ((l - y1) * item_hight) : real_y2 + ((l - y2) * (this->square[0]->boundingRect().height() + 3));
                int overstep;
                if(can) overstep = 0;
                else overstep = l == 0 ? -50 : 50;
                this->route->setOrder(real_x1, real_y1, real_x2, real_y2, order1, order2, 0, num, l==y1 && can, l==y2 && can, overstep);
                can_be_pair = true;
                break;
            }
        }
    }
    if(!can_be_pair)
    {
        QList<int> order1_h;
        QList<int> order2_h;
        int high_y, low_y;
        if(y1 < y2) {high_y = y1; low_y = y2;}
        else {high_y = y2; low_y = y1;}
        for(int i = x1; i < 8; i++)
        {
            if(i == x1 || this->squareArray[y1][i] == 0)
                order1_h.append(i);
            else
                break;
        }
        for(int i = x1 - 1; i >= 0; i--)
        {
            if(this->squareArray[y1][i] == 0)
                order1_h.append(i);
            else
                break;
        }
        for(int j = x2; j < 8; j++)
        {
            if(j == x2 || this->squareArray[y2][j] == 0)
                order2_h.append(j);
            else
                break;
        }
        for(int j = x2 - 1; j >= 0; j--)
        {
            if(this->squareArray[y2][j] == 0)
                order2_h.append(j);
            else
                break;
        }
        for(int h : order1_h)
        {
            if(order2_h.contains(h))
            {
                bool can = true;
                for(int k = high_y + 1; k < low_y; k++)
                {
                    if(this->squareArray[k][h] == 1)
                    {
                        can = false;
                        break;
                    }
                }
                if(can || (h == 0 || h == 7))
                {
                    int num = 0;
                    if(h == x1) num = real_x1;
                    if(h == x2) num = real_x2;
                    if(num == 0)
                        num = x1 < x2 ? real_x1 + ((h - x1) * item_width) : real_x2 + ((h - x2) * (this->square[0]->boundingRect().width() + 3));
                    int overstep;
                    if(can) overstep = 0;
                    else overstep = h == 0 ? -50 : 50;
                    this->route->setOrder(real_x1, real_y1, real_x2, real_y2, order1, order2, 1, num, h==x1 && can, h==x2 && can, overstep);
                    can_be_pair = true;
                    break;
                }
            }
        }
    }
    return can_be_pair;
}

void startInterface::boomSquares(int order)
{
    int target = -1;
    for(int o : remainOrders)
    {
        if(order == o) continue;
        if(this->square[order]->data(0).toInt() == this->square[o]->data(0).toInt())
        {
            target = o;
            break;
        }
    }
    if(target == -1)
        qDebug() << "error";
    else
    {
        int x = 0, y = 0;
        x = this->square[order]->getI();
        y = this->square[order]->getJ();
        this->squareArray[y][x] = 0;
        x = this->square[target]->getI();
        y = this->square[target]->getJ();
        this->squareArray[y][x] = 0;

        this->remain_square_num -= 2;
        this->remainOrders.removeOne(order);
        this->remainOrders.removeOne(target);
        this->square[order]->hide();
        this->square[target]->hide();
        updateScore(2);

        this->boom->setData(1, QVariant(false));
        this->boom->hide();
        this->boom_disabled->show();

        playSound(QCoreApplication::applicationDirPath() + "/audio/boom.wav");
        if(remain_square_num == 0)
            gameOver(true);
    }
}

void startInterface::boom_judge(bool ready)
{
    if(this->isGameStart() == false) return;
    if(selected_square != -1)
    {
        int selected_index = this->square[selected_square]->data(0).toInt();
        this->square[selected_square]->setPixmap(QPixmap(getPath(selected_index)));
        selected_square = -1;
    }
    if(ready)
    {
        this->boom->setAcceptHoverEvents(false);
        this->boom->setPixmap(QPixmap(":/system/img/boom_hover.png"));
        this->boom->setData(1, QVariant(true));
    }
    else
    {
        this->boom->setAcceptHoverEvents(true);
        this->boom->setPixmap(QPixmap(":/system/img/boom.png"));
        this->boom->setData(1, QVariant(false));
    }
}

void startInterface::modifyVolumn(bool on)
{
    setMusicOn(on);
    if(on)
    {
        this->ban_volumn_img->hide();
        this->volumn_img->show();
        this->bgm->setLoops(QSound::Infinite);
        this->bgm->play();
    }else
    {
        this->volumn_img->hide();
        this->ban_volumn_img->show();
        this->bgm->stop();
    }
}

void startInterface::toNextCheckpoint()
{
    this->grade ++;
    resetGameScene();
    if(isMusicOn())
        QSound::play(QCoreApplication::applicationDirPath() + "/audio/ready_go.wav");
    this->game_pass_canvas->hide();
    QString g = QString("%1").arg(this->grade, 2, 10, QChar('0'));
    this->grade_text->setText(QString::fromLocal8Bit(("关卡：")) + g);
    this->ptimer->start(1000);
    setSquares();
}

void startInterface::playSound(QString sound)
{
    if(isMusicOn()) QSound::play(sound);
}

void startInterface::setMusicOn(bool on)
{
    this->music_on = on;
}

bool startInterface::isMusicOn()
{
    return this->music_on;
}

void startInterface::setGameStart(bool start)
{
    this->game_start = start;
}

bool startInterface::isGameStart()
{
    return this->game_start;
}

void startInterface::setGrade(int grade)
{
    this->grade = grade;
}

int startInterface::getGrade()
{
    return this->grade;
}

void startInterface::disapearSquares()
{
    this->route->hide();
    int order1 = this->route->order1;
    int order2 = this->route->order2;
    this->square[order1]->hide();
    this->square[order2]->hide();
    this->disapearTimes->stop();
    int difficult_grade = this->grade % 6;
    switch (difficult_grade)
    {
        case 1:
            break;
        case 2:
        {
            //down
            if(this->square[order1]->getI() == this->square[order2]->getI()
                    && this->square[order1]->getJ() > this->square[order2]->getJ())
            {
                int temp = order1;
                order1 = order2;
                order2 = temp;
            }
            int _i = this->square[order1]->getI();
            int _j = this->square[order1]->getJ();
            for(int k = _j - 1; k >= 0 ; k--)
            {
                if(this->squareArray[k][_i] == 1)
                {
                    int o = findOrderByIJ(_i, k);
                    this->square[o]->setPos(70 + _i*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                    this->squareArray[k][_i] = 0;
                    this->squareArray[k+1][_i] = 1;
                    this->square[o]->setJ(k+1);
                }
                else if(this->squareArray[k][_i] == 0) break;
            }
            _i = this->square[order2]->getI();
            _j = this->square[order2]->getJ();
            for(int k = _j - 1; k >= 0 ; k--)
            {
                if(this->squareArray[k][_i] == 1)
                {
                    int o = findOrderByIJ(_i, k);
                    this->square[o]->setPos(70 + _i*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                    this->squareArray[k][_i] = 0;
                    this->squareArray[k+1][_i] = 1;
                    this->square[o]->setJ(k+1);
                }
                else if(this->squareArray[k][_i] == 0) break;
            }
            break;
        }
        case 3:
        {
            //left
            if(this->square[order1]->getJ() == this->square[order2]->getJ()
                    && this->square[order1]->getI() < this->square[order2]->getI())
            {
                int temp = order1;
                order1 = order2;
                order2 = temp;
            }
            int _i = this->square[order1]->getI();
            int _j = this->square[order1]->getJ();
            for(int k = _i + 1; k <= 7 ; k++)
            {
                if(this->squareArray[_j][k] == 1)
                {
                    int o = findOrderByIJ(k, _j);
                    this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                    this->squareArray[_j][k] = 0;
                    this->squareArray[_j][k-1] = 1;
                    this->square[o]->setI(k-1);
                }
                else if(this->squareArray[_j][k] == 0) break;
            }
            _i = this->square[order2]->getI();
            _j = this->square[order2]->getJ();
            for(int k = _i + 1; k <= 7 ; k++)
            {
                if(this->squareArray[_j][k] == 1)
                {
                    int o = findOrderByIJ(k, _j);
                    this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                    this->squareArray[_j][k] = 0;
                    this->squareArray[_j][k-1] = 1;
                    this->square[o]->setI(k-1);
                }
                else if(this->squareArray[_j][k] == 0) break;
            }
            break;
        }
        case 4:
        {
            //horizontal middel
            if(this->square[order1]->getI() == this->square[order2]->getI()
                    && ((this->square[order1]->getJ() > this->square[order2]->getJ() && this->square[order1]->getJ() <= 3)
                    || (this->square[order1]->getJ() < this->square[order2]->getJ() && this->square[order1]->getJ() >= 4)))
            {
                int temp = order1;
                order1 = order2;
                order2 = temp;
            }
            int _i = this->square[order1]->getI();
            int _j = this->square[order1]->getJ();
            if(_j <= 3)
            {
                //down
                for(int k = _j - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[k][_i] == 1)
                    {
                        int o = findOrderByIJ(_i, k);
                        this->square[o]->setPos(70 + _i*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                        this->squareArray[k][_i] = 0;
                        this->squareArray[k+1][_i] = 1;
                        this->square[o]->setJ(k+1);
                    }
                    else if(this->squareArray[k][_i] == 0) break;
                }
            }
            else
            {
                //up
                for(int k = _j + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[k][_i] == 1)
                    {
                        int o = findOrderByIJ(_i, k);
                        this->square[o]->setPos(70 + _i*this->square[o]->boundingRect().width(),115 + (k-1)*this->square[o]->boundingRect().height());
                        this->squareArray[k][_i] = 0;
                        this->squareArray[k-1][_i] = 1;
                        this->square[o]->setJ(k-1);
                    }
                    else if(this->squareArray[k][_i] == 0) break;
                }
            }
            _i = this->square[order2]->getI();
            _j = this->square[order2]->getJ();
            if(_j <= 3)
            {
                //down
                for(int k = _j - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[k][_i] == 1)
                    {
                        int o = findOrderByIJ(_i, k);
                        this->square[o]->setPos(70 + _i*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                        this->squareArray[k][_i] = 0;
                        this->squareArray[k+1][_i] = 1;
                        this->square[o]->setJ(k+1);
                    }
                    else if(this->squareArray[k][_i] == 0) break;
                }
            }
            else
            {
                //up
                for(int k = _j + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[k][_i] == 1)
                    {
                        int o = findOrderByIJ(_i, k);
                        this->square[o]->setPos(70 + _i*this->square[o]->boundingRect().width(),115 + (k-1)*this->square[o]->boundingRect().height());
                        this->squareArray[k][_i] = 0;
                        this->squareArray[k-1][_i] = 1;
                        this->square[o]->setJ(k-1);
                    }
                    else if(this->squareArray[k][_i] == 0) break;
                }
            }
            break;
        }
        case 5:
        {
            //vertical middel
            if(this->square[order1]->getJ() == this->square[order2]->getJ()
                    && ((this->square[order1]->getI() > this->square[order2]->getI() && this->square[order1]->getI() <= 3)
                    || (this->square[order1]->getI() < this->square[order2]->getI() && this->square[order1]->getI() >= 4)))
            {
                int temp = order1;
                order1 = order2;
                order2 = temp;
            }
            int _i = this->square[order1]->getI();
            int _j = this->square[order1]->getJ();
            if(_i <= 3)
            {
                //right
                for(int k = _i - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k+1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k+1] = 1;
                        this->square[o]->setI(k+1);
                    }
                    else if(this->squareArray[_j][k] == 0) break;
                }
            }
            else
            {
                //left
                for(int k = _i + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k-1] = 1;
                        this->square[o]->setI(k-1);
                    }
                    else if(this->squareArray[_j][k] == 0) break;
                }
            }
            _i = this->square[order2]->getI();
            _j = this->square[order2]->getJ();
            if(_i <= 3)
            {
                //right
                for(int k = _i - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k+1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k+1] = 1;
                        this->square[o]->setI(k+1);
                    }
                    else if(this->squareArray[_j][k] == 0) break;
                }
            }
            else
            {
                //left
                for(int k = _i + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k-1] = 1;
                        this->square[o]->setI(k-1);
                    }
                    else if(this->squareArray[_j][k] == 0) break;
                }
            }
            break;
        }
        case 0:
        {
            //middel
qDebug() << "aaa";
            bool h_judge = this->square[order1]->getJ() == this->square[order2]->getJ()
                    && ((this->square[order1]->getI() > this->square[order2]->getI() && this->square[order1]->getI() <= 3)
                    || (this->square[order1]->getI() < this->square[order2]->getI() && this->square[order1]->getI() >= 4));
            bool v_judge = this->square[order1]->getI() == this->square[order2]->getI()
                    && ((this->square[order1]->getJ() > this->square[order2]->getJ() && this->square[order1]->getJ() <= 3)
                    || (this->square[order1]->getJ() < this->square[order2]->getJ() && this->square[order1]->getJ() >= 4));
            if(h_judge || v_judge)
            {
                int temp = order1;
                order1 = order2;
                order2 = temp;
            }
qDebug() << "bbb";
            int _i = this->square[order1]->getI();
            int _j = this->square[order1]->getJ();
            if(_i <= 3 && _j <= 3)
            {
                //right
                int l = -1;
                for(int k = _i - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k+1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k+1] = 1;
                        this->square[o]->setI(k+1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k + 1;
                        break;
                    };
                }
                if(l == -1 && this->squareArray[_j][0] == 0) l = 0;
                //down
                if(l != -1)
                {
                    for(int m = l; m >= 0; m--)
                    {
                        for(int k = _j - 1; k >= 0 ; k--)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k+1][m] = 1;
                                this->square[o]->setJ(k+1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            else if(_i >= 4 && _j <= 3)
            {
                //left
                int l = -1;
                for(int k = _i + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k-1] = 1;
                        this->square[o]->setI(k-1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k - 1;
                        break;
                    };
                }
                if(l == -1 && this->squareArray[_j][7] == 0) l = 7;
                if(l != -1)
                {
                    //down
                    for(int m = l; m <= 7; m++)
                    {
                        for(int k = _j - 1; k >= 0 ; k++)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k+1][m] = 1;
                                this->square[o]->setJ(k+1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            else if(_i <= 3 && _j >= 4)
            {
                //right
                int l = -1;
                for(int k = _i - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k+1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k+1] = 1;
                        this->square[o]->setI(k+1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k + 1;
                        break;
                    };
                }
                if(l == -1 && this->squareArray[_j][0] == 0) l = 0;
                if(l != -1)
                {
                    //up
                    for(int m = l; m >= 0; m--)
                    {
                        for(int k = _j + 1; k <= 7 ; k++)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k-1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k-1][m] = 1;
                                this->square[o]->setJ(k-1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            else if(_i >= 4 && _j >= 4)
            {
                //left
                int l = -1;
                for(int k = _i + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k-1] = 1;
                        this->square[o]->setI(k-1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k - 1;
                        break;
                    }
                }
                if(l == -1 && this->squareArray[_j][7] == 0) l = 7;
                if(l != -1)
                {
                    //up
                    for(int m = l; m <= 7; m++)
                    {
                        for(int k = _j + 1; k <= 7 ; k++)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k-1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k-1][m] = 1;
                                this->square[o]->setJ(k-1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
qDebug() << "ccc";
            _i = this->square[order2]->getI();
            _j = this->square[order2]->getJ();
            if(_i <= 3 && _j <= 3)
            {
                //right
                int l = -1;
                for(int k = _i - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k+1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k+1] = 1;
                        this->square[o]->setI(k+1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k + 1;
                        break;
                    };
                }
                if(l == -1 && this->squareArray[_j][0] == 0) l = 0;
                //down
                if(l != -1)
                {
                    for(int m = l; m >= 0; m--)
                    {
                        for(int k = _j - 1; k >= 0 ; k--)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k+1][m] = 1;
                                this->square[o]->setJ(k+1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            else if(_i >= 4 && _j <= 3)
            {
                //left
                int l = -1;
                for(int k = _i + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k-1] = 1;
                        this->square[o]->setI(k-1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k - 1;
                        break;
                    };
                }
                if(l == -1 && this->squareArray[_j][7] == 0) l = 7;
                if(l != -1)
                {
                    //down
                    for(int m = l; m <= 7; m++)
                    {
                        for(int k = _j - 1; k >= 0 ; k++)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k+1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k+1][m] = 1;
                                this->square[o]->setJ(k+1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            else if(_i <= 3 && _j >= 4)
            {
                //right
                int l = -1;
                for(int k = _i - 1; k >= 0 ; k--)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k+1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k+1] = 1;
                        this->square[o]->setI(k+1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k + 1;
                        break;
                    };
                }
                if(l == -1 && this->squareArray[_j][0] == 0) l = 0;
                if(l != -1)
                {
                    //up
                    for(int m = l; m >= 0; m--)
                    {
                        for(int k = _j + 1; k <= 7 ; k++)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k-1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k-1][m] = 1;
                                this->square[o]->setJ(k-1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            else if(_i >= 4 && _j >= 4)
            {
                //left
                int l = -1;
                for(int k = _i + 1; k <= 7 ; k++)
                {
                    if(this->squareArray[_j][k] == 1)
                    {
                        int o = findOrderByIJ(k, _j);
                        this->square[o]->setPos(70 + (k-1)*this->square[o]->boundingRect().width(),115 + _j*this->square[o]->boundingRect().height());
                        this->squareArray[_j][k] = 0;
                        this->squareArray[_j][k-1] = 1;
                        this->square[o]->setI(k-1);
                    }
                    else if(this->squareArray[_j][k] == 0)
                    {
                        l = k - 1;
                        break;
                    }
                }
                if(l == -1 && this->squareArray[_j][7] == 0) l = 7;
                if(l != -1)
                {
                    //up
                    for(int m = l; m <= 7; m++)
                    {
                        for(int k = _j + 1; k <= 7 ; k++)
                        {
                            if(this->squareArray[k][m] == 1)
                            {
                                int o = findOrderByIJ(m, k);
                                this->square[o]->setPos(70 + m*this->square[o]->boundingRect().width(),115 + (k-1)*this->square[o]->boundingRect().height());
                                this->squareArray[k][m] = 0;
                                this->squareArray[k-1][m] = 1;
                                this->square[o]->setJ(k-1);
                            }
                            else if(this->squareArray[k][m] == 0) break;
                        }
                    }
                }
            }
            break;
        }
    }
    findIfThereIsAPair();
}
