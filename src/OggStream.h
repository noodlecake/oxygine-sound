#pragma once
#include <vector>
#include "core/Object.h"
#include "core/file.h"
#include "ivorbisfile.h"
#include "MemoryStream.h"


namespace oxygine
{
    class SoundStream
    {
    public:
        virtual bool isStreamEnded() const = 0;
        virtual int decodeNextBlock(bool looped, void* data, int bufferSize) = 0;

        virtual int getRate() const = 0;
        virtual int getNumChannels() const = 0;
        virtual int getPosition() const = 0;
        virtual void reset() = 0;
        virtual void setPosition(int tm) = 0;

        virtual ~SoundStream() {}
    };

    DECLARE_SMART(OggStream, spOggStream);
    class OggStream: public SoundStream
    {
    public:
        OggStream();
        ~OggStream();

        bool init(const void* data, unsigned int len);
        bool init(const char* path);

        void reset();
        void release();

        bool                isEmpty() const {return _empty;}
        int                 getCurrentPCM() const;
        int                 getCurrentMS() const;
        int                 getPosition() const { return getCurrentMS(); }
        int                 getTotalPCM() const;
        int                 getTotalMS() const;
        int                 getRate() const;
        int                 getNumChannels() const;
        void                getDetails(unsigned int* pcm, int* channels, int* rate, int* timeMS);

        int                 seekPCM(int pcm);
        int                 seekMS(int ms);
        void                setPosition(int ms) { seekMS(ms); }
        int                 decodeNextBlock(bool looped, void* data, int bufferSize);
        void                decodeAll(void* data, int bufferSize);

        bool                isStreamEnded() const {return _streamEnded;}

    private:
        bool                _init(const ov_callbacks& cb, void* userData);

        bool                _empty;

        bool                _streamEnded;

        MemoryStream        _memStream;
        OggVorbis_File      _vorbisFile;

        vorbis_info* _info;

        FILE* _file;
        file::handle _oxfile;

        int _section;
    };
}