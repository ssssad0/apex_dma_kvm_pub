#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <random>
#include <chrono>
#include <iostream>
#include <cfloat>
#include "Game.h"
#include <thread>
#include <array>
#include <map>
#include <algorithm> // For std::max and std::min
#include <curl/curl.h>
#include <json/json.h>
#include <ctime>
#include <atomic>
#include <sstream> // Include this header for stringstream
#include <fstream>

#include <unordered_map>
#include <vector>
#include <mutex>

Memory apex_mem; //apex exe memory
Memory client_mem; //overlay memory

//Just setting things up, dont edit.
bool AimSnapToggle = false; //toggle aimsnap code
int TargetID;
int TargetIndex;
int TargetIndexLock;
bool firing_range = false;
bool active = true;
bool InputSystem = false;
//extern bool bone_auto;  //apex_dma.cpp
uintptr_t aimentity = 0;
uintptr_t tmp_aimentity = 0;
uintptr_t lastaimentity = 0;
float max = 999.0f;
float max_dist = 200.0f*40.0f;
int team_player = 0;
float max_fov = 50;
const int toRead = 100;
//item esp test
const int ItemtoRead = 15000;
bool ItemESPClient = false;
bool ItemESPClientALL = false;
int aim = true;
bool esp = true;
bool PrintHeldID;
bool item_glow = true;
bool player_glow = true;
bool PrintModelAndId = false;
int WeaponHeldID;
float ZoomFOVCircle;
char level_name[40];
extern bool aim_no_recoil;
bool aiming = false;
extern float smooth;
extern int bone;
int selectedFPSIndex = 0;
float bulletspeed;
float bulletgrav;
int playerentcount = 100;
bool tapstrafeenable = false;
float CurrentWeaponADSZoom;
float ScopeZoom;
//box bool
bool BoxEnable = false;
//triggerbot?
bool SuperKeyToggle = true;
bool SuperKey = true;
//TDM Toggle
bool TDMToggle = false;
//Trigger Bot
bool triggerbot = false;
float isattacing = 0.0f;
int lstarvalueid;
//Firing Range 1v1 toggle
bool onevone = false;
int curFrameNumber;
//map
bool PrintMapCords = false;
int map = 0;
float veltest = 0.0f;
bool TogglePrediction = true;
//superglide stuff
float m_traversalProgress;
bool shooting = false;
int NoNadeAim = 0;
bool autoshoot = true;
bool TriggerBot = false;
int frameSleepTimer;
bool AutoFire = false;
//auto grapple
bool AutoGrappleToggle = false;
//Player Glow Color and Brightness.
bool insidevaluegoggle = false;
bool lootinsidevaluegoggle = false;
//inside fill
unsigned char insidevalue = 14;  //0 = no fill, 14 = full fill
//Outline size
unsigned char outlinesize = 32; // 0-255
float glowr = 1.0f; //Red 0-255, higher is brighter color.
float glowg = 0.0f; //Green 0-255, higher is brighter color.
float glowb = 0.0f; //Blue 0-255, higher is brighter color.
//visable
float glowrviz = 0.0f; //Red 0-255, higher is brighter color.
float glowgviz = 1.0f; //Green 0-255, higher is brighter color.
float glowbviz = 0.0f; //Blue 0-255, higher is brighter color.
//knocked
float glowrknocked = 1.0f; //Red 0-255, higher is brighter color.
float glowgknocked = 1.0f; //Green 0-255, higher is brighter color.
float glowbknocked = 1.0f; //Blue 0-255, higher is brighter color.
//Screen Res
int ScreenResINT = 0; //0 is 1080p, 1 is 1440p
//Item Configs
//Mobi, Headshield, Jumptower
bool Mobi = false;
bool HeadShield = false;
bool JumpTower = false;
bool KeyCard = false;
//Traps
bool Traps = false;
bool CryptoDrone = true;
//loot Fill
unsigned char lootfilled = 109;  //0 no fill, 14 100% fill
//loot outline siez
unsigned char lootoutline = 0;
bool skull = true;
//Headshot Model
bool HeadShotMode = false;
//Backpacks
bool lightbackpack = false;
bool medbackpack = false;
bool heavybackpack = false;
bool goldbackpack = false;
//Shield Upgrades
bool shieldupgrade1 = false;  //white
bool shieldupgrade2 = false;  //blue
bool shieldupgrade3 = false;  //purple
bool shieldupgrade4 = false;  //gold
bool shieldupgrade5 = false;  //red
//Helmet Upgrades
bool shieldupgradehead1 = false;
bool shieldupgradehead2 = false;
bool shieldupgradehead3 = false;
bool shieldupgradehead4 = false;
//Knockdown Upgrades
bool shielddown1 = false;
bool shielddown2 = false;
bool shielddown3 = false;
bool shielddown4 = false;
//heaing and Misc
bool accelerant = false;
bool phoenix = false;
bool healthlarge = false;
bool healthsmall = false;
bool shieldbattsmall = false;
bool shieldbattlarge = false;
//Ammo
bool sniperammo = false;
bool heavyammo = false;
bool lightammo = false;
bool energyammo = false;
bool shotgunammo = false;
//Optics
bool optic1xhcog = false;
bool optic2xhcog = false;
bool opticholo1x = false;
bool opticholo1x2x = false;
bool opticthreat = false;
bool optic3xhcog = false;
bool optic2x4x = false;
bool opticsniper6x = false;
bool opticsniper4x8x = false;
bool opticsniperthreat = false;
//Magazines
bool sniperammomag1 = false;
bool energyammomag1 = false;
bool lightammomag1 = false;
bool heavyammomag1 = false;
bool sniperammomag2 = false;
bool energyammomag2 = false;
bool lightammomag2 = false;
bool heavyammomag2 = false;
bool sniperammomag3 = false;
bool energyammomag3 = false;
bool lightammomag3 = false;
bool heavyammomag3 = false;
bool sniperammomag4 = false;
bool energyammomag4 = false;
bool lightammomag4 = false;
bool heavyammomag4 = false;
//Attachments 
bool lasersight1 = false;
bool lasersight2 = false;
bool lasersight3 = false;
bool lasersight4 = false;
bool stocksniper1 = false;
bool stocksniper2 = false;
bool stocksniper3 = false;
bool stocksniper4 = false;
bool stockregular1 = false;
bool stockregular2 = false;
bool stockregular3 = false;
bool suppressor1 = false;
bool suppressor2 = false;
bool suppressor3 = false;
bool turbo_charger = false;
bool skull_piecer = false;
bool hammer_point = false;
bool disruptor_rounds = false;
bool boosted_loader = false;
bool gunshield = false;
bool shotgunbolt1 = false;
bool shotgunbolt2 = false;
bool shotgunbolt3 = false;
bool shotgunbolt4 = false;
//Nades
bool grenade_frag = false;
bool grenade_arc_star = false;
bool grenade_thermite = false;
//Kraber
bool weapon_kraber = false;
//Shotguns
bool weapon_mastiff = false;
bool weapon_eva8  = false;
bool weapon_peacekeeper  = false;
bool weapon_mozambique  = false;
//Energy weapons
bool weapon_lstar = false;
bool weapon_nemesis = false;
bool weapon_havoc = false;
bool weapon_devotion = false;
bool weapon_triple_take = false;
bool weapon_prowler  = false;
bool weapon_volt  = false;
//Heavy Weapons
bool weapon_flatline = false;
bool weapon_hemlock  = false;
bool weapon_3030_repeater = false; 
bool weapon_rampage  = false;
bool weapon_car_smg  = false;
//Light weapons
bool weapon_p2020  = false;
bool weapon_re45  = false;
bool weapon_g7_scout  = false;
bool weapon_alternator  = false;
bool weapon_r99  = false;
bool weapon_spitfire  = false;
bool weapon_r301 = false;
//Snipers.. wingman is the odd one...and the bow..
bool weapon_wingman  = false;
bool weapon_longbow  = false;
bool weapon_charge_rifle  = false;
bool weapon_sentinel  = false;
bool weapon_bow  = false;

//aim dist check. Just setting things up, dont edit.
float aimdist = 200.0f * 40.0f;
//Spectator name list for overlay
float LocalYAW;
float TargetYAW;
int TARGET_TEAMID;
int TEAM_TEAMID;
//item glow brightness. Just setting things up, dont edit.
int itemglowbrightness = 1;
int BlueOutlineFunction = 125;
int BlueThirdOption = 64;
int BlueFourthOption = 64;

uint32_t button_state[4];
int AimbotHotKey1 = 108;
int AimbotHotKey2 = 109;

//saved playerid
int AimedPlayerID = 0;
//Just setting things up, dont edit.
bool actions_t = false;
bool esp_t = false;
bool aim_t = false;
bool vars_t = false;
bool item_t = false;
bool cactions_t = false;
bool TriggerBotRun_t = false;
uint64_t g_Base;
uint64_t c_Base;
bool next2 = false;
bool valid = false;
bool lock = false;
//trigger bot
bool is_trigger;
int attackState;

bool GetRanks = false;

void TriggerBotRun() //trigger bot thread/code block
{
	//testing
	//apex_mem.Write<int>(g_Base + OFFSET_IN_ATTACK + 0x8, 4);
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	apex_mem.Write<int>(g_Base + OFFSET_IN_ATTACK + 0x8, 5);
	std::this_thread::sleep_for(std::chrono::milliseconds(60));
	apex_mem.Write<int>(g_Base + OFFSET_IN_ATTACK + 0x8, 4);
	//printf("TriggerBotRun\n");
	//printf("attackState: %i\n", attackState);
}
bool IsInCrossHair(Entity &target) 
{
	static uintptr_t last_t = 0;
	static float last_crosshair_target_time = -1.f;
	float now_crosshair_target_time = target.lastCrossHairTime();
	bool is_trigger = false;
	if (last_t == target.ptr)
	{
		if(last_crosshair_target_time != -1.f)
		{
			if(now_crosshair_target_time > last_crosshair_target_time)
			{
				is_trigger = true;
				//printf("Trigger\n");
				last_crosshair_target_time = -1.f;
			}
			else
			{
				is_trigger = false;
				last_crosshair_target_time = now_crosshair_target_time;
			}
		}
		else
		{
			is_trigger = false;
			last_crosshair_target_time = now_crosshair_target_time;
		}
	}
	else
	{
		last_t = target.ptr;
		last_crosshair_target_time = -1.f;
	}
	return is_trigger;
}


//Player Definitions, dont edit unless you know what you are doing.
typedef struct player
{
	float dist = 0;
	int entity_team = 0;
	float boxMiddle = 0;
	float h_y = 0;
	float width = 0;
	float height = 0;
	float b_x = 0;
	float b_y = 0;
	bool knocked = false;
	bool visible = false;
	int health = 0;
	int shield = 0;
	int maxshield = 0;
	Vector EntityPosition;
	Vector LocalPlayerPosition;
	QAngle localviewangle;
	float targetyaw = 0;
	int player_xp_level = 0;
	bool Observing = false;
	int PlatformID;
	int Rank; 
	uint64_t TargetUID;
	char name[33] = { 0 };
	
	
}player;

//Item esp names
typedef struct item
{
	float dist = 0;
	/*
	float boxMiddle = 0;
	float h_y = 0;
	float width = 0;
	float height = 0;
	float b_x = 0;
	float b_y = 0;
	*/
	Vector EntityPosition;
	uint64_t ItemID = 0;
	char name[200] = { 0 };
	
}item;

//Your in the matrix neo.
struct Matrix
{
	float matrix[16];
}m;

//Visual check and aim check.?
float lastvis_esp[toRead];
float lastvis_aim[toRead];

//Specator stuff. Just setting things up, dont edit.
int tmp_spec = 0, spectators = 0;
int tmp_all_spec = 0, allied_spectators = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////

//int settingIndex;
//int contextId;
//std::array<float, 3> highlightParameter;
//works
void SetPlayerGlow(Entity& LPlayer, Entity& Target, int index)
{
	if (!Target.isGlowing() || (int)Target.buffer[OFFSET_GLOW_THROUGH_WALLS_GLOW_VISIBLE_TYPE] != 1) 
	{
		float currentEntityTime = 5000.f;
		if (!isnan(currentEntityTime) && currentEntityTime > 0.f) 
		{
			int contextId;
			int settingIndex;
			int IDCHeck;
			std::array<float, 3> highlightParameter;

			if (!(firing_range) && (Target.isKnocked()))
			{
				contextId = 1;
				settingIndex = 1;
				highlightParameter = { glowrknocked, glowgknocked, glowbknocked };
				IDCHeck = 1;
			}
			else if (Target.lastVisTime() > lastvis_aim[index] || (Target.lastVisTime() < 0.f && lastvis_aim[index] > 0.f))
			{
				contextId = 2;
				settingIndex = 2;
				highlightParameter = { glowrviz, glowgviz, glowbviz };
				IDCHeck = 2;
			}
			else 
			{
				contextId = 3;
				settingIndex = 3;
				highlightParameter = { glowr, glowg, glowb };
				IDCHeck = 3;
			}
			Target.enableGlow(contextId, settingIndex, IDCHeck, highlightParameter);
		}
	}
}

uint64_t PlayerLocal;
int PlayerLocalTeamID;
int EntTeam;
int LocTeam;

void ProcessPlayer(Entity& LPlayer, Entity& target, uint64_t entitylist, int index)
{
	int entity_team = target.getTeamId();
	TARGET_TEAMID = target.getTeamId();

	TEAM_TEAMID = LPlayer.getTeamId();
	//printf("TEAM_TEAMID: %i\n", TEAM_TEAMID);
	//printf("TARGET_TEAMID: %i\n", TARGET_TEAMID);		
	//
	float localyaw = LPlayer.GetYaw();
	float targetyaw = target.GetYaw();
	LocalYAW = localyaw;
	TargetYAW = targetyaw;
	//printf("localyaw: %f\n", localyaw);
	//printf("LocalYAW: %f\n", LocalYAW);
	if (!target.isAlive())
	{
		
		
		if(target.Observing(LPlayer.ptr))
		{
			if (LPlayer.getTeamId() == entity_team)
				tmp_all_spec++;
			else
				tmp_spec++;
		}
		return;
	}
	
	
	if (TDMToggle)
	{// Check if the target entity is on the same team as the local player
		//int entity_team = Target.getTeamId();
		//printf("Target Team: %i\n", entity_team);


		uint64_t PlayerLocal;
		apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, PlayerLocal);
		int PlayerLocalTeamID;
		apex_mem.Read<int>(PlayerLocal + OFFSET_TEAM, PlayerLocalTeamID);



		if (entity_team % 2) EntTeam = 1;
		else EntTeam = 2;
		if (PlayerLocalTeamID % 2) LocTeam = 1;
		else LocTeam = 2;

		//printf("Target Team: %i\nLocal Team: %i\n", EntTeam, LocTeam);
		if (EntTeam == LocTeam)
			return;

	}
	
	
						

	Vector EntityPosition = target.getPosition();
	Vector LocalPlayerPosition = LPlayer.getPosition();
	//Vector LPlayerVel = LPlayer.getAbsVelocity();
	//printf("LPlayerVel Velocity: (%.2f)\n", fabs(LPlayerVel.x / 39.62));

	float dist = LocalPlayerPosition.DistTo(EntityPosition);
	//Prints POS of localplayer for map cords for full map radar. only enable when adding a new map or fixing a old one, will output to console.
	//std::printf("  X: %.6f   ||    Y:%.6f",LocalPlayerPosition.x, LocalPlayerPosition.y); //Prints x and y cords of localplayer to get mainmap radar stuff.
	if (PrintMapCords)
	{
		std::printf("X: %.6f || Y: %.6f || %s\n", LocalPlayerPosition.x, LocalPlayerPosition.y, level_name);
	}

	if (dist > aimdist) return;
	
	
	//Firing range stuff
	if(!firing_range && !onevone)
		if (entity_team < 0 || entity_team>50 || entity_team == team_player) return;
	
	//Vis check aiming? dunno
	if(aim==2) // 0 = no aimbot, 1 = no vis check so any red or green, 2 is green
	{
		if((target.lastVisTime() > lastvis_aim[index])) // is vis and index 0-100
		{
			float fov = CalculateFov(LPlayer, target);
			if (fov < max)
			{
				if (AimSnapToggle)
				{
					if(fov < max_fov)
					{
						TargetIndex = index; //write index to client
						//printf("Target lastVisTime: %f, lastvis_aim[%d]: %f, fov: %f, TargetID: %i, TargetIndexLock: %i\n", target.lastVisTime(), index, lastvis_aim[index], fov, TargetIndex, TargetIndexLock);
					}
					max = fov;
					tmp_aimentity = target.ptr;
				}
				else
				{
					max = fov;
					tmp_aimentity = target.ptr;
				}
				
				
			}
		}
		else
		{
			if(aimentity==target.ptr)
			{
				aimentity=tmp_aimentity=lastaimentity=0;
			}
		}
		if (aimentity != 0)
		{
			uint64_t LocalPlayer = 0;
			apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
			
			Entity Target = getEntity(aimentity);
			Entity LPlayer = getEntity(LocalPlayer);
			
			if(TriggerBot && IsInCrossHair(Target))
			{
				//printf("TriggerBot\n");
				TriggerBotRun();
			}
		}
	}
	else
	{
		float fov = CalculateFov(LPlayer, target);
		if (fov < max)
		{
			max = fov;
			tmp_aimentity = target.ptr;
		}
	}
	if(player_glow && dist < 12000)
	{
		SetPlayerGlow(LPlayer, target, index);
	}
	lastvis_aim[index] = target.lastVisTime();
}

