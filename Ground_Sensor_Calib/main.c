#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include "elisa3-lib.h"
#include "terminal.h"
#include "input.h"


// received from robot
int robotAddress[1];
unsigned int robProx[8] = {0};
unsigned int robProxAmb[8] = {0};
unsigned int robGround[4] = {0};
unsigned int robGroundAmb[4] = {0};
unsigned int robBattLevel = 0;
unsigned int robBattPercent = 0;
signed int robAccX=0, robAccY=0, robAccZ=0;
int robVertAngle = 0;
unsigned char robSelector=0, robTvRemote=0, robFlagsRx=0;
signed long int robLeftMotSteps=0, robRightMotSteps=0;
signed int robTheta=0, robXPos=0, robYPos=0;
double linkQualityToRob=0;

// sent to robot
char robLSpeed=0, robRSpeed=0;
char robRedLed=0, robGreenLed=0, robBlueLed=0;
unsigned char robFlagsTx = 0x00;
unsigned char obstacleAvoid=0, cliffAvoid=0, irOn=0, tvOn=0, sleepOn=0, smallLedsOn=0;

// various
unsigned int delayCounter=0;
char current_speed=0;
unsigned char exitProg=0;

int main(int argc, char *argv[]) {

    //printf("\r\nInsert the robot address: ");
    //scanf("%d", &robotAddress[0]);

    robotAddress[0] = 3485;
    //robotAddress[1] = 3522;
    initTerminal();

    // init the communication with the robots; set the addresses and number of the robots to control
    startCommunication(robotAddress,1);

    FILE *fp;
    fp = fopen("test.txt", "w+");
    fprintf(fp,"GROUND_White\r\n");
    fprintf(fp, "ground0\t ground1\t ground2\t ground3\r\n");

    //while(!exitProg) {
    for (int i =0; i< 50; i++){
        handleKeyboardInput();

        // set new data for the robot (given from the user through the keyboard)
        setLeftSpeed(robotAddress[0], robLSpeed);
        setRightSpeed(robotAddress[0], robRSpeed);
        setRed(robotAddress[0], robRedLed);
        setBlue(robotAddress[0], robBlueLed);
        setGreen(robotAddress[0], robGreenLed);

        /*
        setLeftSpeed(robotAddress[1], robLSpeed);
        setRightSpeed(robotAddress[1], robRSpeed);
        setRed(robotAddress[1], robRedLed);
        setBlue(robotAddress[1], robBlueLed);
        setGreen(robotAddress[1], robGreenLed);
        */

        // update sensors data received from the robot
        getAllGround(robotAddress[0], robGround);

        fprintf( fp, "%4d\t %4d\t\t %4d\t\t %4d\t\n\r", robGround[0], robGround[1], robGround[2], robGround[3]);

    }

    //fclose(fp);
    stopCommunication();
	closeTerminal();

	return 0;

}

