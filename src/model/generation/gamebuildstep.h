#ifndef GAMEBUILDSTEP_H
#define GAMEBUILDSTEP_H

class GameBuildStep
{
    public:
        explicit GameBuildStep();
        virtual bool build();
};

#endif // GAMEBUILDSTEP_H
