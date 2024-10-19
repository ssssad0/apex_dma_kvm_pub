//Date 2024/10/19
//GameVersion = v3.0.82.42
//KrackerCo's Version
//python3 update.py offsets.h offsets.ini


#define OFFSET_ENTITYLIST 0x1f62278 //[Miscellaneous].cl_entitylist //not in the offset paste, check forums updated 2024/10/19
#define OFFSET_LOCAL_ENT 0x24354F8 //[Miscellaneous].LocalPlayer updated 2024/10/19
#define OFFSET_NAME_LIST 0xd427360  //[Miscellaneous].NameList //not in the offset paste, check forums updated 2024/10/19
#define OFFSET_GLOBAL_VARS 0x1836330 //[Miscellaneous].GlobalVars updated 2024/10/19
#define OFFSET_LEVELNAME 0x1836834 //[Miscellaneous].LevelName updated 2024/10/19
#define OFFSET_CLIENTSTATE 0x1836670   //[Miscellaneous].ClientState updated 2024/10/19
#define OFFSET_SIGNONSTATE 0x183671c //[Miscellaneous].SignonState updated 2024/10/19

//World2Screen
#define OFFSET_MATRIX 0x11a350 //[Miscellaneous].ViewMatrix updated 2024/10/19
#define OFFSET_RENDER 0x76e9ab8 //[Miscellaneous].ViewRender updated 2024/10/19 

//Observer List
#define OFFSET_OBSERVER_LIST 0x1F63068
#define OFF_OBSERVER_LIST_IN_ARRAY 0x974

//get rank api stuff
#define OFFSET_PLAT_FROM_USER_ID 0x2548 //[RecvTable.DT_Player].m_platformUserId updated 2024/10/19
#define OFFSET_PLAT_FROM_ID 0x2540//[RecvTable.DT_Player].m_hardware updated 2024/10/19

//auto grapple
#define OFFSET_GRAPPLE_ACTIVE       0x2d48   //[RecvTable.DT_Player].m_grappleActive pdated 2024/09/1
#define OFFSET_GRAPPLE              0x2cc0 //[RecvTable.DT_Player].m_grapple pdated 2024/09/1
#define OFFSET_GRAPPLEATTACHED      0x0048 //[RecvTable.DT_GrappleData].m_grappleAttached pdated 2024/09/1

//Map ID  
#define OFFSET_HOST_MAP 0x01751ca0 + 0x58 //[ConVars].host_map + 0x58 updated 2024/10/19

//XP stuff
#define OFFSET_M_XP 0x3784 //[RecvTable.DT_Player].m_xp updated 2024/10/19

//Glow ESP
#define OFFSET_TEAM 0x0338 //[RecvTable.DT_BaseEntity].m_iTeamNum updated 2024/10/19
#define OFFSET_HEALTH 0x0328 //[RecvTable.DT_Player].m_iHealth updated updated 2024/10/19
#define OFFSET_SHIELD 0x01a0 //[RecvTable.DT_BaseEntity].m_shieldHealth updated 2024/10/19
#define OFFSET_MAXSHIELD 0x01a4 //[RecvTable.DT_BaseEntity].m_shieldHealthMax updated 2024/10/19
#define OFFSET_ARMORTYPE 0x4724 //[RecvTable.DT_Player].m_armorType updated updated 2024/10/19
#define OFFSET_NAME 0x0481 //[RecvTable.DT_BaseEntity].m_iName updated 2024/10/19
#define OFFSET_SIGN_NAME 0x0478 //[RecvTable.DT_BaseEntity].m_iSignifierName updated 2024/10/19
#define OFFSET_ABS_VELOCITY 0x0170 //[DataMap.C_BaseEntity].m_vecAbsVelocity updated 2024/10/19
#define OFFSET_LIFE_STATE 0x0690 //[RecvTable.DT_Player].m_lifeState updated 2024/10/19 
#define OFFSET_BLEED_OUT_STATE 0x2760 //[RecvTable.DT_Player].m_bleedoutState updated 2024/10/19

