/*
 * PID CONTROL
 * Automatically adjusts the speed of left and right tire
 * to make sure that the droid is always centered while running.
 * Possible Algorithm:
 *  1. Check the current distance from both left and right wall
 *  2. Calculate the offset since the last time we measured the distance
 *      propagation = left - right
 *      derivative = (prop - oldProp)/(currentTime - oldTime)
 *  3. Reset speed to default
 *  4. Check if there is a opening on the left or right
 *  5. Modify speed based on whether it's close to either wall or not
 */
void pidHandler()
{

}
