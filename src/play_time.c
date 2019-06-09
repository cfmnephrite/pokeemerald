#include "global.h"
#include "play_time.h"

enum
{
    STOPPED,
    RUNNING,
    MAXED_OUT
};

static u8 sPlayTimeCounterState;

void PlayTimeCounter_Reset(void)
{
    sPlayTimeCounterState = STOPPED;

    gSaveBlockPtr->playTimeHours = 0;
    gSaveBlockPtr->playTimeMinutes = 0;
    gSaveBlockPtr->playTimeSeconds = 0;
    gSaveBlockPtr->playTimeVBlanks = 0;
}

void PlayTimeCounter_Start(void)
{
    sPlayTimeCounterState = RUNNING;

    if (gSaveBlockPtr->playTimeHours > 999)
        PlayTimeCounter_SetToMax();
}

void PlayTimeCounter_Stop(void)
{
    sPlayTimeCounterState = STOPPED;
}

void PlayTimeCounter_Update(void)
{
    if (sPlayTimeCounterState == RUNNING)
    {
        gSaveBlockPtr->playTimeVBlanks++;

        if (gSaveBlockPtr->playTimeVBlanks > 59)
        {
            gSaveBlockPtr->playTimeVBlanks = 0;
            gSaveBlockPtr->playTimeSeconds++;

            if (gSaveBlockPtr->playTimeSeconds > 59)
            {
                gSaveBlockPtr->playTimeSeconds = 0;
                gSaveBlockPtr->playTimeMinutes++;

                if (gSaveBlockPtr->playTimeMinutes > 59)
                {
                    gSaveBlockPtr->playTimeMinutes = 0;
                    gSaveBlockPtr->playTimeHours++;

                    if (gSaveBlockPtr->playTimeHours > 999)
                        PlayTimeCounter_SetToMax();
                }
            }
        }
    }
}

void PlayTimeCounter_SetToMax(void)
{
    sPlayTimeCounterState = MAXED_OUT;

    gSaveBlockPtr->playTimeHours = 999;
    gSaveBlockPtr->playTimeMinutes = 59;
    gSaveBlockPtr->playTimeSeconds = 59;
    gSaveBlockPtr->playTimeVBlanks = 59;
}
