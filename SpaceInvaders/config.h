#pragma once
#include "swarminfo.h"
#include <QFile>
#include <QHash>
#include <QList>
#include <QPair>
#include <QSet>
#include <QTextStream>
#define NAME_LENGTH 5

namespace game {

class Config {
private:
    static Config* s_configInstance;

    // Write to config
    QString copyConfig(QTextStream& in);

    // Read config
    void processShip(QTextStream& in);
    void processConfigSizeLine(QString l);
    void processInstructions(QStringList& instructs, QStringList& copy);
    void processScores(QTextStream& in);
    void processSwarm(QTextStream& in);
    void processPairs(QStringList list, QList<QPair<int, int>>& positions);
    void processMoves(QStringList& move, QStringList& list);
    void saveSwarm(QString type, QList<QPair<int, int>> positions, QStringList move, int shoot);
    void scalePositions();

    // SHIP values
    QString name;  // this will be useful in Stage 3 ;)
    double scale;
    int startpos;
    int frames;
    QStringList instructs;
    QString defaultInstructs;
    int SCALEDWIDTH;
    int SCALEDHEIGHT;

    // Swarm Info Map
    QList<QList<SwarmInfo>> swarmsList = {};
    int levelCount;
    int swarmCount;

    // default Alien values
    QStringList alienTypes;
    QString defaultAlienType;
    QStringList defaultAlienMove;
    const int defaultAlienShoot = 10;

    // Manual Instructions
    QSet<QString> manualInstructions;

    // High scores
    QList<int> highScores;
    QList<QString> highScoringPlayers;

    void initDefault();

protected:
    Config();

public:
    // testing
    void updateConfigScores(QList<int> scores);

    // AS THE CONFIG GIVES INPUT, THE FILE IS READ TO THEN SET ATTRIBUTES.
    // GETTERS
    static Config* getInstance();
    ~Config();
    QString get_name();

    // Suppot for manual instructions
    QSet<QString> getManualInstructions();
    void addManualInstruction(QString ins);
    void removeManualInstruction(QString ins);
    void clearManualInstructions();

    // Getters
    double get_scale();
    int get_startpos();
    QStringList get_instructs();
    QList<SwarmInfo> getSwarmList(int level);
    int get_frames();
    int numberOfLevels();
    QList<int> getHighScores();
    QList<QString> getHighScoringPlayers();

    int get_SCALEDWIDTH();
    int get_SCALEDHEIGHT();
};
}
