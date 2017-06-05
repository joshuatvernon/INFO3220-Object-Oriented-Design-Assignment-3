#include "gamedialog.h"
#include "bullet.h"
#include "ship.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QSound>
#include <QTimer>
#include <QWidget>
#include <vector>
#include <QInputDialog>
#include <iostream>
#include <string.h>

namespace game {

GameDialog::GameDialog(QWidget* parent)
        : QDialog(parent), bullets(), shipFiringSound(this), gameScore(0) {
    // SET UP GAME DIMENSIONS AND CONFIG

    setMouseTracking(true);
    mouseControl = false;
    arrowManual = true;

    c = Config::getInstance();
    SCALEDWIDTH = c->get_SCALEDWIDTH();
    SCALEDHEIGHT = c->get_SCALEDHEIGHT();
    this->frames = c->get_frames();
    updateHighScores = true;
    highScores = c->getHighScores();
    highScoringPlayers = c->getHighScoringPlayers();

    // MENU
    menu = new Menu(this, this->gameScore, highScores, highScoringPlayers, this->arrowManual);

    // EXTENSION STAGE 1 PART 1 - RESCALE GAME SCREEN FOR SHIP SIZE
    this->setFixedWidth(SCALEDWIDTH);
    this->setFixedHeight(SCALEDHEIGHT);
    // SHIP
    QPixmap ship;
    ship.load(":/Images/ship.png");
    this->ship = new Ship(ship, c->get_scale(), c->get_startpos(), SCALEDHEIGHT);
    this->next_instruct = 0;
    // SHIP SOUND
    shipFiringSound.setSource(QUrl::fromLocalFile(":/Sounds/shoot.wav"));
    shipFiringSound.setVolume(0.3f);

    // LEVEL
    level = 0;
    lastLevel = false;

    // Hyper support
    hyperFuel = 0;

    // Frozen state support
    frozenCountdown = 0;

    // ALIENS
    generateAliens(c->getSwarmList(level));

    // SET BACKGROUND
    setStyleSheet("background-color: #000000;");

    // MENU
    paused = false;

    bool setNewName;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("User Name:"), QLineEdit::Normal, c->get_name(), &setNewName);
    if (setNewName) {
        c->set_name(text);
    }
    c->set_name(c->get_name().toUpper() + " (me)");
    menu->setName(c->get_name());

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(this->frames);

    update();
}

GameDialog::~GameDialog() {
    delete ship;
    delete timer;  // optional, don't have to do this apparently

    // loop though swarms to delete aliens
    delete swarms;  // recursively deletes itself.
    for (Bullet* b : bullets) {
        delete b;
    }
}

// make the swarms for this level.
void GameDialog::generateAliens(const QList<SwarmInfo>& makeSwarms) {
    SwarmInfo def = SwarmInfo();

    swarms = new Swarm(def, *this->ship);
    for (SwarmInfo info : makeSwarms) {
        AlienBase* s = new Swarm(info, *this->ship);
        swarms->add(s);
    }
}

void GameDialog::pauseStart() {
    if (this->paused) {
        // start game
        this->paused = false;
        this->menu->displayMenu(paused);
        this->timer->start(frames);
    } else {
        this->paused = true;
        this->menu->displayMenu(paused);
        this->timer->stop();
    }
}

void GameDialog::setSpeed(QString speed) {
    if (QString::compare(speed, "slow", Qt::CaseInsensitive) == 0) {
        this->frames = 60;
    } else if (QString::compare(speed, "normal", Qt::CaseInsensitive) == 0) {
        this->frames = 40;
    } else if (QString::compare(speed, "fast", Qt::CaseInsensitive) == 0) {
        this->frames = 20;
    } else if (QString::compare(speed, "chaos", Qt::CaseInsensitive) == 0) {
        this->frames = 10;
    }
}

void GameDialog::keyPressEvent(QKeyEvent* event) {
    if (!manualControl) {
        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down || event->key() == Qt::Key_Space) {
            // A control key has been pressed turn on manual control
            manualControl = true;
            arrowManual = true;
            mouseControl = false;
        }
    }

    if (event->key() == Qt::Key_Escape) {
        pauseStart();
    }

    if (arrowManual) {
        // Use arrow keys for movement
        if (event->key() == Qt::Key_Left) {
            c->addManualInstruction("Left");
        } else if (event->key() == Qt::Key_Right) {
            c->addManualInstruction("Right");
        } else if (event->key() == Qt::Key_Up) {
            c->addManualInstruction("Up");
        } else if (event->key() == Qt::Key_Down) {
            c->addManualInstruction("Down");
        }
    } else {
        // use WASD keys for movement
        if (event->key() == Qt::Key_A) {
            c->addManualInstruction("Left");
        } else if (event->key() == Qt::Key_D) {
            c->addManualInstruction("Right");
        } else if (event->key() == Qt::Key_W) {
            c->addManualInstruction("Up");
        } else if (event->key() == Qt::Key_S) {
            c->addManualInstruction("Down");
        }
    }

    if (event->key() == Qt::Key_Space) {
        c->addManualInstruction("Shoot");
    }

}

