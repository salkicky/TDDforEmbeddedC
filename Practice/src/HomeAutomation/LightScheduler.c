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
    int		minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

/* ---------------------------------------- */
static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ---------------------------------------- */
/**************************************************
 * イベントを登録する
 **************************************************/
static void scheduleEvent(int id, DAY day, int minuite_of_day, EVENT event)
{
	_scheduled_event.id = id;
    _scheduled_event.event = event;
    _scheduled_event.minuite_of_day = minuite_of_day;
}

/**************************************************
 * ライトを操作する
 **************************************************/
static void controlLight(SCHEDULED_LIGHT_EVENT *light_event)
{
	switch(light_event->event) {
	case TURN_ON:
		LightController_TurnOn(light_event->id);
		break;
	case TURN_OFF:
		LightController_TurnOff(light_event->id);
		break;
	default:
		break;
	}
}

/**************************************************
 * イベントを実行する
 **************************************************/
static void executeScheduledEvent(Time *time, SCHEDULED_LIGHT_EVENT *light_event)
{
    if (light_event->id == UN_USED) {
        return;
    }
    if (light_event->minuite_of_day != time->minuite_of_day) {
        return;
    }

	controlLight(light_event);
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
void LightScheduler_scheduleTurnOn(int id, DAY day, int minuite_of_day)
{
	scheduleEvent(id, day, minuite_of_day, TURN_ON);
}

/**************************************************
 * OFFイベントのスケジュールを登録する
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, DAY day, int minuite_of_day)
{
	scheduleEvent(id, day, minuite_of_day, TURN_OFF);
}

