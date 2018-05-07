/*
Weicheng Ji
ICEN 150 Intro to Engineering Analysis
4/29/2018
*/

const int redTone = 200;    //red ligth on with 200 Hz buzz sound
const int yellowTone = 500; //yellow light on with 500 Hz buzz sound
const int greenTone = 800;  //green light on with 800 Hz buzz sound
const int failTone = 80; //all lights on with 80 Hz buzz sound

int count = 0; //length of the array
int i;         //global variable defined for for loops

const int buttonPin1 = 4; //1 button with pin 4
const int ledPin1 = 13;   //1 LED with pin 13
const int buttonPin2 = 3; //2 button with pin 3
const int ledPin2 = 12;   //2 LED with pin 12
const int buttonPin3 = 2; //3 button with pin 2
const int ledPin3 = 11;   //3 LED with pin 11
const int buzzer = 7;     //buzzer pin 7

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

/* I/O setup */
void setup()
{
    pinMode(ledPin1, OUTPUT);
    pinMode(buttonPin1, INPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(buttonPin3, INPUT); 
    pinMode(buzzer, OUTPUT); //buzzer PinMode setup
}

/* fail tone and fail lights */
void fail()
{
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    tone(buzzer, failTone);
    delay(1200);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    noTone(buzzer);
    delay(500);
    count = 0;
}

/* red tone and red light */
void red()
{
    digitalWrite(ledPin1, HIGH); 
    tone(buzzer, redTone);
    delay(800);
    noTone(buzzer);
    digitalWrite(ledPin1, LOW);
    delay(300);
}

/* yellow tone and yellow light */
void yellow()
{
    digitalWrite(ledPin2, HIGH);
    tone(buzzer, yellowTone);
    delay(800);
    noTone(buzzer);
    digitalWrite(ledPin2, LOW);
    delay(300);
}

/* green tone and green light */
void green()
{
    digitalWrite(ledPin3, HIGH);
    tone(buzzer, greenTone);
    delay(800);
    noTone(buzzer);
    digitalWrite(ledPin3, LOW);
    delay(300);
}

/* function to check the button state */
void readButtonState()
{
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
}

void loop()
{
    count++;
    if (count <= 20) //define the maximum step to beat the game is 20
    {
        int userInput;

        int randomNumber[count]; //define the random generated array randomNumber[] with length 'count'
        for (i = 0; i < count; i++)
        {
            randomNumber[i] = random(1, 4);
        } //for loop to fill the array sequence

        /* for loop to light up and make the buzz sound */
        for (i = 0; i < count; i++)
        {
            if (randomNumber[i] == 1)
            {
                red();
            }
            else if (randomNumber[i] == 2)
            {
                yellow();
            }
            else if (randomNumber[i] == 3)
            {
                green();
            }
        }

        /* read the button for the first time */
        readButtonState();
        /* Loop to check & read the buttonstate */
        for (i = 0; i < count; i++)
        {
            while ((buttonState1 == HIGH) || (buttonState2 == HIGH) || (buttonState3 == HIGH))
            {

                /* read the button again to see if one has been pressed */
                readButtonState();
                if (buttonState1 == LOW)
                {
                    red();
                    userInput = 1;
                    if (userInput == randomNumber[i])
                    {
                        break;
                    }
                    else
                    {
                        fail();
                        break;
                    }
                }
                else if (buttonState2 == LOW)
                {
                    yellow();
                    userInput = 2;
                    if (userInput == randomNumber[i])
                    {
                        break;
                    }
                    else
                    {
                        fail();
                        break;
                    }
                }
                else if (buttonState3 == LOW)
                {
                    green();
                    userInput = 3;
                    if (userInput == randomNumber[i])
                    {
                        break;
                    }
                    else
                    {
                        fail();
                        break;
                    }
                }
            }
        }
    }
    else
    {
        count = 0; //Reset the count to 0 if 20th win on a roll.
    }
}