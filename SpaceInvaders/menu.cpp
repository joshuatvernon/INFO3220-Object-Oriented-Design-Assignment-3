#include "menu.h"

#include <QPainter>
#include <QDebug>

namespace game {

Menu::Menu(QWidget* parent, int& playerScore, QList<int> scores, QList<QString> players, bool& arrow)
        : gameScore(playerScore), arrowManual(arrow) {
    highScores = scores;
    highScoringPlayers = players;
    int hyperFuel = 0;

    // Handle edge case where different amounts of scores or players are given
    while (highScores.size() < highScoringPlayers.size()) {
        highScoringPlayers.pop_back();
    }
    while (highScores.size() > highScoringPlayers.size()) {
        highScores.pop_back();
    }

    // If there are less than 5 high scoring players add dummy values
    while (highScores.size() < 5) {
        highScores.append(0);
    }
    while (highScoringPlayers.size() < 5) {
        highScoringPlayers.append("None");
    }

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < highScores.size(); i++) {
        for (int j = 0; j < highScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (highScores.at(i) > highScores.at(j)) {
                int tempScore = highScores.at(i);
                highScores.replace(i, highScores.at(j));
                highScores.replace(j, tempScore);

                QString tempPlayer = highScoringPlayers.at(i);
                highScoringPlayers.replace(i, highScoringPlayers.at(j));
                highScoringPlayers.replace(j, tempPlayer);
            }
        }
    }

    playerNameText = "Player 1 (me)";

    makeButtons(parent);
    makeHyperfuelContainers(parent);
}

void Menu::makeHyperfuelContainers(QWidget* parent) {
    hyperContainer = new QLabel(parent);
    hyperContainer->setGeometry(QRect(300, 40, 200, 20));
    hyperContainer->setVisible(true);
    hyperContainer->setStyleSheet("background-color: #452C34");

    hyperAlert = new QLabel(parent);
    hyperAlert->setGeometry(QRect(300, 65, 200, 20));
    hyperAlert->setText("   HYPER READY - HIT SHIFT!!!");
    hyperAlert->setVisible(true);
    hyperAlert->setStyleSheet("font-weight: bold; color: white");

    hyper1 = new QLabel(parent);
    hyper1->setGeometry(QRect(302, 42, 16, 16));
    hyper1->setVisible(false);
    hyper1->setStyleSheet("background-color: #00FF1B");

    hyper2 = new QLabel(parent);
    hyper2->setGeometry(QRect(322, 42, 16, 16));
    hyper2->setVisible(false);
    hyper2->setStyleSheet("background-color: #00FF1B");

    hyper3 = new QLabel(parent);
    hyper3->setGeometry(QRect(342, 42, 16, 16));
    hyper3->setVisible(false);
    hyper3->setStyleSheet("background-color: #C7FF00");

    hyper4 = new QLabel(parent);
    hyper4->setGeometry(QRect(362, 42, 16, 16));
    hyper4->setVisible(false);
    hyper4->setStyleSheet("background-color: #C7FF00");

    hyper5 = new QLabel(parent);
    hyper5->setGeometry(QRect(382, 42, 16, 16));
    hyper5->setVisible(false);
    hyper5->setStyleSheet("background-color: #FF7E00");

    hyper6 = new QLabel(parent);
    hyper6->setGeometry(QRect(402, 42, 16, 16));
    hyper6->setVisible(false);
    hyper6->setStyleSheet("background-color: #FF7E00");

    hyper7 = new QLabel(parent);
    hyper7->setGeometry(QRect(422, 42, 16, 16));
    hyper7->setVisible(false);
    hyper7->setStyleSheet("background-color: #FF410B");

    hyper8 = new QLabel(parent);
    hyper8->setGeometry(QRect(442, 42, 16, 16));
    hyper8->setVisible(false);
    hyper8->setStyleSheet("background-color: #FF410B");

    hyper9 = new QLabel(parent);
    hyper9->setGeometry(QRect(462, 42, 16, 16));
    hyper9->setVisible(false);
    hyper9->setStyleSheet("background-color: #FF0000");

    hyper10 = new QLabel(parent);
    hyper10->setGeometry(QRect(482, 42, 16, 16));
    hyper10->setVisible(false);
    hyper10->setStyleSheet("background-color: #FF0000");
}

