#include "LightScheduler.h"
#include "LightController.h"

enum EVENT {
	NOTHING, TURN_ON, TURN_OFF
};

const int UN_USED = -1;

typedef struct {
    int id;
	enum EVENT	event;
    enum DAY	minuite_of_day;
} SCHEDULED_LIGHT_EVENT;

static SCHEDULED_LIGHT_EVENT _scheduled_event;

/* ---------------------------------------- */

/**************************************************
 * �R���X�g���N�^
 **************************************************/
void LightScheduler_Create(void)
{
    _scheduled_event.id = UN_USED;
    _scheduled_event.event = NOTHING;
    _scheduled_event.minuite_of_day = NONE;
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
 * ON�C�x���g�̃X�P�W���[����o�^����
 **************************************************/
void LightScheduler_scheduleTurnOn(int id, enum DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.event = TURN_ON;
    _scheduled_event.minuite_of_day = minuite;
}

/**************************************************
 * OFF�C�x���g�̃X�P�W���[����o�^����
 **************************************************/
void LightScheduler_scheduleTurnOff(int id, enum DAY day, long minuite)
{
    _scheduled_event.id = id;
    _scheduled_event.event = TURN_OFF;
    _scheduled_event.minuite_of_day = minuite;
}
