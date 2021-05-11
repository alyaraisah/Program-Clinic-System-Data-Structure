struct Order_Treatment{
    char item_name[50];
    int price;
    Order_Treatment* next;
};

struct Orders{
    int order_number;
    char patient_name[50];
    int age;
    char gender[1];
    int total_price;
    Order_Treatment* items;
    Orders* next;
};

struct Queue{
    Orders* front;
    Orders* back;
};

struct Complete{
    int num;
    char patient_complete[50];
    int payment;
    bool paid = false;
    Complete* next;
};

struct csv{
    int csv_num;
    char csv_name[50];
    int csv_payment;
    int csv_age;
    char csv_gender[1];
    csv* next;
};