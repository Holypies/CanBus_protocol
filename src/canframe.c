#include <stdio.h>
#include "canframe.h"

#define MAX_FRAMES 10

// canframe for 8-bit data storeage is 55-bit long
// there will be 9-bit padding 





struct Canframe_8bit{
    uint_64 frame;
};

static Canframe_8bit global_mem[MAX_FRAMES];
static uint_8 pool_occupied[MAX_FRAMES] = {0};



Canframe_8bit* create_canframe_8bit(){
    for(int i=0; i<MAX_FRAMES;i++){
        if(!pool_occupied[i]){
            pool_occupied[i] = 1;
            global_mem[i].frame =0x00;
            return &global_mem[i]; 
        }
    }
    return NULL;

}

void destroy_canframe_8bit(Canframe_8bit* self){
    uint_8 index = self - global_mem;

    if(index < MAX_FRAMES){
        pool_occupied[index]= 0;
        global_mem[index].frame = 0;
    }
}


// setters
void set_can_identifier(Canframe_8bit* self, uint_8 bits){    
    uint_64 bits_64 = 0x0;
    uint_64 identifier_mask = ((uint_64)0x8FF) << 43;
    bits_64 |= bits;
    bits_64 <<= 43; // shift bits to correct placement
    self->frame &= ~identifier_mask;
    self->frame |= bits_64;
}

void set_can_rtr(Canframe_8bit* self, uint_8 bit){
    // 0 for dominant and 1 for recessive
    uint_64 bit_64 = 0x00;
    uint_64 rtr_mask = ((uint_64)0x4) << 40;
    bit_64 |= bit;
    bit_64 <<= 40; // shift bit to correct placement
    self->frame &= ~rtr_mask;
    self->frame |= bit_64;
}

void set_can_ide(Canframe_8bit* self, uint_8 bit){
    // need to be 0 for 11 bit identifier which means it
    // will not be used in this example
}

void set_can_dlc(Canframe_8bit* self, uint_8 bits){
    uint_64 bit_64 = 0x00;
    uint_64 dlc_mask = ((uint_64)0xF) << 36;
    bit_64 |= bits;
    bit_64 <<= 36; // shift bit to correct placement
    self->frame &= ~dlc_mask;
    self->frame |= bit_64;
}

void set_can_data(Canframe_8bit* self, uint_64 bits){
    uint_64 bit_64 = 0x00;
    uint_64 data_mask = ((uint_64)0xFF) << 28;
    bit_64 |= bits;
    bit_64 <<= 28; // shift bit to correct placement
    self->frame &= ~data_mask;
    self->frame |= bit_64;
}

//void set_can_sender(Canframe_8bit* self, uint_8 bit){}

void set_full_canframe(Canframe_8bit* self, uint_64 frame){
    self->frame = frame;
}


// getters
uint_8 get_can_identifier(const Canframe_8bit* self){
    uint_64 bits_64 = 0x00;
    uint_64 identifier_mask = ((uint_64)0x8FF) << 43;
    uint_8 identifier_bits = 0;
    bits_64 = self->frame & identifier_mask;
    bits_64 >>= 43; // shift bits to correct placement
    identifier_bits |= bits_64;
    return identifier_bits;
}

uint_8 get_can_rtr(const Canframe_8bit* self){
    uint_64 bits_64 = 0x0;
    uint_64 rtr_mask = ((uint_64)0x04) << 40;
    uint_8 rtr_bit = 0;
    bits_64 = self->frame & rtr_mask;
    bits_64 >>= 40; // shift bits to correct placement
    rtr_bit |= bits_64;
    return rtr_bit;
}

uint_8 get_can_ide(const Canframe_8bit* self){
    uint_64 bits_64 = 0x0;
    uint_64 ide_mask = ((uint_64)0x02) << 40;
    uint_8 ide_bit = 0;
    bits_64 = self->frame & ide_mask;
    bits_64 >>= 40; // shift bits to correct placement
    ide_bit |= bits_64;
    return ide_bit;
}

uint_8 get_can_dlc(const Canframe_8bit* self){
    uint_64 bits_64 = 0x0;
    uint_64 dlc_mask = ((uint_64)0xF) << 36;
    uint_8 dlc_bit = 0;
    bits_64 = self->frame & dlc_mask;
    bits_64 >>= 36; // shift bits to correct placement
    dlc_bit |= bits_64;
    return dlc_bit;
}

uint_64 get_can_data(const Canframe_8bit* self){
    uint_64 bits_64 = 0x0;
    uint_64 data_mask = ((uint_64)0xFF) << 28;
    uint_8 data_bit = 0;
    bits_64 = self->frame & data_mask;
    bits_64 >>= 28; // shift bits to correct placement
    data_bit |= bits_64;
    return data_bit;
}

//uint_8 get_can_sender(const Canframe_8bit* self){}

uint_64 get_full_canframe(const Canframe_8bit* self){
    return self->frame;
}

// testing
int main(){
    Canframe_8bit* cf = create_canframe_8bit();
    
    set_can_identifier(cf, 0xF);

    uint_64 a = get_full_canframe(cf);

    printf("%llX",a);


    return 0;
}