bool OnSheila;
bool HoldSheila;
bool BowAdjust;

bool isPressed(uint32_t button_code)
{
    return  (button_state[static_cast<uint32_t>(button_code) >> 5] & (1 << (static_cast<uint32_t>(button_code) & 0x1f))) != 0;
}
void printPressedButtons()
{
    // Iterate over possible button codes (from 0 to 230)
    for (uint32_t code = 0; code <= 230; ++code) {
        if (isPressed(code)) {
            // Print the button code and state
            printf("Button Pressed: Code %u\n", code);
        }
    }
}
bool GamepadAimKeyPressed1;
bool GamepadAimKeyPressed2;
float NonADS = 100;
float ADS = 15;
static bool GamepadisPressed = false;
bool minimapradar = true;
bool mainradarmap = false; //if the Main Map Radar is enabled
void ClientActions()
{
	cactions_t = true;
	while (cactions_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_Base!=0)
		{
			
			uint64_t LocalPlayer = 0;
			apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
			Entity LPlayer = getEntity(LocalPlayer);
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
			attackState = 0;
			apex_mem.Read<int>(g_Base + OFFSET_IN_ATTACK, attackState); //108
			int tduckState = 0;
			apex_mem.Read<int>(g_Base + OFFSET_IN_TOGGLE_DUCK, tduckState); //61
			
			apex_mem.Read<typeof(button_state)>(g_Base + OFFSET_INPUT_SYSTEM + 0xb0, button_state);
			int HeldID;
			apex_mem.Read<int>(LocalPlayer + OFFSET_OFF_WEAPON, HeldID); // 0x1a1c
			
			//printf("Triggerbot hotkey: %s\n", TriggerBot ? "true" : "false");
			
			//printPressedButtons();
			if(InputSystem)
			{
				//printf("Working Inputsystem\n");
				//left trigger is 126
				//right trigger is 127

				//back is 121
				//b is 116
				aiming = false;
				max_fov = ADS;
				TriggerBot = false;
				//NotAimingDot = false;
				
				if (isPressed(121) && !GamepadisPressed) //121 is back button
				{
				mainradarmap = !mainradarmap;
				minimapradar = !minimapradar;
				GamepadisPressed = true;  // Set the flag to true when button is pressed
				}
				else if (!isPressed(121))  //121 is back button
				{
					GamepadisPressed = false;  // Reset the flag when button is released
				}

				if (isPressed(116))  //116 is b button
				{
					mainradarmap = false;
					minimapradar = true;
				}

				if (isPressed(126)) //126 is left trigger
				{
					aiming = true;
					max_fov = ADS;
					//NotAimingDot = false;
					if (!GamepadAimKeyPressed1)
					{
						TargetIndexLock = TargetIndex;
						GamepadAimKeyPressed1 = true;
					}
				}
				else if (!isPressed(126))  //126 is left trigger
				{

					GamepadAimKeyPressed1 = false;
				}

				if (isPressed(127)) //127 is right trigger
				{
					aiming = true;
					max_fov = NonADS;
					//NotAimingDot = false;
					if (!GamepadAimKeyPressed2)
					{
						TargetIndexLock = TargetIndex;
						GamepadAimKeyPressed2 = true;
					}
				}
				else if (!isPressed(127))  //127 is right trigger
				{
					GamepadAimKeyPressed2 = false;
				}
			}
			/*
			if (isPressed(34))
			{
				////0 LAND
				////65 JUMP
				
				int Jump;
				apex_mem.Read<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, Jump);
				

				apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 7);
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to ensure the jump is registered
				apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to ensure the jump is registered
				apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 7);
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Small delay to ensure the jump is registered
				apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);

				//printf("IN JUMP : %d\n", Jump);
			}
			*/
			
			
			//printf("NoNadeAim: %s\n", PrintHeldID ? "true" : "false");
			if(PrintHeldID)
			{
				printf("%d\n", HeldID);
			}
			//HeldID is wonky? not being read right but it works, guns are -255 and -256
			if (HeldID == -251)
			{
				NoNadeAim = 1;
			}
			/* if (HeldID >= -257 && HeldID <= -254)
			{
				NoNadeAim = 1;
			} */
			else
			{
				NoNadeAim = 0;
			}
			//printf("NoNadeAim: %s\n", NoNadeAim ? "true" : "false");
			//auto grapple
			if (AutoGrappleToggle)
			{
				//printf("AutoGrappleToggle: %s\n", AutoGrappleToggle ? "true" : "false");
				int isGrappleAttached;
				apex_mem.Read<int>(LocalPlayer + OFFSET_GRAPPLE + OFFSET_GRAPPLEATTACHED, isGrappleAttached);
				//printf("isGrappleAttached: %u\n", isGrappleAttached);
				if (isGrappleAttached == 1)
				{
					// Trigger jump by writing to the appropriate offset
					apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 5);
					std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small delay to ensure the jump is registered
					apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);
					//apex_mem.Write<int>(g_Base + OFFSET_IN_TOGGLE_DUCK + 0x8, 6);
				}
			}
			//Held Weapon ID
			// CREDITS to Rikkie https://www.unknowncheats.me/forum/members/169606.html
			// for all the weapon ids and item ids code, you are a life saver!
			ulong ehWeaponHandle;
			apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, ehWeaponHandle); // 0x1a1c
			ehWeaponHandle &= 0xFFFF; // eHandle
			ulong pWeapon;
			apex_mem.Read<uint64_t>(entitylist + (ehWeaponHandle * 0x20), pWeapon);
			uint32_t weaponID;
			apex_mem.Read<uint32_t>(pWeapon + OFFSET_WEAPON_NAME, weaponID); //0x1844
			//printf("Weapon ID: %u\n", weaponID);
			//End Held Weapon ID
			if (weaponID == 2) //the bow 
			{
				//printf("%d, ModBullet Speed: %f, ModBullet Gravity: %f\n", weaponID, bulletspeed, bulletgrav);
				bulletspeed = 1.00;
				bulletgrav = 1.00;
				BowAdjust = true;
			}
			else
			{
				//printf("Not Bow");
				BowAdjust = false;
				bulletspeed = 0.08;
				bulletgrav = 0.05;
			}
			if (weaponID == 14) //Mounted Sheila 
			{
				OnSheila = true;
			}
			else
			{
				OnSheila = false;
			}
			//printf("Weapon ID: %d\n", weaponID);
			if (HeldID == -16449790 || HeldID == -16449792) // Mounted Sheila 
			{
				//printf("Holding Shiela");
				//printf("HoldSheila in apex_dma.cpp\n");
				HoldSheila = true;
			}
			else
			{
				HoldSheila = false;
			}
			int zoomState = 0;
			apex_mem.Read<int>(g_Base + OFFSET_IN_ZOOM, zoomState); //109
			int frameSleepTimer;
			int lastFrameNumber;
			bool superGlideStart;
			int superGlideTimer;
			curFrameNumber;
			float m_traversalProgressTmp = 0.0f;
			apex_mem.Read<int>(g_Base + OFFSET_GLOBAL_VARS + 0x0008, curFrameNumber); // GlobalVars + 0x0008
			//printf("TriggerBot: %d\n", TriggerBot ? 1 : 0);
			//printf("attackState: %i\n", attackState);
			//printf("TogglePrediction: %d\n", TogglePrediction ? 1 : 0);
			//float zoomfovtest;
			//apex_mem.Read<float>(LocalPlayer + OFFSET_ZOOM_FOV, zoomfovtest); //109
			//printf("zoomfovtest: %f\n", zoomfovtest);
			/*
			uint64_t wephandle = 0;
			apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, wephandle);
			
			wephandle &= 0xffff;

			uint64_t wep_entity = 0;
			apex_mem.Read<uint64_t>(entitylist + (wephandle << 5), wep_entity);
			
			apex_mem.Read<float>(wep_entity + (0x1600 + 0x00bc), ScopeZoom); // m_playerData + m_targetZoomFOV
			
			//apex_mem.Read<float>(wep_entity + OFFSET_ZOOM_FOV, CurrentWeaponADSZoom);
			//printf("Zoom with scopes: %f\n", ScopeZoom);
			
			ulong ehWeaponHandle2;
			apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, ehWeaponHandle2); // 0x1a1c
			ehWeaponHandle2 &= 0xFFFF; // eHandle
			ulong pWeapon2;
			apex_mem.Read<uint64_t>(entitylist + (ehWeaponHandle2 * 0x20), pWeapon2);
			uint32_t weaponID2;
			apex_mem.Read<uint32_t>(pWeapon2 + OFFSET_WEAPON_NAME, weaponID2); //0x1844
			
			printf("%d\n", weaponID2);
			*/
			//printf("Gunshield is %s\n", gunshield ? "on" : "off");
			//float minimapscale = 0.0f;
			//apex_mem.Read<float>(g_Base + OFFSET_MINIMAP_SCALE, minimapscale); //109
			//printf("minimapscale: %f\n", minimapscale);
			//printf("minimapscale: %f\n", minimapscale);
			//printf("Playerentcount: %i\n", playerentcount);
			//printf("Playerentcount: %i\n", itementcount);
			apex_mem.Read<float>(LocalPlayer + OFFSET_TRAVERSAL_PROGRESS, m_traversalProgress);
			//printf("Travel Time: %f\n", m_traversalProgress);
			//printf("Frame Sleep Timer: %i\n", frameSleepTimer);
			//printf("Last Frame: %i\n", lastFrameNumber);
			//printf("Super Glide Timer: %i\n", superGlideTimer);
			//printf("Last Frame: %i\n", lastFrameNumber);
			//printf("Cur Frame: %i\n", curFrameNumber);
			//printf("superGlideStart: %d\n", superGlideStart ? 1 : 0);
			//int jump;
			//int ducktoggle;
			//int forceduck;
			//printf("Jump Value: %i\n", jump);
			//printf("Toggle Jump: %i\n", ducktoggle);
			//printf("Force Duck: %i\n", forceduck);
			//apex_mem.Read<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, jump);
			//apex_mem.Read<int>(g_Base + OFFSET_IN_TOGGLE_DUCK + 0x8, ducktoggle);
			//apex_mem.Read<int>(g_Base + OFFSET_FORCE_DUCK + 0x8, forceduck);
			//apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);
			//autofire
			//printf("FPSIndex: %i\n", frameSleepTimer);
			while (AutoFire)
			{
				apex_mem.Write<int>(g_Base + OFFSET_IN_ATTACK + 0x8, 4);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				apex_mem.Write<int>(g_Base + OFFSET_IN_ATTACK + 0x8, 5);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				apex_mem.Write<int>(g_Base + OFFSET_IN_ATTACK + 0x8, 4);
			}
			//printf("AutoFire: %d\n", AutoFire ? 1 : 0);
			if (curFrameNumber > lastFrameNumber)
			{
				if (selectedFPSIndex == 0)//60
				{
					frameSleepTimer = 10; // <- middle of the frame // needs 5 for 144fps and 10 for 60/75 fps
				}
				if (selectedFPSIndex == 1)//75
				{
					frameSleepTimer = 10; // <- middle of the frame // needs 5 for 144fps and 10 for 75 fps
				}
				if (selectedFPSIndex == 2)//144
				{
					frameSleepTimer = 5; // <- middle of the frame // needs 5 for 144fps and 10 for 75 fps
				}
			}
			lastFrameNumber = curFrameNumber;
			 
			if (frameSleepTimer == 0)
			{
				if(SuperKey)
				{
					float worldtime;
					apex_mem.Read<float>(LocalPlayer + OFFSET_TIME_BASE, worldtime);
					float traversalStartTime; 
					apex_mem.Read<float>(LocalPlayer + OFFSET_TRAVERSAL_START_TIME, traversalStartTime);
					float traversalProgress;
					apex_mem.Read<float>(LocalPlayer + OFFSET_TRAVERSAL_PROGRESS, traversalProgress);
					auto HangOnWall = -(traversalStartTime - worldtime);
					//printf("HangOnWall: %.2f\n", HangOnWall); // This will print with 2 decimal places
					if (selectedFPSIndex == 0)//60
					{
						if (m_traversalProgress > 0.87 && m_traversalProgress < 0.92 && !superGlideStart && HangOnWall > 0.1f && HangOnWall < 1.5f) // needs to end at 0.90 for 144 fps and 0.92 for 75 fps
						{
							superGlideStart = true;
						}
					}
					if (selectedFPSIndex == 1)//75
					{
						if (m_traversalProgress > 0.87 && m_traversalProgress < 0.92 && !superGlideStart && HangOnWall > 0.1f && HangOnWall < 1.5f) // needs to end at 0.90 for 144 fps and 0.92 for 75 fps
						{
							superGlideStart = true;
						}
					}
					if (selectedFPSIndex == 2)//144
					{
						if (m_traversalProgress > 0.87 && m_traversalProgress < 0.90 && !superGlideStart && HangOnWall > 0.1f && HangOnWall < 1.5f) // needs to end at 0.90 for 144 fps and 0.92 for 75 fps
						{
							superGlideStart = true;
						}
					}
				 
					if (superGlideStart)
					{
						superGlideTimer++;
						//printf("Super Glide Timer: %i\n", superGlideTimer);
						if (superGlideTimer == 5)
						{
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 5);
						}
						else if (superGlideTimer == 6)
						{
							apex_mem.Write<int>(g_Base + OFFSET_IN_TOGGLE_DUCK + 0x8, 6);
						}
						else if (superGlideTimer == 10) //needs to be 10 for 75 and 144fps?
						{
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_JUMP + 0x8, 4);
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_DUCK + 0x8, 5);
							apex_mem.Write<int>(g_Base + OFFSET_FORCE_DUCK + 0x8, 4);
							m_traversalProgressTmp = m_traversalProgress;
						}
						else if (superGlideTimer > 10 && m_traversalProgress != m_traversalProgressTmp)
						{
							superGlideStart = false;
							superGlideTimer = 0;
						}
					}
				}
			}
			frameSleepTimer -= 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	cactions_t = false;
}
//Main stuff, dont edit.
void DoActions()
{
	actions_t = true;
	while (actions_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		uint32_t counter = 0;

		while (g_Base!=0 && c_Base!=0)
		{
			uint64_t LocalPlayer = 0;
			apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
			Entity LPlayer = getEntity(LocalPlayer);
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
			
			if(insidevaluegoggle)
			{
				insidevalue = 109;
			}
			else
			{
				insidevalue = 0;
			}
			
			if(lootinsidevaluegoggle)
			{
				lootfilled = 109;
			}
			else
			{
				lootfilled = 0;
			}
			//weapon held stuff
			//uint64_t wephandle = 0;
			//apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, wephandle);
			//wephandle &= 0xffff;
			//uint64_t wep_entity = 0;
			//apex_mem.Read<uint64_t>(entitylist + (wephandle << 5), wep_entity);
			//apex_mem.Read<int>(wep_entity + OFFSET_WEAPON_NAME, WeaponHeldID);
			//targetZoomFOV;
			//apex_mem.Read<float>(wep_entity + (0x1590 + 0x00bc), targetZoomFOV); // m_playerData + m_targetZoomFOV
			//CurrentZoomFOV;
			//apex_mem.Read<float>(wep_entity + (0x1590 + 0x00b8), CurrentZoomFOV); // m_playerData + m_targetZoomFOV

			//weapon held stuff

			
			//float targetZoomFOV;
			//apex_mem.Read<float>(LocalPlayer + OFFSET_TARGETZOOMFOV, targetZoomFOV); // Call getTargetZoomFOV as a function
			//if (LPlayer.isZooming()) 
			//{
			//	if (targetZoomFOV > 1.0 && targetZoomFOV < 90.0) 
			//	{
			//		ZoomFOVCircle = tanf(DEG2RAD(targetZoomFOV) * (0.64285714285));
			//	}
			//}
			//else
			//{
			//	ZoomFOVCircle = 1;
			//}
			
			
			//printf("ZoomFOVCircle: %f, targetZoomFOV: %f, WeaponHeldID: %d, CurrentZoomFOV: %f\n", ZoomFOVCircle, targetZoomFOV, WeaponHeldID, CurrentZoomFOV);


			
			char MapName[200] = { 0 };
			//uint64_t MapName_ptr;
			//apex_mem.Read<uint64_t>(g_Base + OFFSET_HOST_MAP, MapName_ptr);
			//apex_mem.ReadArray<char>(MapName_ptr, MapName, 200);
			
			apex_mem.ReadArray<char>(g_Base + OFFSET_LEVELNAME, level_name, sizeof(level_name));	
			//printf("%s\n", level_name);
			
			
			if (strcmp(level_name, "mp_rr_tropic_island_mu2") == 0) 
			{
				map = 1;
			} 
			else if (strcmp(level_name, "mp_rr_canyonlands_hu") == 0) 
			{
				map = 2;
			}
			else if (strcmp(level_name, "mp_rr_desertlands_hu") == 0) 
			{
				map = 3;
			}
			else if (strcmp(level_name, "mp_rr_olympus_mu2") == 0) 
			{
				map = 4;
			} 
			else  if (strcmp(level_name, "mp_rr_divided_moon_mu1") == 0)
			{
				map = 5;
			}
			else  if (strcmp(level_name, "mp_rr_canyonlands_staging_mu1") == 0)
			{
				map = 6;
			}
			else  if (strcmp(level_name, "mp_rr_district") == 0)
			{
				map = 7;
			}
			else
			{
				map = 0;
			}
			//printf("%i\n", map);
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
			
			if (LocalPlayer == 0) continue;

			//Entity LPlayer = getEntity(LocalPlayer);

			team_player = LPlayer.getTeamId();
			/*
			if(!LPlayer.isAlive())
			{
				team_player = LPlayerDead2.getTeamId();
			}*/
			if (team_player < 0 || team_player>50 && !onevone)
			{
				continue;
			}
			//uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;

			uint64_t baseent = 0;
			apex_mem.Read<uint64_t>(entitylist, baseent);
			if (baseent == 0)
			{
				continue;
			}
			//Nade test
			//int HeldID;
			//apex_mem.Read<int>(LocalPlayer + OFFSET_OFF_WEAPON, HeldID); // 0x1a1c
			//printf("%i\n", HeldID);
			
			
			//Dont edit.
			max = 999.0f;
			tmp_aimentity = 0;
			tmp_spec = 0;
			tmp_all_spec = 0;
			if (map >= 1 && map <= 7)
			{
				if(firing_range)
				{
					int c=0;
					//Ammount of ents to loop, dont edit.
					for (int i = 0; i < 15000; i++)
					{
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i * 32), centity);
						if (centity == 0) continue;
						if (LocalPlayer == centity) continue;

						Entity Target = getEntity(centity);
						if (!Target.isDummy())
						{
							continue;
						}



										   
						ProcessPlayer(LPlayer, Target, entitylist, c);
						c++;
					}
				}
				else
				{ 	
					int d = 0;
					for (int i = 1; i < toRead; i++)
					{
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>(entitylist + ((uint64_t)i * 32), centity);
						if (centity == 0) continue;
						if (LocalPlayer == centity) continue;

						Entity Target = getEntity(centity);
						if (!Target.isPlayer())
						{
							continue;
						}
						
						ProcessPlayer(LPlayer, Target, entitylist, d);

						int entity_team = Target.getTeamId();
						if (entity_team == team_player && !onevone)
						{
							continue;
						}
						d++;						
					}
				}
			}

			spectators = tmp_spec;
			allied_spectators = tmp_all_spec;

			if(!lock)
				aimentity = tmp_aimentity;
			else
				aimentity = lastaimentity;			
		}
	}
	actions_t = false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////