void GameDialog::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        c->removeManualInstruction("Shoot");
    }

    // If shift key pressed and hyper fuel available, change to hyper state
    if (event->key() == Qt::Key_Shift && ship->getCurrentState() == "Normal" && this->hyperFuel >= 100) {
        ship->setState((ShipState*) ship->getHyperState());
    }

    if (arrowManual) {
        // Use arrow keys for movement
        if (event->key() == Qt::Key_Left) {
            c->removeManualInstruction("Left");
        } else if (event->key() == Qt::Key_Right) {
            c->removeManualInstruction("Right");
        } else if (event->key() == Qt::Key_Up) {
            c->removeManualInstruction("Up");
        } else if (event->key() == Qt::Key_Down) {
            c->removeManualInstruction("Down");
        }
    } else {
        // use WASD keys for movement
        if (event->key() == Qt::Key_A) {
            c->removeManualInstruction("Left");
        } else if (event->key() == Qt::Key_D) {
            c->removeManualInstruction("Right");
        } else if (event->key() == Qt::Key_W) {
            c->removeManualInstruction("Up");
        } else if (event->key() == Qt::Key_S) {
            c->removeManualInstruction("Down");
        }
    }
}

void GameDialog::mouseMoveEvent(QMouseEvent *event) {
    if (!paused) {
        if (!mouseControl) {
            manualControl = false;
            mouseControl = true;
        } else {
            if (frozenCountdown <= 0) {
                QPoint pos = event->pos();
                ship->set_x(pos.x());
                if (pos.y() > 350) {
                    ship->set_y(pos.y());
                }
            }
        }
    }
}

void GameDialog::mousePressEvent(QMouseEvent *event) {
    c->addManualInstruction("Shoot");
}

void GameDialog::mouseReleaseEvent(QMouseEvent *event) {
    c->removeManualInstruction("Shoot");
}

// shows this game score
void GameDialog::showScore() {
    // in future, implement 'score list' in menu.
    menu->openScore();
}

void GameDialog::toggleShowSpeed() {
    menu->toggleDisplaySpeeds();
}

void GameDialog::pressSlow() {
    menu->toggleDisplaySpeeds();
    setSpeed("slow");
}

void GameDialog::pressNormal() {
    menu->toggleDisplaySpeeds();
    setSpeed("normal");
}

void GameDialog::pressFast() {
    menu->toggleDisplaySpeeds();
    setSpeed("fast");
}

void GameDialog::pressChaos() {
    menu->toggleDisplaySpeeds();
    setSpeed("chaos");
}

void GameDialog::pressControls() {
    menu->toggleDisplayControls();
}

void GameDialog::setArrowControls() {
    arrowManual = true;
    manualControl = true;
    menu->updateControlKeyColour();
    c->removeManualInstruction("Left");
    c->removeManualInstruction("Right");
    c->removeManualInstruction("Up");
    c->removeManualInstruction("Down");
}

void GameDialog::setWASDControls() {
    arrowManual = false;
    manualControl = true;
    menu->updateControlKeyColour();
    c->removeManualInstruction("Left");
    c->removeManualInstruction("Right");
    c->removeManualInstruction("Up");
    c->removeManualInstruction("Down");
}

void GameDialog::updateHyperFuel() {
    if (this->hyperFuel <= 1) {
        ship->setState((ShipState*) ship->getNormalState());
    }
    if (QString::compare(ship->getCurrentState(), "Normal", Qt::CaseInsensitive) == 0) {
        hyperFuel = hyperFuel < 100 ? hyperFuel + 1 : hyperFuel;
    }
    if (QString::compare(ship->getCurrentState(), "Hyper", Qt::CaseInsensitive) == 0) {
        hyperFuel = hyperFuel > 0 ? hyperFuel - 1 : hyperFuel;
    }
}

