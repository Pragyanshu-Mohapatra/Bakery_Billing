//Bakery Billing
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>



int homepage()
{
system("color B0");
char name,pas;
printf("*******************************************\n");
printf("\n********Welcome to Nirmala Bakery*******\n");
printf("\n----------------------------------------\n");
printf("\n   We offer the best bakery service in the region\n");
printf("***************************************\n");
printf("Please Enter your Credentials :-");
printf("\n----------------------------------------");
printf("\nUser_Name:");
scanf("%c",&name);
printf("\n--");
printf("\nPassword:");
scanf("%c",&pas);
printf("\n----------------------------------------\n");
printf("\nYou have succesfully login!!!\n");
printf("----------------------------------------");

printf("\n*******************************************\n");
getch();
system("cls");
return 0;
}


int menu()
{
// Inpecting of Menu_Item
printf("*********************************\n");
printf("\tMenu:");
printf("\n*********************************\n");
printf("\n\n1.Pizza\n");
printf("--------------\n");
printf("2.Pasta\n");
printf("--------------\n");
printf("3.Coffee\n");
printf("--------------\n");
printf("4.Tea\n");
printf("--------------\n");
printf("5.Biscuits\n");
printf("--------------\n");
printf("5.Burgers\n");
printf("--------------\n");
printf("6.Rolls\n");
printf("--------------\n");	
printf("\n*********************************\n");
getch();
system("cls");
}

int order()
{int amount,pizza,GarlicBNo,baklava;

char x,z;
//  Variables
	int pasta; // pasta number
	int softdr;// drink number
	float cost1= 0.0; // pizza cost
	float cost2= 0.0; //pasta cost
	float tax; // tax amount
	float total;
 // total of pasta 
printf("\nDo you want to place Pizza Order?(Enter 'Y' for YES or 'N' for NO):\n");
scanf("%c",&x);
if(x=='Y'||'y')
{
printf("How many pizza To order?\n");
scanf("%d",&pizza);
}

if(pizza==1)
{printf("Your order is confirmed to 1 pizza:");
cost1=12;
}
if(pizza==2){
printf("You order is confirmed to 2 pizza:");
cost1=22;
}
if(pizza>=3)
{GarlicBNo=pizza/3;
printf("\nYou get %d Garlic Bread Complimentary from our side:\n",GarlicBNo);
printf("\nNumber of Pizza is= %d\n",pizza);
printf("\nNumber of Garlic bread is= %d\n",GarlicBNo);
cost1=pizza*10.0;
printf("\n****************************************************************************\n");
printf("\nOrder cost for Pizza :$%f\n",cost1);
printf("\n****************************************************************************\n");

}


//Ordeing of Pasta logic

printf("\nDo you want to place Pasta Order?(Enter 'Y' for YES or 'N' for NO):\n");
scanf("%c",&z);
if(z=='Y'||'y')
{
printf("How many Pasta To order?\n");
scanf("%d",&pasta);
printf("\n****************************************************************************\n");
}
if(pasta==1)
{printf("Your order is confirmed to 1 pasta:");
cost2=8;}
if(pasta==2){
printf("Your order is confirmed to 2 pasta:");
cost2=18;}
if(pasta>=3)
{softdr=pasta/3;
printf("\nYou get %d 1.5lt Soft drink from our side:\n",softdr);
printf("\nNumber of Pasta is= %d\n",pasta);
printf("\nNumber of Soft Drink is= %d\n",softdr);
cost2=pizza*7.0;
printf("\n****************************************************************************\n");
printf("\nOrder cost :$%f\n",cost2);
printf("\n****************************************************************************\n");}

//Bakalava Offer logic
if(softdr>2||GarlicBNo>2)
{printf("\n You got a small box of Baklava  free complimentry from our side (a famous dessert item)\n");
if(softdr>GarlicBNo)
{baklava=GarlicBNo/3;
printf("Baklava:%d",baklava);}
else
{baklava=softdr/3;
printf("Baklava:%d",baklava);}
}
	
getch();
system("cls");	

}


int total_bill()
{

	//Total Amount Printing
printf("\n****************************************************************************\n");
printf("\n****************************************************************************\n");
//printf("\nThe total payment amounts received for the pizza order:%f\nthe total payment amounts received for pasta order:%f\nthe total amount of pizzas and pasta sold in that session:%d",cost1,cost2,pizza+pasta);
printf("\nIndex                      Item Description                    Quantity  Rate+VA\n--------------------------------------------------------------------------\n");
printf("\n1.                           Pizza                                   1      25     \n");
printf("--\n");
printf("2.                           Pasta                                   1      25     \n");
printf("--\n");
printf("3.                           Coffee                                  1      25     \n");
printf("--\n");
printf("4.                           Tea                                     1      25     \n");
printf("--\n");
printf("5.                           Burger                                  1      25     \n");
printf("--\n");
printf("6.                           Roll                                    1      25     \n\n");

printf("\n****************************************************************************\n");
printf("\n****************************************************************************\n");
getch();
system("cls");
}



int main()
{ 
homepage();
menu();
order();
total_bill();
//Adding all the configuration

}

