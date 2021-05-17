#include"declare.hpp"

int order_number = 0;
// Initialize

void add_patient(Queue& Q){
    Orders* new_order = new Orders;
    new_order->next = NULL;

    // Increment 1 to order number and add to order number
    order_number++;
    new_order->order_number = order_number; 

    // Get patient name
    char name[50];
    cout<<"Patient Name\t: ";
    cin.ignore();
    cin.getline(name, 50);
    strcpy(new_order->patient_name, name);

    //Get patient age
    int age;
    cout<<"Age\t\t: ";
    cin >> age;
    new_order->age = age;
    

    //Get patient gender
    char gender;
    cout << "Gender (M/F)\t: ";
    cin >> gender;
    new_order->gender = gender;

    // Assign the treatment list that patient choose in the order
    Order_Treatment* Item_List = NULL;
    char add_new_item = 'y';
    while(add_new_item == 'y'){
        add_items(Item_List);
        cout<<"Another Treatment? y for yes, other key for no\n";
        cin>>add_new_item;
    }
    new_order->items = Item_List;

    // Calculate total price
    int total_price = 0;
    while(Item_List != NULL){
        total_price += (Item_List->price);
        Item_List = Item_List->next;
    }
    new_order->total_price = total_price;

    // Insert into queue
    if(Q.front == NULL){
        Q.front = new_order;
        Q.back = new_order;
    }else{
        Q.back->next = new_order;
        Q.back = Q.back->next;
    }
}

void add_items(Order_Treatment* &items){
    Order_Treatment* new_item = new Order_Treatment;
    new_item->next = NULL;

    // Select item name
    int select_item;
    cout<<"Items"<<endl;
    cout<<"1. Chemical Peel\tRp. 500.000\n2. Laser Skin\t\tRp. 1.100.000\n3. Facial\t\tRp. 800.000\n4. Botox\t\tRp. 1.500.000\n5. Filler\t\tRp. 6.000.000"<<endl;
    cout<<"Select Item: ";cin>>select_item;
    switch (select_item)
    {
    case 1:
        strcpy(new_item->item_name, "Chemical Peel");
        new_item->price = 500000;
        break;  
    case 2:
        strcpy(new_item->item_name, "Laser Skin");
        new_item->price = 1100000;  
        break;
    case 3:
        strcpy(new_item->item_name, "Facial");
        new_item->price = 800000;    
        break;
    case 4:
        strcpy(new_item->item_name, "Botox");
        new_item->price = 1500000;      
        break;
    case 5:
        strcpy(new_item->item_name, "Filler");
        new_item->price = 6000000;
        break;
    default:
        cout << "Masukan angka 1-5!!\n";
        strcpy(new_item->item_name, "-");
        new_item->price = 0;
        break;
    }

    // Insert into linked list
    if(items == NULL){
        items = new_item;
    }else if(items->next == NULL){
        items->next = new_item;
    }else{
        Order_Treatment* pointer = items;
        while(pointer->next != NULL){
            pointer = pointer->next;
        }
        pointer->next = new_item;
    }
}

void printOrder(Orders* front){
    if(front != NULL){
        do{
            cout<<"============================================="<<endl;
            cout<<"Patient Number: "<< front->order_number<<endl;
            cout<<"Patient Name: "<< front->patient_name<<endl;
            cout<<"Total Price: " << front->total_price<<endl;
            cout<<"Price Details: "<<endl;
            cout<<"\tTreatment\tPrice"<<endl;
            Order_Treatment* items;
            items = front->items;
            while (items != NULL){
                if (items->price != 0){
                    cout<<"\t"<<items->item_name<<"\t"<<items->price<<endl;
                }
                items = items->next;
            }
            cout<<"============================================="<<endl;
            cout<<endl;
            front = front->next;
        }while(front!=NULL);
    }
    else{
        cout<<"No Patient!"<<endl;
    }
}

void served(Queue &Q, Orders* &Served, Complete* &Completed){

    Complete* new_complete = new Complete;
    Orders* now_served = Q.front;
    new_complete->next = NULL;

    if(now_served != NULL){
        strcpy(new_complete->patient_complete, now_served->patient_name);
        new_complete->num = now_served->order_number;
        new_complete->payment = now_served->total_price;
        new_complete->age = now_served->age;
        new_complete->gender = now_served->gender;

        Q.front = now_served->next;
        now_served->next = NULL;
        if(Served == NULL){
            Served = now_served;
        }else if(Served->next == NULL){
            Served->next = now_served;
        }else{
            Orders* pointer = Served;
            while(pointer->next!=NULL){
                pointer = pointer->next;
            }
            pointer->next = now_served;
        }
        if(Completed == NULL){
        Completed = new_complete;
        }
        else if(Completed->next == NULL){
            Completed->next = new_complete;
        }
        else{
            Complete* pointer = Completed;
            while(pointer->next != NULL){
                pointer = pointer->next;  
            }
            pointer->next = new_complete; 
        }
        cout<< now_served->patient_name<<"'s treatment has been completed!"<<endl;
    }else{
        cout<<"No patient to serve!"<<endl;
    }
}

