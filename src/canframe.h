#ifndef CANframe_H
#define CANframe_H

typedef unsigned char uint_8;
typedef unsigned long long int uint_64;




typedef struct Canframe_8bit Canframe_8bit;

Canframe_8bit* create_canframe_8bit();
void destroy_canframe_8bit(Canframe_8bit* self);

// setters
void set_can_identifier(Canframe_8bit* self, uint_8 id);
void set_can_rtr(Canframe_8bit* self, uint_8 bit);
void set_can_ide(Canframe_8bit* self, uint_8 bit);
void set_can_dlc(Canframe_8bit* self, uint_8 bit);
void set_can_data(Canframe_8bit* self, uint_64 bit);
void set_can_sender(Canframe_8bit* self, uint_8 bit);

void set_full_canframe(Canframe_8bit* self, uint_64 frame);


// getters
uint_8 get_can_identifier(const Canframe_8bit* self);
uint_8 get_can_rtr(const Canframe_8bit* self);
uint_8 get_can_ide(const Canframe_8bit* self);
uint_8 get_can_dlc(const Canframe_8bit* self);
uint_64 get_can_data(const Canframe_8bit* self);
uint_8 get_can_sender(const Canframe_8bit* self);

uint_64 get_full_canframe(const Canframe_8bit* self);


#endif