void Menu::setName(QString name) {
    playerNameText = name;
}

Menu::~Menu() {
    delete score;
    delete speed;
    delete slow;
    delete normal;
    delete fast;
    delete chaos;
    delete controls;
    delete controlsLabel;
    delete controlsArrow;
    delete controlsWASD;
    delete menu;
    delete resume;
    delete topScoreLabel1;
    delete topScoreLabel2;
    delete topScoreLabel3;
    delete topScoreLabel4;
    delete topScoreLabel5;
    delete topScoreNameLabel1;
    delete topScoreNameLabel2;
    delete topScoreNameLabel3;
    delete topScoreNameLabel4;
    delete topScoreNameLabel5;
    delete leftArrowKey;
    delete rightArrowKey;
    delete upArrowKey;
    delete downArrowKey;
    delete wKey;
    delete aKey;
    delete sKey;
    delete dKey;
    delete gameOverBackground;
    delete gameOverTitle;
    delete quitGameBtn;
    delete newGameBtn;
    delete continueBtn;
    delete hyperContainer;
    delete hyper1;
    delete hyper2;
    delete hyper3;
    delete hyper4;
    delete hyper5;
    delete hyper6;
    delete hyper7;
    delete hyper8;
    delete hyper9;
    delete hyper10;
}

void Menu::makeButtons(QWidget* parent) {
    score = new QPushButton("Scores", parent);
    score->setGeometry(QRect(300, 0, 200, 30));
    score->setVisible(false);
    score->setStyleSheet("background-color: #FFD954");
    QObject::connect(score, SIGNAL(released()), parent, SLOT(showScore()));

    gameOverBackground = new QLabel(parent);
    gameOverBackground->setGeometry(QRect(280, 120, 240, 385));
    gameOverBackground->setVisible(false);
    gameOverBackground->setStyleSheet("background-color: #3F3131");

    speed = new QPushButton("Speed", parent);
    speed->setGeometry(QRect(500, 0, 100, 30));
    speed->setVisible(false);
    speed->setStyleSheet("background-color: #FFD954");
    QObject::connect(speed, SIGNAL(released()), parent, SLOT(toggleShowSpeed()));

    slow = new QPushButton("Slow", parent);
    slow->setGeometry(QRect(500, 30, 100, 40));
    slow->setVisible(false);
    slow->setStyleSheet("background-color: green");
    QObject::connect(slow, SIGNAL(released()), parent, SLOT(pressSlow()));

    normal = new QPushButton("Normal", parent);
    normal->setGeometry(QRect(500, 70, 100, 40));
    normal->setVisible(false);
    normal->setStyleSheet("background-color: yellow");
    QObject::connect(normal, SIGNAL(released()), parent, SLOT(pressNormal()));

    fast = new QPushButton("Fast", parent);
    fast->setGeometry(QRect(500, 110, 100, 40));
    fast->setVisible(false);
    fast->setStyleSheet("background-color: orange");
    QObject::connect(fast, SIGNAL(released()), parent, SLOT(pressFast()));

    chaos = new QPushButton("Chaos", parent);
    chaos->setGeometry(QRect(500, 150, 100, 40));
    chaos->setVisible(false);
    chaos->setStyleSheet("background-color: red");
    QObject::connect(chaos, SIGNAL(released()), parent, SLOT(pressChaos()));

    controls = new QPushButton("Controls", parent);
    controls->setGeometry(QRect(690, 0, 110, 30));
    controls->setVisible(false);
    controls->setStyleSheet("background-color: #FFD954");
    QObject::connect(controls, SIGNAL(released()), parent, SLOT(pressControls()));

    controlsLabel = new QLabel(parent);
    controlsLabel->setGeometry(QRect(330, 190, 140, 230));
    controlsLabel->setVisible(false);
    controlsLabel->setStyleSheet("background-color: #3F3131");

    controlsArrow = new QPushButton("Arrows", parent);
    controlsArrow->setGeometry(QRect(350, 270, 100, 30));
    controlsArrow->setVisible(false);
    controlsArrow->setStyleSheet("background-color: #FFD954");
    QObject::connect(controlsArrow, SIGNAL(released()), parent, SLOT(setArrowControls()));

    controlsWASD = new QPushButton("WASD", parent);
    controlsWASD->setGeometry(QRect(350, 370, 100, 30));
    controlsWASD->setVisible(false);
    controlsWASD->setStyleSheet("background-color: #FFD954");
    QObject::connect(controlsWASD, SIGNAL(released()), parent, SLOT(setWASDControls()));

    leftArrowKey = new QPushButton("<", parent);
    leftArrowKey->setGeometry(QRect(359, 240, 22, 22));
    leftArrowKey->setVisible(false);

    rightArrowKey = new QPushButton(">", parent);
    rightArrowKey->setGeometry(QRect(419, 240, 22, 22));
    rightArrowKey->setVisible(false);

    upArrowKey = new QPushButton("^", parent);
    upArrowKey->setGeometry(QRect(389, 210, 22, 22));
    upArrowKey->setVisible(false);

    downArrowKey = new QPushButton("v", parent);
    downArrowKey->setGeometry(QRect(389, 240, 22, 22));
    downArrowKey->setVisible(false);

    wKey = new QPushButton("W", parent);
    wKey->setGeometry(QRect(389, 310, 22, 22));
    wKey->setVisible(false);

    aKey = new QPushButton("A", parent);
    aKey->setGeometry(QRect(359, 340, 22, 22));
    aKey->setVisible(false);

    sKey = new QPushButton("S", parent);
    sKey->setGeometry(QRect(389, 340, 22, 22));
    sKey->setVisible(false);

    dKey = new QPushButton("D", parent);
    dKey->setGeometry(QRect(419, 340, 22, 22));
    dKey->setVisible(false);

    menu = new QPushButton("Menu", parent);
    menu->setGeometry(QRect(350,  0, 100, 30));
    menu->setVisible(true);
    menu->setStyleSheet("background-color: #FFD954");
    QObject::connect(menu, SIGNAL(released()), parent, SLOT(pauseStart()));

    resume = new QPushButton("Resume", parent);
    resume->setGeometry(QRect(200, 0, 100, 30));
    resume->setVisible(false);
    resume->setStyleSheet("background-color: #FFD954");
    QObject::connect(resume, SIGNAL(released()), parent, SLOT(pauseStart()));

    topScoreLabel1 = new QLabel(parent);
    topScoreLabel1->setGeometry(QRect(400, 30, 100, 32));
    topScoreLabel1->setVisible(false);

    topScoreLabel2 = new QLabel(parent);
    topScoreLabel2->setGeometry(QRect(400, 62, 100, 32));
    topScoreLabel2->setVisible(false);

    topScoreLabel3 = new QLabel(parent);
    topScoreLabel3->setGeometry(QRect(400, 94, 100, 32));
    topScoreLabel3->setVisible(false);

    topScoreLabel4 = new QLabel(parent);
    topScoreLabel4->setGeometry(QRect(400, 126, 100, 32));
    topScoreLabel4->setVisible(false);

    topScoreLabel5 = new QLabel(parent);
    topScoreLabel5->setGeometry(QRect(400, 158, 100, 32));
    topScoreLabel5->setVisible(false);

    topScoreNameLabel1 = new QLabel(parent);
    topScoreNameLabel1->setGeometry(QRect(300, 30, 100, 32));
    topScoreNameLabel1->setVisible(false);

    topScoreNameLabel2 = new QLabel(parent);
    topScoreNameLabel2->setGeometry(QRect(300, 62, 100, 32));
    topScoreNameLabel2->setVisible(false);

    topScoreNameLabel3 = new QLabel(parent);
    topScoreNameLabel3->setGeometry(QRect(300, 94, 100, 32));
    topScoreNameLabel3->setVisible(false);

    topScoreNameLabel4 = new QLabel(parent);
    topScoreNameLabel4->setGeometry(QRect(300, 126, 100, 32));
    topScoreNameLabel4->setVisible(false);

    topScoreNameLabel5 = new QLabel(parent);
    topScoreNameLabel5->setGeometry(QRect(300, 158, 100, 32));
    topScoreNameLabel5->setVisible(false);

    updateTopScores();

    // Game Over
    gameOverTitle = new QLabel(parent);
    gameOverTitle->setGeometry(QRect(350, 135, 100, 30));
    gameOverTitle->setText("     Game Over");
    gameOverTitle->setVisible(false);
    gameOverTitle->setStyleSheet("background-color: white");

    quitGameBtn = new QPushButton("Quit Game", parent);
    quitGameBtn->setGeometry(QRect(350, 455, 100, 32));
    quitGameBtn->setVisible(false);
    quitGameBtn->setStyleSheet("background-color: #FFD954");
    QObject::connect(quitGameBtn, SIGNAL(released()), parent, SLOT(closeGame()));

    newGameBtn = new QPushButton("New Game", parent);
    newGameBtn->setGeometry(QRect(350, 410, 100, 32));
    newGameBtn->setVisible(false);
    newGameBtn->setStyleSheet("background-color: #FFD954");
    QObject::connect(newGameBtn, SIGNAL(released()), parent, SLOT(newGame()));

    continueBtn = new QPushButton("Continue", parent);
    continueBtn->setGeometry(QRect(350, 365, 100, 32));
    continueBtn->setVisible(false);
    continueBtn->setStyleSheet("background-color: #FFD954");
    QObject::connect(continueBtn, SIGNAL(released()), parent, SLOT(continueGame()));
}

