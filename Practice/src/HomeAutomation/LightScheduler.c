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
    long	minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

/* ---------------------------------------- */
static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ---------------------------------------- */
/**************************************************
 * イベントを登録する
 **************************************************/
static void scheduleEvent(int id, DAY day, long minuite_of_day, EVENT event)
{
	_scheduled_event.id = id;
    _scheduled_event.event = event;
    _scheduled_event.minuite_of_day = minuite_of_day;
}

/**************************************************
 * イベントを実行する
 **************************************************/
static void executeScheduledEvent(Time *time, SCHEDULED_LIGHT_EVENT *scheduled_event)
{
    if (scheduled_event->id == UN_USED) {
        return;
    }
    if (scheduled_event->minuite_of_day != time->minuite_of_day) {
        return;
    }

	if (scheduled_event->event == TURN_OFF) {
    	LightController_TurnOff(scheduled_event->id);
	} else if (scheduled_event->event == TURN_ON) {
		LightController_TurnOn(scheduled_event->id);
	}
}

/* ---------------------------------------- */
/**************************************************
 * コンストラクタ
 **************************************************/
void LightScheduler_Create(void)
{
	scheduleEvent(UN_USED, NONE, 0, NOTHING);
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

	executeScheduledEvent(&time, &_scheduled_event);
}

/**************************************************
 * ONイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, DAY day, long minuite_of_day)
{
	scheduleEvent(id, day, minuite_of_day, TURN_ON);
}

/**************************************************
 * OFFイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, DAY day, long minuite_of_day)
{
	scheduleEvent(id, day, minuite_of_day, TURN_OFF);
}