//Inputs
#define OFFSET_INPUT_SYSTEM 0x18e47c0 //[Miscellaneous].InputSystem updated 2024/10/19 
#define OFFSET_IN_ATTACK 0x076e9bc0 //[Buttons].in_attack updated 2024/10/19
#define OFFSET_IN_TOGGLE_DUCK 0x076e9be0 //[Buttons].in_toggle_duck updated 2024/10/19
#define OFFSET_IN_ZOOM 0x076e9d38 //[Buttons].in_zoom updated 2024/10/19
#define OFFSET_IN_FORWARD 0x076e9af0 //[Buttons].in_forward updated 2024/10/19
#define OFFSET_FORCE_JUMP 0x076e9cb8 //[Buttons].in_jump updated 2024/10/19
#define OFFSET_ZOOMING 0x1be1 //[RecvTable.DT_Player].m_bZooming updated 2024/10/19
#define OFFSET_FORCE_DUCK 0x076e9db0 //[Buttons].in_duck updated 2024/10/19 
#define OFFSET_IN_USE 0x076e9d28 //[Buttons].in_use updated 2024/10/19

//Aimbot Stuff
#define OFFSET_WEAPON_NAME 0x1788 //[RecvTable.DT_WeaponX].m_weaponNameIndex updated 2024/10/19
#define OFFSET_OFF_WEAPON 0x1954 //[DataMap.C_BaseCombatCharacter].m_latestNonOffhandWeapons updated 2024/10/19
#define OFFSET_ORIGIN 0x017c //[DataMap.C_BaseEntity].m_vecAbsOrigin updated 2024/10/19
#define OFFSET_BONES 0x0db0 + 0x48 //[RecvTable.DT_BaseAnimating].m_nForceBone + 0x48 updated 2024/10/19
#define OFFSET_STUDIOHDR 0x1000 //[Miscellaneous].CBaseAnimating!m_pStudioHdr updated 2024/10/19
#define OFFSET_AIMPUNCH 0x2438 //[DataMap.C_Player].m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle updated 2024/10/19
#define OFFSET_CAMERAPOS 0x1ee0 //[Miscellaneous].CPlayer!camera_origin updated 2024/10/19
#define OFFSET_VIEWANGLES 0x2534 - 0x14 //[RecvTable.DT_Player].m_ammoPoolCapacity - 0x14 updated 2024/10/19
#define OFFSET_BREATH_ANGLES OFFSET_VIEWANGLES - 0x10 //Ignore Auto Update --- 
#define OFFSET_OBSERVER_MODE 0x3584 //[RecvTable.DT_LocalPlayerExclusive].m_iObserverMode updated 2024/10/19
#define OFFSET_OBSERVING_TARGET 0x3590 //[RecvTable.DT_LocalPlayerExclusive].m_hObserverTarget updated 2024/10/19
#define OFFSET_WEAPON 0x1944 //[RecvTable.DT_BaseCombatCharacter].m_latestPrimaryWeapons updated 2024/10/19
#define OFFSET_BULLET_SPEED 0x1ec4 //[Miscellaneous].CWeaponX!m_flProjectileSpeed updated 2024/08/06
#define OFFSET_BULLET_SCALE OFFSET_BULLET_SPEED + 0x08 //[Miscellaneous].CWeaponX!m_flProjectileScale updated 2024/08/06
#define OFFSET_ZOOM_FOV 0x15e0 + 0x00b8 //[RecvTable.DT_WeaponX].m_playerData + m_curZoomFOV updated 2024/10/19
#define OFFSET_AMMO 0x1564 //[RecvTable.DT_PropSurvival].m_ammoInClip updated 2024/10/19 
#define OFFSET_YAW 0x223c - 0x8 //[DataMap.C_Player].m_currentFramePlayer.m_ammoPoolCount - 0x8 updated 2024/10/19

