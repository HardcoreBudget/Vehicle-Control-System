#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum MainMenuChoices{
	On = 1,
	Reset,
	Quit,
};

enum SensorSetMenuChoices{
	Off = 1,
	Traffic,
	RoomTemp,
	EngineTemperature,
};

char state[2][4] = {"OFF", "ON"};
char engineState = 0;
char temperatureState = 0;
char acState = 0;
unsigned char vehicleSpeed = 0;
int roomTemp = 0;
int engineTemp = 0;
int mainMenuChoice = 0;
char SensorsSetMenuChoice = 0;

void MainMenu(char errorFlag);
void SensorsSetMenu(char errorFlag);
void DisplaySystemState();
void TrafficLights();
void RoomTempControl();
void EngineTempControl();

void main(){

	char currentMenu = 0;
	char menuErrorFlag = 0;
	char restartFlag = 0;
	while(1){
		if(currentMenu == 0){
			MainMenu(menuErrorFlag);
			printf("Enter your choice: ");
			scanf("%d", &mainMenuChoice);
		}
		menuErrorFlag = 0;
		switch(mainMenuChoice){
			case On:
				
				currentMenu = 1;
				do{
					engineState = 1;
					DisplaySystemState();
					SensorsSetMenu(menuErrorFlag);
					printf("Enter your choice: ");
					scanf("%d", &SensorsSetMenuChoice);
					menuErrorFlag = 0;
					switch(SensorsSetMenuChoice){
						case Traffic: TrafficLights(); break;
						case RoomTemp: RoomTempControl(); break;
						case EngineTemperature: EngineTempControl();  break;
						case Off: restartFlag = 1; engineState = 0; break;
						default: menuErrorFlag = 1; continue;
					}	
					
				}while(menuErrorFlag);
				
				if(restartFlag) {
					currentMenu = 0; 
					restartFlag = 0; 
					DisplaySystemState();
					continue; 
				}
				break;
				
			case Reset:
				DisplaySystemState();
				continue;
				
			case Quit: return;
			
			default: menuErrorFlag = 1; continue;
		}
	}
}

void MainMenu(char errorFlag){
	system("cls");
	if(errorFlag){
		printf("*****************************\n");
		printf("Error! Please try again.\n");
		printf("*****************************\n");
	}
	printf("\t-------Main Menu-------\n");
	printf("\t1.Turn on vehicle Engine\n"\
	"\t2.Turn off vehicle Engine\n"\
	"\t3.Quit the system\n");
	printf("--------------------------------------------------------------\n");
}

void SensorsSetMenu(char errorFlag){
	system("cls");
	if(errorFlag){
		printf("*****************************\n");
		printf("Error! Please try again.\n");
		printf("*****************************\n");
	}
	printf("\t-------Sensors Set Menu-------\n");
	printf("\t1.Turn off the Engine\n"\
	"\t2.Set the traffic light color\n"\
	"\t3.Set the room temperature\n"\
	"\t4.Set the engine temperature\n");
	printf("--------------------------------------------------------------\n");
}

void DisplaySystemState(){
	system("cls");
	printf("\t-------System State-------\n");
	printf("\tEngine State: %s\n"\
	"\tAC: %s\n"\
	"\tVehicle Speed: %d\n"\
	"\tRoom Temperature: %dF\n"\
	"\tEngine Temperature Controller: %s\n"\
	"\tEngine Temperature: %dF\n"\
	, state[engineState], state[acState], vehicleSpeed, roomTemp, state[temperatureState], engineTemp);
	printf("--------------------------------------------------------------\n");
	printf("Press any key to continue...");
	getch();
}

void TrafficLights(){
	char trafficStatus;
	system("cls");
	printf("Please enter the traffic light status (G, O, R): ");
	scanf(" %c", &trafficStatus);
	switch(trafficStatus){
		case 'G':
			vehicleSpeed =100;
			break;
		case 'O':
			vehicleSpeed =30;
			acState = 1;
			roomTemp = roomTemp * (5/4) + 1;
			engineState = 1;
			engineTemp = engineTemp * (5/4) + 1;
			break;
		case 'R':
			vehicleSpeed =0;
			break;
		default: 
			printf("Wrong status use (G, O, R) next time\n");
			printf("Press any key to continue...");
			getch();
	}
}

void RoomTempControl(){
	system("cls");
	printf("Please enter the room temperature: ");
	scanf("%d", &roomTemp);
	
	if(roomTemp < 10){
		acState = 1;
		roomTemp = 20;
	}
	else if(roomTemp > 30){
		acState = 1;
		roomTemp = 20;
	}
	else{
		acState = 0;
	}
}

void EngineTempControl(){
	system("cls");
	printf("Please enter the engine temperature: ");
	scanf("%d", &engineTemp);
	
	if(engineTemp < 100){
		temperatureState = 1;
		engineTemp = 125;
	}
	else if(engineTemp > 150){
		temperatureState = 1;
		engineTemp = 125;
	}
	else{
		temperatureState = 0;
	}
}