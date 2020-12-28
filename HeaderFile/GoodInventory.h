#ifndef _GOODINVENTORY_H_
#define _GOODINVENTORY_H_

#include <vector>
#include <string>
#include "Good.h"


class GoodInventory: public Good{
    
    public:
 
        
        //Constructor
        GoodInventory(int input_id, std::string input_category, std::string input_name, int input_price, int input_quantity);
         
        
   
        //return the quantity of the goods
        int getQuantity() const;

    
    
    protected:

        int quantity;

}

#endif