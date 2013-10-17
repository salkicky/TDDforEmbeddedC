#ifndef D_LightController_H
#define D_LightController_H

/**********************************************************
 *
 * LightController is responsible for ...
 *
 **********************************************************/

void LightController_Create(void);
void LightController_Destroy(void);

void LightController_TurnOn(int id);
void LightController_TurnOff(int id);

#endif  /* D_FakeLightController_H */
