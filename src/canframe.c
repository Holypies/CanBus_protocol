#include <stdio.h>
#include "canframe.h"

struct Canframe_8bit{
    uint_64 frame;
};



Canframe_8bit* create_canframe(){
    Canframe_8bit* self =(Canframe_8bit*)malloc(sizeof(Canframe_8bit));
    if(self!=NULL){
        self->frame = 0x00;
    }
    return self;
}

void destroy_canframe(Canframe_8bit* self){
    if(self!=NULL){
        free(self);
    }
}

// setters
void set_can_identifier(Canframe_8bit* self, uint_8 bits){    
    uint_64 bits_64 = 0x0;
    uint_64 identifier_mask = ((uint_64)0x8FF) << 0x2B;
    bits_64 |= bits;
    bits_64 <<= 0x2B; // shift bits to correct placement
    self->frame &= ~identifier_mask;
    self->frame |= bits_64;
}


void set_can_rtr(Canframe_8bit* self, uint_8 bit){
    uint_64 bit_64 = 0x00;
    uint_64 rtr_mask = ((uint_64)0x9) << 0x2A;
    bit_64 |= bit;
    bit_64 <<= 0x2A; // shift bit to correct placement
    self->frame &= ~rtr_mask;
    self->frame |= bit_64;
}

void set_can_ide(Canframe_8bit* self, uint_8 bit){

}

void set_can_dlc(Canframe_8bit* self, uint_8 bit){

}

void set_can_data(Canframe_8bit* self, uint_64 bit){

}

void set_can_sender(Canframe_8bit* self, uint_8 bit){

}

void set_full_can_frame(Canframe_8bit* self, uint_8 frame){

}


// getters
uint_8 get_can_identifier(const Canframe_8bit* self){}
uint_8 get_can_rtr(const Canframe_8bit* self){}
uint_8 get_can_ide(const Canframe_8bit* self){}
uint_8 get_can_dlc(const Canframe_8bit* self){}
uint_64 get_can_data(const Canframe_8bit* self){}
uint_8 get_can_sender(const Canframe_8bit* self){}

void get_full_can_frame(const Canframe_8bit* self){}