#ifndef yy
#define yy
#define set_bit(var,bit_no) (var) |= (1<<(bit_no))
#define clear_bit(var,bit_no) (var) &= ~(1<<(bit_no))
#define toggle_bit(var,bit_no) (var) ^= (1<<(bit_no))
#define get_bit(var,bit_no) ((var>>bit_no) &(1))
#define assign_bit(var,bit_no,value) do{ if(value==1) set_bit(var,bit_no);\
	                                     else clear_bit(var,bit_no); } while(0)
#endif
