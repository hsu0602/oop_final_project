#include <iostream>
#include <vector>
#include "../HeaderFile/UserInterface.h"
#include "../HeaderFile/CashierUI.h"
using namespace std;
//correct

static const char* category_string[] = {"碗裝泡麵", "包裝餅乾", "利樂包", "寶特瓶", "酒"};




void UserInterface::clearScreen(){
    std::cout << std::flush;
    system("clear");
 }


//correct
void UserInterface::idPage(){

	//this->input_invalid = false;
	
	clearScreen();
	
	// find the goods of chosen category and print it out 
	vector<GoodInventory> good_need_print( search.findInventoriesByCategory(string(category_string[category_now])));
	
	printMenu(good_need_print);
	//cout << "MENU\n";
	int chosen_id = inputId();

	while(chosen_id == INVALID){
		

		// need to print the text to warn user
		clearScreen();
		printMenu(good_need_print);/////////////////////////
		cout << "MENU\n";
		cout << "We don't have this product. please choose the valid id.\n";
		chosen_id = inputId();

	}

	if(chosen_id == BACK){
		
		//back to category page
		this->page_status = CATEGORY_STATUS;

	}
	else{

		this->id_now = chosen_id;
		this->page_status = QUANTITY_STATUS;

	}

}




void UserInterface::recieptPage(){

	this->input_invalid = false;
	clearScreen();
	//virtual
	printReciept();

	int chosen_order = inputReciept();

	while(chosen_order == INVALID){
		this->input_invalid = true;
		clearScreen();
		printReciept();

		//cout << "Please input Valid choice!\n\n";
		chosen_order = inputReciept();
	}

	// when user choose to confirm the purchase
	if(chosen_order == CONFIRM){

		// return reciept to system and clear the reciept
		
		//virtual
		confirm();

		// go back to choose category
		this->page_status = CATEGORY_STATUS;

	}
	// go back to choose category
	else if(chosen_order == BACK){

		this->page_status = CATEGORY_STATUS;
	}
	
	// user choose to delete a good chose before
	else {
		
		//virtual
		deleteOrder(chosen_order);
		
	}


}



int UserInterface::inputId(){
	string ID;
	cout << "Please enter the ID of good you want to buy or press b for backing to previous page:";
	getline(cin, ID);
	
	// back command	
	if(ID == "b")
		return BACK;

	vector<GoodInventory> temp = search.findInventoriesByCategory(category_string[category_now]);
	int size = temp.size();


	// check whether the input is valid
	for(int i = 0; i < size; ++i){
		int temp_id_int = temp[i].getId();

		// convert id form int to string
		string temp_id = to_string(temp_id_int);

		//compare whether they are same
		if(ID == temp_id){
			id_now = temp_id_int;
			return temp_id_int;
		}
	}

	// no matching ID
	return INVALID;
}



int UserInterface::inputReciept(){
	string cmd;
	cout << "You can enter the number which mean the order of good you want to delete of the reciept." << endl;
	cout << "Press c for confirming the reciept or press b for backing to previous page.\n" << endl;
	cout << "Please choose the service you want:";
	getline(cin, cmd);

	// back command
	if(cmd == "b")
		return BACK;

	// confirm command
	if(cmd == "c")
		return CONFIRM;
	
	// judge whether the command is invalid
	// if the command is invalid(true)
	bool cmd_invalid = false;
	for(int i = 0 ; i < cmd.size(); ++i){
		if(cmd[i] < '0' || cmd[i] > '9'){
			cmd_invalid = true;
			break;
		}
	}
	
	if(cmd_invalid)
		return INVALID;

	// convert the order of good want to delete from string to int
	int order = stoi(cmd);

	// the delete order should start from 1 and can't larger than the total order
	if(order <= 0 || order > sizeOfReciept())
		return INVALID;
		
	// legal input then return the index of vector(order - 1)
	if(order <= sizeOfReciept() && order > 0)
		return (order - 1);

	return INVALID;

}



void UserInterface::printborder(){
    std::cout << FORE_GROUND_BLACK << BACK_GROUND_GREEN << ' ' << RESET;
}
void UserInterface::printcontent_b(std::string str){
    std::cout << FORE_GROUND_BLACK << BACK_GROUND_BLUE << str << RESET;
}
void UserInterface::printcontent_w(std::string str){
    std::cout << FORE_GROUND_BLACK << BACK_GROUND_WHITE << str << RESET;
}

void UserInterface::printMenu(std::vector <GoodInventory> &menu){
    std::string tmp;
    std::vector<std::string> mu;
    for (int i = 0; i < WIDe; ++i) tmp.push_back(' ');
    mu.push_back(tmp);
    tmp.clear();
    for (int i = 0; i < ((WIDe - 1) / 2) - menu[0].getCategory().size()/2 - 3; ++i) tmp.push_back(' ');
    tmp += "  類別 :  ";
    tmp += menu[0].getCategory();
    for (int i = 0; i < WIDe - (((WIDe - 1) / 2) - menu[0].getCategory().size() / 2) - menu[0].getCategory().size() - 3; ++i) tmp.push_back(' ');
    mu.push_back(tmp);
    tmp.clear();
    for (int i = 0; i < WIDe; ++i) tmp.push_back(' ');
    mu.push_back(tmp);
    tmp.clear();
    for (int i = 0; i < 8; ++i) tmp.push_back(' ');
    tmp += "ID";
    for (int i = 0; i < 6; ++i) tmp.push_back(' ');
    tmp += "Name";
    for (int i = 0; i < 28; ++i) tmp.push_back(' ');
    tmp += "Price";
    for (int i = 0; i < 11; ++i) tmp.push_back(' ');
    tmp += "Quantity";
    for (int i = 0; i < 8; ++i) tmp.push_back(' ');
    mu.push_back(tmp);
    tmp.clear();
    for (int i = 0; i < WIDe; ++i) tmp.push_back(' ');
    mu.push_back(tmp);
    tmp.clear();
    for (int i = 0; i < menu.size(); ++i){
        for (int j = 0; j < 8; ++j) tmp.push_back(' ');
        std::string q = std::to_string(menu[i].getQuantity());
        std::string p = std::to_string(menu[i].getPrice());
        std::string d = std::to_string(menu[i].getId());
        tmp += d;
        for (int j = 0; j < 8 - d.size(); ++j) tmp.push_back(' ');
        tmp += menu[i].getName();
        for (int j = 0; j < 32 - menu[i].getName().size(); ++j) tmp.push_back(' ');
        tmp += "NT$";
        tmp += p;
        for (int j = 0; j < 16 - p.size() - 3; ++j) tmp.push_back(' ');
        tmp += q;
        for (int j = 0; j < 16 - q.size(); ++j) tmp.push_back(' ');
        mu.push_back(tmp);
        tmp.clear();
        for (int i = 0; i < WIDe; ++i) tmp.push_back(' ');
        mu.push_back(tmp);
        tmp.clear();
    }

    for (int i = 0; i < WIDe; ++i) tmp.push_back(' ');
    mu.push_back(tmp);
    tmp.clear();

    for (int i = 0; i < WIDe; ++i) tmp.push_back('-');
    mu.push_back(tmp);
    tmp.clear();

    for (int i = 0; i < mu.size(); ++i){
        printborder();
        printborder();
        if (i % 2)
            printcontent_w(mu[i]);
        else
            printcontent_b(mu[i]);
        printborder();
        printborder();
        std::cout << '\n';
    }
}