// killArtistCommand.h
#ifndef KILLARTISTCOMMAND_H
#define KILLARTISTCOMMAND_H

#include "iCommand.h"
#include "levelData.h"
#include "tile.h"


class KillArtistCommand : public ICommand {
public:
    KillArtistCommand(LevelData& aLevelData);

    void execute() override;

private:
    LevelData& mLevelData;
};

#endif // KILLARTISTCOMMAND_H