bool FireRangePlayers[9000] = {false}; // Array to keep track of updated items
bool NonFireRangePlayers[toRead] = {false};
//player players[toRead];
std::vector<player> players(toRead);
//item items[ItemtoRead];
std::vector<item> items(ItemtoRead);
Entity LPlayerDead2;
bool LPDead = false;




//Rank API stuff

std::mutex fileMutex2;
std::mutex throttleMutex;
std::map<uint64_t, std::string> playerRanksMap;
std::mutex cullMutex; // Mutex for thread safety of lastCullTime and other shared resources


std::unordered_map<uint64_t, bool> rankPrintedMap;
std::unordered_map<uint64_t, std::thread> rankThreadMap;
int ApiKeycurrent = 0;
std::vector<std::string> apiKeys;



static size_t CustomWriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getJson(std::string url)
{
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CustomWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return readBuffer;
}
bool loadApiKeysFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file: " << filename << " - " << std::strerror(errno) << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			apiKeys.push_back(line);
		}
	}

	file.close();
	return !apiKeys.empty();  // Return true if keys are loaded
}

std::string getApiKey()
{
	if (apiKeys.empty()) {
		std::cerr << "Error: No API keys loaded." << std::endl;
		return "";
	}

	// Get the current API key and update the index
	std::string key = apiKeys[ApiKeycurrent];
	ApiKeycurrent = (ApiKeycurrent + 1) % apiKeys.size();  // Loop back to 0 after the last key
	return key;
}

//std::mutex rateLimiterMutex;
std::chrono::steady_clock::time_point lastApiCallTime = std::chrono::steady_clock::now();
std::mutex rankMutex;
std::string getRank(uint64_t platformUserId, int platformId, const char* name)
{
	//std::unique_lock<std::mutex> lock(rateLimiterMutex);



	// Existing code for constructing the URL and making the request
	std::string platformName;
	switch (platformId)
	{
	case 7: //pc for sure
		platformName = "PC";
		break;
	case 2:
		platformName = "PC";
		break;
	case 1: //not sure might have to do with rookie
		platformName = "PS4";
		break;
	case 8:
		platformName = "PS4";
		break;
	case 10: //not sure might have to do with rookie
		platformName = "X1";
		break;
	case 9: //not sure 
		platformName = "SWITCH";
		break;
	case 0: //not sure not SWITCH, not PC
		platformName = "X1";
		break;
	default:
		platformName = "PC";
		break;
	}

	std::string url = "https://api.mozambiquehe.re/bridge?auth=";
	url.append(getApiKey());
	url.append("&uid=");
	url.append(std::to_string(platformUserId));
	url.append("&platform=");
	url.append(platformName);
	std::string json = getJson(url);
	//debug printf all the url
	//printf("JSON Response: %s\n", json.c_str());

	Json::Value root;
	Json::CharReaderBuilder reader;
	std::string errors;
	std::istringstream sstream(json);
	bool parsingSuccessful = Json::parseFromStream(reader, sstream, &root, &errors);
	if (!parsingSuccessful)
	{
		std::cout << "Failed to parse configuration: " << errors << std::endl;
		return "0";
	}

	// Check for error messages
	if (root.isMember("Error"))
	{
		std::string errorMessage = root["Error"].asString();

		// Handle "Invalid API key" error
		if (errorMessage == "Invalid API key")
		{
			printf("Error: Invalid API key in apikey.txt\n");
			return "Invalid API key";
		}

		// Handle throttling error
		if (errorMessage.find("Slow down") != std::string::npos)
		{
			printf("Error: Throttling detected: %s\n", errorMessage.c_str());
			return "Throttling error";
		}
	}

	std::string rank = root["global"]["rank"]["rankName"].asString();
	if (rank.empty())
	{
		
		//std::cout << "Empty rank" << std::endl;
		//std::cout << "User ID: " << platformUserId << std::endl;
		//std::cout << "Platform ID: " << platformId << std::endl;
		//return "0";
		
		// Use printf to output when the rank is empty
		//printf("Empty rank for Name: %s, User ID: %llu, Platform ID: %d\n", name, platformUserId, platformId);
		return "Empty rank";
	}
	return rank;
}

void updateRankFile(uint64_t targetUID, const std::string& rank)
{
	if (rank == "Empty rank" || rank == "Throttling error" || rank == "0") {
		//std::cout << "Invalid rank: " << rank << ". Not updating the file." << std::endl;
		printf("Invalid rank: %s. Not updating the file.\n", rank.c_str());
		return;
	}
	std::lock_guard<std::mutex> lock(fileMutex2);

	std::ifstream rankFileIn("player_ranks.txt");
	std::vector<std::string> lines;
	bool found = false;

	// Read the file content into memory
	if (rankFileIn.is_open()) {
		std::string line;
		while (std::getline(rankFileIn, line)) {
			std::stringstream ss(line);
			uint64_t fileUID;
			std::string temp;

			// Parse each line to extract the TargetUID
			ss >> fileUID;

			// If the TargetUID matches, update the line with the new rank
			if (fileUID == targetUID) {
				std::stringstream newLine;
				newLine << targetUID << " " << rank;
				lines.push_back(newLine.str());
				found = true;
			}
			else {
				lines.push_back(line); // Keep the original line if UID doesn't match
			}
		}
		rankFileIn.close();
	}

	// If TargetUID wasn't found, append a new line
	if (!found) {
		std::stringstream newLine;
		newLine << targetUID << " " << rank;
		lines.push_back(newLine.str());
	}

	// Write the updated content back to the file
	std::ofstream rankFileOut("player_ranks.txt");
	for (const auto& updatedLine : lines) {
		rankFileOut << updatedLine << "\n";
	}
	rankFileOut.close();
	// Update playerRanksMap
	playerRanksMap[targetUID] = rank;
}
std::unordered_map<uint64_t, std::chrono::high_resolution_clock::time_point> throttledPlayersMap;
std::string processPlayerRank(int index, const player& p)
{
    try
    {
        std::string rank = getRank(p.TargetUID, p.PlatformID, p.name);
        // Update the rank in the file (or add it if not present)
        updateRankFile(p.TargetUID, rank);

        // Handle throttling error
        if (rank == "Throttling error")
        {
            {
                std::lock_guard<std::mutex> lock(rankMutex);
                rankPrintedMap[p.TargetUID] = false; // Set rank as not processed
            }

            // Set throttling state with 0.5 seconds delay using high_resolution_clock
            {
                std::lock_guard<std::mutex> lock(throttleMutex);
                throttledPlayersMap[p.TargetUID] = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(500);
            }

            printf("Throttling error for Name: %s, User ID: %llu, Platform ID: %d\n", p.name, p.TargetUID, p.PlatformID);
            return rank;
        }

        // Print if the rank is empty
        if (rank == "Empty rank")
        {
            printf("Empty rank for Name: %s, User ID: %llu, Platform ID: %d\n", p.name, p.TargetUID, p.PlatformID);
            return rank;
        }

        // If rank is valid, update rankPrintedMap
        {
            std::lock_guard<std::mutex> lock(rankMutex);
            rankPrintedMap[p.TargetUID] = true;
        }

        //printf("Index: %i, TargetUID: %llu, Player Name: %s, Player Rank: %s\n", index, p.TargetUID, p.name, rank.c_str());
        return rank; // Return the rank to match the future type
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        // Handle the exception or rethrow it if necessary
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred.\n";
        // Handle unknown exceptions or rethrow if necessary
    }

    return "Error"; // Return a default or error value if an exception occurred
}

void processPlayers(const std::vector<player>& players, int toRead)
{
	static auto lastCullTime = std::chrono::high_resolution_clock::now(); // Static to keep track across calls
	auto currentTime = std::chrono::high_resolution_clock::now();

	// Check if enough time has passed since the last cull (1.5 seconds)
	std::chrono::duration<float> cullElapsedTime = currentTime - lastCullTime;

	// If less than 1.5 seconds have passed, return without doing anything
	if (cullElapsedTime.count() < 1.0f) 
	{
		return;
	}

	// Proceed with processing players if 1.5 seconds have passed
	for (int i = 0; i < toRead; i++)
	{
		if (players[i].health > 0)
		{

			// Check if player is currently throttled
			auto it = throttledPlayersMap.find(players[i].TargetUID);
			if (it != throttledPlayersMap.end())
			{
				auto throttledUntil = it->second;
				if (currentTime < throttledUntil)
				{
					// Player is still throttled
					continue;
				}
				else
				{
					// Throttling period has passed, remove from map
					throttledPlayersMap.erase(it);
				}
			}
			// Ensure the player’s TargetUID is initialized in rankPrintedMap
			if (rankPrintedMap.find(players[i].TargetUID) == rankPrintedMap.end())
			{
				rankPrintedMap[players[i].TargetUID] = false;
			}
			// Check if rank has already been processed
			if (!rankPrintedMap[players[i].TargetUID])
			{

				// Mark this player's rank as being processed
				rankPrintedMap[players[i].TargetUID] = true;

				// Start a new thread to process the player's rank
				rankThreadMap[players[i].TargetUID] = std::thread(processPlayerRank, i, players[i]);



				// Update lastCullTime to ensure global delay of 1.5 seconds between future launches
				//std::cout << "Elapsed time: " << cullElapsedTime.count() << " seconds\n";
				lastCullTime = currentTime;

				// Break the loop to delay further calls for 1.5 seconds
				break;
			}
		}
	}
}
void loadPlayerRanks(const std::string& filename) {
	std::ifstream rankFileIn(filename);
	std::string line;

	while (std::getline(rankFileIn, line)) {
		std::istringstream ss(line);
		uint64_t fileUID;
		std::string rank;

		// Read the UID
		ss >> fileUID;

		// Use getline to read the rest of the line as the rank (including spaces)
		std::getline(ss >> std::ws, rank);  // std::ws skips any leading whitespace

		playerRanksMap[fileUID] = rank;
	}

	rankFileIn.close();
}

std::string getRankMap(uint64_t targetUID) {
	auto it = playerRanksMap.find(targetUID);
	if (it != playerRanksMap.end()) {
		return it->second;
	}
	return "Unknown"; // Default value if not found
}

//Rank API stuff



bool previous_firing_range = false; // Previous state of firing_range
int previous_map = 0; // Previous state of firing_range
//ESP loop.. this helps right?
std::chrono::steady_clock::time_point resetStartTime;
const std::chrono::seconds resetDuration(5); // 1 minute duration
bool resetInProgress = false;
std::chrono::steady_clock::time_point lastResetTime = std::chrono::steady_clock::now();
const std::chrono::seconds resetInterval(30);
void resetPlayersAndItems() {
	//std::cout << "Resetting players and items arrays every 30 sec." << std::endl;
	players.clear();  // Remove all elements
	players.resize(toRead);  // Refill the vector to the original size with default-initialized objects

	items.clear();  // Remove all elements
	items.resize(ItemtoRead);  // Refill the vector to the original size with default-initialized objects
}

