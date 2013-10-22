#include "LightScheduler.h"
#include "LightController.h"

/* ---------------------------------------- */
const int UN_USED = -1;

enum EVENT {
	NOTHING, TURN_ON, TURN_OFF
};

typedef enum EVENT EVENT;

typedef struct {
    int id;
	EVENT	event;
    DAY		minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

/* ---------------------------------------- */
static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ---------------------------------------- */

/**************************************************
 * コンストラクタ
 **************************************************/
void LightScheduler_Create(void)
{
    _scheduled_event.id = UN_USED;
    _scheduled_event.event = NOTHING;
    _scheduled_event.minuite_of_day = NONE;
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

	if (_scheduled_event.event == TURN_OFF) {
    	LightController_TurnOff(_scheduled_event.id);
	} else if (_scheduled_event.event == TURN_ON) {
		LightController_TurnOn(_scheduled_event.id);
	}
}

/**************************************************
 * ONイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.event = TURN_ON;
    _scheduled_event.minuite_of_day = minuite;
}

/**************************************************
 * OFFイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.event = TURN_OFF;
    _scheduled_event.minuite_of_day = minuite;
}
