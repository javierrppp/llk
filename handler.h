#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class handler : public QObject
{
    Q_OBJECT
public:
    static handler *getInstance();
    void tellStart();
    void tellExit();
    void tellShowHistory();
    void tellSettings();
    void tellReset();
    void tellModifyVolumn(bool on);
    void tellPlaySound(QString path);
    void tellRefresh(bool used=true);
    void tellToFind();
    void tellToBoom(int order);
    void boom_be_clicked(bool ready);
    void tellToHomepage(int from);
    void tellToPlayAgain();
    void tellToNextCheckpoint();

    //game
    void tellTheSelectOrder(int order);

private:
    explicit handler(QObject *parent = nullptr);
    static handler *hand;

signals:
    void startGame();
    void exitGame();
    void showHistory();
    void showSettingsInterface();
    void resetInterface();
    void modifyVolumn(bool on);
    void playSound(QString path);
    void refresh(bool used);
    void findAPair();
    void boom(bool ready);
    void toHomepage(int from);
    void playAgain();
    void toNextCheckpoint();

    //game
    void selectOrder(int order);

public slots:
};

#endif // HANDLER_H
