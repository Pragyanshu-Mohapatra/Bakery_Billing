#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_BILLS 100
#define GST_RATE 0.05

struct Date {
    int day, month, year;
};

struct Item {
    int code;
    char name[50];
    float price;
    int stock;
    float total;
};

struct Inventory {
    struct Item items[MAX_ITEMS];
    int count;
};

struct Bill {
    int bill_no;
    char customer_name[100];
    long long phone;
    float old_balance;
    float payment;
    float gst;
    float grand_total;
    struct Date date;
    int num_items;
    int item_codes[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    float subtotals[MAX_ITEMS];
};

struct Inventory inv;
struct Bill bills[MAX_BILLS];
int bill_count = 0;

void init_inventory();
void load_inventory();
void save_inventory();
void display_menu();
int find_item(int code);
void input_bill(struct Bill *b);
void calculate_bill(struct Bill *b);
void save_bill(struct Bill *b);
void load_bills();
void display_all_bills();
void search_bill();
void edit_bill();
void delete_bill();
void print_bill(struct Bill b, char *filename);
void inventory_menu();

int main() {
    load_inventory();
    load_bills();
    int choice;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    
    while (1) {
        system("cls");
        printf("\n=== ADVANCED BAKERY BILLING SYSTEM ===\n");
        printf("Date: %02d/%02d/%04d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
        printf("1. Add New Bill\n");
        printf("2. View All Bills\n");
        printf("3. Search Bill\n");
        printf("4. Edit Bill\n");
        printf("5. Delete Bill\n");
        printf("6. Inventory Management\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                input_bill(&bills[bill_count]);
                calculate_bill(&bills[bill_count]);
                save_bill(&bills[bill_count]);
                bill_count++;
                printf("\nBill %d saved!\n", bills[bill_count-1].bill_no);
                getch();
                break;
            case 2: display_all_bills(); getch(); break;
            case 3: search_bill(); getch(); break;
            case 4: edit_bill(); getch(); break;
            case 5: delete_bill(); getch(); break;
            case 6: inventory_menu(); getch(); break;
            case 7: save_inventory(); exit(0);
            default: printf("Invalid!"); getch();
        }
    }
    return 0;
}

void init_inventory() {
    inv.count = 10;
    strcpy(inv.items[0].name, "Bread"); inv.items[0].code=1; inv.items[0].price=20; inv.items[0].stock=100;
    strcpy(inv.items[1].name, "Cake"); inv.items[1].code=2; inv.items[1].price=150; inv.items[1].stock=50;
    strcpy(inv.items[2].name, "Biscuit"); inv.items[2].code=3; inv.items[2].price=10; inv.items[2].stock=200;
    strcpy(inv.items[3].name, "Pastry"); inv.items[3].code=4; inv.items[3].price=30; inv.items[3].stock=80;
    strcpy(inv.items[4].name, "Cookies"); inv.items[4].code=5; inv.items[4].price=25; inv.items[4].stock=120;
    strcpy(inv.items[5].name, "Puff"); inv.items[5].code=6; inv.items[5].price=15; inv.items[5].stock=90;
    strcpy(inv.items[6].name, "Roll"); inv.items[6].code=7; inv.items[6].price=12; inv.items[6].stock=150;
    strcpy(inv.items[7].name, "Donut"); inv.items[7].code=8; inv.items[7].price=35; inv.items[7].stock=60;
    strcpy(inv.items[8].name, "Muffin"); inv.items[8].code=9; inv.items[8].price=40; inv.items[8].stock=70;
    strcpy(inv.items[9].name, "Croissant"); inv.items[9].code=10; inv.items[9].price=45; inv.items[9].stock=55;
}

void load_inventory() {
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp) {
        fread(&inv, sizeof(inv), 1, fp);
        fclose(fp);
    } else {
        init_inventory();
    }
}

void save_inventory() {
    FILE *fp = fopen("inventory.dat", "wb");
    if (fp) {
        fwrite(&inv, sizeof(inv), 1, fp);
        fclose(fp);
    }
}

void display_menu() {
    printf("\n=== MENU ===\n");
    for (int i = 0; i < inv.count; i++) {
        printf("%d. %s - Rs.%.2f (Stock: %d)\n", inv.items[i].code, inv.items[i].name, inv.items[i].price, inv.items[i].stock);
    }
}

int find_item(int code) {
    for (int i = 0; i < inv.count; i++) {
        if (inv.items[i].code == code) return i;
    }
    return -1;
}

void input_bill(struct Bill *b) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    b->date.day = tm->tm_mday; b->date.month = tm->tm_mon+1; b->date.year = tm->tm_year+1900;
    