//Item Stuff
#define OFFSET_ITEM_ID 0x1568 //[RecvTable.DT_PropSurvival].m_customScriptInt updated 2024/10/19
#define OFFSET_MODELNAME 0x0030 //[DataMap.C_BaseEntity].m_ModelName updated 2024/10/19
#define OFFSET_M_CUSTOMSCRIPTINT OFFSET_ITEM_ID //[RecvTable.DT_PropSurvival].m_customScriptInt updated 2024/10/19

//Triggerbot stuff
#define OFFSET_VISIBLE_TIME 0x19a0 //[Miscellaneous].CPlayer!lastVisibleTime updated 2024/10/19
#define OFFSET_CROSSHAIR_LAST OFFSET_VISIBLE_TIME + 0x8  //Ignore Auto Update --- CPlayer!lastCrosshairTargetTime // CPlayer!lastVisibleTime + 0x8 
#define OFFSET_CROSSHAIR_START 0x19C8 //Ignore Auto Update --- CPlayer!crosshairTargetStartTime updated 01/9/2024

//Glow Stuff
#define OFFSET_GLOW_ENABLE 0x29C //Ignore Auto Update --- 7 = enabled, 2 = disabled  Script_Highlight_SetCurrentContext 
#define OFFSET_GLOW_THROUGH_WALLS 0x26C //Ignore Auto Update --- 2 = enabled, 5 = disabled  Script_Highlight_SetVisibilityType // Glow_VisibleType 
#define GLOW_START_TIME 0x02c8 + 0x30 //Ignore Auto Update --- m_playerFloatLookStartTime=0x02c4 
#define OFFSET_HIGHLIGHTSERVERACTIVESTATES 0x29C //Ignore Auto Update --- updated 11/1/2023
#define OFFSET_GLOW_ENABLE_GLOW_CONTEXT OFFSET_GLOW_ENABLE //Ignore Auto Update ---  Script_Highlight_SetCurrentContext 
#define OFFSET_GLOW_THROUGH_WALLS_GLOW_VISIBLE_TYPE OFFSET_GLOW_THROUGH_WALLS //Ignore Auto Update ---  Script_Highlight_SetVisibilityType 5th mov 
#define GLOW_LIFE_TIME 0x3A4+ 0x30 //Ignore Auto Update --- Script_Highlight_SetLifeTime + 4 
#define GLOW_DISTANCE 0x26c //Ignore Auto Update ---  Script_Highlight_SetFarFadeDist 
#define GLOW_TYPE 0x29c //Ignore Auto Update ---  Script_Highlight_GetState + 4 
#define GLOW_COLOR 0x1D0+ 0x30 //Ignore Auto Update ---  Script_CopyHighlightState 15th mov 
#define GLOW_FADE 0x388+ 0x30 //Ignore Auto Update ---  ats 3rd result of 3 offsets consecutive or first + 8 
#define HIGHLIGHT_SETTINGS 0xb1db5a0 //[Miscellaneous].HighlightSettings updated 2024/10/19 //not in the offset paste, check forums updated 2024/08/06
#define HIGHLIGHT_TYPE_SIZE 0x34 //Ignore Auto Update --- ? 

//Superglide Stuff
#define OFFSET_TRAVERSAL_PROGRESS 0x2b6c //[DataMap.C_Player].m_traversalProgress updated 2024/10/19 
#define OFFSET_WALL_RUN_START_TIME 0x3674 //[DataMap.C_Player].m_wallRunStartTime updated 2024/10/19
#define OFFSET_WALL_RUN_CLEAR_TIME 0x3678 //[DataMap.C_Player].m_wallRunClearTime updated 2024/10/19 
#define OFFSET_TIME_BASE 0x2088 //[RecvTable.DT_Player].m_currentFramePlayer updated 2024/10/19 
#define OFFSET_TRAVERSAL_START_TIME 0x2b70 //[DataMap.C_Player].m_traversalStartTime updated 2024/10/19