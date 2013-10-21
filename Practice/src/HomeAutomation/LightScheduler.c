#include "LightScheduler.h"
#include "LightController.h"

typedef struct {
    int id;
    long minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

const int UN_USED = -1;

static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ---------------------------------------- */

/**************************************************
 * コンストラクタ
 **************************************************/
void LightScheduler_Create(void)
{
    _scheduled_event.id = UN_USED;
}

/**************************************************
 * デストラクタ
 **************************************************/
void LightScheduler_Destroy(void)
{
}

/**************************************************
 * 周期実行関数
 **************************************************/
void LightScheduler_wakeup(void)
{
    Time time;

    TimeService_getTime(&time);

    if (_scheduled_event.id == UN_USED) {
        return;
    }
    if (_scheduled_event.minuite_of_day != time.minuite_of_day) {
        return;
    }

    LightController_TurnOn(_scheduled_event.id);
}

/**************************************************
 * ONイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, enum WEEK_DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.minuite_of_day = minuite;
}
