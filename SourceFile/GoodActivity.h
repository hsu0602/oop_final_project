GoodActivity(int input_id, std::string input_category, std::string input_name, int input_price, int input_quantity, time_t input_t); Good(input_id, input_category, input_name, input_price),
                                                                                                                                     quantity(input_quantity),
                                                                                                                                     time(input_t)
                                                                                                                                     {}

GoodActivity(int input_id, std::string input_category, std::string input_name, int input_price, int input_quantity, time_t input_t) : GoodInventory(input_id, input_category, input_name, input_price, input_quantity),
                                                                                                                                      time(input_t)
                                                                                                                                      {}

time_t getTime() const{
    return time;
}