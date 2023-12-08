#include <stdio.h>
#include <stdlib.h>
#include "Store_Operations.h"
#include <windows.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define ESCAPE 27
COORD coord = {0, 0};
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int ForgC, int BackC) {
    WORD wColor = (BackC << 4) | ForgC;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
int main()
{
    //Initialize Store
    struct Store Store;
    Store.numOfCategories = 0;
    for(int i = 0; i< 5; i++){
        Store.Categories[i].numOfProduct = 0;
        Store.Categories[i].Products[i].quantity = 0;
    }
    //Store.Categories[catIndx].numOfProduct = 0;
    system("cls"); // Clear the console

    int x = 10;      // X-coordinate of the menu
    int y = 5;       // Y-coordinate of the menu
    int textColor = 15;      // Text color (15 = White)
    int backgroundColor = 0; // Background color (0 = Black)

    int choice = 1; // Default choice is "New"

    while (1) {
        system("cls"); // Clear the console
        gotoxy(x, y);
        SetColor(textColor, backgroundColor);
        printf("    Main Menu\n");

        // Option 1: Add Category
        gotoxy(x, y + 2);
        if (choice == 1) {
            SetColor(0, 15);
        }
        printf("    1. Add Category");
        SetColor(textColor, backgroundColor);

        // Option 2: Add Product
        gotoxy(x, y + 4);
        if (choice == 2) {
            SetColor(0, 15);
        }
        printf("    2. Add Product");
        SetColor(textColor, backgroundColor);

        // Option 3: Move Product
        gotoxy(x, y + 6);
        if (choice == 3) {
            SetColor(0, 15);
        }
        printf("    3. Move Product");
        SetColor(textColor, backgroundColor);

        // Option 4: Sell Product
        gotoxy(x, y + 8);
        if (choice == 4) {
            SetColor(0, 15);
        }
        printf("    4. Sell Product");
        SetColor(textColor, backgroundColor);

        // Option 5: Display Products
        gotoxy(x, y + 10);
        if (choice == 5) {
            SetColor(0, 15);
        }
        printf("    5. Display Products");
        SetColor(textColor, backgroundColor);

        // Option 6: Display Categories
        gotoxy(x, y + 12);
        if (choice == 6) {
            SetColor(0, 15);
        }
        printf("    6. Display Categories");
        SetColor(textColor, backgroundColor);

        // Option 3: Exit
        gotoxy(x, y + 14);
        if (choice == 7) {
            SetColor(0, 15);
        }
        printf("    7. Exit");
        SetColor(textColor, backgroundColor);

        int key = _getch();
        switch (key) {
            case KEY_UP:
                choice = (choice - 1 < 1) ? 7 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice + 1 > 7) ? 1 : choice + 1;
                break;
            case KEY_ENTER:
                if (choice == 1) {
                    system("cls");
                    addCategory(&Store);
                    _getch();
                }else if (choice == 2) {
                    system("cls");
                    int cateChoice;
                    printf("-----  Please Select Category You Want To Add Products In From Menu Below  -----\n");
                    printf("    Categories Names : \n");
                    for(int i = 0; i < Store.numOfCategories; i++){
                        printf("    ###### %d.%s ######  \n",i+1,Store.Categories[i]);
                    }
                    while(1){
                        scanf("%d",&cateChoice);
                        if (cateChoice < 1 || cateChoice > 5){
                            printf("    !Invalid Choice. \n");
                        }else{
                            break;
                        }
                    }
                    addProducts(&Store,cateChoice-1);
                    _getch();
                }else if (choice == 3) {
                    system("cls");
                    int cIndx,pIndx,newcIndx;
                    printf("    Categories Names : \n");
                    for(int i = 0; i < Store.numOfCategories; i++){
                        printf("    ###### %d.%s ######  \n",i+1,Store.Categories[i].name);
                    }
                    printf("        1.Please Enter Number Of Product Category You Want To Move\n");
                    scanf("%i",&cIndx);
                    printf("        2.Please Enter Number Of Product You Want To Move \n");
                    scanf("%i",&pIndx);
                    printf("        3.Please Enter Number of Category You Want To Move The Product To \n");
                    scanf("%i",&newcIndx);
                    moveProduct(&Store,cIndx-1,pIndx-1,newcIndx-1);
                    _getch();
                }else if (choice == 4) {
                    system("cls");
                    int numOfP;
                    float totalPrice = 0;
                    printf("Please Enter Number of Products You Want To Sell \n");
                    scanf("%d",&numOfP);
                    for(int i = 0; i < numOfP; i++){
                        int cn,pn;
                        printf("Categories Names : \n");
                        for(int i = 0; i < Store.numOfCategories; i++){
                            printf("###### %d.%s ######  \n",i+1,Store.Categories[i].name);
                        }
                        while(1){
                            while(1){
                                printf("    Please Enter Category Number Of Product Number %i. \n",i+1);
                                scanf("%d",&cn);
                                if(cn <= 0 || cn > 5){
                                    printf("        !!Invalid Input For Category Number! \n");

                                }else if (cn > Store.numOfCategories){
                                    printf("        !!Invalid Category Input \n");
                                }else if (Store.Categories[cn-1].numOfProduct < 1){
                                    printf("        !!No Products In This Category \n");
                                }else{
                                    break;
                                }
                            }
                            while(1){
                                printf("    Please Enter Product Number To Be Sold for Product Number %i. \n",i+1);
                                scanf("%d",&pn);
                                if(pn <= 0 || pn > 20 ){
                                    printf("        !!Invalid Input For Product Number! \n");
                                }else if (pn > Store.Categories[pn-1].numOfProduct){
                                    printf("        !!Invalid Product Input \n");
                                }else if (Store.Categories[cn-1].Products[pn-1].quantity < 1){
                                    printf("        !!Items Out Of Stock \n");
                                }else{
                                    break;
                                }
                            }
                            break;
                        }
                        totalPrice = totalPrice + sellProduct(&Store,cn-1,pn-1);
                    }
                    printf("                        $$$$$$$$ Total Products Price Is : %f $$$$$$$$ \n",totalPrice);
                    printf("                                ----- Press Any Key to Back -----");
                    _getch();

                }else if (choice == 5) {
                    printf("    Categories Names : \n");
                    for(int i = 0; i < Store.numOfCategories; i++){
                        printf("    ###### %d.%s ######  \n",i+1,Store.Categories[i]);
                    }
                    system("cls");
                    printf("### Please Enter Category Number Of Products You Want To Display : ### \n");
                    int cIndx;
                    scanf("%i",&cIndx);
                    system("cls");
                    displayProducts(&Store,cIndx-1);
                    _getch();
                }else if (choice == 6) {
                    system("cls");
                    displayCategories(&Store);
                    _getch();
                } else if (choice == 7) {
                    return 0; // Exit the program
                }
                break;
            case ESCAPE:
                return 0; // Exit the program
        }
    }
    return 0;
}

