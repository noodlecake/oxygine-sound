#pragma once
#include "../SoundSystem.h"
#include "../oal.h"
#include "SoundOAL.h"

namespace oxygine
{
    class SoundOAL;
    class SoundSystemOAL : public SoundSystem
    {
    public:
        SoundSystemOAL();
        ~SoundSystemOAL();

        void init(int channels_num);
        void release();

        void pause();
        void resume();
        void stop();

        SoundOAL* createSound(const char* path, bool streaming);


        bool        isAvailable() const {return _context != 0;}
        float       getVolume() const {return _volume;}

        void setContext();

        void update();

        ALuint getSource();
        void   freeSource(ALuint);

        ALuint getBuffer();
        void   freeBuffer(ALuint);

    private:
        std::vector<ALuint> _freeSources;
        std::vector<ALuint> _sources;

        std::vector<ALuint> _freeBuffers;
        std::vector<ALuint> _buffers;

        float _volume;

        ALCdevice* _device;
        ALCcontext* _context;
    };
}