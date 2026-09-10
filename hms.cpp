#include <iostream>
#include <fstream>	// provides functionality for reading from and writing to files
#include <string>	// Include the string library
#include <iomanip>	// Include the iomanip library for formatting I/O 

using namespace std ;

struct Hotel
{
    int room_no ;
    string name ;
    string address ;
    string phone ;
    int days ;
    float fare ;
} ;

void display_header( const string &title )	// to display header 
{
    cout << "\n=============================\n" ;
    cout << title << "\n" ;
    cout << "=============================\n" ;
}

void add()
{
    Hotel h ;
    int roomNumber ;
    cout << "\nEnter Room No (1-100): " ;
    cin >> roomNumber ;

    ifstream infile("hotel_records.txt") ;
    bool roomBooked = false ;

    if (infile.is_open())
	{
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            if (h.room_no == roomNumber) // Check if room is already booked
			{ 
                roomBooked = true ;
                break ;
            }
        }
        
        infile.close() ;
    }

    if (roomBooked)
	{
        cout << "\nRoom already booked!\n" ;
        return ;
    }

    h.room_no = roomNumber ; // Assign room number
    cout << "Enter Name: " ;
    cin.ignore() ;
    getline(cin, h.name) ;
    cout << "Enter Address: " ;
    getline(cin, h.address) ;
    cout << "Enter Phone: " ;
    getline(cin, h.phone) ;
    cout << "Enter Number of Days: " ;
    cin >> h.days ;

    h.fare = h.days * 900 ;

    ofstream outfile("hotel_records.txt", ios::app) ;
    if (outfile.is_open())
	{
        outfile << h.room_no << endl ;
        outfile << h.name << endl ;
        outfile << h.address << endl ;
        outfile << h.phone << endl ;
        outfile << h.days << endl ;
        outfile << h.fare << endl << endl ;
        
        outfile.close() ;
        cout << "\nRoom booked successfully! Total Fare: $" << h.fare << "\n" ;
    } 
    
	else
	{
        cout << "\nError saving booking!\n" ;
    }
}

void display(int room)
{
    Hotel h ;
    ifstream infile("hotel_records.txt") ;
    bool found = false ;

    if (infile.is_open())
	{
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            if (h.room_no == room)
			 {
                display_header("Customer Details") ;
                cout << "Room No: " << h.room_no << "\n" ;
                cout << "Name: " << h.name << "\n" ;
                cout << "Address: " << h.address << "\n" ;
                cout << "Phone: " << h.phone << "\n" ;
                cout << "Number of Days: " << h.days << "\n" ;
                cout << "Total Fare: $" << h.fare << "\n" ;
                
                found = true ;
                break ;
            }
        }
        infile.close() ;
    }

    if (!found) 
	{
        cout << "\nRoom not found!\n" ;
    }
}

void view_all()
{
    Hotel h ;
    ifstream infile("hotel_records.txt") ;
    bool found = false ;

    if (infile.is_open())
	{
        display_header("All Booked Rooms") ;
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            cout << "Room No: " << h.room_no << ", Name: " << h.name << ", Days: " << h.days << ", Fare: $" << h.fare << "\n" ;
            found = true ;
        }
        infile.close() ; 
    }

    if (!found)
	{
        cout << "\nNo rooms are booked!\n" ;
    }
}

void delete_record(int room)
{
    Hotel h ;
    ifstream infile("hotel_records.txt") ;
    ofstream tempFile("temp.txt") ;
    bool found = false ;

    if (infile.is_open() && tempFile.is_open())
	{
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            if (h.room_no != room)
			{
                tempFile << h.room_no << endl ;
                tempFile << h.name << endl ;
                tempFile << h.address << endl ;
                tempFile << h.phone << endl ;
                tempFile << h.days << endl ;
                tempFile << h.fare << endl ;
            }
            
			else
			{
                found = true ;
            }
        }
        
        infile.close() ;
        tempFile.close() ;

        remove("hotel_records.txt") ;
        rename("temp.txt", "hotel_records.txt") ;

        if (found)
		{
            cout << "\nRecord deleted successfully!\n" ;
        }
		else
		{
            cout << "\nRoom not found!\n" ;
        }
    }
}

