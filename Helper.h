#pragma once
#include <string>
#include <ctime>

namespace Helper
{
    int GetValidatedInt(const char* strMessage, int nMinimumRange = 0, int nMaximumRange = 0)
    {
        int userinput;

        while (true)//will loop forever unless it returns
        {

            std::cout << strMessage << "\n";//im assuming this is intended in a way that allows the user(me) to define a string,
            std::cin >> userinput;           // then output it by passing it as an argument.
            if (!std::cin)// found this nugget here https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
            {
                std::cout << "User did not enter an integer.\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;//restarts loop. why was this never taught? handy thing to know. also found on stack overflow.
            }
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');//clear and ignore further buffered inputs uding the same method as the last assignment. 

            if (nMinimumRange != nMaximumRange && (userinput < nMinimumRange || userinput > nMaximumRange))//ah it worked! i wanted it so that if both range values were zero, it would accept any value. i was having a hard time as it only wanted to accept 0 and nothing else.
            {
                std::cout << "Input out of range!" << "\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
                //GetValidatedInt(strMessage, nMinimumRange, nMaximumRange);//if input is out of range, start over// dosnt work
            }
            else
            {
                return userinput;//if input is within range, return it.
            }

        }


        /*
        Return random number within a range
        Print a menu(array of strings) and return the user’s selection
        Clear and ignore the cin input buffer
        Print a provided integer in binary, hex, or oct
        Copy string reference

        print array
        fill array with random ints


        */
    }
}
int PrintMenu(std::string menuMessage ,const std::string menu[], int size)//this unfortuantely relies on the user(me) knowing the size of the array, but thats ok.
    {
        int choice;
        std::cout << menuMessage;
        for (int i = 0; i < size; i++)
        {
            std::cout << i+1<<". "<<menu[i] << "\n";
        }
        choice = Helper::GetValidatedInt(" ", 1, size);
        
        return choice;

    }
        

int RandInt(int range=1)//a lottery style random number generator. uses a fixed set with introduced randomness. while it is statistically random, it is not mathematically uniform randomness. some may or may not like my approach, but it is mine.
{//make sure to seed rand()!!

    int number;
    
    //this is pi with the decimal removed. i cant find any tutorials or anything useful, so im coming up with my own way. the goal here is just to make a really big random number and take digits as needed.
    std::string pi = "31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";//100 digits of pi
    std::string chosenOnes;
    if (range <= 0)
    {
        return 0;
    }
       for (int i = 0; i < range; i++)
       {
           int adder =rand()% pi.length();//i was having issues with string out of range, had to find a way to ensure it stays within the string length
           
           chosenOnes += pi[adder];//the idea here is im making a string using the random digits, pulling the desired number of digits out, then casting back to int. the end result should be acceptably random.
            
       }
       
       if (stoi(chosenOnes) > INT_MAX)
       {
           return 0;
       }
       else
       { 
           number = stoi(chosenOnes);
        return number;
        }
    


}

void CI()//Clear and Ignore
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

std::string StrRef(const std::string stringtodupe)//const so that it cant be changed.
{
    std::string a = stringtodupe;
    //not really sure what a method to copy a string reference should do, or what it might be useful for...
    return a;//basically returns a duplicate string, i may see what use i can make of this later.
}

std::string ItoBin(unsigned int number)
{
    std::string binary;
    int count = sizeof(number) * 8;
    for (int i = count - 1; i >= 0; --i)
    {
        if (number & (1 << i)) binary += "1";//had to borrow from last weeks work to make this work. this should** return a binary of the int, if i did it right.
        else binary += "0";

        
    }
    
    
    
    
    return binary;
}


std::string ItoOct(int number)
{//ok so an octal counts from 0 to 7, so i need only make a counting system that resets after 7. convoluted, and i did try using math, but couldnt make it work.
    //oh snap nevermind, i figured it out. you just divide by 8 and take the ramainder.
    if (number == 0) {
        return "0";  // it dosnt like dividing by zero.
    }

    std::string octal = "";
    while (number > 0) {
        int remainder = number % 8;  // Get the remainder of dividing by 8
        octal = std::to_string(remainder) + octal;  //to it string. do it.
        number /= 8;  //divide by 8 again
    }

    return octal;
}

std::string ItoHex(int number)//!!not working right!!
{//so this is pretty simmilar to octal from what ive read, so im going to try and just adapt the code over, then contrive a way to appent the letters to their corresponding values.
    if (number == 0) {
        return "0";  // it still dosnt like dividing by zero.
    }

    std::string hex = "";
    while (number > 0) {
        int remainder = number % 16;  // Get the remainder of dividing by 16 for hex
        hex = std::to_string(remainder) + hex; 
        number /= 16;  //divide by 16 again
    }

    return hex;//somethings not jiving
}


int* FillArray(int* array, int size, int numDigits)
{
    if (numDigits == 0)
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = rand();
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = RandInt(numDigits);
        }
    }

    return array;
}

void DisplayArrayInt(int* array, int size)//needed these, so made them real quick. might be handy to have in the helper.
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }

}
void DisplayArrayString(std::string* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }

}