    FILE *fp = fopen("bills.dat", "ab");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        b->bill_no = ftell(fp) / sizeof(struct Bill) + 1;
        fclose(fp);
    } else b->bill_no = bill_count + 1;
    
    printf("\nCustomer Name: "); fflush(stdin); fgets(b->customer_name, 100, stdin); b->customer_name[strlen(b->customer_name)-1]=0;
    printf("Phone: "); scanf("%lld", &b->phone);
    printf("Old Balance: "); scanf("%f", &b->old_balance);
    printf("Payment: "); scanf("%f", &b->payment);
    printf("No. of Items: "); scanf("%d", &b->num_items);
    
    display_menu();
    float subtotal = 0;
    for (int i = 0; i < b->num_items; i++) {
        printf("Item %d code: ", i+1);
        scanf("%d", &b->item_codes[i]);
        int idx = find_item(b->item_codes[i]);
        if (idx == -1 || inv.items[idx].stock == 0) {
            printf("Invalid/Out of stock!\n"); i--; continue;
        }
        printf("Quantity: "); scanf("%d", &b->quantities[i]);
        if (b->quantities[i] > inv.items[idx].stock) {
            printf("Insufficient stock!\n"); i--; continue;
        }
        b->subtotals[i] = b->quantities[i] * inv.items[idx].price;
        subtotal += b->subtotals[i];
        inv.items[idx].stock -= b->quantities[i];
    }
    b->gst = subtotal * GST_RATE;
    b->grand_total = subtotal + b->gst + b->old_balance - b->payment;
}

void calculate_bill(struct Bill *b) {
    // Already calculated in input
}

void save_bill(struct Bill *b) {
    FILE *fp = fopen("bills.dat", "ab");
    if (fp) {
        fwrite(b, sizeof(struct Bill), 1, fp);
        fclose(fp);
    }
    char filename[20];
    sprintf(filename, "bill_%d.txt", b->bill_no);
    print_bill(*b, filename);
}

void load_bills() {
    FILE *fp = fopen("bills.dat", "rb");
    if (!fp) return;
    bill_count = 0;
    while (fread(&bills[bill_count], sizeof(struct Bill), 1, fp) && bill_count < MAX_BILLS) {
        bill_count++;
    }
    fclose(fp);
}

void display_all_bills() {
    system("cls");
    printf("\n=== ALL BILLS ===\n");
    for (int i = 0; i < bill_count; i++) {
        printf("\nBill #%d: %s, Grand Total: Rs.%.2f\n", bills[i].bill_no, bills[i].customer_name, bills[i].grand_total);
    }
}

void search_bill() {
    int opt; char name[100]; int no;
    printf("1. By Bill No  2. By Name: "); scanf("%d", &opt);
    if (opt == 1) {
        printf("Bill No: "); scanf("%d", &no);
        for (int i = 0; i < bill_count; i++) {
            if (bills[i].bill_no == no) {
                print_bill(bills[i], NULL);
                return;
            }
        }
    } else {
        printf("Name: "); fflush(stdin); fgets(name, 100, stdin); name[strlen(name)-1]=0;
        for (int i = 0; i < bill_count; i++) {
            if (strstr(bills[i].customer_name, name)) {
                print_bill(bills[i], NULL);
            }
        }
    }
    printf("Not found!\n");
}

