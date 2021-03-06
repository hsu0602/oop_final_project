#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H
#include <vector>
#include "../HeaderFile/GoodInventory.h"
#include "../HeaderFile/SearchSystem.h"

#define SNACK 0
#define DRINK 1
#define DAILY 2
#define CLOTHES 3
#define ELECTRONIC 4

#define INVALID -100 
#define VALID -200

// page option
#define BACK -1
#define QUIT -2
#define DELETE -3
#define CONFIRM -4 
#define RECIEPT -5
#define NEWGOOD -6
#define OLDGOOD -7



#define FORE_GROUND_BLACK "\033[30m"
#define BACK_GROUND_WHITE "\033[47m"
#define BACK_GROUND_GREEN "\033[42m"
#define BACK_GROUND_BLUE "\033[46m"
#define RESET "\033[0m"
#define WIDE 101
#define WIDe 80

enum status {CATEGORY_STATUS, ID_STATUS, QUANTITY_STATUS, RECIEPT_STATUS, NAME_STATUS, PRICE_STATUS, NEWGOOD_STATUS, OLDGOOD_STATUS};

class UserInterface{

    protected:

        UserInterface(){}

        //=============Page===============
        virtual void categoryPage() = 0;

        void idPage();


        virtual void quantityPage() = 0;

        void recieptPage();

        //=================================



        //=============input==================
    	virtual int inputCategory() = 0;


	    // 1.Need to see if we have the chosen ID
		//   If we don't have, it's a invalid input--> return INVALID.
		// 2.return the valid id input
		//   input 'b' means back to the last page, return BACK
		// 3.same as above 3.
    	int inputId();


	    // 1.Need to see if we have the chosen Quantity.
		//   If we don't have enough goods, tell customer that the goods has only X left
		//   and return INVALID
		// 	 
		// 2.return the valid id input
		//   input 'b' means back to choose id --> return BACK
    	virtual int inputQuantity() = 0;


        int inputReciept();


        // see the size of reciept
        virtual int sizeOfReciept() = 0;
        //====================================
    	
        // recieve list of goods and print with nice format
		// need to show id, name, quantity, and price $        
        void printMenu(std::vector<GoodInventory> &menu);

        

        void printborder();
    
        void printcontent_b(std::string str);
        void printcontent_w(std::string str);
    

        virtual void printReciept() = 0;
       

        // confirm the reciept
        virtual void confirm() = 0;

        virtual void addReciept() = 0;

        virtual void deleteOrder(int chosen_order) = 0;


        

        void clearScreen();
        	

    protected:


    	


    	// the recent chose ategory
    	int category_now;
    	
    	// the recent chose id
    	int id_now;

        int quantity_now;

    	// check this variable to determine
		// whether to print warning  
    	bool input_invalid = false;

    	//check if it's true terminate the program
    	bool terminate = false;

    	// indicate what page is user in
    	status page_status = CATEGORY_STATUS;


    	//used to interact with searchSystem;
    	SearchSystem search;


};


#endif