void edit_record(int room)
{
    Hotel h ;
    ifstream infile("hotel_records.txt") ;
    ofstream tempFile("temp.txt") ;
    bool found = false ;

    if (infile.is_open() && tempFile.is_open())
	{
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            if (h.room_no == room)
			{
                cout << "\nEnter New Details\n" ;
                cout << "Name: " ;
                cin.ignore() ;
                getline(cin, h.name) ;
                cout << "Address: " ;
                getline(cin, h.address) ;
                cout << "Phone: " ;
                getline(cin, h.phone) ;
                cout << "Number of Days: " ;
                cin >> h.days ; 
                h.fare = h.days * 900 ;
                found = true ;
            }
            
            tempFile << h.room_no << endl ;
            tempFile << h.name << endl ;
            tempFile << h.address << endl ;
            tempFile << h.phone << endl ;
            tempFile << h.days << endl ;
            tempFile << h.fare << endl ;
        }
        
        infile.close() ; 
        tempFile.close() ;

        remove("hotel_records.txt") ;
        rename("temp.txt", "hotel_records.txt") ;

        if (found)
		{
            cout << "\nRecord updated successfully!\n" ;
        }
		else
		{
            cout << "\nRoom not found!\n" ;
        }
    }
}

void calculate_revenue()
{
    Hotel h ;
    ifstream infile("hotel_records.txt") ;
    float totalRevenue = 0 ;

    if (infile.is_open())
	{
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            totalRevenue = totalRevenue + h.fare ;
        }
        infile.close() ;
    }

    display_header("Total Revenue") ;
    cout << "Total Revenue: $" << totalRevenue << "\n" ;
}

void room_availability()
{
    bool rooms[100] = {false} ;
    Hotel h ;
    ifstream infile("hotel_records.txt") ;

    if (infile.is_open())
	{
        while (infile >> h.room_no >> ws && getline(infile, h.name) && getline(infile, h.address) && getline(infile, h.phone) && infile >> h.days && infile >> h.fare )
		{
            rooms[h.room_no - 1] = true ;
        }
        infile.close() ;
    }

    display_header("Available Rooms") ;
    for (int i=0 ; i<100 ; i++)
	{
        if (!rooms[i])
		{
            cout << "Room " << ( i+1 ) << " is available.\n" ;
        }
    }
}

int main()
{
    int choice;

    do {
        display_header("Hotel Management System") ;
        
        cout << "1. Book a Room " << endl ;
        cout << "2. Display Customer Record" << endl ;
        cout << "3. View All Rooms" << endl ;
        cout << "4. Delete Record" << endl ;
        cout << "5. Edit Record" << endl ;
        cout << "6. Check Room Availability" << endl ;
        cout << "7. Calculate Revenue" << endl ;
        cout << "8. Exit" << endl << endl ;
        
        cout << "Enter your choice : " ;
        cin >> choice ;

        switch (choice)
		{
            case 1:
            	{
            		add() ;
            	    break ;
				}
                
            case 2:
				{
	                int room ;
	                cout << "\nEnter Room No: " ;
    	            cin >> room ;
        	        display(room);
            	    break ;
            	}
            	
            case 3:
            	{
            		view_all() ;
                	break ;
				}
               
            case 4:
				{
    	            int room ; 
        	        cout << "\nEnter Room No: " ;
            	    cin >> room ;
                	delete_record(room) ;
                	break ;
            	}
            	
            case 5:
				{
	                int room ;
    	            cout << "\nEnter Room No: " ;
                	cin >> room ;
        	        edit_record(room) ;
            	    break ;
            	}
            	
            case 6:
            	{
            		room_availability() ;
                	break ;
				}
                
            case 7:
            	{
            		calculate_revenue() ;
                	break ;
				}
                
            case 8:
            	{
            		cout << "\nExiting...\n" ;
                	break ;
				}
                
            default:
            	{
            		cout << "\nInvalid choice! Try again.\n" ;
				}
                
        }
    } while (choice != 8) ;

    return 0 ;
}
