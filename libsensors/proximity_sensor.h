
/**
 *Added for Morrison 02/09 tnbq73 
 *Feature ID 964  : Proximity Sensor  
 **/

#ifndef _HARDWARE_VIBRATOR_H
#define _HARDWARE_VIBRATOR_H

#if __cplusplus
extern "C" {
#endif

/**
 * Turn on proximity sensor
 *
 * @return 0 if successful, -1 if error
 */
int proximity_on();

/**
 * Turn off proximity
 *
 * @return 0 if successful, -1 if error
 */
int proximity_off();

/**
 * Enable touchpad
 *
 * @return 0 if successful, -1 if error
 */
int touchpad_enable();

/**
 * Disable touchpad
 *
 * @return 0 if successful, -1 if error
 */
int touchpad_disable(); 


#if __cplusplus
}  // extern "C"
#endif

#endif  // _HARDWARE_VIBRATOR_H