// FOLLOWING EACH INSTRUCTION TO FRAME - for PLAYER ship.
void GameDialog::nextFrame() {
    if (ship->getCurrentState() == "Frozen") {
        if (frozenCountdown <= 0) {
            ship->setState((ShipState*) ship->getNormalState());
        } else {
            frozenCountdown = frozenCountdown > 0 ? frozenCountdown - 1 : frozenCountdown;
            hyperFuel = hyperFuel > 0 ? hyperFuel - 1 : hyperFuel;
        }
    } else {
        updateHyperFuel();
    }

    menu->updateHyperFuel(hyperFuel);
    if (!paused) {
        // Check if all aliens are killed -- if true, update level
        if (swarms->getAliens().size() == 0 && (manualControl || mouseControl)) {
            if (!lastLevel) {
                level++;
            }
            generateAliens(c->getSwarmList(level));
            if (level > c->numberOfLevels() && updateHighScores) {
                // Winner!
                updateHighScores = false;
                c->updateConfigScores(menu->getHighScores(), menu->getHighScoringPlayers());
                lastLevel = true;
                gameOver();
            }
        }
        if (!manualControl && !mouseControl) {
            // Read ship controls from config
            QStringList instruct = c->get_instructs();
            if (next_instruct >= instruct.size()) {
                next_instruct = next_instruct % instruct.size();
            } else {

            }
            QString ins = instruct[next_instruct];
            next_instruct++;

            if (ins == "Left") {
                ship->move_left();
            } else if (ins == "Right") {
                ship->move_right();
            } else if (ins == "Shoot") {
                addBullets(this->ship->shoot());
                this->shipFiringSound.play();
            }
        } else if (manualControl) {
            // Read ship controls from key commands
            QSet<QString> ins = c->getManualInstructions();
            if (ins.contains("Left")) {
                ship->move_left();
            }
            if (ins.contains("Right")) {
                ship->move_right();
            }
            if (ins.contains("Up")) {
                ship->move_up();
            }
            if (ins.contains("Down")) {
                ship->move_down();
            }
            if (ins.contains("Shoot")) {
                addBullets(this->ship->shoot());
                c->removeManualInstruction("Shoot");
                this->shipFiringSound.play();
            }
        } else {
            QSet<QString> ins = c->getManualInstructions();
            if (ins.contains("Shoot")) {
                addBullets(this->ship->shoot());
                c->removeManualInstruction("Shoot");
                this->shipFiringSound.play();
            }
        }

        updateBullets();

        // loop through each alien swarm, move and calculated collisions
        swarms->move("");  // recursive.
        checkSwarmCollisions(swarms);
        addBullets(swarms->shoot(""));
    }
    // prepare collisions and calculate score
    update();
}

void GameDialog::paintBullets(QPainter& painter) {
    for (int i = 0; i < 0 || (unsigned) i < bullets.size(); i++) {
        Bullet* b = bullets[i];
        painter.drawPixmap(b->get_x(), b->get_y(), b->get_image());
    }
}

void GameDialog::updateBullets()
{
    for (int i = 0; i < 0 || (unsigned) i < bullets.size(); i++) {
        Bullet* b = bullets[i];
        // WHEN BULLET OFF GAME SCREEN, FREE MEMORY AND DELETE
        int score = get_collided(b, swarms);
        if (b->get_y() < 0 || b->get_y() >= SCALEDHEIGHT || b->get_x() < 0 ||
                b->get_x() >= SCALEDWIDTH || score > 0) {
            delete b;
            bullets.erase(bullets.begin() + i);
            i--;
        } else if (score == -1) {
            // DEAD SHIP!
            delete b;
            bullets.erase(bullets.begin() + i);
            i--;
            if (ship->getCurrentState() == "Frozen") {
                c->updateConfigScores(menu->getHighScores(), menu->getHighScoringPlayers());
                gameOver();
            } else {
                ship->setState((ShipState*) ship->getFrozenState());
                frozenCountdown = 25;
            }
        } else {
            b->move();// we move at the end so that we can see collisions before the game ends
        }
        gameScore += score;
    }
}

void GameDialog::gameOver() {
   if (swarms->getAliens().size() == 0 && lastLevel) {
       this->menu->winner();
   } else {
       this->menu->loser();
       ship->setState((ShipState*) ship->getDeadState());
   }
   this->paused = true;
   this->menu->gameOver();
   this->timer->stop();
}

void GameDialog::continueGame() {
    this->menu->newGame();
    ship->setState((ShipState*) ship->getNormalState());
    this->bullets.clear();
    this->paused = false;
    this->frozenCountdown = 0;
    this->hyperFuel = 0;
    ship->set_x(c->get_startpos());
    ship->set_y(700);
    frames = c->get_frames();
    this->timer->setInterval(frames);
    this->timer->start();
}

