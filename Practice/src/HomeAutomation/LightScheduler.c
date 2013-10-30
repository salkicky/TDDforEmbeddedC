#include "LightScheduler.h"
#include "LightController.h"

/* ======================================================================== */
const int UN_USED = -1;

enum EVENT {
	NOTHING, TURN_ON, TURN_OFF
};

typedef enum EVENT EVENT;

typedef struct {
    int     id;
	EVENT	event;
    DAY     day;
    int		minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

/* ======================================================================== */
static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ======================================================================== */
/**************************************************
 * �C�x���g��o�^����
 **************************************************/
static void _scheduleEvent(int id, DAY day, int minuite_of_day, EVENT event)
{
	_scheduled_event.id = id;
    _scheduled_event.day = day;
    _scheduled_event.event = event;
    _scheduled_event.minuite_of_day = minuite_of_day;
}

/**************************************************
 * ���C�g�𑀍삷��
 **************************************************/
static void _operateLight(SCHEDULED_LIGHT_EVENT *light_event)
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
 * �����`�F�b�N
 **************************************************/
static int _isItsDay(DAY today, DAY reaction_day)
{
    if (reaction_day == EVERYDAY) {
        return 1;
    }
    
    if ((reaction_day == WEEKEND) && (today == SATURDAY)) {
        return 1;
    }

    if ((reaction_day == WEEKEND) && (today == SUNDAY)) {
        return 1;
    }

    if (today == reaction_day) {
        return 1;
    }

    return 0;
}

/**************************************************
 * �C�x���g�����s����
 **************************************************/
static void _executeScheduledEvent(Time *time, SCHEDULED_LIGHT_EVENT *light_event)
{
    if (light_event->id == UN_USED) {
        return;
    }

    if (_isItsDay(time->day_of_week, light_event->day) == 0) {
        return;
    }

    if (light_event->minuite_of_day != time->minuite_of_day) {
        return;
    }

	_operateLight(light_event);
}

/* ======================================================================== */
/**************************************************
 * �R���X�g���N�^
 **************************************************/
void LightScheduler_Create(void)
{
    /* set wakeup calljack */
    TimeService_setPeriodicAlarmInSeconds(60, LightScheduler_wakeup);
    /* initialize event */
	_scheduleEvent(UN_USED, NONE, 0, NOTHING);
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

	_executeScheduledEvent(&time, &_scheduled_event);
}

/**************************************************
 * ON�C�x���g�̃X�P�W���[����o�^����
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, DAY day, int minuite_of_day)
{
	_scheduleEvent(id, day, minuite_of_day, TURN_ON);
}

/**************************************************
 * OFF�C�x���g�̃X�P�W���[����o�^����
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, DAY day, int minuite_of_day)
{
	_scheduleEvent(id, day, minuite_of_day, TURN_OFF);
}

