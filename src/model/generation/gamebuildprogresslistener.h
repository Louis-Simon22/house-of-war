#ifndef GAMEBUILDPROGRESSLISTENER_H
#define GAMEBUILDPROGRESSLISTENER_H

#include <string>

using namespace std;

class GameBuildProgressListener
{
    public:
        explicit GameBuildProgressListener();
        virtual void broadcastProgress(float progress);
        virtual void broadcastError(string error);
};

#endif // GAMEBUILDPROGRESSLISTENER_H
