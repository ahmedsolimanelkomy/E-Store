#ifndef STORE_OPERATIONS_H_INCLUDED
#define STORE_OPERATIONS_H_INCLUDED
#include <ctype.h>
//Defining the Structures
struct Product{
    char name[20];
    float price;
    int quantity;
};
struct Category{
    char name[20];
    struct Product Products[20];
    int numOfProduct;
};
struct Store{
    struct Category Categories[5];
    int numOfCategories;
};
typedef struct Product Product;
typedef struct Category Category;
typedef struct Store Store;

//operations on products
void addProducts(Store *store,int catIndx){
    int numOfPro;
    while(1){
        printf("    Please Enter Number Of Products You Will Add (1-20) \n");
        scanf("%d",&numOfPro);
        if (numOfPro <= 0){
            printf("    !Please Enter Invalid Input. \n ");
            continue;
        }else if(numOfPro > 20){
            printf("    Products Range From (1-20) \n ");
            continue;
        }
        else{
            break;
        }

    }
    struct Product *p = &(store->Categories[catIndx].Products);
    int count = store->Categories[catIndx].numOfProduct;
    for(int i = 0; i < numOfPro ;i++){
        printf("For Product no.%d \n",i+1);
        printf("    Please Enter Product Name : \n");
        scanf("%s",&p[i+count].name);
        printf("    Please Enter Product Price : \n");
        scanf("%f",&p[i+count].price);
        printf("    Please Enter Product Quantity : \n");
        scanf("%d",&p[i+count].quantity);
        store->Categories[catIndx].numOfProduct++;
    }
    printf("----- Press Any Key to Back -----");
}
void displayProducts(Store *store ,int catIndx){
    for(int i = 0; i < store->Categories[catIndx].numOfProduct; i++){

        printf("            ########################################\n");
        printf("                Product Category : %s \n",store->Categories[catIndx].name);
        printf("                Product Name : %s \n",store->Categories[catIndx].Products[i].name);
        printf("                Price : %f $ \n",store->Categories[catIndx].Products[i].price);
        printf("                Quantity : %i \n",store->Categories[catIndx].Products[i].quantity);
        printf("            ########################################\n");
    }
    if(store->Categories[catIndx].numOfProduct == 0){
            printf("        ######## No Products To be shown In This Category ###### \n");
        }
    printf("        ----- Press Any Key to Back -----       \n");

}
float sellProduct(Store *store,int cIndx ,int pIndx){
    int quantity;
    printf("    Please Enter Quantity To Be Sold \n");
    scanf("%d",&quantity);
    if(quantity<=0){
        printf("    !Invalid Input \n");
    }else if(quantity > store->Categories[cIndx].Products[pIndx].quantity){
        printf("    Quantity Out Of Stock \n");
    }
    else{
        printf("***** Sold Items Report *****\n");
        printf("    Product Name : %s \n",store->Categories[cIndx].Products[pIndx].name);
        printf("    Category : %s \n",store->Categories[cIndx].name);
        printf("    Product Price : %f $ \n",store->Categories[cIndx].Products[pIndx].price);
        printf("    Product Quantity : %i \n",quantity);
        printf("    Total Price : %f \n",store->Categories[cIndx].Products[pIndx].price * (float)quantity);
        store->Categories[cIndx].Products[pIndx].quantity = store->Categories[cIndx].Products[pIndx].quantity-quantity;
    }
    return store->Categories[cIndx].Products[pIndx].price * (float)quantity;
    printf("----- Press Any Key to Back -----");
}
void moveProduct(Store *store ,int cIndx ,int pIndx ,int newcIndx){
    while(1){
        if (store->Categories[cIndx].numOfProduct < 1){
            printf("    !!!!!!! the Product Not Founded     \n");
            break;
        }else {
            int newpIndex = store->Categories[newcIndx].numOfProduct;
            store->Categories[newcIndx].Products[newpIndex] = store->Categories[cIndx].Products[pIndx];
            store->Categories[newcIndx].numOfProduct++;
            for(int i = pIndx+1; i < store->Categories[cIndx].numOfProduct; i++){
                store->Categories[cIndx].Products[i-1] = store->Categories[cIndx].Products[i];
            }
            store->Categories[cIndx].numOfProduct--;
            printf("----- Press Any Key to Back -----");
            break;
        }
    }
}

//operations on categories
void addCategory(Store *store){
    int numOfCate;
    int count = store->numOfCategories;
    printf("1.Please Enter Number Of Categories You Will Add Range (1-5) \n");
    while(1){
        scanf("%i",&numOfCate);
        if (numOfCate <=0){
            printf("!Please Enter Invalid Input. \n ");
        }else if(numOfCate > 5){
            printf("Categories Range From (1-5) \n ");
        }
        else{
            break;
        }
    }

    for(int i = 0; i < numOfCate ; i++){
        printf("2.Please Enter Category Name : \n");
        scanf("%s",&store->Categories[count + i].name);
        store->numOfCategories++;
    }
    printf("----- Press Any Key to Back -----");

}
void displayCategories(Store *store){
    for(int i = 0; i < store->numOfCategories; i++){
        printf("######################################## \n");
        printf("Category Number : %d \n",i+1);
        printf("Category Name : %s \n",store->Categories[i].name);
        printf("Number Of Products : %d \n",store->Categories[i].numOfProduct);
        printf("######################################## \n");
        displayProducts(store,store->numOfCategories-1);
    }
    if(store->numOfCategories == 0){
            printf("######## No Categories To be shown In The Store ###### \n");
        }
    printf("        ----- Press Any Key to Back -----       \n");
}


#endif // STORE_OPERATIONS_H_INCLUDED