void checkAndReset() {
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsed = currentTime - lastResetTime;

	if (elapsed >= resetInterval) {
		// 30 seconds have passed, perform the reset
		resetPlayersAndItems();
		lastResetTime = currentTime;  // Update the timestamp for the last reset
	}
}
void PlayerMapChange() {
    auto currentTime = std::chrono::steady_clock::now();

    if (map != previous_map) {
        if (!resetInProgress) {
            // Map has changed, start/reset the timer and start the reset process
            //std::cout << "Map state changed. Starting reset process." << std::endl;
            resetStartTime = currentTime;  // Record the start time
            resetInProgress = true;
        }
    }
    
    if (resetInProgress) {
        // Perform the reset operation
        auto elapsed = currentTime - resetStartTime;
        
        if (elapsed < resetDuration) {
            // Continue resetting players array
            //std::cout << "Resetting players array." << std::endl;
			// memset(players, 0, sizeof(players));  // Clear the players array
			players.clear();  // Remove all elements
			players.resize(toRead);  // Refill the vector to the original size with default-initialized objects
			//memset(items, 0, sizeof(items));
			items.clear();  // Remove all elements
			items.resize(ItemtoRead);  // Refill the vector to the original size with default-initialized objects
        } else {
            // Reset duration has completed
           // std::cout << "Reset duration completed." << std::endl;
            resetInProgress = false;  // Stop resetting
        }
    }

    // Update the previous state
    previous_map = map;
}
static void EspLoop()
{
	esp_t = true;
	while(esp_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while(g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (esp)
			{
				//if (map >= 1 && map <= 7)
				//{
					
					static bool APILoad = false;

					// Load API keys from a file
					if (!APILoad)
					{
						loadApiKeysFromFile("apikey.txt");
						APILoad = true;
					}
					valid = false;
					
					static bool RanksLoad = false;
					if (!RanksLoad)
					{
						loadPlayerRanks("player_ranks.txt");
						RanksLoad = true;
					}

					uint64_t LocalPlayer = 0;
					apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
					if (LocalPlayer == 0)
					{
						continue;
					}
					Entity LPlayer = getEntity(LocalPlayer);
					bool LPlayerisAlive = false;
					if (LPlayer.isAlive())
					{
						LPlayerisAlive = true;
					}
					
					
					int team_player = LPlayer.getTeamId();
					
					if (team_player < 0 || team_player>50)
					{
						next2 = true;
						while(next2 && g_Base!=0 && c_Base!=0 && esp)
						{
							std::this_thread::sleep_for(std::chrono::milliseconds(1));
						}
						continue;
					}
					Vector LocalPlayerPosition = LPlayer.getPosition();

					uint64_t viewRenderer = 0;
					apex_mem.Read<uint64_t>(g_Base + OFFSET_RENDER, viewRenderer);
					uint64_t viewMatrix = 0;
					apex_mem.Read<uint64_t>(viewRenderer + OFFSET_MATRIX, viewMatrix);

					apex_mem.Read<Matrix>(viewMatrix, m);

					uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
					
					//memset(players,0,sizeof(players));
					//memset(items, 0, sizeof(items));
					//map change
					PlayerMapChange();
					//checkAndReset();
					int ScreenX;
					int ScreenY;
					if (ScreenResINT == 0)
					{
						ScreenX = 1920;
						ScreenY = 1080;
					}
					if (ScreenResINT == 1)
					{
						ScreenX = 2560;
						ScreenY = 1440;
					}
					if(firing_range)
					{
						if (firing_range != previous_firing_range)
						{
							// State has changed, so reset players array
							//std::cout << "Firing range state changed. Clearing players array." << std::endl;
							//memset(players, 0, sizeof(players));
							players.assign(toRead, player());

							// Update the previous state
							previous_firing_range = firing_range;
						}
						
						
						//int c=0;
						//Ammount of ents to loop, dont edit.
						for (int i = 8000; i < 9000; i++)
						{
							//if (i - 8000 >= 1000) break; // Ensure index within bounds of players array
							uint64_t centity = 0;
							apex_mem.Read<uint64_t>( entitylist + ((uint64_t)i * 32), centity);
							if (centity == 0)
							{
								continue;
							}		
							
							if (LocalPlayer == centity)
							{
								continue;
							}

							Entity Target = getEntity(centity);
							
							if (!Target.isDummy())
							{
								continue;
							}
							
							if (!Target.isAlive())
							{
								continue;
							}
							
							int entity_team = Target.getTeamId();
							/*
							if (!onevone)
							{
								if (entity_team < 0 || entity_team>50 || entity_team == team_player)
								{
									continue;
								}
							}
							else
							{
								if (entity_team < 0 || entity_team>50)
								{
								  continue;
								}
							}
							*/
							Vector EntityPosition = Target.getPosition();
							float dist = LocalPlayerPosition.DistTo(EntityPosition);

							if (dist > max_dist || dist < 50.0f)
							{	
								continue;
							}
							
							Vector bs = Vector();
							//Change res to your res here, default is 1080p but can copy paste 1440p here
							//printf("Firing Range Test\n");
							WorldToScreen(EntityPosition, m.matrix, ScreenX, ScreenY, bs); //2560, 1440
							if (esp)
							{
								Vector hs = Vector();
								Vector HeadPosition = Target.getBonePositionByHitbox(0);
								//Change res to your res here, default is 1080p but can copy paste 1440p here
								WorldToScreen(HeadPosition, m.matrix, ScreenX, ScreenY, hs); //2560, 1440
								float height = abs(abs(hs.y) - abs(bs.y));
								float width = height / 2.0f;
								float boxMiddle = bs.x - (width / 2.0f);
								int health = Target.getHealth();
								int shield = Target.getShield();
								int maxshield = Target.getMaxshield();
								players[i] = 
								{
									dist,
									entity_team,
									boxMiddle,
									hs.y,
									width,
									height,
									bs.x,
									bs.y,
									0,
									(Target.lastVisTime() > lastvis_esp[i]),
									health,
									shield,
									maxshield
									//Target.isAlive()
									
								};
								Target.get_name(g_Base, i-1, &players[i].name[0]);
								lastvis_esp[i] = Target.lastVisTime();
								
								//printf("Current index: %d\n", i);
								valid = true;
								FireRangePlayers[i] = true;
								//c++;
							}
							
						}
						for (int i = 8000; i < 9000; i++) 
						{
							//printf("FireRangePlayers[%d] = %s\n", i, FireRangePlayers[i] ? "true" : "false");
							if (!FireRangePlayers[i]) 
							{
								//printf("Current index: %d\n", i);
								//printf("FireRangePlayers[%d] = %s\n", i, FireRangePlayers[i] ? "true" : "false");
								//memset(&players[c], 0, sizeof(player));
								//players.at(c) = player();
								memset(&players[i], 0, sizeof(player));
							}						
							else 
							{
								//printf("FireRangePlayers[%d] = %s\n", i, FireRangePlayers[i] ? "true" : "false");
								// Reset the updated status for the next iteration
								FireRangePlayers[i] = false;
							}
						}
					}
					

					
					else if (!firing_range)
					{
						if (firing_range != previous_firing_range)
						{
							// State has changed, so reset players array
							//std::cout << "Firing range state changed. Clearing players array." << std::endl;
							//memset(players, 0, sizeof(players));
							players.assign(toRead, player());

							// Update the previous state
							previous_firing_range = firing_range;
						}
						
						//PlayerMapChange();
						
						//int d = 0;
						for (int i = 0; i < toRead; i++)
						{
							uint64_t centity = 0;
							apex_mem.Read<uint64_t>( entitylist + ((uint64_t)i * 32), centity);
							if (centity == 0)
							{
								continue;
							}
							
							if (LocalPlayer == centity)
							{
								continue;
							}
							

							Entity Target = getEntity(centity);
				
							if (!Target.isPlayer())
							{
								continue;
							}
							//players[i].Observing = Target.Observing(LPlayer.ptr);
							/*
							if (!Target.isAlive())
							{
								continue;
							}
							*/
							int entity_team = Target.getTeamId();
							
							if (!onevone)
							{
								if (entity_team < 0 || entity_team>50 || entity_team == team_player)
								{
									continue;
								}
							}
							else
							{
								if (entity_team < 0 || entity_team>50)
								{
								  continue;
								}
							}
							
							

							//Vector EntityPosition = Target.getPosition();
							bool Observing = Target.Observing(LPlayer.ptr);
							if (!LPlayerisAlive)
							{
								LPDead = true;
							}
							else 
							{
								LPDead = false;
							}
							Vector EntityPosition = Target.getPosition();
							LocalPlayerPosition = LPlayer.getPosition();  // Adjust to observed player's position
							QAngle localviewangle = LPlayer.GetViewAngles();
							
							float dist = LocalPlayerPosition.DistTo(EntityPosition);
							
							//float dist = LocalPlayerPosition.DistTo(EntityPosition);

							
							if (dist > max_dist || dist < 50.0f)
							{	
								continue;
							}
							
							//printf("Dead after dist\n");
							Vector bs = Vector();
							//Change res to your res here, default is 1080p but can copy paste 1440p here
							WorldToScreen(EntityPosition, m.matrix, ScreenX, ScreenY, bs); //2560, 1440
							if (esp)
							{
								
								Vector hs = Vector();
								Vector HeadPosition = Target.getBonePositionByHitbox(0);
								//Change res to your res here, default is 1080p but can copy paste 1440p here
								WorldToScreen(HeadPosition, m.matrix, ScreenX, ScreenY, hs); //2560, 1440
								float height = abs(abs(hs.y) - abs(bs.y));
								float width = height / 2.0f;
								float boxMiddle = bs.x - (width / 2.0f);
								int health = Target.getHealth();
								int shield = Target.getShield();
								int maxshield = Target.getMaxshield();
								
								//Vector LocalPlayerPosition = LPlayer.getPosition();
								//if(!LPlayer.isAlive())
								//{
								//	LocalPlayerPosition = LPlayerDead2.getPosition();
								//}
								//QAngle localviewangle = LPlayer.GetViewAngles();
								//if(!LPlayer.isAlive())
								//{
								//	localviewangle = LPlayerDead2.GetViewAngles();
								//}
								float targetyaw = Target.GetYaw();
								bool IsAlive = Target.isAlive();
								
								//get rank and stuff
								int PlatformID = Target.PlatformID();
								uint64_t TargetUID = Target.TargetUID();
								bool rankPrinted;
								//int playerlevel = Target.GetPlayerLevel(centity);
								
								if (GetRanks)
								{
									processPlayers(players, toRead);
								}
								
								
								//std::string Rank;
								//players[i].Rank = getRankMap(players[i].TargetUID);
								std::string rank = getRankMap(players[i].TargetUID);
								
								int RankID = 2;
								if (rank == "Rookie")
								{
									RankID = 1;
								}
								else if (rank == "Unranked")
								{
									RankID = 2;
								}
								else if (rank == "Bronze")
								{
									RankID = 3;
								}
								else if (rank == "Silver")
								{
									RankID = 4;
								}
								else if (rank == "Gold")
								{
									RankID = 5;
								}
								else if (rank == "Platinum")
								{
									RankID = 6;
								}
								else if (rank == "Diamond")
								{
									RankID = 7;
								}
								else if (rank == "Master")
								{
									RankID = 8;
								}
								else if (rank == "Apex Predator")
								{
									RankID = 9;
								}
								else
								{
									RankID = 0;
								}
								players[i] = 
								{
									dist,
									entity_team,
									boxMiddle,
									hs.y,
									width,
									height,
									bs.x,
									bs.y,
									Target.isKnocked(),
									(Target.lastVisTime() > lastvis_esp[i]),
									health,
									shield,
									maxshield,
									EntityPosition,
									LocalPlayerPosition,
									localviewangle,
									targetyaw,
									Target.read_xp_level(),
									Observing,
									PlatformID,
									RankID,
									TargetUID
								};
								//int playerslevel = 0;
								//char playerName[90];
								//Target.get_name(g_Base, i-1, playerName);
								Target.get_name(g_Base, i-1, &players[i].name[0]);
								//printf("Rank: %s\n", players[i].Rank.c_str());
								
								
									
									
								
								//if(Observing)
								//{
								//	printf("Player Name: %s, Observing: %d\n", players[i].name, Observing);
								//}
								//printf("Player Name: %s, PlatformID: %i, TargetUID: %lu\n", players[i].name, PlatformID, TargetUID);
								
								//printf("%i\n", level);
								//printf("Player Name: %s, Level: %i\n", playerName, playerlevel);
								//uint64_t modelname_ptr = 0;
								//apex_mem.Read<uint64_t>(g_Base + OFFSET_MODELNAME, modelname_ptr);
								//apex_mem.ReadArray<char>(modelname_ptr, &players[i].modelname[0], 1024);
								//printf("Model Name: %s\n", &players[i].modelname[0]);
								
								
								
								
								lastvis_esp[i] = Target.lastVisTime();
								valid = true;
								NonFireRangePlayers[i] = true;
								//d++;
								
							}
							
						}
						for (int i = 0; i < toRead; i++) 
						{
							//printf("FireRangePlayers[%d] = %s\n", i, FireRangePlayers[i] ? "true" : "false");
							if (!NonFireRangePlayers[i]) 
							{
								//printf("Current index: %d\n", i);
								//printf("FireRangePlayers[%d] = %s\n", i, FireRangePlayers[i] ? "true" : "false");
								//memset(&players[d], 0, sizeof(player));
								//players.at(d) = player();
								memset(&players[i], 0, sizeof(player));
							}						
							else 
							{
								//printf("FireRangePlayers[%d] = %s\n", i, FireRangePlayers[i] ? "true" : "false");
								// Reset the updated status for the next iteration
								NonFireRangePlayers[i] = false;
							}
						}
					}
					
					

					next2 = true;
					while(next2 && g_Base!=0 && c_Base!=0 && esp)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
				//}
			}
		}
	}
	esp_t = false;
}
//Aimbot Loop stuff
static void AimbotLoop()
{
	aim_t = true;
	while (aim_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (aim>0)
			{
				if(AimSnapToggle)
				{
					if (!HoldSheila || !OnSheila)
					{
						//printf("OnSheila: %d\n", OnSheila ? 1 : 0);
						if(TargetIndex == TargetIndexLock)
						{
							if (aimentity == 0 || !aiming)
							{
								lock=false;
								lastaimentity=0;
								continue;
							}
							lock=true;
							lastaimentity = aimentity;
							uint64_t LocalPlayer = 0;
							apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
							if (LocalPlayer == 0) continue;
							Entity LPlayer = getEntity(LocalPlayer);
							QAngle Angles = CalculateBestBoneAim(LPlayer, aimentity, max_fov);
							if (Angles.x == 0 && Angles.y == 0)
							{
								lock=false;
								lastaimentity=0;
								continue;
							}
							LPlayer.SetViewAngles(Angles);
						}
					}
					else
					{
						if (aimentity == 0 || !aiming)
						{
							lock=false;
							lastaimentity=0;
							continue;
						}
						lock=true;
						lastaimentity = aimentity;
						uint64_t LocalPlayer = 0;
						apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
						if (LocalPlayer == 0) continue;
						Entity LPlayer = getEntity(LocalPlayer);
						QAngle Angles = CalculateBestBoneAim(LPlayer, aimentity, max_fov);
						if (Angles.x == 0 && Angles.y == 0)
						{
							lock=false;
							lastaimentity=0;
							continue;
						}
						LPlayer.SetViewAngles(Angles);
					}
				}
				else
				{
					if (aimentity == 0 || !aiming)
					{
						lock=false;
						lastaimentity=0;
						continue;
					}
					lock=true;
					lastaimentity = aimentity;
					uint64_t LocalPlayer = 0;
					apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
					if (LocalPlayer == 0) continue;
					Entity LPlayer = getEntity(LocalPlayer);
					QAngle Angles = CalculateBestBoneAim(LPlayer, aimentity, max_fov);
					if (Angles.x == 0 && Angles.y == 0)
					{
						lock=false;
						lastaimentity=0;
						continue;
					}
					LPlayer.SetViewAngles(Angles);
				}
			}
		}
	}
	aim_t = false;
}
//Client memory vars/reads. HAVE to match windows client numbers. TODO
static void set_vars(uint64_t add_addr)
{
	printf("Reading BeefGuyDoom vars...\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	//Get addresses of client vars
	uint64_t check_addr = 0;
	client_mem.Read<uint64_t>(add_addr, check_addr);
	uint64_t aim_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t), aim_addr);
	uint64_t esp_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*2, esp_addr);
	uint64_t aiming_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*3, aiming_addr);
	uint64_t g_Base_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*4, g_Base_addr);
	uint64_t next2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*5, next2_addr);
	uint64_t player_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*6, player_addr);
	uint64_t valid_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*7, valid_addr);
	uint64_t max_dist_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*8, max_dist_addr);
	uint64_t item_glow_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*9, item_glow_addr);
	uint64_t player_glow_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*10, player_glow_addr);
	uint64_t aim_no_recoil_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*11, aim_no_recoil_addr);
	uint64_t smooth_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*12, smooth_addr);
	uint64_t max_fov_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*13, max_fov_addr);
	uint64_t bone_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*14, bone_addr);
	uint64_t spectators_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*16, spectators_addr);
	uint64_t allied_spectators_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*17, allied_spectators_addr);
	uint64_t glowr_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*18, glowr_addr);
	uint64_t glowg_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*19, glowg_addr);
	uint64_t glowb_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*20, glowb_addr);
	uint64_t firing_range_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*21, firing_range_addr);
	uint64_t lightbackpack_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*22, lightbackpack_addr);
	uint64_t medbackpack_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*23, medbackpack_addr);
	uint64_t heavybackpack_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*24, heavybackpack_addr);
	uint64_t shieldupgrade1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*25, shieldupgrade1_addr);
	uint64_t shieldupgradehead1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*26, shieldupgradehead1_addr);
	uint64_t accelerant_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*27, accelerant_addr);
	uint64_t phoenix_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*28, phoenix_addr);
	uint64_t healthlarge_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*29, healthlarge_addr);
	uint64_t healthsmall_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*30, healthsmall_addr);
	uint64_t shieldbattsmall_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*31, shieldbattsmall_addr);
	uint64_t shieldbattlarge_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*32, shieldbattlarge_addr);
	uint64_t sniperammo_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*33, sniperammo_addr);
	uint64_t heavyammo_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*34, heavyammo_addr);
	uint64_t optic1xhcog_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*35, optic1xhcog_addr);
	uint64_t lightammo_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*36, lightammo_addr);
	uint64_t energyammo_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*37, energyammo_addr);
	uint64_t shotgunammo_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*38, shotgunammo_addr);
	uint64_t lasersight1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*39, lasersight1_addr);
	uint64_t sniperammomag1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*40, sniperammomag1_addr);
	uint64_t energyammomag1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*41, energyammomag1_addr);
	uint64_t stocksniper1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*42, stocksniper1_addr);
	uint64_t stockregular1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*43, stockregular1_addr);
	uint64_t shielddown1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*44, shielddown1_addr);
	uint64_t lightammomag1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*45, lightammomag1_addr);
	uint64_t heavyammomag1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*46, heavyammomag1_addr);
	uint64_t optic2xhcog_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*47, optic2xhcog_addr);
	uint64_t opticholo1x_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*48, opticholo1x_addr);
	uint64_t opticholo1x2x_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*49, opticholo1x2x_addr);
	uint64_t opticthreat_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*50, opticthreat_addr);
	uint64_t optic3xhcog_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*51, optic3xhcog_addr);
	uint64_t optic2x4x_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*52, optic2x4x_addr);
	uint64_t opticsniper6x_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*53, opticsniper6x_addr);
	uint64_t opticsniper4x8x_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*54, opticsniper4x8x_addr);
	uint64_t opticsniperthreat_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*55, opticsniperthreat_addr);
	uint64_t suppressor1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*56, suppressor1_addr);
	uint64_t turbo_charger_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*57, turbo_charger_addr);
	uint64_t grenade_frag_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*58, grenade_frag_addr);
	uint64_t grenade_arc_star_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*59, grenade_arc_star_addr);
	uint64_t grenade_thermite_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*60, grenade_thermite_addr);
	uint64_t shotgunbolt1_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*61, shotgunbolt1_addr);
	uint64_t weapon_kraber_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*62, weapon_kraber_addr);
	uint64_t weapon_mastiff_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*63, weapon_mastiff_addr);
	uint64_t weapon_lstar_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*64, weapon_lstar_addr);
	uint64_t weapon_havoc_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*65, weapon_havoc_addr);
	uint64_t weapon_devotion_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*66, weapon_devotion_addr);
	uint64_t weapon_triple_take_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*67, weapon_triple_take_addr);
	uint64_t weapon_flatline_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*68, weapon_flatline_addr);
	uint64_t weapon_hemlock_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*69, weapon_hemlock_addr);
	uint64_t weapon_g7_scout_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*70, weapon_g7_scout_addr);
	uint64_t weapon_alternator_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*71, weapon_alternator_addr);
	uint64_t weapon_r99_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*72, weapon_r99_addr);
	uint64_t weapon_prowler_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*73, weapon_prowler_addr);
	uint64_t weapon_volt_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*74, weapon_volt_addr);
	uint64_t weapon_longbow_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*75, weapon_longbow_addr);
	uint64_t weapon_charge_rifle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*76, weapon_charge_rifle_addr);
	uint64_t weapon_spitfire_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*77, weapon_spitfire_addr);
	uint64_t weapon_r301_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*78, weapon_r301_addr);
	uint64_t weapon_eva8_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*79, weapon_eva8_addr);
	uint64_t weapon_peacekeeper_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*80, weapon_peacekeeper_addr);
	uint64_t weapon_mozambique_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*81, weapon_mozambique_addr);
	uint64_t weapon_wingman_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*82, weapon_wingman_addr);
	uint64_t weapon_p2020_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*83, weapon_p2020_addr);
	uint64_t weapon_re45_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*84, weapon_re45_addr);
	uint64_t weapon_sentinel_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*85, weapon_sentinel_addr);
	uint64_t weapon_bow_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*86, weapon_bow_addr);
	uint64_t weapon_3030_repeater_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*87, weapon_3030_repeater_addr);
	uint64_t weapon_rampage_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*88, weapon_rampage_addr);
	uint64_t weapon_car_smg_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*89, weapon_car_smg_addr);
	uint64_t aimdist_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*90, aimdist_addr);
	uint64_t itemglowbrightness_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*91, itemglowbrightness_addr);
	uint64_t glowrviz_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*92, glowrviz_addr);
	uint64_t glowgviz_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*93, glowgviz_addr);
	uint64_t glowbviz_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*94, glowbviz_addr);
	uint64_t glowrknocked_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*95, glowrknocked_addr);
	uint64_t glowgknocked_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*96, glowgknocked_addr);
	uint64_t glowbknocked_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*97, glowbknocked_addr);
	//uint64_t bulletspeed_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*98, bulletspeed_addr);
	//uint64_t bulletgrav_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*99, bulletgrav_addr);
	uint64_t weapon_nemesis_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*100, weapon_nemesis_addr);
	uint64_t EntTeam_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*102, EntTeam_addr);
	uint64_t LocTeam_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*103, LocTeam_addr);
	uint64_t TDMToggle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*104, TDMToggle_addr);
	uint64_t onevone_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*105, onevone_addr);
	uint64_t shieldupgrade2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*106, shieldupgrade2_addr);
	uint64_t shieldupgradehead2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*107, shieldupgradehead2_addr);
	uint64_t shieldupgrade3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*108, shieldupgrade3_addr);
	uint64_t shieldupgradehead3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*109, shieldupgradehead3_addr);
	uint64_t shieldupgrade4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*110, shieldupgrade4_addr);
	uint64_t shieldupgradehead4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*111, shieldupgradehead4_addr);
	uint64_t shielddown2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*112, shielddown2_addr);
	uint64_t shielddown3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*113, shielddown3_addr);
	uint64_t shielddown4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*114, shielddown4_addr);
	uint64_t sniperammomag2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*115, sniperammomag2_addr);
	uint64_t sniperammomag3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*116, sniperammomag3_addr);
	uint64_t sniperammomag4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*117, sniperammomag4_addr);
	uint64_t energyammomag2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*118, energyammomag2_addr);
	uint64_t energyammomag3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*119, energyammomag3_addr);
	uint64_t energyammomag4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*120, energyammomag4_addr);
	uint64_t lightammomag2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*121, lightammomag2_addr);
	uint64_t lightammomag3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*122, lightammomag3_addr);
	uint64_t lightammomag4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*123, lightammomag4_addr);
	uint64_t heavyammomag2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*124, heavyammomag2_addr);
	uint64_t heavyammomag3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*125, heavyammomag3_addr);
	uint64_t heavyammomag4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*126, heavyammomag4_addr);
	uint64_t lasersight2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*127, lasersight2_addr);
	uint64_t lasersight3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*128, lasersight3_addr);
	uint64_t lasersight4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*129, lasersight4_addr);
	uint64_t stocksniper2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*130, stocksniper2_addr);
	uint64_t stockregular2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*131, stockregular2_addr);
	uint64_t stocksniper3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*132, stocksniper3_addr);
	uint64_t stockregular3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*133, stockregular3_addr);
	uint64_t suppressor2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*134, suppressor2_addr);
	uint64_t suppressor3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*135, suppressor3_addr);
	uint64_t skull_piecer_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*136, skull_piecer_addr);
	uint64_t hammer_point_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*137, hammer_point_addr);
	uint64_t disruptor_rounds_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*138, disruptor_rounds_addr);
	uint64_t boosted_loader_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*139, boosted_loader_addr);
	uint64_t shotgunbolt2_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*140, shotgunbolt2_addr);
	uint64_t shotgunbolt3_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*141, shotgunbolt3_addr);
	uint64_t shotgunbolt4_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*142, shotgunbolt4_addr);
	uint64_t insidevaluegoggle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*143, insidevaluegoggle_addr);
	uint64_t outlinesize_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*144, outlinesize_addr);
	uint64_t goldbackpack_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*145, goldbackpack_addr);
	uint64_t shieldupgrade5_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*146, shieldupgrade5_addr);
	uint64_t SuperKey_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*147, SuperKey_addr);
	uint64_t m_traversalProgress_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*150, m_traversalProgress_addr);
	uint64_t LocalYAW_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*151, LocalYAW_addr);
	uint64_t TargetYAW_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*152, TargetYAW_addr);
	uint64_t TARGET_TEAMID_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*153, TARGET_TEAMID_addr);
	uint64_t TEAM_TEAMID_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*154, TEAM_TEAMID_addr);
	uint64_t TriggerBot_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*155, TriggerBot_addr);
	uint64_t tapstrafeenable_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*156, tapstrafeenable_addr);
	uint64_t lstarvalueid_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*157, lstarvalueid_addr);
	uint64_t PrintMapCords_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*158, PrintMapCords_addr);
	uint64_t veltest_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*159, veltest_addr);
	uint64_t CurrentWeaponADSZoom_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*160, CurrentWeaponADSZoom_addr);
	uint64_t map_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*161, map_addr);
	uint64_t TogglePrediction_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*162, TogglePrediction_addr);
	uint64_t AutoFire_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*163, AutoFire_addr);
	uint64_t PrintModelAndId_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*164, PrintModelAndId_addr);
	uint64_t ScreenResINT_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*165, ScreenResINT_addr);
	uint64_t BoxEnable_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*166, BoxEnable_addr);
	uint64_t NoNadeAim_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*167, NoNadeAim_addr);
	uint64_t PrintHeldID_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*168, PrintHeldID_addr);
	uint64_t HeadShotMode_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*169, HeadShotMode_addr);
	uint64_t selectedFPSIndex_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*170, selectedFPSIndex_addr);
	uint64_t Mobi_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*171, Mobi_addr);
	uint64_t HeadShield_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*172, HeadShield_addr);
	uint64_t JumpTower_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*173, JumpTower_addr);
	uint64_t Traps_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*174, Traps_addr);
	
	uint64_t TargetIndex_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*175, TargetIndex_addr);
	uint64_t TargetIndexLock_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*176, TargetIndexLock_addr);
	
	uint64_t AimSnapToggle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*177, AimSnapToggle_addr);
	//item esp test
	uint64_t item_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*178, item_addr);
	uint64_t ItemESPClient_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*179, ItemESPClient_addr);
	uint64_t ItemESPClientALL_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*180, ItemESPClientALL_addr);
	
	
	
	uint64_t Matrixm_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*181, Matrixm_addr);
	
	
	uint64_t KeyCard_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*182, KeyCard_addr);
	
	uint64_t gunshield_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*183, gunshield_addr);
	
	//lootfilledtoggle
	uint64_t lootinsidevaluegoggle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*184, lootinsidevaluegoggle_addr);
	
	//auto grapple
	uint64_t AutoGrappleToggle_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*185, AutoGrappleToggle_addr);
	
	
	uint64_t LPDead_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*186, LPDead_addr);
	
	uint64_t GetRanks_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*187, GetRanks_addr);
	
	uint64_t InputSystem_addr = 0;
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*188, InputSystem_addr);
	
	uint64_t minimapradar_addr = 0;
	uint64_t mainradarmap_addr = 0;


	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*189, minimapradar_addr);
	client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*190, mainradarmap_addr);


	if (InputSystem)
	{
		client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*189, minimapradar_addr);
		
		
		client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*190, mainradarmap_addr);
	}

	
	//item esp test
	//fov circle testing
	//uint64_t ZoomFOVCircle_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*170, ZoomFOVCircle_addr);
	//uint64_t WeaponHeldID_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*171, WeaponHeldID_addr);
	//uint64_t targetZoomFOV_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*172, targetZoomFOV_addr);
	//uint64_t CurrentZoomFOV_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*173, CurrentZoomFOV_addr);
	
	
	//itemnameesp
	//uint64_t item_addr = 0;
	//client_mem.Read<uint64_t>(add_addr + sizeof(uint64_t)*174, item_addr);
	//itemnameesp
	uint32_t check = 0;
	client_mem.Read<uint32_t>(check_addr, check);
	if(check != 0xABCD)
	{
		printf("Incorrect values read. Check if the add_off (line 3035 in apex_dma.cpp) is correct. Quitting.\n");
		active = false;
		return;
	}
	vars_t = true;
	while(vars_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if(c_Base!=0 && g_Base!=0)
		{
			client_mem.Write<uint32_t>(check_addr, 0);
			printf("\nLet the fun begin!\n");
		}

		while(c_Base!=0 && g_Base!=0)
		{
			//same as above, has to match with eveything else
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			client_mem.Write<uint64_t>(g_Base_addr, g_Base);
			client_mem.Write<int>(spectators_addr, spectators);
			client_mem.Write<int>(allied_spectators_addr, allied_spectators);
			client_mem.Read<int>(aim_addr, aim);
			client_mem.Read<bool>(esp_addr, esp);
			client_mem.Read<bool>(aiming_addr, aiming);
			client_mem.Read<float>(max_dist_addr, max_dist);
			client_mem.Read<bool>(item_glow_addr, item_glow);
			client_mem.Read<bool>(player_glow_addr, player_glow);
			client_mem.Read<bool>(aim_no_recoil_addr, aim_no_recoil);
			client_mem.Read<float>(smooth_addr, smooth);
			client_mem.Read<float>(max_fov_addr, max_fov);
			client_mem.Read<int>(bone_addr, bone);
			client_mem.Read<float>(glowr_addr, glowr);
			client_mem.Read<float>(glowg_addr, glowg);
			client_mem.Read<float>(glowb_addr, glowb);
			client_mem.Read<bool>(firing_range_addr, firing_range);
			client_mem.Read<bool>(lightbackpack_addr, lightbackpack);
			client_mem.Read<bool>(medbackpack_addr, medbackpack);
			client_mem.Read<bool>(heavybackpack_addr, heavybackpack);
			client_mem.Read<bool>(shieldupgrade1_addr, shieldupgrade1);
			client_mem.Read<bool>(shieldupgradehead1_addr, shieldupgradehead1);
			client_mem.Read<bool>(accelerant_addr, accelerant);
			client_mem.Read<bool>(phoenix_addr, phoenix);
			client_mem.Read<bool>(healthlarge_addr, healthlarge);
			client_mem.Read<bool>(healthsmall_addr, healthsmall);
			client_mem.Read<bool>(shieldbattsmall_addr, shieldbattsmall);
			client_mem.Read<bool>(shieldbattlarge_addr, shieldbattlarge);
			client_mem.Read<bool>(sniperammo_addr, sniperammo);
			client_mem.Read<bool>(heavyammo_addr, heavyammo);
			client_mem.Read<bool>(optic1xhcog_addr, optic1xhcog);
			client_mem.Read<bool>(lightammo_addr, lightammo);
			client_mem.Read<bool>(energyammo_addr, energyammo);
			client_mem.Read<bool>(shotgunammo_addr, shotgunammo);
			client_mem.Read<bool>(lasersight1_addr, lasersight1);
			client_mem.Read<bool>(sniperammomag1_addr, sniperammomag1);
			client_mem.Read<bool>(energyammomag1_addr , energyammomag1);
			client_mem.Read<bool>(stocksniper1_addr, stocksniper1);
			client_mem.Read<bool>(stockregular1_addr, stockregular1);
			client_mem.Read<bool>(stocksniper2_addr, stocksniper2);
			client_mem.Read<bool>(stockregular2_addr, stockregular2);
			client_mem.Read<bool>(stocksniper3_addr, stocksniper3);
			client_mem.Read<bool>(stockregular3_addr, stockregular3);
			client_mem.Read<bool>(shielddown1_addr, shielddown1);
			client_mem.Read<bool>(lightammomag1_addr, lightammomag1);
			client_mem.Read<bool>(heavyammomag1_addr, heavyammomag1);
			client_mem.Read<bool>(optic2xhcog_addr, optic2xhcog);
			client_mem.Read<bool>(opticholo1x_addr, opticholo1x);
			client_mem.Read<bool>(opticholo1x2x_addr, opticholo1x2x);
			client_mem.Read<bool>(opticthreat_addr, opticthreat);
			client_mem.Read<bool>(optic3xhcog_addr, optic3xhcog);
			client_mem.Read<bool>(optic2x4x_addr, optic2x4x);
			client_mem.Read<bool>(opticsniper6x_addr, opticsniper6x);
			client_mem.Read<bool>(opticsniper4x8x_addr, opticsniper4x8x);
			client_mem.Read<bool>(opticsniperthreat_addr, opticsniperthreat);
			client_mem.Read<bool>(suppressor1_addr, suppressor1);
			client_mem.Read<bool>(turbo_charger_addr, turbo_charger);
			client_mem.Read<bool>(grenade_frag_addr, grenade_frag);
			client_mem.Read<bool>(grenade_arc_star_addr, grenade_arc_star);
			client_mem.Read<bool>(grenade_thermite_addr, grenade_thermite);
			client_mem.Read<bool>(shotgunbolt1_addr, shotgunbolt1);
			client_mem.Read<bool>(shotgunbolt2_addr, shotgunbolt2);
			client_mem.Read<bool>(shotgunbolt3_addr, shotgunbolt3);
			client_mem.Read<bool>(shotgunbolt4_addr, shotgunbolt4);
			client_mem.Read<bool>(weapon_kraber_addr, weapon_kraber);
			client_mem.Read<bool>(weapon_mastiff_addr, weapon_mastiff);
			client_mem.Read<bool>(weapon_lstar_addr, weapon_lstar);
			client_mem.Read<bool>(weapon_havoc_addr, weapon_havoc);
			client_mem.Read<bool>(weapon_devotion_addr, weapon_devotion);
			client_mem.Read<bool>(weapon_triple_take_addr, weapon_triple_take);
			client_mem.Read<bool>(weapon_flatline_addr, weapon_flatline);
			client_mem.Read<bool>(weapon_hemlock_addr, weapon_hemlock);
			client_mem.Read<bool>(weapon_g7_scout_addr, weapon_g7_scout);
			client_mem.Read<bool>(weapon_alternator_addr, weapon_alternator);
			client_mem.Read<bool>(weapon_r99_addr, weapon_r99);
			client_mem.Read<bool>(weapon_prowler_addr, weapon_prowler);
			client_mem.Read<bool>(weapon_volt_addr, weapon_volt);
			client_mem.Read<bool>(weapon_longbow_addr, weapon_longbow);
			client_mem.Read<bool>(weapon_charge_rifle_addr, weapon_charge_rifle);
			client_mem.Read<bool>(weapon_spitfire_addr, weapon_spitfire);
			client_mem.Read<bool>(weapon_r301_addr, weapon_r301);
			client_mem.Read<bool>(weapon_eva8_addr, weapon_eva8);
			client_mem.Read<bool>(weapon_peacekeeper_addr, weapon_peacekeeper);
			client_mem.Read<bool>(weapon_mozambique_addr, weapon_mozambique);
			client_mem.Read<bool>(weapon_wingman_addr, weapon_wingman);
			client_mem.Read<bool>(weapon_p2020_addr, weapon_p2020);
			client_mem.Read<bool>(weapon_re45_addr, weapon_re45);
			client_mem.Read<bool>(weapon_sentinel_addr, weapon_sentinel);
			client_mem.Read<bool>(weapon_bow_addr, weapon_bow);
			client_mem.Read<bool>(weapon_3030_repeater_addr, weapon_3030_repeater);
			client_mem.Read<bool>(weapon_rampage_addr, weapon_rampage);
			client_mem.Read<bool>(weapon_car_smg_addr, weapon_car_smg);
			client_mem.Read<float>(aimdist_addr, aimdist);
			client_mem.Read<int>(itemglowbrightness_addr, itemglowbrightness);
			//glow visable
			client_mem.Read<float>(glowrviz_addr, glowrviz);
			client_mem.Read<float>(glowgviz_addr, glowgviz);
			client_mem.Read<float>(glowbviz_addr, glowbviz);
			//knocked
			client_mem.Read<float>(glowrknocked_addr, glowrknocked);
			client_mem.Read<float>(glowgknocked_addr, glowgknocked);
			client_mem.Read<float>(glowbknocked_addr, glowbknocked);
			//client_mem.Read<float>(bulletspeed_addr, bulletspeed);
			//client_mem.Read<float>(bulletgrav_addr, bulletgrav);
			//new weapon, nemesis
			
			client_mem.Read<bool>(weapon_nemesis_addr, weapon_nemesis);
			//More TDM toggle stuff
			client_mem.Write<int>(EntTeam_addr, EntTeam);
			client_mem.Write<int>(LocTeam_addr, LocTeam);
			client_mem.Read<bool>(TDMToggle_addr, TDMToggle);
			//1v1
			client_mem.Read<bool>(onevone_addr, onevone);
			//map
			client_mem.Read<bool>(shieldupgrade2_addr, shieldupgrade2);
			client_mem.Read<bool>(shieldupgradehead2_addr, shieldupgradehead2);
			
			client_mem.Read<bool>(shieldupgrade3_addr, shieldupgrade3);
			client_mem.Read<bool>(shieldupgradehead3_addr, shieldupgradehead3);
			
			client_mem.Read<bool>(shieldupgrade4_addr, shieldupgrade4);
			client_mem.Read<bool>(shieldupgrade5_addr, shieldupgrade5);
			client_mem.Read<bool>(shieldupgradehead4_addr, shieldupgradehead4);
			client_mem.Read<bool>(shielddown2_addr, shielddown2);
			client_mem.Read<bool>(shielddown3_addr, shielddown3);
			client_mem.Read<bool>(shielddown4_addr, shielddown4);
			
			client_mem.Read<bool>(sniperammomag2_addr, sniperammomag2);
			client_mem.Read<bool>(sniperammomag3_addr, sniperammomag3);
			client_mem.Read<bool>(sniperammomag4_addr, sniperammomag4);
			
			client_mem.Read<bool>(energyammomag2_addr, energyammomag2);
			client_mem.Read<bool>(energyammomag3_addr, energyammomag3);
			client_mem.Read<bool>(energyammomag4_addr, energyammomag4);
			
			client_mem.Read<bool>(lightammomag2_addr, lightammomag2);
			client_mem.Read<bool>(lightammomag3_addr, lightammomag3);
			client_mem.Read<bool>(lightammomag4_addr, lightammomag4);
			
			client_mem.Read<bool>(heavyammomag2_addr, heavyammomag2);
			client_mem.Read<bool>(heavyammomag3_addr, heavyammomag3);
			client_mem.Read<bool>(heavyammomag4_addr, heavyammomag4);
			
			client_mem.Read<bool>(lasersight2_addr, lasersight2);
			client_mem.Read<bool>(lasersight3_addr, lasersight3);
			client_mem.Read<bool>(lasersight4_addr, lasersight4);
			
			client_mem.Read<bool>(stocksniper2_addr, stocksniper2);
			client_mem.Read<bool>(stockregular2_addr, stockregular2);
			
			client_mem.Read<bool>(stocksniper3_addr, stocksniper3);
			client_mem.Read<bool>(stockregular3_addr, stockregular3);
		
			client_mem.Read<bool>(suppressor2_addr, suppressor2);
			client_mem.Read<bool>(suppressor3_addr, suppressor3);
			
			client_mem.Read<bool>(skull_piecer_addr, skull_piecer);
			client_mem.Read<bool>(hammer_point_addr, hammer_point);
			client_mem.Read<bool>(disruptor_rounds_addr, disruptor_rounds);
			client_mem.Read<bool>(boosted_loader_addr, boosted_loader);
			client_mem.Read<bool>(insidevaluegoggle_addr, insidevaluegoggle);
			client_mem.Read<unsigned char>(outlinesize_addr, outlinesize);
			client_mem.Read<bool>(goldbackpack_addr, goldbackpack);
			client_mem.Write<float>(m_traversalProgress_addr, m_traversalProgress);
			client_mem.Read<bool>(SuperKey_addr, SuperKey);
			
			client_mem.Write<float>(LocalYAW_addr, LocalYAW);
			client_mem.Write<float>(TargetYAW_addr, TargetYAW);
			
			client_mem.Write<int>(TARGET_TEAMID_addr, TARGET_TEAMID);
			client_mem.Write<int>(TEAM_TEAMID_addr, TEAM_TEAMID);
			
			client_mem.Read<bool>(TriggerBot_addr, TriggerBot);
			
			client_mem.Read<bool>(tapstrafeenable_addr, tapstrafeenable);
			
			client_mem.Read<int>(lstarvalueid_addr, lstarvalueid);
			
			client_mem.Read<bool>(PrintMapCords_addr, PrintMapCords);
			client_mem.Read<float>(veltest_addr, veltest);
			client_mem.Write<float>(CurrentWeaponADSZoom_addr, CurrentWeaponADSZoom);
			client_mem.Write<int>(map_addr, map);
			
			client_mem.Read<bool>(TogglePrediction_addr, TogglePrediction);
			
			client_mem.Read<bool>(AutoFire_addr, AutoFire);
			
			client_mem.Read<bool>(PrintModelAndId_addr, PrintModelAndId);
			client_mem.Read<int>(ScreenResINT_addr, ScreenResINT);
			client_mem.Read<bool>(BoxEnable_addr, BoxEnable);
			client_mem.Write<int>(NoNadeAim_addr, NoNadeAim);
			client_mem.Read<bool>(PrintHeldID_addr, PrintHeldID);
			client_mem.Read<bool>(HeadShotMode_addr, HeadShotMode);
			client_mem.Read<int>(selectedFPSIndex_addr, selectedFPSIndex);
			client_mem.Read<bool>(Mobi_addr, Mobi);
			client_mem.Read<bool>(HeadShield_addr, HeadShield);
			client_mem.Read<bool>(JumpTower_addr, JumpTower);
			client_mem.Read<bool>(Traps_addr, Traps);
			
			client_mem.Write<int>(TargetIndex_addr, TargetIndex); //write index to client
			client_mem.Read<int>(TargetIndexLock_addr, TargetIndexLock); //read lock state from client
			
			client_mem.Read<bool>(AimSnapToggle_addr, AimSnapToggle);
			client_mem.Read<bool>(ItemESPClient_addr, ItemESPClient);
			client_mem.Read<bool>(ItemESPClientALL_addr, ItemESPClientALL);
			
			client_mem.Read<bool>(KeyCard_addr, KeyCard);
			
			client_mem.Read<bool>(gunshield_addr, gunshield);
			
			//lootfilledtoggle
			client_mem.Read<bool>(lootinsidevaluegoggle_addr, lootinsidevaluegoggle);

			//auto grapple 
			client_mem.Read<bool>(AutoGrappleToggle_addr, AutoGrappleToggle);
			
			client_mem.Write<bool>(LPDead_addr, LPDead);
			
			client_mem.Read<bool>(GetRanks_addr, GetRanks);
			
			
			client_mem.Read<bool>(InputSystem_addr, InputSystem);	
			if (InputSystem)
			{

				//printf("Test for write mem\n");


				client_mem.Write<bool>(minimapradar_addr, minimapradar);
				client_mem.Write<bool>(mainradarmap_addr, mainradarmap);
			}
			
			//fov circle testing
			//client_mem.Write<float>(ZoomFOVCircle_addr, ZoomFOVCircle);
			//client_mem.Write<int>(WeaponHeldID_addr, WeaponHeldID);
			//client_mem.Write<float>(targetZoomFOV_addr, targetZoomFOV);
			//client_mem.Write<float>(CurrentZoomFOV_addr, CurrentZoomFOV);
			
			if(esp && next2)
			{
				if (ItemESPClient)
				{
					client_mem.WriteArray<item>(item_addr, items.data(), ItemtoRead);
					client_mem.Write<Matrix>(Matrixm_addr, m);
				}
				if(valid)
				//client_mem.Write<Matrix>(Matrixm_addr, m);
				//client_mem.WriteArray<player>(player_addr, players, toRead);
				//client_mem.WriteArray<item>(item_addr, items, ItemtoRead);
				client_mem.WriteArray<player>(player_addr, players.data(), toRead);
				client_mem.Write<bool>(valid_addr, valid);
				client_mem.Write<bool>(next2_addr, true); //next2

				bool next2_val = false;
				do
				{
					client_mem.Read<bool>(next2_addr, next2_val);
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				} while (next2_val && g_Base!=0 && c_Base!=0);
				
				next2 = false;
			}
		}
	}
	vars_t = false;
}