// called when game is paused or unpaused
void Menu::displayMenu(bool paused) {
    if (!paused) {
        closeButtons();
    } else {
        score->setVisible(true);
        speed->setVisible(true);
        controls->setVisible(true);
        resume->setVisible(true);
        menu->setVisible(false);
        hyperContainer->setVisible(false);
        hyper1->setVisible(false);
        hyper2->setVisible(false);
        hyper3->setVisible(false);
        hyper4->setVisible(false);
        hyper5->setVisible(false);
        hyper6->setVisible(false);
        hyper7->setVisible(false);
        hyper8->setVisible(false);
        hyper9->setVisible(false);
        hyper10->setVisible(false);
    }
}

// helper, closes all the opened menus
void Menu::closeButtons() {
    menu->setVisible(true);
    resume->setVisible(false);
    score->setVisible(false);
    speed->setVisible(false);
    slow->setVisible(false);
    normal->setVisible(false);
    fast->setVisible(false);
    chaos->setVisible(false);
    controls->setVisible(false);
    controlsLabel->setVisible(false);
    controlsArrow->setVisible(false);
    controlsWASD->setVisible(false);
    leftArrowKey->setVisible(false);
    rightArrowKey->setVisible(false);
    upArrowKey->setVisible(false);
    downArrowKey->setVisible(false);
    wKey->setVisible(false);
    aKey->setVisible(false);
    sKey->setVisible(false);
    dKey->setVisible(false);
    hyperContainer->setVisible(true);
    revealPlayerScore(false);
}

