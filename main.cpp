#include<iostream>
#include<string.h>
#include<fstream>
#include "struct.hpp"
#include "function.hpp"
#include<vector>
using namespace std;

int main(){
    Q.front = NULL;
    Q.back = NULL;
    int m;
    char read;
    cout<<"========================================"<<endl;
    cout<<"             KLINIK HORAY"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
    do{
        cout<<"1. Add New Patient\n2. Serve Patient\n3. Patient List\n4. Payment\n5. Delete Patient\n6. Update Patient\n7. See Data\n8. Undo an order\n9. Export to CSV\n10. Exit Program"<<endl;
        cout<<"========================================"<<endl;
        cout<<"Select Menu: ";cin>>m;
        switch (m)
        {
            case 1:
                add_patient(Q);
                cout<<"\nAdded!"<<endl;
                break;
            case 2:
                //addData(Q, complete_list);
                served(Q, served_list, complete_list);
                break;
            case 3:
                cout<<"\n--Patient List--"<<endl;
                printOrder(Q.front);
                break;
            case 4:
                cout<<"\n--Completed Treatment--"<<endl;
                printComplete(complete_list);
                completeOrder(complete_list, csv_list);
                //completeOrder();
                break;
            case 5:
                deleteOrder(Q, Q.front);
                break;
            case 6:
                update(Q);
                break;
            case 7:
                printCSV(csv_list);
                break;
            case 8:
                // undo orderan terbaru
                undo_order(Q, Q.front);
                break;
            case 9:
                // Export to CSV 
                createCSV(csv_list);
                cout << endl;
                cout << "Read data CSV file? y for yes, other key for no" << endl;
                cin >> read;
                if (read == 'y' || read == 'Y'){
                    readCSV();
                }
            default:
                break;
        }
        cout << endl;
    } 
    while(m != 10);
}