//Item numbers for easy change
enum ItemType {
    HeavyAmmo,//mdl/weapons_r5/loot/_master/w_loot_wep_ammo_hc.rmdl
    Flatline,//mdl/techart/mshop/weapons/class/assault/flatline/flatline_base_w.rmdl
    Hemlock,//mdl/weapons/m1a1_hemlok/w_hemlok.rmdl
    Prowler,//mdl/techart/mshop/weapons/class/smg/prowler/prowler_base_w.rmdl
    Repeater_3030,//mdl/weapons/3030repeater/w_3030repeater.rmdl
    Rampage,//mdl/techart/mshop/weapons/class/lmg/dragon/dragon_base_w.rmdl
    Car_SMG,//mdl/techart/mshop/weapons/class/smg/car/car_base_w.rmdl
	MedBackpack,//mdl/humans_r5/loot/w_loot_char_backpack_medium.rmdl
    ShieldUpgradeHead2,//mdl/weapons_r5/loot/_master/w_loot_cha_shield_upgrade_head.rmdl
    Accelerant,//mdl/weapons_r5/loot/w_loot_wep_iso_ultimate_accelerant.rmdl
    ShieldBattSmall,//mdl/weapons_r5/loot/w_loot_wep_iso_shield_battery_small.rmdl
    ShieldBattLarge,//mdl/weapons_r5/loot/w_loot_wep_iso_shield_battery_large.rmdl
    SniperAmmo,//mdl/weapons_r5/loot/_master/w_loot_wep_ammo_sniper.rmdl
    LaserSight2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_lasersight_v1.rmdl
    SniperAmmoMag2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_sniper_v1.rmdl
    EnergyAmmoMag2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_energy_v1.rmdl
    StockSniper2,//mdl/weapons_r5/loot/w_loot_wep_iso_stock_folded_sniper.rmdl
    StockRegular2,//mdl/weapons_r5/loot/w_loot_wep_iso_stock_folded_regular.rmdl
    ShieldDown2,//mdl/weapons_r5/loot/w_loot_wep_iso_shield_down_v1.rmdl
    LightAmmoMag2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_v1b.rmdl
    HeavyAmmoMag2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_v2b.rmdl
    Optic2xHCOG,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_optic_cq_hcog_r2.rmdl
    OpticHolo1x2x,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_optic_cq_holo_var_2x.rmdl
    OpticSniper6x,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_optic_sni_dcom.rmdl
    Suppressor2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_suppr_v2b.rmdl
    ShotgunBolt2,//mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_v3b.rmdl
    GrenadeArcStar,//mdl/weapons_r5/loot/w_loot_wep_iso_shuriken.rmdl ? red still
    WeaponLongbow,//mdl/weapons/rspn101_dmr/w_rspn101_dmr.rmdl
    WeaponChargeRifle,//mdl/weapons/defender/w_defender.rmdl
    WeaponWingman,//mdl/weapons/b3wing/w_b3wing.rmdl
    WeaponSentinel,//mdl/Weapons/sentinel/w_sentinel.rmdl
	ShotgunAmmo,
    GrenadeFrag,
    GrenadeThermite,
    WeaponKraber,
    WeaponMastiff,
    WeaponEva8,
    WeaponPeacekeeper,
    WeaponMozambique,
    WeaponBow,
	LightBackpack,
    ShieldUpgradeHead1,
    HealthLarge,
    HealthSmall,
    Optic1xHcog,
    LaserSight1,
    SniperAmmoMag1,
    EnergyAmmoMag1,
    StockSniper1,
    StockRegular1,
    ShieldDown1,
    LightAmmoMag1,
    HeavyAmmoMag1,
    OpticHolo1x,
    Suppressor1,
    ShotgunBolt1,
	HeavyBackpack,
    ShieldUpgradeHead3,
    Phoenix,
    SniperAmmoMag3,
    LaserSight3,
    EnergyAmmoMag3,
    StockSniper3,
    StockRegular3,
    ShieldDown3,
    LightAmmoMag3,
    HeavyAmmoMag3,
    Optic3xHcog,
    Optic2x4x,
    OpticSniper4x8x,
    Suppressor3,
    ShotgunBolt3,
	GoldBackpack,
    ShieldUpgradeHead4,
    SniperAmmoMag4,
    EnergyAmmoMag4,
    ShieldDown4,
    LightAmmoMag4,
    HeavyAmmoMag4,
    OpticThreat,
    OpticSniperThreat,
    TurboCharger,
    SkullPiecer,
    HammerPoint,
    DisruptorRounds,
    BoostedLoader,
    ShotgunBolt4,
    GunShield,
	LightAmmo,
    G7_Scout,
    Alternator,
    R99,
    Spitfire,
    R301,
    P2020,
    RE45,
	EnergyAmmo,
    LStar,
    Nemesis,
    Havoc,
    Devotion,
    TripleTake,
    Volt,
    // Add more item types here as needed
};

