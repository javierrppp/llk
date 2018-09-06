#ifndef STARTINTERFACE_H
#define STARTINTERFACE_H
#include <QGraphicsScene>
#include <QObject>
#include <llkbutton.h>
#include <QTimer>
#include <QList>
#include <QSound>
#include "llksqure.h"


class startInterface : public QGraphicsScene
{
    Q_OBJECT
public:
    startInterface();
    void removeStartButtons();
    void showSqaureArray();
    bool checkIfCanBePair(int order1, int order2);
    void resetSquareArray();
    int squareArray[8][8];
    QString getPath(int index, int type=0);
    void gameOver(bool success);
    void updateScore(int score);
    void findAPair(int& order1, int& order2);
    void findIfThereIsAPair();
    void resetGameScene();
    int findOrderByIJ(int i, int j);
private slots:
    void start();
    void exit();
    void search();
    void toHomepage(int from);
    void playAgain();
    void setSettingInterface();
    void setStartInterface();
    void initStartInterface();
    void removeSettingButtons();
    void gameUpdate();
    void setSquares();
    void judgeAndUpdate(int order);
    void disapearSquares();
    void shuffle(bool used);
    void playSound(QString sound);
    void modifyVolumn(bool on);
    void findAPairThenTips();
    void boomSquares(int order);
    void boom_judge(bool ready);
    void toNextCheckpoint();
    bool isMusicOn();
    void setMusicOn(bool on);
    bool isGameStart();
    void setGameStart(bool start);
    int getGrade();
    void setGrade(int grade);
private:
    llkButton* start_btn;
    llkButton* search_btn;
    llkButton* exit_btn;
    QGraphicsPixmapItem* title;
    assemble* arrow_img;
    assemble* volumn_img;
    assemble* ban_volumn_img;
    assemble* settings;
    assemble* home;
    assemble* refresh;
    assemble* refresh_disabled;
    assemble* tip;
    assemble* tip_disabled;
    assemble* boom;
    assemble* boom_disabled;
    assemble* play_again;
    assemble* next_checkpoint;
    assemble* game_home1;
    assemble* game_home2;
    llkcanvas* opache_canvas;
    llkcanvas* settings_canvas;
    llkcanvas* game_canvas;
    llkcanvas* game_over_canvas;
    llkcanvas* game_pass_canvas;
    QTimer* ptimer;
    QTimer* disapearTimes;
    QSound* bgm;
    llkSqure* square[80];
    llkRoute* route;
    llkText* time_text;
    llkText* score_text;
    llkText* grade_text;
    llkText* game_over_text;
    llkText* game_pass_text;
    int time;
    int score;
    int remain_square_num;
    QList<int> remainOrders;
    bool music_on;
    bool game_start;

    int selected_square;
    int order1_tips;
    int order2_tips;
    int grade;
};

#endif // STARTINTERFACE_H
