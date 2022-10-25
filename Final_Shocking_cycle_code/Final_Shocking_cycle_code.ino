/*********
  Amirarsham Farahmand
  2022-OCT-25
  Honours project setup
  Shocking cycle


Explanation: 

  Cycle goes as follow:
    **When All fishes are in the chamber plug the system to power**
    
    Click the restart button on the Arduino
    
    Display will show a the experiment "Code" for 5 minutes(Habituation)
    
    Record "Experiment Code" for blind reveal

    Shocks will start after 5 minute based on the Shock arrays
    
    Display will update as experiment moves forward

    After 1 hour 55 minute hours of shocking cycle, display will prompt start removing fishes.

    Cycle continues for another 5 minute and at the end display will show cycle ended.

  Tail cutting:
    Have 4 1:5 solution ready on ice
    Have 4 blades
    Have 4 cutting plates

    Remove 3 fish in a row Repeat for all columns set all on ice

    Move 3 fishes from one row to the corresponding cutting plate for tail removal

    Transfer 3 heads to the corresponding 1.7 tube


//ABRVs

//IG = Isolate group
//SG = Social group
//B = Biological Replicate
//IG1A = Isolate group 1 Row A
//IG1B = Isolate group 1 Row B
//IG2A = Isolate group 2 Row A
//IG2B = Isolate group 2 Row B

//SG1C = Isolate group 1 Row C
//SG1D = Isolate group 1 Row D
//SG2C = Isolate group 2 Row C
//SG2D = Isolate group 2 Row D

//Date 2022-10-25 = 221025
//Time of grouping = Time based 24+-1
//Experiment Day = exp. Date
    
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

//Generating double blind variables

int rowa[]={11, 13, 17, 19};
int rowb[]={ 23, 29, 31, 37};
int rowc[]={41, 43, 47, 53};
int rowd[]={59, 61, 67, 71};
int randomiser[]={103, 107, 109, 113, 127, 131, 137, 139, 149, 151};// for the sake of making the numbers hard to comprehend
int long exprows=1;


//Setting time and variables of the cycle 

long period=7500000; //time in each full cycle in milli seconds 2 hours and 5 minutes
long cycle=0;        //shocking cycle
int stime=0;        //Time passed from the begining of shocking cycle
long ftime=0;        //Time passed from pushing the RESET button
int voltage=3;      //CHOOSE THE VOLTAGE FOR THE SHOCKS
int volta=153; // Calculation of the voltage for the program
long resting[]={300000, 10534, 10087, 9763, 10147, 9849, 9450, 9796, 13223, 11114, 10716, 11106, 11205, 9792, 9904, 10689, 9965, 10206, 9371, 10512, 8025, 9836, 11084, 11478, 11358, 8874, 10168, 8779, 10993, 8795, 9217, 9990, 9379, 9598, 8835, 10601, 7991, 8593, 11384, 9411, 10653, 10448, 11179, 9458, 10018, 10264, 10497, 9170, 8850, 11394, 9274, 10769, 8459, 9589, 11573, 9703, 8063, 9829, 8904, 9300, 9928, 9029, 7001, 8076, 10161, 8557, 8901, 11029, 10953, 10361, 9733, 10229, 9907, 11148, 9846, 11132, 9151, 9978, 10348, 10647, 9983, 8735, 10379, 11661, 8285, 10565, 10286, 9814, 10794, 11346, 10541, 10494, 9911, 10276, 9885, 10735, 7678, 10866, 9865, 10758, 11258, 9807, 10987, 8778, 11495, 11813, 9410, 10948, 11498, 11066, 10648, 9223, 11659, 9682, 10548, 11160, 9386, 10458, 10714, 9008, 9353, 9190, 10942, 9724, 10145, 10162, 8540, 10669, 9405, 10416, 11125, 10529, 11021, 10718, 10556, 7989, 10271, 9866, 9090, 10560, 10117, 10453, 11247, 10324, 10604, 7346, 10575, 8531, 10031, 10747, 9259, 9564, 10039, 12872, 9617, 11140, 9083, 9834, 9579, 9027, 8806, 10534, 9751, 9861, 11206, 9902, 11185, 9640, 9843, 11836, 9895, 8690, 8668, 9899, 8021, 12787, 10169, 9099, 8628, 10961, 7800, 11052, 10791, 8390, 10793, 10048, 9424, 10776, 8665, 11113, 11232, 8478, 10497, 11204, 11603, 11369, 10200, 6506, 11703, 11138, 9643, 8871, 9793, 9317, 10024, 8067, 10119, 10753, 10255, 9352, 9413, 9232, 8493, 8004, 7263, 9508, 8813, 8766, 10400, 10823, 6823, 10211, 11472, 11051, 11011, 9513, 9480, 11534, 10117, 9740, 11529, 10334, 9487, 9730, 10250, 10051, 9672, 9760, 9685, 10191, 9883, 9078, 12442, 10334, 9313, 9241, 10443, 10603, 8975, 9642, 10345, 9251, 7975, 9581, 9908, 9458, 12329, 7873, 8359, 9538, 10220, 10127, 8730, 9214, 9830, 8888, 11117, 9620, 10208, 8866, 9600, 10003, 8787, 9403, 10133, 11143, 10616, 10937, 11096, 10987, 10414, 9497, 9236, 10715, 9802, 9972, 8387, 11214, 9232, 10040, 11180, 10486, 9887, 9683, 9959, 9459, 9166, 10843, 9273, 10893, 12037, 10573, 9199, 9203, 11265, 9471, 10126, 10043, 10007, 9938, 9859, 12009, 9569, 8890, 11262, 10678, 9068, 11090, 8057, 9705, 9164, 11379, 10851, 11455, 12223, 8597, 9879, 10804, 9546, 10276, 9201, 9265, 8789, 10004, 9798, 10542, 7562, 8832, 10977, 9110, 9582, 9619, 9700, 10107, 9822, 10456, 10538, 11105, 10478, 10300, 9580, 11535, 9401, 10246, 8998, 11094, 10860, 8809, 10201, 9111, 10770, 9376, 8987, 9583, 10619, 10043, 9685, 9493, 9947, 12565, 9753, 9034, 10756, 9389, 9852, 9884, 10703, 9127, 10080, 10022, 11476, 10441, 10761, 9579, 10544, 10154, 9728, 9902, 12532, 10085, 8821, 9126, 10615, 12281, 9150, 10175, 10292, 9474, 10229, 8930, 10476, 7724, 12582, 10980, 10106, 8244, 9549, 9634, 10858, 9699, 12013, 11298, 10693, 10129, 9119, 9627, 10205, 12655, 8551, 8619, 9769, 10613, 10388, 10432, 8993, 11321, 11330, 9875, 10103, 9598, 8986, 10332, 8928, 9737, 10890, 9872, 10182, 10625, 10223, 10357, 10309, 10800, 11145, 8500, 10286, 9137, 9761, 10460, 9206, 10710, 10768, 11282, 10474, 11756, 9887, 9673, 11177, 9106, 10192, 11345, 11387, 10553, 7999, 10936, 11407, 11025, 9138, 9065, 8729, 10579, 9781, 9674, 11981, 9334, 9242, 10118, 10260, 10667, 9211, 11947, 11157, 12525, 10232, 9582, 10437, 9027, 10713, 9259, 10741, 9516, 9368, 8987, 9482, 9981, 11218, 10757, 10286, 12086, 10380, 9357, 9721, 7901, 9414, 9728, 10811, 12198, 8772, 8395, 9784, 10713, 9789, 8002, 10525, 8460, 8634, 9542, 10229, 9575, 9817, 9403, 9873, 10696, 10065, 10113, 9219, 10452, 9136, 9032, 11386, 10131, 9242, 11358, 9204, 9669, 9070, 8936, 10094, 7935, 9899, 9621, 11288, 9677, 10807, 9521, 10987, 9955, 10551, 9553, 8569, 9794, 10204, 9062, 10119, 9413, 12192, 8821, 9714, 12099, 10948, 10283, 8687, 9356, 10649, 11727, 10768, 11434, 11584, 10384, 11046, 11840, 9045, 9169, 10962, 9577, 10385, 7901, 11290, 11659, 9747, 9140, 10515, 9948, 8706, 9660, 7665, 10684, 11095, 11025, 10697, 9732, 10766, 9319, 9698, 10249, 10164, 10228, 7905, 9890, 8658, 7817, 9286, 8071, 8018, 9290, 10603, 10002, 9344, 10731, 10971, 9548, 8545, 11466, 12418, 9778, 10473, 8531, 10472, 9770, 10223, 9924, 8579, 10645, 9730, 9531, 9957, 10414, 9351, 9999, 10256, 8438, 8564, 10595, 8590, 9862, 10584, 10111, 10854, 10451, 10113, 10500, 11182, 9717, 10090, 8926, 8524, 11589, 9021, 9550, 9086, 9418, 10487, 8610, 9233, 10610, 10284, 9479, 9846, 9824, 11251, 9799, 9377, 8782, 9082, 10419, 10971, 8875, 10128, 9913, 9163, 9465, 12685, 10333, 9336, 8998, 10566, 9686, 10640, 8100, 9484, 8831, 10468, 10468, 9461, 8860, 10104, 11495, 10371, 10662, 10788, 9978, 8161, 9024, 11247, 11019, 11396, 10542, 10124, 8555, 9794, 8176, 11229, 8433, 9554, 8388, 11253, 11017, 10917, 10282, 10821, 11320, 7943, 10277, 9332, 11067, 10567, 8251, 10482, 8417, 10944, 10037, 10831, 9204, 8874, 10082, 10428, 9152, 10272, 9899, 9812, 7860, 9112, 10770, 11072, 9096, 8178, 10764, 11374, 11152, 10390, 11737, 11230, 10503, 10057, 8788, 8631, 9205, 9166, 10624, 11839, 9964, 10811};
int shocking[]={0, 87, 98, 100, 92, 118, 87, 95, 102, 104, 111, 117, 109, 110, 89, 96, 105, 103, 94, 86, 123, 98, 100, 106, 92, 94, 98, 89, 107, 93, 90, 118, 107, 103, 94, 96, 104, 88, 99, 97, 79, 95, 94, 93, 108, 94, 109, 81, 91, 103, 99, 111, 83, 112, 91, 103, 106, 114, 114, 103, 109, 95, 106, 89, 92, 96, 105, 101, 102, 99, 83, 117, 84, 92, 97, 112, 92, 110, 105, 112, 84, 106, 90, 96, 98, 86, 104, 102, 101, 85, 115, 102, 94, 114, 111, 98, 98, 114, 105, 105, 104, 91, 98, 117, 108, 110, 80, 94, 108, 114, 103, 111, 96, 116, 101, 101, 95, 104, 113, 105, 80, 101, 98, 106, 102, 93, 104, 103, 113, 75, 113, 96, 91, 85, 116, 98, 95, 113, 111, 103, 99, 106, 107, 88, 116, 106, 103, 106, 115, 104, 111, 96, 91, 97, 118, 100, 100, 95, 93, 89, 110, 98, 103, 98, 101, 105, 102, 80, 113, 109, 79, 97, 85, 109, 108, 113, 81, 114, 99, 89, 85, 78, 100, 106, 89, 101, 103, 95, 105, 93, 103, 92, 104, 81, 103, 96, 88, 96, 107, 95, 87, 105, 90, 108, 94, 101, 119, 105, 99, 124, 109, 101, 88, 110, 101, 101, 94, 92, 89, 110, 100, 90, 96, 97, 86, 118, 96, 98, 89, 93, 105, 102, 112, 102, 89, 75, 102, 109, 88, 97, 107, 115, 96, 91, 109, 107, 98, 119, 110, 90, 94, 104, 103, 97, 109, 84, 100, 104, 100, 96, 107, 99, 107, 86, 84, 106, 110, 92, 80, 98, 102, 96, 93, 94, 86, 110, 90, 95, 98, 107, 99, 109, 97, 84, 113, 106, 99, 84, 84, 97, 94, 100, 113, 100, 89, 101, 109, 100, 102, 112, 103, 85, 112, 111, 96, 110, 100, 94, 101, 92, 94, 99, 88, 113, 116, 92, 106, 112, 100, 104, 92, 94, 93, 94, 107, 103, 108, 107, 89, 97, 99, 92, 99, 98, 94, 99, 109, 92, 97, 90, 109, 76, 95, 113, 101, 110, 110, 93, 99, 112, 112, 99, 105, 84, 102, 102, 84, 107, 89, 89, 97, 79, 112, 94, 104, 100, 110, 107, 105, 104, 108, 86, 94, 116, 92, 98, 109, 101, 106, 103, 88, 105, 99, 92, 92, 93, 104, 93, 84, 86, 91, 96, 85, 103, 90, 95, 105, 97, 96, 102, 99, 89, 94, 85, 106, 105, 100, 87, 98, 117, 97, 100, 96, 110, 95, 109, 99, 90, 86, 94, 98, 97, 102, 104, 87, 88, 84, 95, 124, 102, 84, 96, 95, 98, 120, 100, 89, 109, 96, 102, 103, 104, 97, 118, 113, 101, 115, 91, 98, 105, 110, 100, 87, 94, 104, 104, 103, 97, 96, 82, 103, 104, 116, 107, 97, 76, 96, 91, 107, 119, 102, 95, 104, 109, 87, 101, 95, 99, 112, 118, 95, 97, 89, 106, 93, 87, 108, 89, 111, 120, 94, 91, 94, 112, 100, 82, 89, 94, 99, 94, 97, 93, 99, 97, 95, 87, 85, 88, 107, 95, 85, 109, 112, 93, 96, 81, 107, 107, 108, 92, 86, 91, 103, 102, 91, 120, 125, 81, 100, 108, 96, 98, 74, 87, 102, 91, 99, 102, 91, 88, 100, 90, 90, 106, 105, 80, 89, 106, 107, 97, 113, 95, 107, 102, 94, 104, 96, 117, 94, 102, 92, 107, 99, 113, 102, 92, 94, 104, 100, 92, 107, 98, 91, 109, 97, 106, 85, 87, 84, 112, 117, 85, 96, 102, 98, 102, 99, 100, 111, 92, 103, 114, 99, 97, 102, 106, 113, 103, 104, 102, 87, 96, 110, 107, 90, 92, 90, 99, 98, 85, 84, 95, 104, 108, 99, 101, 95, 102, 89, 111, 111, 95, 85, 92, 94, 108, 118, 113, 86, 109, 114, 110, 89, 100, 89, 101, 100, 104, 88, 94, 112, 115, 90, 94, 89, 112, 100, 98, 99, 113, 108, 123, 84, 98, 119, 85, 92, 106, 85, 97, 88, 85, 94, 96, 99, 109, 104, 101, 102, 116, 104, 98, 113, 101, 104, 98, 96, 100, 95, 105, 103, 98, 102, 78, 95, 93, 94, 93, 98, 86, 109, 116, 91, 108, 104, 89, 100, 109, 100, 98, 112, 91, 83, 91, 105, 85, 93, 112, 98, 86, 104, 101, 109, 96, 85, 93, 108, 92, 96, 97, 103, 98, 110, 90, 123, 97, 96, 111, 102, 99, 95, 91, 94, 115, 88, 85, 80, 90, 116, 100, 99, 108, 97, 105, 90, 107, 95, 115, 102, 105, 97};

//300000, 
//shock_isolate=1 means row A in test chamber got shock
//shock_isolate=2 means row B in test chamber got shock
//shock_social=1 means row C in test chamber got shock
//shock_social=2 means row D in test chamber got shock

int shock_isolate=0;
int shock_social=0;

//________
void setup() {
  //Serial monitor only for seeing the progress when the system is connected to a laptop.
  Serial.begin(115200);
  randomSeed(analogRead(0));//generate real random
  //Choosing the Rows for stimuli delivery
  //pwm 2-row A
  //pwm 3-row B
  //pwm 4-row C
  //pwm 5-row D
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);//for the led
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Experiment will start in 30 seconds. Press the Reset button to restart the experiment.");
  display.display(); 
  delay(30000);
}

void loop() {
  while(ftime<(period)){
    
    if(cycle==0){//Double blind
      shock_social=random(1,3);
      shock_isolate=random(1,3);
      Serial.println(shock_social);
      Serial.println(shock_isolate);

      exprows=1*randomiser[random(10)];
      
      if(shock_isolate==1){// blinding isolate in row A getting shock
        exprows=exprows*rowa[random(4)];
      }
      if(shock_isolate==2){// blinding isolate in row B getting shock
        exprows=exprows*rowb[random(4)];
      }
      if(shock_social==1){// blinding isolate in row C getting shock
        exprows=exprows*rowc[random(4)];
      }
      if(shock_social==2){// blinding isolate in row D getting shock
        exprows=exprows*rowd[random(4)];
      }
      
      Serial.println("Shocking is happening in row");//Will only  be visible if he system is connected to a laptop
      Serial.println(shock_isolate);//Will only  be visible if he system is connected to a laptop
      Serial.println(shock_social+2);//Will only  be visible if he system is connected to a laptop
      Serial.println("Save This Code: ");//Will only  be visible if he system is connected to a laptop
      Serial.println(exprows);//Will only  be visible if he system is connected to a laptop
      
      display.clearDisplay();
      display.setCursor(0, 10);
      display.println("Experiment Code is ");
      display.println(exprows);
      display.println("Save This Code.");
      display.println("Remaining Time 2 Hours.");
      display.println("Now in 5 Minute Habituation.");
      display.display(); 
    }
    //shock_isolate and shock_social range 1,2 hence isolate+1 social+2 will turn them to the owm connected to board and
      //pwm 2-row A
      //pwm 3-row B
      //pwm 4-row C
      //pwm 5-row D
    //resting period
    analogWrite(shock_isolate+1, volta-volta);
    analogWrite(shock_social+2, volta-volta);
    delay(resting[cycle]);
    
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Code");
    display.println(exprows);
    display.println("Time Passed in Seconds:");
    display.println((ftime+resting[cycle])/1000);
    if((period-ftime)<300000){
      display.println("Remaining is less than 5 minutes. Start removing fishes.");
    }
    display.display(); 
    
    //shocking period
    analogWrite(shock_isolate+1, volta);
    analogWrite(shock_social+3, volta); 
    analogWrite(6, volta); 
    delay(shocking[cycle]);
    analogWrite(shock_isolate+1, volta-volta);
    analogWrite(shock_social+3, volta-volta);
    analogWrite(6, volta-volta);

    
    ftime=ftime+resting[cycle]+shocking[cycle];
    cycle=cycle+1;
    Serial.println(ftime);
  }
  while(ftime>=period){
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Code");
    display.println(exprows);
    display.println("Shocking period has ended. Remove the remaining fish.");

    display.display(); 
    
  }
  
}
