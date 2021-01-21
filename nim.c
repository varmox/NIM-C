/*
NIM GAME in C

yannick gerber

*/

//Libraries
#include <stdio.h>      // rpintf, scanf
#include <stdint.h>     // int32_t
#include <stdlib.h>     // rand()


//Konstanten

#define MaxRows 8
#define Arraysize 10 
#define MaxTokens 10


void Gamesetup(int32_t* arraynim);                           //Variable für den Aufbau des spielfeldes (Anz. Reihen und Hoelzchen)
void ReadTokens(int32_t* arraynim, int8_t reihen);           //Fragt die einzenen Reihe Anzahl Hoelzchen ab
void Arrayfill(int32_t* arraynim);                          //befüllt das Ganze Array mit -1(-1 wird genutzt um die Anzahl der Rowsherauszufinden)
void UserInput(int32_t* arraynim);                          //Fragt Nutzer in welcher Reihe und wieviele Hoelzchen er entfernen moechte
void ComputerInput(int32_t* arraynim);                      //Spielzug Computer

int8_t LastToken(int32_t* arraynim);                           //Abfrage, ob noch Hoelzchen (Token existent) sind auf dem Spielfeld
int32_t UserInputNumber();                                     //Fragt den User nach der Anzahl an Hoelzchen
int8_t UserInputRow();                                         //Fragt den User nach der Anzahl an Reihen, welche er im Spiel haben möchte.

int main()
{
    int32_t arraynim[Arraysize];                             //array, in welchen das Spielfeld gespeichert wird. Arrayelements sind die Reihen, Wert der Elemente sind die Anz. Hoelzchen
    Arrayfill(arraynim);
    int8_t victory = 0;                                        //Victory geht auf 1 falls der Spieler gewonnen hat
    int8_t rows = 0;                                          //Anzahl Rows werden hier gespeichert

    printf("#######################################################################\n");
    printf("##                             NIM GAME                              ##\n");
    printf("#######################################################################\n\n");
    printf("Willkomenn zum Spiel NIM! Du spielst abwechslungsweise gegen einen Computer\n");
    printf("Die Regeln:\n ");
    printf("- Du darfst nur von einer Reihe Hoelchen entfernen \n");
    printf("- Du musst mindesten 1 oder gleich alle Hoelchen nehmen \n");
    printf("- Gewonnen hast du, wenn du das letzte Hoelzchen wegräumen kannst! \n\n");
    printf("Viel Spass!\n\n");

    rows = UserInputRow();
    ReadTokens(arraynim, rows);
    Gamesetup(arraynim);

    while (LastToken(arraynim) != 1)
    {
        UserInput(arraynim);
        Gamesetup(arraynim);
        if (LastToken(arraynim) != 1)
        {
            ComputerInput(arraynim);
            Gamesetup(arraynim);
        }
        else
            victory = 1;
    }
    if (victory == 1)
        printf("Du hast Gewonnen!\n\n");
    else
        printf("Du hast verloren!\n\n");
}

int8_t LastToken(int32_t* arraynim)
{
    int8_t i = 0;
    while (arraynim[i] != -1)
    {
        if (arraynim[i] != 0)
            return 0;
        i++;
    }
    return 1;
}



void UserInput(int32_t* arraynim)
{
    int8_t InputCorrect = 0;
    int32_t eingabereihe = 0;
    int32_t ReadTokens = 0;

    while (InputCorrect != 1)
    {
        printf("Waelen Sie die Reihe aus in der Sie Hoelzchen entfernen moechten: \n");
        eingabereihe = UserInputNumber();
        if (arraynim[eingabereihe - 1] > 0)
            InputCorrect = 1;
        else
            printf("Ausgewaelte Reihe steht nicht zur Verfuegung\n");
    }
    InputCorrect = 0;

    while (InputCorrect != 1)
    {
        printf("Waelen sie die Anzahl Hoelzchen die Sie in Reihe %i entfernen moechten: \n", eingabereihe);
        ReadTokens = UserInputNumber();
        if (arraynim[eingabereihe - 1] >= ReadTokens && ReadTokens > 0)
            InputCorrect = 1;
        else
            printf("Anzahl der Hoelzchen nicht korrekt\n");
    }
    arraynim[eingabereihe - 1] = arraynim[eingabereihe - 1] - ReadTokens;
}

void ComputerInput(int32_t* arraynim)
{
    int8_t i = 0;
    printf("Spielzug Computer");
    while (arraynim[i] != -1)
    {
        if (arraynim[i] != 0)
        {
            arraynim[i] = arraynim[i] - 1;
            return;
        }
        i++;
    }
}

int8_t UserInputRow()
{
    int8_t eingabe = 0;
    int8_t InputCorrect = 0;
    while (InputCorrect == 0)
    {
        printf("Geben sie die Anzahl der Rowsein die das Spiel haben soll(Zwischen 2 und 8): ");
        eingabe = UserInputNumber();
        if (eingabe > MaxRows || eingabe < 2)
            printf("Nicht korrekte Anzahl der Rows\n");
        else
        {
            InputCorrect = 1;
            return eingabe;
        }
    }
}


void Arrayfill(int32_t* arraynim)
{
    int8_t fill;
    for (fill = 0; fill < Arraysize; fill++)
        arraynim[fill] = -1;
}

void ReadTokens(int32_t* arraynim, int8_t rows)
{
    int8_t i;
    int32_t Input = 0;
    for (i = 0; i <= rows - 1; i++)
    {
        printf("Geben sie die Hoelzchen der Reihe %i ein (zwischen 0 und 10):  \n", i + 1);
        Input = UserInputNumber();
        if (Input > MaxTokens || Input < 0)
        {
            printf("Bitte definieren Sie eine kleinere Anzahl!\n");
            i--;
        }
        else
            arraynim[i] = Input;
    }
}

int32_t UserInputNumber()
{
    int32_t eingabe = 0;
    scanf_s("%i", &eingabe);
    while (getchar() != '\n');
    return eingabe;
}

void Gamesetup(int32_t* arraynim)
{
    int32_t i = 0;
    int32_t counter = arraynim[i];
    printf("\n\NIM SPIELFELD\n\n");
    while (counter != -1)
    {
        if (arraynim[i] != 0)
        {
            while (counter != 0)
            {
                printf("|");
                counter--;
            }
        }
        printf("\n--------------------------------\n");
        i++;
        counter = arraynim[i];
    }
    printf("\n\n\n");
}

