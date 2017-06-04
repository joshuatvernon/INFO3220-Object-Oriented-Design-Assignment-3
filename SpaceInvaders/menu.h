#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QPushButton>
namespace game {
class Menu {
public:
    Menu(QWidget* parent, int& playeScore, QList<int> scores, QList<QString> players, bool& arrow);
    ~Menu();
    void displayMenu(bool paused);
    void openScore();
    void toggleDisplaySpeeds();
    void toggleDisplayControls();
    void updateTopScores();
    QList<int> getHighScores();
    QList<QString> getHighScoringPlayers();
    void updateControlKeyColour();
    void gameOver();
    void newGame();
    void winner();
    void loser();
    void setName(QString name);
    void updateHyperFuel(int newHyperFuel);

private:
    void makeButtons(QWidget* parent);
    void closeButtons();  // if any buttons are left open, close them
    int& gameScore;
    bool& arrowManual;

    // Hyperfuel
    int hyperFuel;
    QLabel* hyperContainer;
    QLabel* hyperAlert;
    QLabel* hyper1;
    QLabel* hyper2;
    QLabel* hyper3;
    QLabel* hyper4;
    QLabel* hyper5;
    QLabel* hyper6;
    QLabel* hyper7;
    QLabel* hyper8;
    QLabel* hyper9;
    QLabel* hyper10;
    void makeHyperfuelContainers(QWidget* parent);

    // High scores
     QList<int> highScores;
     QList<QString> highScoringPlayers;
     QString playerNameText;

    // Buttons
    QPushButton* score;
    QPushButton* speed;
    QPushButton* slow;
    QPushButton* normal;
    QPushButton* fast;
    QPushButton* chaos;
    QPushButton* controls;
    QPushButton* menu;
    QPushButton* resume;

    // Labels
    // Scores
    QLabel* topScoreNameLabel1;
    QLabel* topScoreNameLabel2;
    QLabel* topScoreNameLabel3;
    QLabel* topScoreNameLabel4;
    QLabel* topScoreNameLabel5;
    QLabel* topScoreLabel1;
    QLabel* topScoreLabel2;
    QLabel* topScoreLabel3;
    QLabel* topScoreLabel4;
    QLabel* topScoreLabel5;
    // Controls
    QLabel* controlsLabel;
    QPushButton* controlsArrow;
    QPushButton* controlsWASD;
    QPushButton* leftArrowKey;
    QPushButton* rightArrowKey;
    QPushButton* upArrowKey;
    QPushButton* downArrowKey;
    QPushButton* wKey;
    QPushButton* aKey;
    QPushButton* sKey;
    QPushButton* dKey;

    // Game Over
    // Display gameOver backgrond modal
    QLabel* gameOverBackground;
    QLabel* gameOverTitle;
    QPushButton* quitGameBtn;
    QPushButton* newGameBtn;
    QPushButton* continueBtn;

    // Menu
    void paintMenu();

    // Methods
    void revealPlayerScore(bool open);
};
}
#endif  // SCOREBUTTON_H
