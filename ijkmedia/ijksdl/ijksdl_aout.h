/*****************************************************************************
 * ijksdl_aout.h
 *****************************************************************************
 *
 * Copyright (c) 2013 Bilibili
 * copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef IJKSDL__IJKSDL_AOUT_H
#define IJKSDL__IJKSDL_AOUT_H

#include "ijksdl_audio.h"
#include "ijksdl_class.h"
#include "ijksdl_mutex.h"

typedef struct SDL_Aout_Opaque SDL_Aout_Opaque;
typedef struct SDL_Aout SDL_Aout;
struct SDL_Aout {
    SDL_mutex *mutex;
    //最小的延迟秒数  在opensles中有用到
    double     minimal_latency_seconds;

    SDL_Class       *opaque_class;
    SDL_Aout_Opaque *opaque;
    void (*free_l)(SDL_Aout *vout);
    //打开audio函数指针
    int (*open_audio)(SDL_Aout *aout, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained);
   //暂停audio函数指针
    void (*pause_audio)(SDL_Aout *aout, int pause_on);
   //刷新
    void (*flush_audio)(SDL_Aout *aout);
    //设置音量函数指针
    void (*set_volume)(SDL_Aout *aout, float left, float right);
    void (*close_audio)(SDL_Aout *aout);
    //获取最小的延迟秒数
    double (*func_get_latency_seconds)(SDL_Aout *aout);
    //设置最小的延迟秒数
    void   (*func_set_default_latency_seconds)(SDL_Aout *aout, double latency);

    // optional
    //设置播放速度
    void   (*func_set_playback_rate)(SDL_Aout *aout, float playbackRate);
    //设置音量
    void   (*func_set_playback_volume)(SDL_Aout *aout, float playbackVolume);
    int    (*func_get_audio_persecond_callbacks)(SDL_Aout *aout);

    // Android only  获取audio_session_id
    int    (*func_get_audio_session_id)(SDL_Aout *aout);
};


int SDL_AoutOpenAudio(SDL_Aout *aout, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained);
void SDL_AoutPauseAudio(SDL_Aout *aout, int pause_on);
void SDL_AoutFlushAudio(SDL_Aout *aout);
void SDL_AoutSetStereoVolume(SDL_Aout *aout, float left_volume, float right_volume);
void SDL_AoutCloseAudio(SDL_Aout *aout);
void SDL_AoutFree(SDL_Aout *aout);
void SDL_AoutFreeP(SDL_Aout **paout);

double SDL_AoutGetLatencySeconds(SDL_Aout *aout);
void   SDL_AoutSetDefaultLatencySeconds(SDL_Aout *aout, double latency);
int    SDL_AoutGetAudioPerSecondCallBacks(SDL_Aout *aout);

// optional
void   SDL_AoutSetPlaybackRate(SDL_Aout *aout, float playbackRate);
void   SDL_AoutSetPlaybackVolume(SDL_Aout *aout, float volume);

// android only
int    SDL_AoutGetAudioSessionId(SDL_Aout *aout);

#endif