void printComplete(Complete* head){
    if(head != NULL){
        do{
            if(head->paid == false){
                cout<<head->num<<". "<<head->patient_complete << " ("<< head->age<< "/ "<< head->gender<<") : "<<head->payment<<"  NOT PAID"<<endl;
            } else {
                cout<<head->num<<". "<<head->patient_complete << " ("<< head->age<< "/ "<< head->gender<<") : "<<head->payment<<"  PAID"<<endl;
            }
            head = head->next;
        }while(head!=NULL);
    }
    else{
        cout<<"No Completed Treatment!"<<endl;
    }
}


void printCSV(csv* head){

    if(head != NULL){
        do{
            cout<<head->csv_num<<", "<<head->csv_name<<", "<<head->csv_age<<", "<<head->csv_gender<<", "<<head->csv_payment<<";"<<endl;
            head = head->next;
        }while(head!=NULL);
    }
    else{
        cout<<"CSV has no data!"<<endl;
    }
}

// read data from CSV
void readCSV(){
    ifstream ip("PatientData.csv");

    ip.is_open();
    string num;
    string name;
    string age;
    string gender;
    string payment;
    if(!ip.fail()){
        cout << endl;
        cout << "Patients Data in CSV" << endl;
        while(ip.good()){
           getline(ip, num, ',');
           getline(ip, name, ',');
           getline(ip, age, ',');
           getline(ip, gender, ',');
           getline(ip, payment, ';');
           cout<< num <<","<<name<<", "<<age<<", "<<gender<< ", " << payment<<";"<<endl;
        }
    } else {
        cout << "CSV has no Data" << endl;
    }
    ip.close();
}

bool file_exists(const std::string& str)
{
   std::ifstream fs(str);
   return fs.is_open();
}

void createCSV(csv* head){

    std::ofstream myfile;
    if (file_exists("PatientData.csv")==false){
        myfile.open ("PatientData.csv", std::ios_base::app);
        myfile<<"Number,Name,Gender,Age,Payment Total\n";
        if(head != NULL){
            do{
                myfile<<head->csv_num<<","<<head->csv_name<<","<<head->csv_age<<","<<head->csv_gender<<","<<head->csv_payment<<endl;
                head = head->next;
            }while(head!=NULL);
            myfile.close();
        } else{
            cout<<"CSV has no data!"<<endl;
        }
    } else {
        myfile.open ("PatientData.csv", std::ios_base::app);
        if(head != NULL){
            do{
                myfile<<head->csv_num<<","<<head->csv_name<<","<<head->csv_age<<","<<head->csv_gender<<","<<head->csv_payment<<endl;
                head = head->next;
            }while(head!=NULL);
            myfile.close();
        } 
        else{
            cout<<"CSV has no data!"<<endl;
        }
    }
}

void completeOrder(Complete* head, csv* &added){

    // kurang error handling ketika : orderannya hanya satu dan kita salah input nomor payment
    // harusnya keluar note "No patient found with that number!" tapi malah exit program
    
    int paid, n;
    csv* new_csv = new csv;
    new_csv->next = NULL;
    Complete* convert = head;
    Complete* pointer = head;

    if(convert != NULL){
        cout<<"Which patient number has been paid?"<<endl;
        cin>>paid;
        n = paid-1;
        while(convert != NULL){
            if(n==0 && head->num==1){
                if(head->paid == true){
                    cout<<"That patient has already paid!"<<endl;
                    break;
                } else {
                    strcpy(new_csv->csv_name, head->patient_complete);
                    new_csv->csv_num = head->num;
                    new_csv->csv_payment = head->payment;
                    new_csv->csv_age = head->age;
                    new_csv->csv_gender = head->gender;

                    head->paid = true;
                    if(added == NULL){
                         added = new_csv;
                    }
                    else if(added->next == NULL){
                        added->next = new_csv;
                    }
                    else{
                        csv* pointer = added;
                        while(pointer->next != NULL){
                            pointer = pointer->next;  
                        }
                        pointer->next = new_csv; 
                    }
                    cout<<"Data Has been succesfully added to csv!"<<endl;
                    break;  
                    }      
            } else if(pointer->num == n && pointer->next->num == paid){
                if(pointer->next->paid == true){
                    cout<<"That Patient has already paid!"<<endl;
                    break;
                } else {
                    strcpy(new_csv->csv_name, pointer->next->patient_complete);
                    new_csv->csv_num = pointer->next->num;
                    new_csv->csv_payment = pointer->next->payment;
                    new_csv->csv_age = pointer->next->age;
                    new_csv->csv_gender = pointer->next->gender;

                    pointer->next->paid = true;
                    if(added == NULL){
                        added = new_csv;
                    }
                    else if(added->next == NULL){
                        added->next = new_csv;
                    }
                    else{
                        csv* pointer = added;
                        while(pointer->next != NULL){
                            pointer = pointer->next;  
                        }
                        pointer->next = new_csv; 
                    }
                    cout<<"Data Has been succesfully added to csv!"<<endl;
                    break;
                }
            } else if (pointer->num == paid){
                if (pointer->paid == true){
                    cout<<"That Patient has already paid!"<<endl;
                    break;
                } else {
                    strcpy(new_csv->csv_name, pointer->patient_complete);
                    new_csv->csv_num = pointer->num;
                    new_csv->csv_payment = pointer->payment;
                    new_csv->csv_age = pointer->age;
                    new_csv->csv_gender = pointer->gender;

                    pointer->paid = true;
                    if(added == NULL){
                        added = new_csv;
                    }
                    else if(added->next == NULL){
                        added->next = new_csv;
                    }
                    else{
                        csv* pointer = added;
                        while(pointer->next != NULL){
                            pointer = pointer->next;  
                        }
                        pointer->next = new_csv; 
                    }
                    cout<<"Data Has been succesfully added to csv!"<<endl;
                    break;
                }
            }
                else if(pointer->num != paid){
                pointer = pointer->next;
            }   else {
                cout<<"No patient found with that number!"<<endl;
            }
            convert = convert->next;
        }
    }
}