void GameDialog::newGame() {
    this->menu->newGame();
    this->bullets.clear();
    this->paused = false;
    generateAliens(c->getSwarmList(0));
    lastLevel = false;
    level = 0;
    gameScore = 0;
    frozenCountdown = 0;
    hyperFuel = 0;
    ship->set_x(c->get_startpos());
    ship->set_y(700);
    frames = c->get_frames();
    this->timer->setInterval(frames);
    this->timer->start();
}

void GameDialog::closeGame() {
    close();
}

// recurse throughout the tree and draw everything.
// will also
void GameDialog::paintSwarm(QPainter& painter, AlienBase*& root) {
    for (AlienBase* child : root->getAliens()) {
        // if the child is a leaf (i.e., an alien that has no children), draw it.
        const QList<AlienBase*>& list = child->getAliens();
        if (list.size() == 0) {  // leaf
            painter.drawPixmap(child->get_x(), child->get_y(), child->get_image());
        } else {
            paintSwarm(painter, child);
        }
    }
}

// check if any aliens based off the alien root are crashing with the player ship.
void GameDialog::checkSwarmCollisions(AlienBase *&root) {
    for (AlienBase* child : root->getAliens()) {
        // if the child is a leaf (i.e., an alien that has no children), check for collisions.
        const QList<AlienBase*>& list = child->getAliens();
        if (list.size() == 0) {  // leaf
            // check if it is crashing into the player ship
            if (child->collides(*this->ship)) {
                // DEAD SHIP AGAIN
                if (ship->getCurrentState() == "Frozen") {
                    c->updateConfigScores(menu->getHighScores(), menu->getHighScoringPlayers());
                    gameOver();
                } else {
                    ship->setState((ShipState*) ship->getFrozenState());
                    frozenCountdown = 25;
                }
            }
        } else {
          checkSwarmCollisions(child);
        }
    }
}

// PAINTING THE SHIP AND ANY BULLETS
void GameDialog::paintEvent(QPaintEvent*) {
    // SHIP
    QPainter painter(this);

    // Background image
    QPixmap bkgnd(":/Images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    painter.drawPixmap(0, 0, bkgnd);

    // Paint Score
    QString score = QString("SCORE: %1").arg(gameScore);
    QString levelString = QString("Level: %1").arg(level);
    painter.setPen(QColor("#FFD954"));
    QFont font = QFont("Courier New");
    font.setPixelSize(20);
    font.bold();
    painter.setFont(font);
    painter.drawText(8, 22, score);
    painter.drawText(692, 22, levelString);

    painter.drawPixmap(ship->get_x(), ship->get_y(), ship->get_image());

    // loop through each alien swarm and draw
    paintSwarm(painter, swarms);

    // BULLETS last so they draw over everything
    paintBullets(painter);
}

// if this bullet is unfriendly, only check if it hits Ship
// if this bullet is friendly, will check the swarm;
// returns the score from the deleted hit object.
// Returns 0 if nothing hit, -ve if ship is hit.
int GameDialog::get_collided(Bullet*& b, AlienBase*& root) {
    int totalScore = 0;

    // if it's an enemy bullet, then don't look at the swarm.
    if (!b->isFriendly()) {
        // check it hits the player ship
        if (b->collides(*this->ship)) {
            totalScore = -1;
//            delete b;
        }  // future; add barriers here.
    } else {
        totalScore += get_collided_swarm(b, root);
    }
    return totalScore;
}

// helper function, recursively searches swarms.
int GameDialog::get_collided_swarm(Bullet*& b, AlienBase*& root) {
    int totalScore = 0;
    // Case 1: you are a leaf node, or root node
    if (root->getAliens().size() == 0) {
        // check collision.
        if (b->collides(*root)) {
            // if it is an alien, it will return >0.
            // if it's a swarm (i.e., root) it will return 0.
            return root->get_score();
        }

    } else {
        for (int i = 0; i < root->getAliens().size(); i++) {
            AlienBase* child = root->getAliens().at(i);
            // if it's another swarm, recurse down the tree
            totalScore += get_collided_swarm(b, child);
            // if something was hit, score > 0
            if (totalScore > 0 && child->getAliens().size() == 0) {
                // some children shoot more bullets when they die.
                // ask child for reaction when you're going to delete them
                addBullets(child->react());
                root->remove(child);
                i--;
                return totalScore;
            }
        }
    }
    return totalScore;
}

void GameDialog::addBullets(const QList<Bullet*>& list) {
    for (Bullet* b : list) {
        this->bullets.push_back(b);
    }
}
}
