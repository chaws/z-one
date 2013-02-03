/**
 *@file sound.cpp
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Arquivo com a implementação da classe responsável por controlar a placa de som
 **/

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <commonTypes.hpp>
#include <sound.hpp>

#define NUM_SOUNDS 1

using namespace std;

struct sample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[NUM_SOUNDS];

/**
 *
 */
int Sound::init()
{
    return NOT_IMPLEMENTED;
}

/**
 *
 */
void Sound::play()
{
    
}

void Sound::playFile(string file)
{
    int index;
    SDL_AudioSpec wave;
    Uint8 * data;
    Uint32 dlen;
    SDL_AudioCVT cvt;

    /* Look for an empty (or finished) sound slot */
    for(index = 0; index < NUM_SOUNDS; ++index) 
        if(sounds[index].dpos == sounds[index].dlen) 
            break;

    if (index == NUM_SOUNDS)
        return;

    /* Load the sound file and convert it to 16-bit stereo at 22kHz */
    if(SDL_LoadWAV(file.c_str(), &wave, &data, &dlen) == NULL) 
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file.c_str(), SDL_GetError());
        return;
    }
    SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
                            AUDIO_S16,   2,             22050);
    cvt.buf = (Uint8 *)malloc(dlen * cvt.len_mult);
    memcpy(cvt.buf, data, dlen);
    cvt.len = dlen;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);

    /* Put the sound data in the slot (it starts playing immediately) */
    if(sounds[index].data)
        free(sounds[index].data);
    
    SDL_LockAudio();
    sounds[index].data = cvt.buf;
    sounds[index].dlen = cvt.len_cvt;
    sounds[index].dpos = 0;
    SDL_UnlockAudio();
}

void Sound::mix(Uint8 * stream, unsigned int len)
{
    int i;
    Uint32 amount;

    for (i = 0; i < NUM_SOUNDS; ++i){
        amount = (sounds[i].dlen - sounds[i].dpos);
        if (amount > (Uint32)len)
            amount = len;
        
        SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
        sounds[i].dpos += amount;
    }
}
