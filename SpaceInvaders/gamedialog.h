#pragma once

#include "config.h"
#include "menu.h"
#include "ship.h"
#include "swarm.h"
#include "swarminfo.h"
#include <QDialog>
#include <QSoundEffect>
#include <QWidget>
#include <vector>

namespace game {
class GameDialog : public QDialog {
    Q_OBJECT

public:
    GameDialog(QWidget* parent = nullptr);
    void generateAliens(const QList<SwarmInfo>& swarms);
    virtual ~GameDialog();

protected:
    QTimer* timer;
    void paintEvent(QPaintEvent* event);
    void paintBullets(QPainter& painter);
    void updateBullets();
    void paintSwarm(QPainter& painter, AlienBase*& root);
    void checkSwarmCollisions(AlienBase*& root);

    // ship and swarms
    Ship* ship;
    std::vector<Bullet*> bullets;
    AlienBase* swarms;  // swarms is the ROOT node of the composite
    QSoundEffect shipFiringSound;
    int next_instruct;

    // Key controls
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    int level;

    // Mouse control
    void mouseMoveEvent(QMouseEvent *event);
    bool mouseControl;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // about the canvas
    int frames;
    const int WIDTH = 800;
    const int HEIGHT = 600;
    int SCALEDWIDTH;
    int SCALEDHEIGHT;

    // collision...
    int get_collided_swarm(Bullet*& b, AlienBase*& root);
    int get_collided(Bullet*& b, AlienBase*& root);
    void addBullets(const QList<Bullet*>& list);

    // pausing & menu
    bool manualControl;
    bool paused;

    void setSpeed(QString speed);

    void pressControls();
    void pressLevels();

    Menu* menu;
    Config* c;

    // score
    int gameScore;  // this run's score.
    bool updateHighScores;
    QList<int> highScores;
    QList<QString> highScoringPlayers;
public slots:
    void nextFrame();
    // menus
    void showScore();
    void toggleShowSpeed();
    void pressSlow();
    void pressNormal();
    void pressFast();
    void pressChaos();
    void pauseStart();
    void paintMenu();
};
}
