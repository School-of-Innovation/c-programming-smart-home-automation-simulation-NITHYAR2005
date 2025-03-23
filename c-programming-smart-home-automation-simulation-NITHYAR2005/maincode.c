/*
 * 🚨 WARNING: CHALLENGE MODE ACTIVATED 🚨
 * 
 * 1️⃣ Sit back, take a deep breath, and **THINK**.
 * 2️⃣ For the next **10 minutes**, avoid using **Gen AI, ChatGPT, or any shortcuts**.
 * 3️⃣ Trust your **brain**—you’re smarter than you think!
 * 4️⃣ Consider yourself a **LOSER** if you cheat. Seriously, promise yourself you won't. 😤
 * 5️⃣ If you solve it on your own, **you WIN** and level up as a true programmer and come and meet me ! 
 * 
 * 
 * 💡 Remember: The best coders aren’t the ones who copy-paste. They are the ones who **struggle, think, fail, and then succeed.** 
 *    
 * Now, write your code! You got this! 💪🔥
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROOMS 5 // max number of rooms

// Function prototypes
void initializeSystem(int lights[], int temp[], int motion[], int locks[], int ROOMS);
void displayMenu();
void Control_Lights(int lights[], int ROOMS);
void Read_Temperature(int temp[], int ROOMS);
void Detect_Motion(int motion[], int locks[], int ROOMS);
void Security_System(int locks[], int ROOMS);
void Analyze_House_Status(int lights[], int temp[], int motion[], int locks[], int ROOMS);
void AutoLock(int motion[], int locks[], int ROOMS);
void EnergySavingMode(int lights[], int ROOMS);

int noMotionCount = 0;

int main() {
    srand(time(0)); //  random motion detection
    int ROOMS;
    printf("ENTER THE NUMBER OF ROOMS: ");
    scanf("%d", &ROOMS);
    if (ROOMS > MAX_ROOMS) {
        printf("Rooms not available! Maximum allowed is %d.\n", MAX_ROOMS);
        return 1;
    }
    
    int lights[ROOMS], temp[ROOMS], motion[ROOMS], locks[ROOMS], choice;
    initializeSystem(lights, temp, motion, locks, ROOMS);
    
    do {
        printf("\n===== Smart Home Menu =====\n");
        printf("1. Control_Lights \n");
        printf("2. Read_Temperature\n");
        printf("3. Detect_Motion \n");
        printf("4. Security_System\n");
        printf("5. Analyze_House_Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: Control_Lights(lights, ROOMS); break;
            case 2: Read_Temperature(temp, ROOMS); break;
            case 3: Detect_Motion(motion, locks, ROOMS); break;
            case 4: Security_System(locks, ROOMS); break;
            case 5: Analyze_House_Status(lights, temp, motion, locks, ROOMS); EnergySavingMode(lights, ROOMS); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}

void initializeSystem(int lights[], int temp[], int motion[], int locks[], int ROOMS) {
    printf("Initializing system...\n");
    for (int i = 0; i < ROOMS; i++) {
        lights[i] = 0;
        temp[i] = 22 + (i + 1);
        motion[i] = rand() % 2;
        locks[i] = 1;
    }
}

void Control_Lights(int lights[], int ROOMS) {
    int room;
    printf("Enter room number to switch on light (1-%d): ", ROOMS);
    scanf("%d", &room);
    if (room < 1 || room > ROOMS) {
        printf("Invalid room number!\n");
        return;
    }
    lights[room - 1] = !lights[room - 1];
    printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
}

void Read_Temperature(int temp[], int ROOMS) {
    int room;
    printf("Enter room number to check temperature (1-%d): ", ROOMS);
    scanf("%d", &room);
    if (room < 1 || room > ROOMS) {
        printf("Invalid room number!\n");
        return;
    }
    printf("Temperature in Room %d: %d°C\n", room, temp[room - 1]);
    if (temp[room - 1] > 30) {
        printf("WARNING: Temperature in Room %d is above safe levels!\n", room);
    }
}

void Detect_Motion(int motion[], int locks[], int ROOMS) {
    int allNoMotion = 1;
    printf("\nMotion Sensor Status:\n");
    for (int i = 0; i < ROOMS; i++) {
        motion[i] = rand() % 2; // Randomly set motion status
        printf("- Room %d: %s\n", i + 1, motion[i] ? "Motion Detected" : "No Motion");
        if (motion[i]) {
            allNoMotion = 0;
        }
    }
    if (allNoMotion) {
        AutoLock(motion, locks, ROOMS);
    }
}

void Security_System(int locks[], int rooms) {
    int room;
    printf("Enter room number to lock/unlock (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number!\n");
        return;
    }
    locks[room - 1] = !locks[room - 1];
    printf("Security lock in Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
}

void Analyze_House_Status(int lights[], int temp[], int motion[], int locks[], int ROOMS) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < ROOMS; i++) {
        printf("- Room %d: Light %s, Temp %d°C, %s, %s\n",
               i + 1,
               lights[i] ? "ON" : "OFF",
               temp[i],
               motion[i] ? "Motion Detected" : "No Motion",
               locks[i] ? "Locked" : "Unlocked");
    }
}

void AutoLock(int motion[], int locks[], int ROOMS) {
    printf("Auto-Lock: All rooms locked due to inactivity.\n");
    for (int i = 0; i < ROOMS; i++) {
        locks[i] = 1;
    }
}

void EnergySavingMode(int lights[], int ROOMS) {
    int allOn = 1;
    for (int i = 0; i < ROOMS; i++) {
        if (!lights[i]) {
            allOn = 0;
            break;
        }
    }
    if (allOn) {
        printf("Energy Saving Mode: All lights are ON for too long. Consider turning them OFF.\n");
    }
}