std::map<ItemType, uint64_t> ItemIDMap = {
	//Light Ammo
	{LightAmmo, 144},
	//Heavy Ammo
    {HeavyAmmo, 147},
	//Energy Ammo
	{EnergyAmmo, 145},
	//Shotgun Ammo
	{ShotgunAmmo, 146},
	//Sniper Ammo
	{SniperAmmo, 148},
	//Light Ammo Mags
	{LightAmmoMag1, 248},
	{LightAmmoMag2, 249},
	{LightAmmoMag3, 250},
	{LightAmmoMag4, 251},
	//Heavy Ammo Mags
	{HeavyAmmoMag1, 252},
	{HeavyAmmoMag2, 253},
	{HeavyAmmoMag3, 254},
	{HeavyAmmoMag4, 255},
	//Energy Ammo Mags
	{EnergyAmmoMag1, 256},
	{EnergyAmmoMag2, 257},
	{EnergyAmmoMag3, 258},
	{EnergyAmmoMag4, 259},
	//Shotgun Ammo Mags
	{ShotgunBolt1, 264},
	{ShotgunBolt2, 265},
	{ShotgunBolt3, 266},
	{ShotgunBolt4, 267},
	//Sniper Ammo Mags
    {SniperAmmoMag1, 260},
	{SniperAmmoMag2, 261},
    {SniperAmmoMag3, 262},
    {SniperAmmoMag4, 263},
	//Heavy Weapons
    {Flatline, 29},
    {Hemlock, 34},
    {Prowler, 55},
    {Repeater_3030, 133},
    {Rampage, 150},
    {Car_SMG, 155},
	//Light Weapons
    {G7_Scout, 39},
    {Alternator, 44},
    {R99, 49},
    {Spitfire, 75},
    {R301, 80},
    {P2020, 113},
    {RE45, 122},
	//Energy Weapons
    {LStar, 7},
    {Nemesis, 139},
    {Havoc, 13},
    {Devotion, 19},
    {TripleTake, 24},
    {Volt, 60},
	//Shotgun Weapons
	{WeaponMastiff, 2},
    {WeaponEva8, 85},
    {WeaponPeacekeeper, 90},
    {WeaponMozambique, 95},
	//Sniper Weapons
	{WeaponLongbow, 65},
    {WeaponChargeRifle, 70},
    {WeaponWingman, 108},
    {WeaponSentinel, 127},
	//Red Weapons
    {WeaponBow, 132},
	{WeaponKraber, 1},
	//Gernades
	{GrenadeArcStar, 230},
    {GrenadeFrag, 229},
    {GrenadeThermite, 228},
	//Heath Healing Items
	{HealthLarge, 195},
    {HealthSmall, 196},
	//Shield Healing Items
	{ShieldBattSmall, 198},
    {ShieldBattLarge, 197},
	{Phoenix, 194},
	//Backpacks
	{LightBackpack, 223},
	{MedBackpack, 224},
	{HeavyBackpack, 225},
	{GoldBackpack, 226},
	//Helm Upgrades
	{ShieldUpgradeHead1, 199},
	{ShieldUpgradeHead2, 200},
	{ShieldUpgradeHead3, 201},
	{ShieldUpgradeHead4, 202},
	//Knockdown Upgrades
	{ShieldDown1, 219},
	{ShieldDown2, 220},
	{ShieldDown3, 221},
    {ShieldDown4, 222},
	//Survival Slot
    {Accelerant, 193},
    //Attachments Laser Sights
	{LaserSight1, 245},
    {LaserSight2, 246},
	{LaserSight3, 247},
	//Attachments Suppressors
	{Suppressor1, 241},
	{Suppressor2, 242},
	{Suppressor3, 243},
	//Regular Stocks
	{StockRegular1, 268},
	{StockRegular2, 269},
	{StockRegular3, 270},
	//Sniper Stocks
	{StockSniper1, 271},
	{StockSniper2, 272},
	{StockSniper3, 273},
	//Regular Scopes
	{OpticHolo1x, 233},
    {Optic2xHCOG, 232},
    {OpticHolo1x2x, 234},
	{Optic1xHcog, 231},
	{Optic3xHcog, 236},
    {Optic2x4x, 237},
	//{OpticThreat, 232}, gone from the game?
	//Sniper Scopes
	{OpticSniper6x, 238},
	{OpticSniper4x8x, 239},
	{OpticSniperThreat, 240},
	//Gun Attachments
	{TurboCharger, 54354354343}, //Fix me when they are on the floor again
    {SkullPiecer, 54354354343}, //Fix me when they are on the floor again
    {HammerPoint, 280},
    {DisruptorRounds, 534534543543}, //Fix me when they are on the floor again
    {BoostedLoader, 288},
	{GunShield, 289},
	
   
   
    
    
	
    // Add more mappings here as needed
};


