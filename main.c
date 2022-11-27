#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items{
    char item[50];
    float price;
    int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//The bill header should show the name of the customer and the date of purchase
void generateBillHeader(char name[50], char date[50]){
    printf("\n\n");
    printf("\t SCENT HUB PERFUMERY \n\t   10, MOJO STREET \n\t    AGRIC, ILORIN");
    printf("\n\n\n Date:%s", date);
    printf("\n Invoice to: %s\n", name);
    printf("\n");
    printf(" ==================================================\n");
    printf(" ITEMS");
    printf(" \t\t\tQTY");
    printf(" \tUNIT PRICE");
    printf(" \tTOTAL\t\t");
    printf("\n ==================================================");
    printf("\n\n");
}
// body should contain the item, quantity and price
void generateBillBody(char item[50], int qty, float price){
    printf(" %s", item);
    printf("\t\t%d", qty);
    printf("\t%.2f", price);
    printf("\t%.2f\t\t", qty*price);
    printf("\n");
}
//footer includes just the total and a thank you message
void generateBillFooter(float total, float discount){
    printf("\n");
    //removing discount from the total if it is applied
    printf(" ==================================================");
    printf("\n Sub total\t\t\t\t%.2f", total);
    float dis = (discount/100) *total;
    float netTotal = total-dis;
    float vat = 0.075*netTotal;
    float grandTotal = netTotal+vat;

    printf("\n Discount @ %.1f%s\t\t\t%.2f", discount, "%", dis);
    printf("\n ADD VAT @ 7.5%s\t\t\t\t%.2f", "%", vat);
    printf("\n ==================================================");
    printf("\n GRAND TOTAL \t\t\t\t%.2f", grandTotal);
    printf("\n ==================================================");
    printf("\n\n\n -------------------------------------------------");
    printf("\n   ====THANK YOU FOR CHOOSING TO SMELL GOOD====");

}
int main(){
    int opt;
    struct orders ord;
    char saveBill = 'y', contLoop = 'y';
    struct orders order;
    char name[50];
    FILE *fp;
    //dashboard
    while('0' == '0' || contLoop == 'y'){
    float total = 0;
    float discount;

    int invoiceFound = 0;
    printf("\t ==================SCENTHUB BY NAE==================");
    printf("\n\n Please select the preferred operation: ");
    printf("\n 1.Generate Invoice");
    printf("\n 2.View all Invoices");
    printf("\n 3.Search Invoice");
    printf("\n 4.Exit");

    printf("\n\n Select an option:\t");
    scanf("%d", &opt);
    fgetc(stdin);

    switch (opt){
    case 1:

        printf("\n Enter name of customer:\t\t");
        fgets(ord.customer, 50, stdin);
        ord.customer[strlen(ord.customer)-1]= 0;
        strcpy(ord.date, __DATE__);
        printf("\n Enter the number of items:\t ");
        scanf("%d", &ord.numOfItems);

        for(int i = 0; i < ord.numOfItems; i++){
            fgetc(stdin);
            printf("\n\n");
            printf(" Enter item %d:\t\t", i+1);
            fgets(ord.itm[i].item, 50, stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("\n Enter the quantity:\t");
            scanf("%d", &ord.itm[i].qty);
            printf("\n Enter the unit price:\t");
            scanf("%f", &ord.itm[i].price);
            printf("\n Enter discount: ");
            scanf("%f", &discount);
            fgetc(stdin);

            total += ord.itm[i].qty * ord.itm[i].price;
        }
        //printing the bill header which includes just the name and the date
        generateBillHeader(ord.customer, ord.date);
        for(int i = 0; i < ord.numOfItems; i++){
            generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
        }
        generateBillFooter(total, discount);
i
        printf("\n\n\n Save invoice [y/n] ?\t");
        scanf("%s", &saveBill);
        //saving the invoice. the while loop will always be executed
        while('0' == '0'){
            if(saveBill == 'y'){
                fp = fopen("RestaurantBill.dat", "a+");
                fwrite(&ord,sizeof(struct orders), 1, fp);
                if(fwrite != 0)
                    printf("\n ===Successfully saved.===");
                else
                    printf("\n Error saving.");
                fclose(fp);
                break;
            }
            else if(saveBill == 'n'){
                printf("\n Invoice not saved.");
                break;
            }
            else{printf(" command not recognized");}
            break;
        }
    //Checking the difference in the effect of struct name 'ord' and 'order'

/**    case 2:

        fp = fopen("RestaurantBill.dat", "r");
        printf("\n\t ****PREVIOUS INVOICES****\n");
        while(fread(&order, sizeof(struct orders), 1, fp)){
            float tot = 0;
            generateBillHeader(order.customer, order.date);
            for(int i = 0; i < order.numOfItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot, discount);
        }
        fclose(fp);
        break;
*/
    case 2:

        fp = fopen("RestaurantBill.dat", "r");
        printf("\n\t ****PREVIOUS ****\n");
        while(fread(&ord, sizeof(struct orders), 1, fp)){
            float tot = 0;
            generateBillHeader(ord.customer, ord.date);
            for(int i = 0; i < ord.numOfItems; i++){
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                tot += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillFooter(tot, discount);
        }
        fclose(fp);
        break;

    case 3:
        printf("\n Search for a customer:\t");
        //fgetc(stdin);
        fgets(name, 50, stdin);
        name[strlen(name) -1] = 0;
        if(!strcmp(ord.customer, name)){
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n  ****Invoice of %s****\n", name);
            while(fread(&order, sizeof(struct orders), 1, fp)){
            float tot = 0;
            generateBillHeader(order.customer, order.date);
            for(int i = 0; i < order.numOfItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot, discount);
            invoiceFound = 1;
            }
        }
        if(!invoiceFound){
            printf("\n Sorry, invoice for %s not found.\n\n", name);
        }
        fclose(fp);
        break;

    case 4:
        printf("\n\t\t See you later. \n\n");
        exit(0);
        break;

    default:
        printf(" Invalid option selected.");
        break;
    }

    printf("\n\n Perform another operation [y/n] \t");
    scanf("%s", &contLoop);
    printf("\n");

    while(contLoop != 'y' && contLoop != 'n'){
        printf("\n Invalid selection.");
        printf("\n\n Perform another operation [y/n] \t");
        scanf("%s", &contLoop);
        printf("\n\n\n");
        }

    while(contLoop == 'n'){
        printf("\n\t\t See you later. \n\n");
        printf("\n\n");
        return 0;

    }
}


}
