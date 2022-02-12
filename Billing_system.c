/*
This is my simple billing system 
Made by QuangVu
Vgu
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
These functions aims to generate bills
*/

//items list
struct items
{
    char item[20];
    float price;
    int qty;

};
//order list
struct orders{
    char customer[50];
    char date[50];
    int numOfItems;    
    struct  items itm[50];
};
//header of the bill
void generateBillHeader(char name[50],char date[30])
{
    printf("\n\n");
        printf("\tQUANGVU.restaurant");
        printf("\n-----------------------------"); 
        printf("\nDate:%s",date);
        printf("\nInvoice to :%s",name);
        printf("\n");
        printf("--------------------------------\n");
        printf("items\t\t");
        printf("qty\t\t");
        printf("total\t\t");
        printf("\n-------------------------------");
        printf("\n\n");
}
//body list
void generateBillBody(char item[30],int qty,float price)
{
        printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty*price);
        printf("\n");

}
//footer list
void generateBillFooter(float total)
{
    printf("\n");
    float dis =( 0.1*total);
    float netTotal=total-dis;
    //caculate csgt
    //cgst :Central Goods and Services Tax
    float cgst=(0.09*netTotal), grandTotal=(netTotal+2*cgst);
    printf("\n------------------------------------------\n");
    printf("sub total\t\t\t%.2f",netTotal);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCSGT @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n-----------------------------------------\n");
    printf("GrandTotal\t\t\t%.2f",grandTotal);
    printf("\n-----------------------------------------\n");
}

int main()
{   
    
    struct orders ord;
  
    char saveBill='y';
    FILE*fp;
    // dashboard
    float total;
    int opt,n;
    printf("\t=================QuangVu.Restaurant===================");
    printf("\n\nPlease select your prefer4ed operation");
    printf("\n\n1.Generate  Invoice");
    printf("\n\n2.Show all invoices");
    printf("\n\n3.Search Invoice");
    printf("\n\n4.Exit");
    printf("\n\nPlease select your prefered option:");
    scanf("%d", &opt);
    fgetc(stdin);
    //selections
    switch(opt) {
        case 1: 
        printf("please enter the customer name:\t");
        //stdin:standard input
        fgets(ord.customer,50,stdin);
        //give extra length
        ord.customer[strlen(ord.customer)-1] =0;
        strcpy(ord.date,__DATE__);
        printf("#nPlease enter the number of items:\t");
        scanf("%d", &n);
        ord.numOfItems= n ;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item%d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1] =0;
            printf("\nPlease enter the quantity of the item:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("\nplease enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            //caculate the total price
            total+= (ord.itm[i].qty*ord.itm[i].price);
        }
        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++)
        {
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);
        //save bill
        printf("\nDo you want to save the invoice[y/n]:\t");
        scanf("%s",&saveBill);
        //additional data to save bill
        if(saveBill=='y')
        {
           fp=fopen("RestaurantBill.dat","a+"); 
           fwrite(&ord,sizeof( struct orders),1,fp);
           if(!fwrite != 0)
           printf("\nSuccessfully saved");
           else
           printf("\nerror saving");
           fclose(fp);
        }
        break;

    }
    //notify you 
    printf("\nYou have chosen %d",opt);
    printf("\n\n");
    return 0;
}