bool updatedItems[ItemtoRead] = {false}; // Array to keep track of updated items

void ApplyGlow(uint64_t entity, float r, float g, float b, int glowId, unsigned char OutlineFunction) {
    std::array<unsigned char, 4> highlightFunctionBits = {
        lootfilled,   // InsideFunction  HIGHLIGHT_FILL_LOOT_SCANNED
        OutlineFunction,          // OutlineFunction HIGHLIGHT_OUTLINE_LOOT_SCANNED
        64,           // OutlineRadius: size * 255 / 8
        64            // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7)
    };
    std::array<float, 3> highlightParameter = { r, g, b };
    apex_mem.Write<int>(entity + OFFSET_GLOW_THROUGH_WALLS, 2);
    apex_mem.Write<int>(entity + OFFSET_GLOW_ENABLE, glowId);
    long highlightSettingsPtr;
    apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
    apex_mem.Write(highlightSettingsPtr + HIGHLIGHT_TYPE_SIZE * glowId + 0x0, highlightFunctionBits);
    apex_mem.Write(highlightSettingsPtr + HIGHLIGHT_TYPE_SIZE * glowId + 0x4, highlightParameter);
	uint8_t InsideHighlightID;
	apex_mem.Read<uint8_t>(entity + 0x24C, InsideHighlightID);
	apex_mem.Write<uint8_t>(entity + 0x248, InsideHighlightID);
}


bool itemprevious_firing_range = false; // Previous state of firing_range
int itemprevious_map = 0;