// helper function for OpenScore
void Menu::revealPlayerScore(bool open) {
    // recalculate playerScoreLabel
    // Top scores
    topScoreLabel1->setVisible(open);
    topScoreLabel2->setVisible(open);
    topScoreLabel3->setVisible(open);
    topScoreLabel4->setVisible(open);
    topScoreLabel5->setVisible(open);
    topScoreNameLabel1->setVisible(open);
    topScoreNameLabel2->setVisible(open);
    topScoreNameLabel3->setVisible(open);
    topScoreNameLabel4->setVisible(open);
    topScoreNameLabel5->setVisible(open);
}

void Menu::openScore() {
    if (topScoreLabel1->isVisible()) {
        revealPlayerScore(false);
    } else {
        updateTopScores();
        revealPlayerScore(true);
    }
}

void Menu::toggleDisplaySpeeds() {
    if (slow->isVisible()) {
        slow->setVisible(false);
        normal->setVisible(false);
        fast->setVisible(false);
        chaos->setVisible(false);
    } else {
        slow->setVisible(true);
        normal->setVisible(true);
        fast->setVisible(true);
        chaos->setVisible(true);
    }
}

void Menu::toggleDisplayControls() {
    if (controlsLabel->isVisible()) {
        controlsLabel->setVisible(false);
        controlsArrow->setVisible(false);
        controlsWASD->setVisible(false);
        leftArrowKey->setVisible(false);
        rightArrowKey->setVisible(false);
        upArrowKey->setVisible(false);
        downArrowKey->setVisible(false);
        wKey->setVisible(false);
        aKey->setVisible(false);
        sKey->setVisible(false);
        dKey->setVisible(false);
    } else {
        controlsLabel->setVisible(true);
        controlsArrow->setVisible(true);
        controlsWASD->setVisible(true);
        updateControlKeyColour();
        leftArrowKey->setVisible(true);
        rightArrowKey->setVisible(true);
        upArrowKey->setVisible(true);
        downArrowKey->setVisible(true);
        wKey->setVisible(true);
        aKey->setVisible(true);
        sKey->setVisible(true);
        dKey->setVisible(true);
    }
}

