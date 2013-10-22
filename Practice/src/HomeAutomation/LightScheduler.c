#include "LightScheduler.h"
#include "LightController.h"

typedef struct {
    int id;
	int operation;
    long minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

const int UN_USED = -1;

enum EVENT_OPERATION {
		NOTHING, TURN_ON, TURN_OFF
};

static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ---------------------------------------- */

/**************************************************
 * コンストラクタ
 **************************************************/
void LightScheduler_Create(void)
{
    _scheduled_event.id = UN_USED;
    _scheduled_event.operation = NOTHING;
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

	if (_scheduled_event.operation == TURN_OFF) {
    	LightController_TurnOff(_scheduled_event.id);
	} else {
		LightController_TurnOn(_scheduled_event.id);
	}
}

/**************************************************
 * ONイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, enum WEEK_DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.minuite_of_day = minuite;
}

/**************************************************
 * OFFイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, enum WEEK_DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.operation = TURN_OFF;
    _scheduled_event.minuite_of_day = minuite;
}