void update(Queue &Q){
    int up;
    Orders* change = new Orders;
    change->next = NULL;
    Order_Treatment* Item_List = NULL;
    Orders* pointer = Q.front;
    Orders* prev_pointer = NULL;
    bool changed = false;

    if(Q.front != NULL){
        cout<<"Which patient number should be changed?"<<endl;
        cin>>up;
        if(Q.front->order_number == up){
            changed = true;
        }else if(Q.front->next->order_number == up){
            prev_pointer = Q.front;
            pointer = Q.front->next;
            changed = true;
        }else{
            while(pointer != NULL){
                if(pointer->order_number == up){
                    changed = true;
                    break;
                }
                prev_pointer = pointer;
                pointer = pointer->next;
            }
        }
    }else{
        changed = true;
        cout<<"There are no patient!"<<endl;
    }

    if(changed){
        cout<<"Input new treatment:"<<endl;
        char add_new_item = 'y';
        while(add_new_item == 'y'){
            add_items(Item_List);
            cout<<"New Item? y for yes, other key for no\n";
            cin>>add_new_item;
        }
        change->items = Item_List;

        // Calculate total price
        int total_price = 0;
        while(Item_List != NULL){
            total_price += (Item_List->price);
            Item_List = Item_List->next;
        }
        change->total_price = total_price;

        strcpy(change->patient_name, pointer->patient_name);
        change->order_number = pointer->order_number;
        change->total_price = pointer->total_price;
        change->age = pointer->age;
        change->gender= pointer->gender;
        
        if(pointer->next != NULL){
            change->next = pointer->next;
        }else{
            Q.back = change;
        }
        if(prev_pointer!=NULL){
            prev_pointer->next = change;
        }
        bool change_on_front = false;
        if(pointer == Q.front){
            change_on_front = true;
        }
        pointer = change;
        if(change_on_front){
            Q.front = pointer;
        }
        cout<<"Change successful!"<<endl;
    }
    else{
        cout<<"No patient found with that number!"<<endl;
    }
}

void deleteOrder(Queue &Q, Orders* &deletion){
    int del, n;

    Orders* erase = Q.front;
    Orders* pointer = deletion;

    if(erase != NULL){
        cout<<"Which patient's number should be deleted?"<<endl;
        cin>>del;
        n=del-1;
        while(erase != NULL){
            if(Q.front->next == NULL){
            	Q.front = NULL;
            	Q.back = NULL;
            	cout<<"Deletion successful!"<<endl;
            }else if(del == Q.front->order_number){
                Q.front = pointer->next;
                pointer->next = pointer->next->next;
                cout<<"Deletion successful!"<<endl;
                break;
            } else if(pointer->order_number == n && pointer->next->order_number == del){
            	if(pointer->next->next == NULL){
            		pointer->next = NULL;
            		Q.back = pointer;
            		cout<<"Deletion successful!"<<endl;
            	}else{
		            pointer->next = pointer->next->next;
		            pointer = pointer->next;
		            cout<<"Deletion successful!"<<endl;
		        }
            } else if(pointer->order_number != n){
                pointer = pointer->next;
            } else {
                cout<<"No patient found with that number!"<<endl;
                break;
            }
            erase = erase->next;
        }
    }else{
        cout<<"There are no patient!"<<endl;
    }
}

void undo_order(Queue& Q, Orders* &deletion){
    Orders* erase = Q.front;
    Orders* pointer = deletion;
    if(erase == NULL){
        erase = nullptr;
        cout << "There are no patient to delete!";
    } else if (Q.front->next == NULL){
        Q.front = nullptr;
        Q.back = nullptr;
        cout << "Last patient has been deleted!";
    } else if (pointer->next->next == NULL){
        pointer->next = NULL;
        Q.back = pointer;
        cout << "Last patient has been deleted!";
    }  else {
        while(pointer->next->next != NULL){
            pointer = pointer->next;
        }
        pointer->next = nullptr;
        Q.back = pointer;
        cout << "Last patient has been deleted!";
    } 
}