void Menu::updateControlKeyColour() {
    if (arrowManual) {
        leftArrowKey->setStyleSheet("background-color: #43AFF8");
        rightArrowKey->setStyleSheet("background-color: #43AFF8");
        upArrowKey->setStyleSheet("background-color: #43AFF8");
        downArrowKey->setStyleSheet("background-color: #43AFF8");
        wKey->setStyleSheet("background-color: #E2E1E3");
        aKey->setStyleSheet("background-color: #E2E1E3");
        sKey->setStyleSheet("background-color: #E2E1E3");
        dKey->setStyleSheet("background-color: #E2E1E3");
    } else {
        leftArrowKey->setStyleSheet("background-color: #E2E1E3");
        rightArrowKey->setStyleSheet("background-color: #E2E1E3");
        upArrowKey->setStyleSheet("background-color: #E2E1E3");
        downArrowKey->setStyleSheet("background-color: #E2E1E3");
        wKey->setStyleSheet("background-color: #43AFF8");
        aKey->setStyleSheet("background-color: #43AFF8");
        sKey->setStyleSheet("background-color: #43AFF8");
        dKey->setStyleSheet("background-color: #43AFF8");
    }
}

void Menu::updateTopScores() {
    QList<int> overallScores = highScores;
    QList<QString> overallPlayers = highScoringPlayers;
    overallScores.append(gameScore);
    overallPlayers.append(playerNameText);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);

                QString tempPlayer = overallPlayers.at(i);
                overallPlayers.replace(i, overallPlayers.at(j));
                overallPlayers.replace(j, tempPlayer);
            }
        }
    }

    topScoreLabel1->setText(" " + QString::number(overallScores.at(0)));
    if (QString::compare(overallPlayers.at(0), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel1->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel1->setStyleSheet("background-color: white");
    }
    topScoreLabel2->setText(" " + QString::number(overallScores.at(1)));
    if (QString::compare(overallPlayers.at(1), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel2->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel2->setStyleSheet("background-color: white");
    }

    topScoreLabel3->setText(" " + QString::number(overallScores.at(2)));
    if (QString::compare(overallPlayers.at(2), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel3->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel3->setStyleSheet("background-color: white");
    }

    topScoreLabel4->setText(" " + QString::number(overallScores.at(3)));
    if (QString::compare(overallPlayers.at(3), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel4->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel4->setStyleSheet("background-color: white");
    }

    topScoreLabel5->setText(" " + QString::number(overallScores.at(4)));
    if (QString::compare(overallPlayers.at(4), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel5->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel5->setStyleSheet("background-color: white");
    }

    topScoreNameLabel1->setText(" " + overallPlayers.at(0));
    if (QString::compare(overallPlayers.at(0), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel1->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel1->setStyleSheet("background-color: white");
    }

    topScoreNameLabel2->setText(" " + overallPlayers.at(1));
    if (QString::compare(overallPlayers.at(1), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel2->setStyleSheet("background-color: #E3216F");
    } else {

        topScoreNameLabel2->setStyleSheet("background-color: white");
    }

    topScoreNameLabel3->setText(" " + overallPlayers.at(2));
    if (QString::compare(overallPlayers.at(2), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel3->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel3->setStyleSheet("background-color: white");
    }

    topScoreNameLabel4->setText(" " + overallPlayers.at(3));
    if (QString::compare(overallPlayers.at(3), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel4->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel4->setStyleSheet("background-color: white");
    }

    topScoreNameLabel5->setText(" " + overallPlayers.at(4));
    if (QString::compare(overallPlayers.at(4), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel5->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel5->setStyleSheet("background-color: white");
    }
}

QList<int> Menu::getHighScores() {
    QList<int> overallScores = highScores;
    overallScores.append(gameScore);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);
            }
        }
    }

    overallScores.pop_back();

    return overallScores;
}

QList<QString> Menu::getHighScoringPlayers() {
    QList<int> overallScores = highScores;
    QList<QString> overallPlayers = highScoringPlayers;
    overallScores.append(gameScore);
    overallPlayers.append(playerNameText);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);

                QString tempPlayer = overallPlayers.at(i);
                overallPlayers.replace(i, overallPlayers.at(j));
                overallPlayers.replace(j, tempPlayer);
            }
        }
    }

    overallPlayers.pop_back();

    for (int i = 0; i < 5; i++) {
        if (QString::compare(overallPlayers.at(i), playerNameText, Qt::CaseInsensitive) == 0) {
            QString formatPlayerName = overallPlayers.at(i);
            formatPlayerName.chop(4);
            overallPlayers.replace(i, formatPlayerName);
        }
    }

    return overallPlayers;
}

void Menu::gameOver() {

    menu->setEnabled(false);

    // Display gameOver backgrond modal
    gameOverBackground->setVisible(true);

    // Display game over title
    gameOverTitle->setVisible(true);

    // Display final score -- against top scores
    QList<int> overallScores = highScores;
    QList<QString> overallPlayers = highScoringPlayers;
    overallScores.append(gameScore);
    overallPlayers.append(playerNameText);

    // BubbleSort both highScores and highScoringPlayers
    for (int i = 0; i < overallScores.size(); i++) {
        for (int j = 0; j < overallScores.size(); j++) {
            if (i == j) {
                continue;
            }
            if (overallScores.at(i) >= overallScores.at(j)) {
                int tempScore = overallScores.at(i);
                overallScores.replace(i, overallScores.at(j));
                overallScores.replace(j, tempScore);

                QString tempPlayer = overallPlayers.at(i);
                overallPlayers.replace(i, overallPlayers.at(j));
                overallPlayers.replace(j, tempPlayer);
            }
        }
    }

    overallPlayers.pop_back();
    overallScores.pop_back();

    // Update top scores
    highScores = overallScores;
    highScoringPlayers = overallPlayers;
    // Remove (me) from any top score as its a new game
    for (int i = 0; i < 5; i++) {
        if (QString::compare(highScoringPlayers.at(i), playerNameText, Qt::CaseInsensitive) == 0) {
            QString formattedPlayerName = highScoringPlayers.at(i);
            formattedPlayerName.chop(5);
            highScoringPlayers.replace(i, formattedPlayerName);
        }
    }

    topScoreLabel1->setText(" " + QString::number(overallScores.at(0)));
    if (QString::compare(overallPlayers.at(0), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel1->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel1->setStyleSheet("background-color: white");
    }
    topScoreLabel2->setText(" " + QString::number(overallScores.at(1)));
    if (QString::compare(overallPlayers.at(1), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel2->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel2->setStyleSheet("background-color: white");
    }

    topScoreLabel3->setText(" " + QString::number(overallScores.at(2)));
    if (QString::compare(overallPlayers.at(2), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel3->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel3->setStyleSheet("background-color: white");
    }

    topScoreLabel4->setText(" " + QString::number(overallScores.at(3)));
    if (QString::compare(overallPlayers.at(3), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel4->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel4->setStyleSheet("background-color: white");
    }

    topScoreLabel5->setText(" " + QString::number(overallScores.at(4)));
    if (QString::compare(overallPlayers.at(4), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreLabel5->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreLabel5->setStyleSheet("background-color: white");
    }

    topScoreNameLabel1->setText(" " + overallPlayers.at(0));
    if (QString::compare(overallPlayers.at(0), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel1->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel1->setStyleSheet("background-color: white");
    }

    topScoreNameLabel2->setText(" " + overallPlayers.at(1));
    if (QString::compare(overallPlayers.at(1), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel2->setStyleSheet("background-color: #E3216F");
    } else {

        topScoreNameLabel2->setStyleSheet("background-color: white");
    }

    topScoreNameLabel3->setText(" " + overallPlayers.at(2));
    if (QString::compare(overallPlayers.at(2), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel3->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel3->setStyleSheet("background-color: white");
    }

    topScoreNameLabel4->setText(" " + overallPlayers.at(3));
    if (QString::compare(overallPlayers.at(3), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel4->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel4->setStyleSheet("background-color: white");
    }

    topScoreNameLabel5->setText(" " + overallPlayers.at(4));
    if (QString::compare(overallPlayers.at(4), playerNameText, Qt::CaseInsensitive) == 0) {
        topScoreNameLabel5->setStyleSheet("background-color: #E3216F");
    } else {
        topScoreNameLabel5->setStyleSheet("background-color: white");
    }

    topScoreLabel1->setGeometry(QRect(402, 178, 100, 32));
    topScoreLabel2->setGeometry(QRect(402, 213, 100, 32));
    topScoreLabel3->setGeometry(QRect(402, 248, 100, 32));
    topScoreLabel4->setGeometry(QRect(402, 283, 100, 32));
    topScoreLabel5->setGeometry(QRect(402, 318, 100, 32));
    topScoreNameLabel1->setGeometry(QRect(298, 178, 100, 32));
    topScoreNameLabel2->setGeometry(QRect(298, 213, 100, 32));
    topScoreNameLabel3->setGeometry(QRect(298, 248, 100, 32));
    topScoreNameLabel4->setGeometry(QRect(298, 283, 100, 32));
    topScoreNameLabel5->setGeometry(QRect(298, 318, 100, 32));


    topScoreLabel1->setVisible(true);
    topScoreLabel2->setVisible(true);
    topScoreLabel3->setVisible(true);
    topScoreLabel4->setVisible(true);
    topScoreLabel5->setVisible(true);

    topScoreNameLabel1->setVisible(true);
    topScoreNameLabel2->setVisible(true);
    topScoreNameLabel3->setVisible(true);
    topScoreNameLabel4->setVisible(true);
    topScoreNameLabel5->setVisible(true);

    // Display continue game button
    continueBtn->setVisible(true);

    // Display newGame button
    newGameBtn->setVisible(true);

    // Display quit button
    quitGameBtn->setVisible(true);
}

void Menu::newGame() {
    // Close Game Over menu
    gameOverTitle->setVisible(false);
    gameOverBackground->setVisible(false);
    quitGameBtn->setVisible(false);
    newGameBtn->setVisible(false);
    continueBtn->setVisible(false);
    continueBtn->setEnabled(true);
    topScoreLabel1->setGeometry(QRect(400, 30, 100, 32));
    topScoreLabel1->setVisible(false);
    topScoreLabel2->setGeometry(QRect(400, 62, 100, 32));
    topScoreLabel2->setVisible(false);
    topScoreLabel3->setGeometry(QRect(400, 94, 100, 32));
    topScoreLabel3->setVisible(false);
    topScoreLabel4->setGeometry(QRect(400, 126, 100, 32));
    topScoreLabel4->setVisible(false);
    topScoreLabel5->setGeometry(QRect(400, 158, 100, 32));
    topScoreLabel5->setVisible(false);
    topScoreNameLabel1->setGeometry(QRect(300, 30, 100, 32));
    topScoreNameLabel1->setVisible(false);
    topScoreNameLabel2->setGeometry(QRect(300, 62, 100, 32));
    topScoreNameLabel2->setVisible(false);
    topScoreNameLabel3->setGeometry(QRect(300, 94, 100, 32));
    topScoreNameLabel3->setVisible(false);
    topScoreNameLabel4->setGeometry(QRect(300, 126, 100, 32));
    topScoreNameLabel4->setVisible(false);
    topScoreNameLabel5->setGeometry(QRect(300, 158, 100, 32));
    topScoreNameLabel5->setVisible(false);
    menu->setEnabled(true);
}

void Menu::winner() {
    gameOverTitle->setText("      You Win!");
    gameOverTitle->setStyleSheet("background-color: #A1E95B");
    continueBtn->setEnabled(false);
}

void Menu::loser() {
    gameOverTitle->setText("     Game Over");
    gameOverTitle->setStyleSheet("background-color: #DD231D");
}

void Menu::updateHyperFuel(int newHyperFuel) {
    this->hyperFuel = newHyperFuel;
    if (this->hyperFuel >= 10) {
        hyper1->setVisible(true);
    } else {
        hyper1->setVisible(false);
    }
    if (this->hyperFuel >= 20) {
        hyper2->setVisible(true);
    } else {
        hyper2->setVisible(false);
    }
    if (this->hyperFuel >= 30) {
        hyper3->setVisible(true);
    } else {
        hyper3->setVisible(false);
    }
    if (this->hyperFuel >= 40) {
        hyper4->setVisible(true);
    } else {
        hyper4->setVisible(false);
    }
    if (this->hyperFuel >= 50) {
        hyper5->setVisible(true);
    } else {
        hyper5->setVisible(false);
    }
    if (this->hyperFuel >= 60) {
        hyper6->setVisible(true);
    } else {
        hyper6->setVisible(false);
    }
    if (this->hyperFuel >= 70) {
        hyper7->setVisible(true);
    } else {
        hyper7->setVisible(false);
    }
    if (this->hyperFuel >= 80) {
        hyper8->setVisible(true);
    } else {
        hyper8->setVisible(false);
    }
    if (this->hyperFuel >= 90) {
        hyper9->setVisible(true);
    } else {
        hyper9->setVisible(false);
    }
    if (this->hyperFuel >= 100) {
        hyper10->setVisible(true);
        hyperAlert->setVisible(true);
    } else {
        hyper10->setVisible(false);
        hyperAlert->setVisible(false);
    }
}

}
