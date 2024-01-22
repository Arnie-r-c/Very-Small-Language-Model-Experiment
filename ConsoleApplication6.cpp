#include <iostream>
#include "Helper.h"
#include "languagemodel.h"
#include "tokenizer.h"

using namespace std;
using namespace Helper;
int main()
{
	int choose;
	language a;
	tokenizer b;
	while(true)
	{ 
	choose = GetValidatedInt("Choose:\n1. Tokenizer\n2. Model\n", 1, 2);
switch(choose)
{ 
case 1:
	b.tokenize();
	break;
case 2:
	a.model();
	break;
}





}
}