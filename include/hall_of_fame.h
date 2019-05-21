#ifndef GUARD_HALL_OF_FAME_H
#define GUARD_HALL_OF_FAME_H

struct HallofFameMon
{
    /*
    u32 tid;
    u32 personality;
    u16 species;
    u8 lvl;
    u8 nick[POKEMON_NAME_LENGTH];
    */
    
    u32 tid;
    u16 species;
    u8 shiny:1;
    u8 gender:2;
    u8 formId:5;
    u8 lvl;
    
    u8 nick[12];
    
    /*
    u16 tId;
    
    u8 formId:5;
    u8 shiny:1;
    u8 gender:2;
    u8 jpName:1;
    u8 level:7;
    
    u8 nick[12];
    species fits into nick by making chars all 7 bits. Can't be arsed rn, lel.
    
    16 bytes
    */
};

struct HallofFameTeam
{
    struct HallofFameMon mon[6];
};

void CB2_DoHallOfFameScreen(void);
void CB2_DoHallOfFameScreenDontSaveData(void);
void CB2_DoHallOfFamePC(void);
void sub_8175280(void);

// hof_pc.c
void ReturnFromHallOfFamePC(void);

#endif // GUARD_HALL_OF_FAME_H
