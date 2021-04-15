#pragma once
#include <cstdint>
#include "HardwareSerial.h"


enum class STPM_ERROR
{
	OK		= 0,
	Timeout	= 1,
	CRC		= 2,
	Invalid = 3
};


//
// Configuration settings for a current/voltage channel
//
struct STPM_Config_Channel
{
	bool enVref;	// Enable internal voltage reference for channel
	float vRef;		// Voltage reference (set to 1.18v if using internal reference)
	int TC;			// Temperature compensation coefficient (see Table 9 in Datasheet)

	bool enV;		// Enable voltage measurement on channel
	bool enC;		// Enable current measurement on channel
		
	int Ai;			// Gain for current ADC (Set to 16 for current shunt, 2 for Current CT and 16 for Rogowski coil)

	float R1;		// Potential divider resistors fitted (in Ohmns)
	float R2;

	bool Rogowski;	// Set to true if current sensor is a Rogowski coil otherwise set to false
	float ks;		// ks: Sensitivity of current measurement :
					//		- For a shunt it is the resistance of the shunt
					// 	    - For a CT coil it is the <burden resistance>/<Number of turns in the CT coil> (in V/A)
					// 	    - For a Rogowski coil it is the RoCoil (in V/A)

	bool aem;		// Apparent Energy mode:
					//		false - Use apparent RMS power
					//		true  - Use apparent vectorial power
	bool apm;		// Apparent vectorial power mode:
					//		false - Use funamental power
					//		true  - Use active power
	bool bhpfv;		// High pass filter bypass for voltage channel:
					//		false - HPF enabled (bypass disabled)
					//		true  - HPF disabled (bypass enabled)
	bool bhpfc;		// High pass filter bypass for current channel:
					//		false - HPF enabled (bypass disabled)
					//		true  - HPF disabled (bypass enabled)

	STPM_Config_Channel()
	{
		enVref = true;
		vRef = 1.18f;
		TC = 2;

		enV = true;
		enC = true;

		Ai = 16;
		R1 = 810000;
		R2 = 470;

		Rogowski = false;
		ks = 0.3f/1000.0f;

		aem = false;
		apm = false;
		bhpfv = false;
		bhpfc = false;
	}
};

// Sag/Swell configuration
struct STPM_SS_Config
{
	float sag_voltage;			// The target RMS voltage of the SAG threshold
	float swell_voltage;		// The target RMS voltage of the SWELL threshold
	float sag_time_threshold;	// How long (in milliseconds) that the SAG event needs to be before it is 
								// registered.  Note for a 50Hz mains signal this must be at least 10ms, so that the
								// normal sinusoidal wave is not registered as a SAG event.

	STPM_SS_Config()
	{
		sag_voltage = 0;
		swell_voltage = 0;
		sag_time_threshold = 0;
	}
};

struct STPM_Configuration
{
	STPM_Config_Channel primary_channel;
	STPM_Config_Channel secondary_channel;

	//	freq - Select 50 or 60Hz:
	//			false - 50Hz
	//			true  - 60Hz
	//
	bool freq;

	// Cumulative energy calculation:
	//			false - cumulative is the sum of channel energies
	//			true  - total is the difference of energies
	bool en_cum;

	// Tamper enable (true) or disable (false)
	bool tmp_en;

	// Tamper tolerance:
	//	0 - 12.5%
	// 	1 - 8.33%
	// 	2 - 6.25%
	// 	3 - 3.125%
	//		
	int	tmp_tol;

	STPM_Configuration()
	{
		freq = false;
		en_cum = false;
		tmp_tol = 0;
		tmp_en = false;
	}
};

class Stpm3x
{
private:
	HardwareSerial	serial;

	// These values have been taken from the datasheet
	const float calv = 0.875f;
	const float cali = 0.875f;
	const float kintrc = 0.8155773f;
	const float Vref = 1.18f;
	const float Dclk = 7812.5f;
	const int Av = 2;

	// These values are calculated in the configure() function
	float	primary_Vc;			// Primary Channel Voltage multiplier
	float	primary_Ic;			// Primary Channel Current multiplier
	float	primary_Pc;			// Primary Channel Power multiplier
	float	primary_Ec;			// Primary Channel Energy multipler
	float	secondary_Vc;		// Secondary Channel Voltage multiplier
	float	secondary_Ic;		// Secondary Channel Current multiplier
	float	secondary_Pc;		// Primary Channel Power multiplier
	float	secondary_Ec;		// Primary Channel Energy multipler


	void flush();

public:
	Stpm3x(int port);

	// Perform a S/W reset
	STPM_ERROR sw_reset();

	// Reset sag/swell on primary (true) or secondary (false) channels
	STPM_ERROR reset_ss(bool primary);

	//
	// Configure the hardware
	// 
	// 	   The call to configure() is mandatory, and must be done after a sw_reset().
	// 	   The rest of the hardware configuration is optional, and if you are not
	// 	   using the all the hardware, then the defaults are probably fine.

	STPM_ERROR configure(STPM_Configuration config);

	// Configure Sag/Swell 
	// 	   
	// Call this function *after* calling configure() above, pass in the same "config" structure
	// as passed to the configure() function, as this is required to calculate sag/swell registers.
	//
	STPM_ERROR configure_ss(STPM_Configuration config, STPM_SS_Config primary, STPM_SS_Config secondary);

	//
	// Read back data
	//

	// Latch the read-only registers before reading
	STPM_ERROR latch(bool primary, bool secondary);

	// Read voltage and current of primary and secondary channels
	STPM_ERROR read_rms(float& primary_v, float& primary_i, float& secondary_v, float& secondary_i);

	// Read the power and energy for the primary and secondary channels
	STPM_ERROR read_active(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy);
	STPM_ERROR read_fundamental(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy);
	STPM_ERROR read_reactive(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy);
	STPM_ERROR read_apparent_rms(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy);
	STPM_ERROR read_apparent_vectorial(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy);

	//
	// Talk to the hardware over the serial port
	//

	// The low level package exchange with the STPM3x
	STPM_ERROR exchange(uint8_t read_addr, uint8_t write_addr, uint16_t write_data, uint32_t& out);

	// Read a single register
	STPM_ERROR read(uint8_t read_addr, uint32_t& out);

	// Write a single register
	STPM_ERROR write(uint8_t write_addr, uint16_t write_data);

	// Read/update/write a register
	STPM_ERROR update(uint8_t write_addr, uint16_t write_data, uint16_t mask);

private:

	STPM_ERROR read_power(int energy_reg, int power_reg, int total_reg, float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy);
};
