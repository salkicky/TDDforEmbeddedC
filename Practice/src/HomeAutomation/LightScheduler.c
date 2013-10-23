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
 * �C�x���g��o�^����
 **************************************************/
static void scheduleEvent(int id, DAY day, int minuite_of_day, EVENT event)
{
	_scheduled_event.id = id;
    _scheduled_event.event = event;
    _scheduled_event.minuite_of_day = minuite_of_day;
}

/**************************************************
 * ���C�g�𑀍삷��
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
 * �C�x���g�����s����
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
 * �R���X�g���N�^
 **************************************************/
void LightScheduler_Create(void)
{
	scheduleEvent(UN_USED, NONE, 0, NOTHING);
}

/**************************************************
 * �f�X�g���N�^
 **************************************************/
void LightScheduler_Destroy(void)
{
}

/**************************************************
 * �������s�֐�
 **************************************************/
void LightScheduler_wakeup(void)
{
    Time time;

    TimeService_getTime(&time);

	executeScheduledEvent(&time, &_scheduled_event);
}

/**************************************************
 * ON�C�x���g�̃X�P�W���[����o�^����
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, DAY day, int minuite_of_day)
{
	scheduleEvent(id, day, minuite_of_day, TURN_ON);
}

/**************************************************
 * OFF�C�x���g�̃X�P�W���[����o�^����
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, DAY day, int minuite_of_day)
{
	scheduleEvent(id, day, minuite_of_day, TURN_OFF);
}