void edit_bill() {
    int no; printf("Bill No: "); scanf("%d", &no);
    for (int i = 0; i < bill_count; i++) {
        if (bills[i].bill_no == no) {
            printf("New Payment: "); scanf("%f", &bills[i].payment);
            calculate_bill(&bills[i]);
            // Re-save all bills
            FILE *fp = fopen("bills.dat", "wb");
            for (int j = 0; j < bill_count; j++) fwrite(&bills[j], sizeof(struct Bill), 1, fp);
            fclose(fp);
            printf("Updated!\n");
            return;
        }
    }
    printf("Not found!\n");
}

void delete_bill() {
    int no; printf("Bill No: "); scanf("%d", &no);
    for (int i = 0; i < bill_count; i++) {
        if (bills[i].bill_no == no) {
            for (int j = i; j < bill_count-1; j++) bills[j] = bills[j+1];
            bill_count--;
            FILE *fp = fopen("bills.dat", "wb");
            for (int j = 0; j < bill_count; j++) fwrite(&bills[j], sizeof(struct Bill), 1, fp);
            fclose(fp);
            printf("Deleted!\n");
            return;
        }
    }
    printf("Not found!\n");
}

void print_bill(struct Bill b, char *filename) {
    if (filename) {
        FILE *f = fopen(filename, "w");
        fprintf(f, "=== BAKERY BILL %d ===\n", b.bill_no);
        fprintf(f, "Customer: %s\nPhone: %lld\nDate: %02d/%02d/%04d\n\n", b.customer_name, b.phone, b.date.day, b.date.month, b.date.year);
        fprintf(f, "Items:\n");
        float sub = 0;
        for (int i = 0; i < b.num_items; i++) {
            fprintf(f, "Code %d: Qty %d @ Rs.%.2f = Rs.%.2f\n", b.item_codes[i], b.quantities[i], 0, b.subtotals[i]);
            sub += b.subtotals[i];
        }
        fprintf(f, "\nSubtotal: Rs.%.2f\nGST (5%%): Rs.%.2f\nOld Bal: Rs.%.2f\nPayment: Rs.%.2f\nGrand Total: Rs.%.2f\n", sub, b.gst, b.old_balance, b.payment, b.grand_total);
        fclose(f);
        printf("Bill saved to %s\n", filename);
    } else {
        // Console print similar
        printf("\n=== BILL %d ===\nCustomer: %s\nGrand Total: Rs.%.2f\n", b.bill_no, b.customer_name, b.grand_total);
    }
}

void inventory_menu() {
    int choice, code, stock;
    float price;
    char name[50];
    printf("\n1. Add Item  2. Update Stock  3. View Inventory\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            if (inv.count < MAX_ITEMS) {
                printf("Code: "); scanf("%d", &inv.items[inv.count].code);
                printf("Name: "); fflush(stdin); fgets(inv.items[inv.count].name, 50, stdin); inv.items[inv.count].name[strlen(inv.items[inv.count].name)-1]=0;
                printf("Price: "); scanf("%f", &inv.items[inv.count].price);
                printf("Stock: "); scanf("%d", &inv.items[inv.count].stock);
                inv.count++;
            }
            break;
        case 2:
            printf("Code: "); scanf("%d", &code);
            int idx = find_item(code);
            if (idx != -1) {
                printf("New Stock: "); scanf("%d", &stock);
                inv.items[idx].stock = stock;
            }
            break;
        case 3:
            printf("\n=== INVENTORY ===\n");
            for (int i = 0; i < inv.count; i++) {
                printf("%d. %s - Rs.%.2f, Stock: %d\n", inv.items[i].code, inv.items[i].name, inv.items[i].price, inv.items[i].stock);
            }
            break;
    }
    save_inventory();
}