static void item_glow_t()
{
	auto lastCullTime = std::chrono::high_resolution_clock::now();
	//Timer for loop
	/*
	double totalElapsedTime = 0.0;
    int iterationCount = 0;
    auto startTime = std::chrono::steady_clock::now();
	*/
	
	item_t = true;
	while (item_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_Base!=0 && c_Base!=0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
			//memset(items, 0, sizeof(items));
			if (item_glow)
			{
				if (firing_range != itemprevious_firing_range)
				{
					// State has changed, so reset items array
					//std::cout << "Firing range state changed. Clearing items array." << std::endl;
					//memset(items, 0, sizeof(items));
					items.clear();  // Remove all elements
					items.resize(ItemtoRead);  // Refill the vector to the original size with default-initialized objects
					//printf("firing_range = %s\n", firing_range ? "true" : "false");
					// Update the previous state
					itemprevious_firing_range = firing_range;
				}
				
				//map change
				if (map != itemprevious_map)
				{
					// State has changed, so reset items array
					//std::cout << "Map state changed. Clearing items array." << std::endl;
					//memset(items, 0, sizeof(items));
					items.clear();  // Remove all elements
					items.resize(ItemtoRead);  // Refill the vector to the original size with default-initialized objects

					// Update the previous state
					itemprevious_map = map;
				}
				if (map >= 1 && map <= 7)
				{
					
					/*
					// Update the current time inside the loop
					auto currentTime = std::chrono::high_resolution_clock::now();
					// Check if 2 seconds have passed since the last cull
					std::chrono::duration<float> cullElapsedTime = currentTime - lastCullTime;

					if (cullElapsedTime.count() >= 10.0f) 
					{
						memset(items, 0, sizeof(items));
						lastCullTime = currentTime;
					}
					*/
					
					uint64_t LocalPlayer = 0;
					apex_mem.Read<uint64_t>(g_Base + OFFSET_LOCAL_ENT, LocalPlayer);
					Entity LPlayer = getEntity(LocalPlayer);
					for (int i = 0; i < ItemtoRead; i++)
					{
						//if (map == 0)
						//{
							//continue;
						//}
						//items[i] = {};
						
						
						if (LocalPlayer == 0)
						{
							continue;
						}
						//item esp names on screen
						
						
						Vector LocalPlayerPosition = LPlayer.getPosition();
						
						uint64_t centity = 0;
						apex_mem.Read<uint64_t>(entitylist + ((uint64_t) i * 32 ), centity);
						if (centity == 0)
						{
							continue;
						}
						if (LocalPlayer == centity)
						{
							continue;
						}
						Item item = getItem(centity);
						
						//item esp names on screen
						//Item filter glow name setup and search.
						char glowName[200] = { 0 };
						uint64_t name_ptr;
						apex_mem.Read<uint64_t>(centity + OFFSET_MODELNAME, name_ptr);
						apex_mem.ReadArray<char>(name_ptr, glowName, 200);
						
						//item ids?
						uint64_t ItemID;
						apex_mem.Read<uint64_t>(centity + OFFSET_ITEM_ID, ItemID);
						Vector EntityPosition = item.getPosition(); // get item Position... if you can't read that is.
						float dist = LocalPlayerPosition.DistTo(EntityPosition); // dist to item Position from local Position.
						if (dist > 6000)
						{	
							continue;
						}
						if (BoxEnable)
						{
							if (item.isBox())
							{
								int RedEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, RedEnable);
								if (RedEnable != 73)
								{
									ApplyGlow(centity, 1.0f, 0.0f, 0.0f, 73, 125);  // Red glow
								}
								//valid = true;
								continue;
							}
						}
						//RED GLOW  is 1 0 0  89
						if (Traps && strstr(glowName, "mdl/props/wattson_trophy_system/wattson_trophy_system.rmdl") || 
						Traps && strstr(glowName, "mdl/props/conduit/conduit_shield_jammer.rmdl") ||
						Traps && strstr(glowName, "mdl/fx/loba_staff_holo_stand.rmdl") ||
						Traps && strstr(glowName, "mdl/fx/ferrofluid_tac_calm_side_R.rmdl") ||
						Traps && strstr(glowName, "mdl/fx/ferrofluid_tac_calm_side_L.rmdl") ||
						Traps && strstr(glowName, "mdl/props/caustic_gas_tank/caustic_gas_tank.rmdl") ||
						Traps && strstr(glowName, "mdl/props/wattson_electric_fence/wattson_electric_fence.rmdl") ||
						Traps && strstr(glowName, "mdl/props/rampart_cover_wall/rampart_cover_wall.rmdl") ||
						CryptoDrone && strstr(glowName, "mdl/props/crypto_drone/crypto_drone.rmdl") ||  //crypto drone
						(shotgunammo && ItemID == ItemIDMap[ShotgunAmmo]) ||
						(grenade_frag && ItemID == ItemIDMap[GrenadeFrag]) ||
						(grenade_thermite && ItemID == ItemIDMap[GrenadeThermite]) ||
						(weapon_kraber && ItemID == ItemIDMap[WeaponKraber]) ||
						(weapon_mastiff && ItemID == ItemIDMap[WeaponMastiff]) ||
						(weapon_eva8 && ItemID == ItemIDMap[WeaponEva8]) ||
						(weapon_peacekeeper && ItemID == ItemIDMap[WeaponPeacekeeper]) ||
						(weapon_mozambique && ItemID == ItemIDMap[WeaponMozambique]) ||
						(weapon_bow && ItemID == ItemIDMap[WeaponBow]))
						{
							updatedItems[i] = true;
							if(ItemESPClient)
							{
								
								
								items[i] = 
								{
								dist,
								EntityPosition,
								ItemID
								};
								std::strcpy(items[i].name, glowName);
								//items[i].ItemID = ItemID;
							}
							int RedEnable;
							apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, RedEnable);
							if (RedEnable != 73)
							{
								ApplyGlow(centity, 1.0f, 0.0f, 0.0f, 73, 125);  // Red glow
							}
							//valid = true;
							continue;
						}
						
						if (item.isItem())
						{
							//uint64_t ItemID2;
							//ItemID2 = ItemID % 301;
							//printf("%ld\n", ItemID); 
							if (PrintModelAndId)
							{
								printf("Model Name: %s, Item ID: %lu\n", glowName, ItemID);
							}
							
							//uint64_t wephandle = 0;
							//apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, wephandle);
							
							//wephandle &= 0xffff;

							//uint64_t wep_entity = 0;
							//apex_mem.Read<uint64_t>(entitylist + (wephandle << 5), wep_entity);
							//float projectile_speed;
							//apex_mem.Read<float>(wep_entity + OFFSET_BULLET_SPEED, projectile_speed);
							//float projectile_scale;
							//apex_mem.Read<float>(wep_entity + OFFSET_BULLET_SCALE, projectile_scale);
							//int ammo;
							//apex_mem.Read<int>(wep_entity + OFFSET_AMMO, ammo);
							//float zoom_fov;
							//apex_mem.Read<float>(wep_entity + OFFSET_ZOOM_FOV, zoom_fov);
							//printf("Weapon ID: %ld - Bullet Speed: %f - Bullet Gravity: %f - Zoom FOV: %f - Ammo: %d - Speed: %f - Scale: %f\n", wep_entity, bulletspeed, bulletgrav, zoom_fov, ammo, projectile_speed, projectile_scale);	
							
							
							
							
							
							//debug
							/*
							if (Mobi && strstr(glowName, "mdl/Weapons/beacon_capsule_01/beacon_capsule_01.rmdl"))
							{
								printf("Model Name: %s, Item ID: %lu, Position: (%f, %f, %f), Distance: %f\n", glowName, ItemID, EntityPosition.x, EntityPosition.y, EntityPosition.z, dist);

							}
							*/

							
						
								
							//Level name printf
							//char LevelNAME[200] = { 0 };
							//uint64_t levelname_ptr;
							//apex_mem.Read<uint64_t>(g_Base + OFFSET_LEVELNAME, levelname_ptr);
							//apex_mem.ReadArray<char>(levelname_ptr, LevelNAME, 200);
							//printf("%s\n", LevelNAME);
							//if(ItemID == 142)
							//{
							//printf("Shotgun Ammo dist: %f\n", dist);
							//}
						
							//Prints stuff you want to console
							//if (strstr(glowName, "mdl/")) 
							//{
							//printf("%ld\n", ItemID);
							//}
							//Search model name and if true sets glow, must be a better way to do this.. if only i got the item id to work..
							//BOX
							
							if(ItemESPClientALL)
							{
								updatedItems[i] = true;
								items[i] = {
									dist,
									EntityPosition,
									ItemID									
								};
								std::strcpy(items[i].name, glowName);
								items[i].ItemID = ItemID;
								//valid = true;
								
								//if(boxMiddle)
								//printf("ItemID: %ld\n", items[i].ItemID);
								//printf("Name: %s\n", items[i].name);
								//printf("dist: %f, boxMiddle: %f, h_y: %f, width: %f, height: %f, b_x: %f, b_y: %f, Item ID:ItemID: %ld\n", items[i].dist, items[i].boxMiddle, items[i].h_y, items[i].width, items[i].height, items[i].b_x, items[i].b_y, items[i].ItemID);
								//printf("boxMiddle: %f, Tripple Take\n", items[i].boxMiddle);
								//printf("Distance: %f, BoxMiddle: %f, Tripple Take\n", items[i].dist, items[i].boxMiddle);
								continue;	
							}

							
							
							//GREEN GLOW  is 0 1 0   91  
							if (strstr(glowName, "mdl/props/nessie/nessie_april_fools.rmdl") ||
							strstr(glowName, "mdl/props/octane_jump_pad/octane_jump_pad.rmdl") ||
							strstr(glowName, "mdl/props/nessie/nessie_april_fools_large.rmdl")) 
							{
								int GreenEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, GreenEnable);
								if (GreenEnable != 76)
								{
									ApplyGlow(centity, 0.0f, 1.0f, 0.0f, 76, 125);  // Green glow
								}
								//valid = true;
								continue;
							}
							//PINK GLOW
							if (Mobi && strstr(glowName, "mdl/Weapons/beacon_capsule_01/beacon_capsule_01.rmdl") ||
							JumpTower && strstr(glowName, "mdl/props/evac_tower_loot/evac_tower_loot.rmdl") ||
							HeadShield && strstr(glowName, "mdl/props/void_ring/loot_void_ring.rmdl") ||
							KeyCard && strstr(glowName, "mdl/weapons_r5/loot/_master/w_loot_msc_keycard_v1.rmdl")) 
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
									//printf("Item %d: dist=%f, boxMiddle=%f, h_y=%f, width=%f, height=%f, b_x=%f, b_y=%f, ItemID=%llu, name=%s\n",
									//i, items[i].dist, items[i].boxMiddle, items[i].h_y, items[i].width,
									//items[i].height, items[i].b_x, items[i].b_y, items[i].ItemID, items[i].name);
									//printf("EntityPosition: x=%f, y=%f, z=%f\n", EntityPosition.x, EntityPosition.y, EntityPosition.z);
								}
								int PinkEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, PinkEnable);
								if (PinkEnable != 77)
								{
									ApplyGlow(centity, 1, 0, 1, 77, 119);  // PINK glow
								}
								//valid = true;
								continue;
							}
							//BLUE GLOW  is 0 0 1  90
							if ((medbackpack && ItemID == ItemIDMap[MedBackpack]) ||
							(shieldupgradehead2 && ItemID == ItemIDMap[ShieldUpgradeHead2]) ||
							(accelerant && ItemID == ItemIDMap[Accelerant]) ||
							(shieldbattsmall && ItemID == ItemIDMap[ShieldBattSmall]) ||
							(shieldbattlarge && ItemID == ItemIDMap[ShieldBattLarge]) ||
							(sniperammo && ItemID == ItemIDMap[SniperAmmo]) ||
							(lasersight2 && ItemID == ItemIDMap[LaserSight2]) ||
							(sniperammomag2 && ItemID == ItemIDMap[SniperAmmoMag2]) ||
							(energyammomag2 && ItemID == ItemIDMap[EnergyAmmoMag2]) ||
							(stocksniper2 && ItemID == ItemIDMap[StockSniper2]) ||
							(stockregular2 && ItemID == ItemIDMap[StockRegular2]) ||
							(shielddown2 && ItemID == ItemIDMap[ShieldDown2]) ||
							(lightammomag2 && ItemID == ItemIDMap[LightAmmoMag2]) ||
							(heavyammomag2 && ItemID == ItemIDMap[HeavyAmmoMag2]) ||
							(optic2xhcog && ItemID == ItemIDMap[Optic2xHCOG]) ||
							(opticholo1x2x && ItemID == ItemIDMap[OpticHolo1x2x]) ||
							(opticsniper6x && ItemID == ItemIDMap[OpticSniper6x]) ||
							(suppressor2 && ItemID == ItemIDMap[Suppressor2]) ||
							(shotgunbolt2 && ItemID == ItemIDMap[ShotgunBolt2]) ||
							(grenade_arc_star && ItemID == ItemIDMap[GrenadeArcStar]) ||
							(weapon_longbow && ItemID == ItemIDMap[WeaponLongbow]) ||
							(weapon_charge_rifle && ItemID == ItemIDMap[WeaponChargeRifle]) ||
							(weapon_wingman && ItemID == ItemIDMap[WeaponWingman]) ||
							(weapon_sentinel && ItemID == ItemIDMap[WeaponSentinel]))
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int BlueEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, BlueEnable);
								if (BlueEnable != 74)
								{
									ApplyGlow(centity, 0, 0, 1, 74, 125);  // Blue glow
								}
								//valid = true;
								continue;
							}
							//WHITE GLOW  is 1 1 1  72
							if ((lightbackpack && ItemID == ItemIDMap[LightBackpack]) ||
							(shieldupgradehead1 && ItemID == ItemIDMap[ShieldUpgradeHead1]) ||
							(healthlarge && ItemID == ItemIDMap[HealthLarge]) ||
							(healthsmall && ItemID == ItemIDMap[HealthSmall]) ||
							(optic1xhcog && ItemID == ItemIDMap[Optic1xHcog]) ||
							(lasersight1 && ItemID == ItemIDMap[LaserSight1]) ||
							(sniperammomag1 && ItemID == ItemIDMap[SniperAmmoMag1]) ||
							(energyammomag1 && ItemID == ItemIDMap[EnergyAmmoMag1]) ||
							(stocksniper1 && ItemID == ItemIDMap[StockSniper1]) ||
							(stockregular1 && ItemID == ItemIDMap[StockRegular1]) ||
							(shielddown1 && ItemID == ItemIDMap[ShieldDown1]) ||
							(lightammomag1 && ItemID == ItemIDMap[LightAmmoMag1]) ||
							(heavyammomag1 && ItemID == ItemIDMap[HeavyAmmoMag1]) ||
							(opticholo1x && ItemID == ItemIDMap[OpticHolo1x]) ||
							(suppressor1 && ItemID == ItemIDMap[Suppressor1]) ||
							(shotgunbolt1 && ItemID == ItemIDMap[ShotgunBolt1]))  //mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_v3b.rmdl
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int WhiteEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, WhiteEnable);
								if (WhiteEnable != 4)
								{
									ApplyGlow(centity, 1, 1, 1, 4, 125);  // White glow
								}
								//valid = true;
								continue;
							}
							//PURPLE GLOW   is 0.2941, 0, 0.5098   74
							if ((heavybackpack && ItemID == ItemIDMap[HeavyBackpack]) ||
							(shieldupgradehead3 && ItemID == ItemIDMap[ShieldUpgradeHead3]) ||
							(phoenix && ItemID == ItemIDMap[Phoenix]) ||
							(sniperammomag3 && ItemID == ItemIDMap[SniperAmmoMag3]) ||
							(lasersight3 && ItemID == ItemIDMap[LaserSight3]) ||
							(energyammomag3 && ItemID == ItemIDMap[EnergyAmmoMag3]) ||
							(stocksniper3 && ItemID == ItemIDMap[StockSniper3]) ||
							(stockregular3 && ItemID == ItemIDMap[StockRegular3]) ||
							(shielddown3 && ItemID == ItemIDMap[ShieldDown3]) ||
							(lightammomag3 && ItemID == ItemIDMap[LightAmmoMag3]) ||
							(heavyammomag3 && ItemID == ItemIDMap[HeavyAmmoMag3]) ||
							(optic3xhcog && ItemID == ItemIDMap[Optic3xHcog]) ||
							(optic2x4x && ItemID == ItemIDMap[Optic2x4x]) ||
							(opticsniper4x8x && ItemID == ItemIDMap[OpticSniper4x8x]) ||
							(suppressor3 && ItemID == ItemIDMap[Suppressor3]) ||
							(shotgunbolt3 && ItemID == ItemIDMap[ShotgunBolt3]))  //mdl/weapons_r5/loot/_master/w_loot_wep_mods_mag_v3b.rmdl
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int PurpleEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, PurpleEnable);
								if (PurpleEnable != 5)
								{
									ApplyGlow(centity, 0.2941, 0, 0.5098, 5, 125);  // Purple glow
								}
								//valid = true;
								continue;
							}
							//GOLD GLOW  is 1, 0.8431, 0  75
							//new hopup gun shieldgen 295
							if ((goldbackpack && ItemID == ItemIDMap[GoldBackpack]) ||
							(shieldupgradehead4 && ItemID == ItemIDMap[ShieldUpgradeHead4]) ||
							(sniperammomag4 && ItemID == ItemIDMap[SniperAmmoMag4]) ||
							(energyammomag4 && ItemID == ItemIDMap[EnergyAmmoMag4]) ||
							(shielddown4 && ItemID == ItemIDMap[ShieldDown4]) ||
							(lightammomag4 && ItemID == ItemIDMap[LightAmmoMag4]) ||
							(heavyammomag4 && ItemID == ItemIDMap[HeavyAmmoMag4]) ||
							//gone from the game? (opticthreat && ItemID == ItemIDMap[OpticThreat]) ||
							(opticsniperthreat && ItemID == ItemIDMap[OpticSniperThreat]) ||
							(turbo_charger && ItemID == ItemIDMap[TurboCharger]) ||
							(skull_piecer && ItemID == ItemIDMap[SkullPiecer]) ||
							(hammer_point && ItemID == ItemIDMap[HammerPoint]) ||
							(disruptor_rounds && ItemID == ItemIDMap[DisruptorRounds]) ||
							(boosted_loader && ItemID == ItemIDMap[BoostedLoader]) ||
							(shotgunbolt4 && ItemID == ItemIDMap[ShotgunBolt4]) ||
							(gunshield && ItemID == ItemIDMap[GunShield])) //mdl/weapons_r5/loot/_master/w_loot_wep_mods_chip.rmdl
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int GoldEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, GoldEnable);
								if (GoldEnable != 6)
								{
									ApplyGlow(centity, 1, 0.8431, 0, 6, 125);  // Gold glow
								}
								//valid = true;
								continue;
							}
							//TEAL GLOW  is 0 1 1   65
							if ((heavyammo && ItemID == ItemIDMap[HeavyAmmo]) || //mdl/weapons_r5/loot/_master/w_loot_wep_ammo_hc.rmdl
							(weapon_flatline  && ItemID == ItemIDMap[Flatline]) || //mdl/techart/mshop/weapons/class/assault/flatline/flatline_base_w.rmdl
							(weapon_hemlock && ItemID == ItemIDMap[Hemlock]) || //mdl/weapons/m1a1_hemlok/w_hemlok.rmdl
							(weapon_prowler && ItemID == ItemIDMap[Prowler]) || //mdl/techart/mshop/weapons/class/smg/prowler/prowler_base_w.rmdl
							(weapon_3030_repeater && ItemID == ItemIDMap[Repeater_3030]) || //mdl/weapons/3030repeater/w_3030repeater.rmdl
							(weapon_rampage && ItemID == ItemIDMap[Rampage]) || //mdl/techart/mshop/weapons/class/lmg/dragon/dragon_base_w.rmdl
							(weapon_car_smg && ItemID == ItemIDMap[Car_SMG])) //mdl/techart/mshop/weapons/class/smg/car/car_base_w.rmdl
							{
								
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int TealEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, TealEnable);
								if (TealEnable != 78)
								{
									ApplyGlow(centity, 0, 1, 1, 78, 125);  // Teal glow
								}
								//valid = true;
								continue;
							}
							//ORANGE GLOW   is  1, 0.5490, 0   66
							if ((lightammo && ItemID == ItemIDMap[LightAmmo]) ||
							(weapon_g7_scout && ItemID == ItemIDMap[G7_Scout]) ||
							(weapon_alternator && ItemID == ItemIDMap[Alternator]) ||
							(weapon_r99 && ItemID == ItemIDMap[R99]) ||
							(weapon_spitfire && ItemID == ItemIDMap[Spitfire]) ||
							(weapon_r301 && ItemID == ItemIDMap[R301]) ||
							(weapon_p2020 && ItemID == ItemIDMap[P2020]) ||
							(weapon_re45 && ItemID == ItemIDMap[RE45])) //mdl/weapons/p2011_auto/w_p2011_auto.rmdl
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int OrangeEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, OrangeEnable);
								if (OrangeEnable != 8)
								{
									ApplyGlow(centity, 0.5058, 0.2392, 0, 8, 125);  // Orange glow
								}
								//valid = true;
								continue;
							}
							//YELLOW GLOW  is 0.2, 1, 0   73
							
							if ((energyammo && ItemID == ItemIDMap[EnergyAmmo]) ||
							(weapon_lstar && ItemID == ItemIDMap[LStar]) ||
							(weapon_nemesis && ItemID == ItemIDMap[Nemesis]) ||
							(weapon_havoc && ItemID == ItemIDMap[Havoc]) ||
							(weapon_devotion && ItemID == ItemIDMap[Devotion]) ||
							(weapon_triple_take && ItemID == ItemIDMap[TripleTake]) ||
							(weapon_volt && ItemID == ItemIDMap[Volt])) //mdl/weapons/hemlok_smg/w_hemlok_smg.rmdl ?
							{
								updatedItems[i] = true;
								if(ItemESPClient)
								{
									
									
									items[i] = 
									{
									dist,
									EntityPosition,
									ItemID
									};
									std::strcpy(items[i].name, glowName);
									//items[i].ItemID = ItemID;
								}
								int YellowEnable;
								apex_mem.Read<int>(centity + OFFSET_GLOW_ENABLE, YellowEnable);
								if (YellowEnable != 10)
								{
									ApplyGlow(centity, 0.2, 1, 0, 10, 125);  // Yellow glow
								}		
								//valid = true;
								continue;
							}
						}
					}
						
					
					
					for (int i = 0; i < ItemtoRead; i++) 
					{
						if (!updatedItems[i]) 
						{
							memset(&items[i], 0, sizeof(item));
							//items.at(i) = item();
							//items[i] = item();
						} 
						else 
						{
							// Reset the updated status for the next iteration
							updatedItems[i] = false;
						}
					}
					//Change the 60 ms to lower to make the death boxes filker less.
					//std::this_thread::sleep_for(std::chrono::milliseconds(75));
				
					next2 = true;
					while(next2 && g_Base!=0 && c_Base!=0 && item_glow)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
				}
			}
		}
					
	}

	item_t = false;
}



float deltaTime;

int main(int argc, char *argv[])
{
	if(geteuid() != 0)
	{
		//run as root..
		printf("Error: %s is not running as root\n", argv[0]);
		return 0;
	}

	const char* cl_proc = "BeefGuyDoom.exe";
	const char* ap_proc = "r5apex.exe";
	//const char* ap_proc = "EasyAntiCheat_launcher.exe";

	//Client "add" offset
	uint64_t add_off = 0x95f60; //todo make this auto update..

	std::thread aimbot_thr;
	std::thread esp_thr;
	std::thread actions_thr;
	std::thread cactions_thr;
	//std::thread TriggerBotRun_thr; //triggerbot
	std::thread itemglow_thr;
	std::thread vars_thr;
	
	//auto prevTime = std::chrono::high_resolution_clock::now();
	
	while(active)
	{
		
		//auto currentTime = std::chrono::high_resolution_clock::now();
		//deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - prevTime).count() / 1000.0f;
		//prevTime = currentTime;
		if(apex_mem.get_proc_status() != process_status::FOUND_READY)
		{
			if(aim_t)
			{
				aim_t = false;
				esp_t = false;
				actions_t = false;
				cactions_t = false;
				//TriggerBotRun_t	= false; //triggerbot
				item_t = false;
				g_Base = 0;
				cactions_thr.~thread();
				//TriggerBotRun_thr.~thread(); //triggerbot
				aimbot_thr.~thread();
				esp_thr.~thread();
				actions_thr.~thread();
				itemglow_thr.~thread();
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
			printf("Searching for Apex process...\n");

			apex_mem.open_proc(ap_proc);

			if(apex_mem.get_proc_status() == process_status::FOUND_READY)
			{
				g_Base = apex_mem.get_proc_baseaddr();
				printf("\nApex process found\n");
				printf("Base: %lx\n", g_Base);

				aimbot_thr = std::thread(AimbotLoop);
				esp_thr = std::thread(EspLoop);
				actions_thr = std::thread(DoActions);
				cactions_thr = std::thread(ClientActions);
				//TriggerBotRun_thr = std::thread(TriggerBotRun); //triggerbot
				itemglow_thr = std::thread(item_glow_t);
				aimbot_thr.detach();
				esp_thr.detach();
				cactions_thr.detach();
				//TriggerBotRun_thr.detach(); //triggerbot
				actions_thr.detach();
				itemglow_thr.detach();
			}
		}
		else
		{
			apex_mem.check_proc();
		}

		if(client_mem.get_proc_status() != process_status::FOUND_READY)
		{
			if(vars_t)
			{
				vars_t = false;
				c_Base = 0;

				vars_thr.~thread();
			}
			
			std::this_thread::sleep_for(std::chrono::seconds(1));
			printf("Searching for BeefGuyDoom process...\n");

			client_mem.open_proc(cl_proc);

			if(client_mem.get_proc_status() == process_status::FOUND_READY)
			{
				c_Base = client_mem.get_proc_baseaddr();
				printf("BeefGuyDoom process found\n");
				printf("Base: %lx\n", c_Base);

				vars_thr = std::thread(set_vars, c_Base + add_off);
				vars_thr.detach();
			}
		}
		else
		{
			client_mem.check_proc();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return 0;
}