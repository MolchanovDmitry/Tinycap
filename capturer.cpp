#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "pcm.h"
#include "../assessment/clSound.h"
#include <android/log.h>
#include <time.h>
#include <unistd.h>
#include <AACCodec.h>

#define FILENAME "pcmreadi"
#define EXIT_FAILURE_MEMORY_ALLOCATE 10
#define EXIT_FAILURE_PCM_OPEN 11
#define EXIT_FAILURE_FRAMES_ALLOCATE 12

const int BUFFER_SIZE = 1024;

int capture(int audioDeviceId) {
    struct pcm *pcm;

    unsigned int device = 0;
    unsigned int flags = PCM_IN;

    const struct pcm_config config = {
            .channels = 4,
            .rate = 44100,
            .format = PCM_FORMAT_S16_LE,
            .period_size = BUFFER_SIZE,
            .period_count = 2,
            .start_threshold = BUFFER_SIZE,
            .silence_threshold = BUFFER_SIZE * 2,
            .stop_threshold = BUFFER_SIZE * 2
    };

    pcm = pcm_open(audioDeviceId, device, flags, &config);
    if (pcm == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, FILENAME, "failed to allocate memory for PCM");
        return EXIT_FAILURE_MEMORY_ALLOCATE;
    } else if (!pcm_is_ready(pcm)) {
        pcm_close(pcm);
        __android_log_print(ANDROID_LOG_ERROR, FILENAME, "failed to open PCM");
        return EXIT_FAILURE_PCM_OPEN;
    }

    //some job

    pcm_close(pcm);
    __android_log_print(ANDROID_LOG_INFO, FILENAME, "Success capture close");
    return EXIT_SUCCESS;
}