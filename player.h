#pragma once

typedef struct player
{
    float dist;
    int entity_team;
    float boxMiddle;
    float h_y;
    float width;
    float height;
    float b_x;
    float b_y;
    bool knocked;
    bool visible;
    int health;
    int shield;
    int maxshield;
    Vector EntityPosition;
    Vector LocalPlayerPosition;
    QAngle localviewangle;
    float targetyaw;
    int xp_level;
    bool Observing;
    int PlatformID;
    uint64_t TargetUID;
    char name[33];

    // Constructor to initialize all fields
    player(float dist = 0, int entity_team = 0, float boxMiddle = 0, float h_y = 0, float width = 0,
           float height = 0, float b_x = 0, float b_y = 0, bool knocked = false, bool visible = false,
           int health = 0, int shield = 0, int maxshield = 0, Vector EntityPosition = Vector(),
           Vector LocalPlayerPosition = Vector(), Vector localviewangle = Vector(), float targetyaw = 0,
           int xp_level = 0, bool Observing = false, int PlatformID = 0, uint64_t TargetUID = 0)
        : dist(dist), entity_team(entity_team), boxMiddle(boxMiddle), h_y(h_y), width(width), height(height),
          b_x(b_x), b_y(b_y), knocked(knocked), visible(visible), health(health), shield(shield), maxshield(maxshield),
          EntityPosition(EntityPosition), LocalPlayerPosition(LocalPlayerPosition), localviewangle(localviewangle),
          targetyaw(targetyaw), xp_level(xp_level), Observing(Observing), PlatformID(PlatformID), TargetUID(TargetUID)
    {
        memset(name, 0, sizeof(name));  // Initialize name to 0
    }
    
} player;