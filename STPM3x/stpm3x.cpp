#include "Stpm3x.h"
#include "Stpm3x_define.h"
#include <stdio.h>
#include <stdlib.h>

#define debug_log	printf

const unsigned char crc8_table[256] = {
    0x0, 0x7, 0xE, 0x9, 0x1C, 0x1B, 0x12, 0x15, 0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
    0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65, 0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
    0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5, 0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
    0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85, 0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
    0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2, 0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
    0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2, 0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
    0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32, 0x1F, 0x18, 0x11, 0x16, 0x3, 0x4, 0xD, 0xA,
    0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42, 0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
    0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C, 0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
    0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC, 0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
    0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C, 0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
    0x19, 0x1E, 0x17, 0x10, 0x5, 0x2, 0xB, 0xC, 0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
    0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B, 0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
    0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B, 0x6, 0x1, 0x8, 0xF, 0x1A, 0x1D, 0x14, 0x13,
    0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB, 0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
    0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB, 0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

// This table is for reversing the bit order of bytes during the CRC calculation
const unsigned char bit_reverse[256] = {
    0x0, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
    0x8, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
    0x4, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0xC, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
    0x2, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
    0xA, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x6, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
    0xE, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
    0x1, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
    0x9, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
    0x5, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
    0xD, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
    0x3, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
    0xB, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
    0x7, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
    0xF, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF,
};

inline void crc_stpm3x(unsigned char* crc, unsigned char m)
/*
 * For a byte array whose accumulated crc value is stored in *crc, computes
 * resultant crc obtained by appending m to the byte array.
 * NOTE: This function takes in to account the unique CRC function in the STPM3x
 */
{
    *crc = crc8_table[(*crc) ^ bit_reverse[m]];
    *crc &= 0xFF;
}

Stpm3x::Stpm3x(int port)
	: primary_Vc(1.0f), primary_Ic(1.0f)
	, primary_Pc(1.0f), primary_Ec(1.0f)
	, secondary_Vc(1.0f), secondary_Ic(1.0f)
	, secondary_Pc(1.0f), secondary_Ec(1.0f)
	, serial(port)
{
	serial.begin(9600);
	serial.setTimeout(100);
}


// Configure
STPM_ERROR Stpm3x::configure(STPM_Configuration config)
{
	STPM_ERROR r;

	// Write the configuration registers
	DSP_CR100bits_t reg0;
	reg0.WORD = 0;

	reg0.CLRSS_T01 = 0;
	reg0.ClearSS1 = 0;
	reg0.ENVREF1 = config.primary_channel.enVref ? 1 : 0;
	reg0.TC1 = config.primary_channel.TC;
	r = write(0, reg0.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DSP_CR101bits_t reg1;
	reg1.WORD = 0;

	reg1.AEM1 = config.primary_channel.aem ? 1 : 0;
	reg1.APM1 = config.primary_channel.apm ? 1 : 0;
	reg1.BHPFV1 = config.primary_channel.bhpfv ? 1 : 0;
	reg1.BHPFC1 = config.primary_channel.bhpfc ? 1 : 0;
	reg1.ROC1 = config.primary_channel.Rogowski ? 1 : 0;
	reg1.BLPFV1 = 0;
	reg1.BLPFC1 = 0;
	reg1.LPW1 = 0;
	reg1.LPC1 = 0;
	reg1.LCSI = 0;
	r = write(1, reg1.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DSP_CR200bits_t reg2;
	reg2.WORD = 0;

	reg2.CLRSS_T02 = 0;
	reg2.ClearSS2 = 0;
	reg2.ENVREF2 = config.secondary_channel.enVref ? 1 : 0;
	reg2.TC2 = config.secondary_channel.TC;
	r = write(2, reg2.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DSP_CR201bits_t reg3;
	reg3.WORD = 0;

	reg3.AEM2 = config.primary_channel.aem ? 1 : 0;
	reg3.APM2 = config.primary_channel.apm ? 1 : 0;
	reg3.BHPFV2 = config.primary_channel.bhpfv ? 1 : 0;
	reg3.BHPFC2 = config.primary_channel.bhpfc ? 1 : 0;
	reg3.ROC2 = config.primary_channel.Rogowski ? 1 : 0;
	reg3.BLPFV2 = 0;
	reg3.BLPFC2 = 0;
	reg3.LPW2 = 0;
	reg3.LPC2 = 0;
	reg3.LCS2 = 0;
	r = write(3, reg3.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DSP_CR300bits_t reg4;
	reg4.WORD = 0;
	reg4.SAG_TIME_THR = 0x4E0;
	reg4.ZCR_SEL = 0;
	r = write(4, reg4.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DSP_CR301bits_t reg5;
	reg5.WORD = 0;
	reg5.TMP_TOL = config.tmp_tol;
	reg5.TMP_EN = config.tmp_en;
	reg5.SW_Reset = 0;
	reg5.SW_Latch1 = 0;
	reg5.SW_Latch2 = 0;
	reg5.SWAuto_Latch = 0;
	reg5.LED_OFF1 = 0;
	reg5.LED_OFF2 = 0;
	reg5.EN_CUM = config.en_cum;
	reg5.REFFREQ = config.freq;
	r = write(5, reg5.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DFE_CR100bits_t reg18;
	reg18.WORD = 0;
	reg18.ENV1 = config.primary_channel.enV ? 1 : 0;
	r = write(0x18, reg18.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}
	DFE_CR101bits_t reg19;
	reg19.WORD = 0;
	reg19.ENC1 = config.primary_channel.enC ? 1 : 0;
	switch (config.primary_channel.Ai)
	{
	case 2: 
		reg19.GAIN1 = 0;
		break;
	case 4:
		reg19.GAIN1 = 1;
		break;
	case 8:
		reg19.GAIN1 = 2;
		break;
	case 16:
		reg19.GAIN1 = 3;
		break;
	default:
		return STPM_ERROR::Invalid;
	}
	r = write(0x19, reg19.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}

	DFE_CR200bits_t reg20;
	reg20.WORD = 0;
	reg20.ENV2 = config.secondary_channel.enV ? 1 : 0;
	r = write(0x20, reg20.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}
	DFE_CR201bits_t reg21;
	reg21.WORD = 0;
	reg21.ENC2 = config.secondary_channel.enC ? 1 : 0;
	switch (config.secondary_channel.Ai)
	{
	case 2:
		reg21.GAIN2 = 0;
		break;
	case 4:
		reg21.GAIN2 = 1;
		break;
	case 8:
		reg21.GAIN2 = 2;
		break;
	case 16:
		reg21.GAIN2 = 3;
		break;
	default:
		return STPM_ERROR::Invalid;
	}
	r = write(0x21, reg21.WORD);
	if (r != STPM_ERROR::OK)
	{
		return r;
	}


	// The following registers have already been written:
	// 0,1,2,3,4,5,18,19,20,21
	// So now write the defaults in to the rest of the registers.  This ensures
	// every configuration register is written for configuring the STPM3x.
	// These are the default values give in the datasheet:
	const int register_defaults[] = {
		0x00000000,	// Register 6/7
		0x003FF800,	// Register 8/9
		0x003FF800, // Register 0xa/0xb
		0x003FF800,	// Register 0xc/0xd
		0x003FF800, // Register 0xe/0xf
		0x00000FFF, // Register 0x10/0x11
		0x00000FFF, // Register 0x12/0x13
		0x00000FFF, // Register 0x14/0x15
		0x00000FFF, // Register 0x16/0x17
		-1,			// Register 0x18 (already written above)
		-1,			// Register 0x1a (already written above)
		0x00000000, // Register 0x1c/0x1d
		0x00000000, // Register 0x1e/0x1f
		0x00000000, // Register 0x20/0x21
		0x00000000, // Register 0x22/0x23
		0x00004007, // Register 0x24/0x25
		0x00000683, // Register 0x26/0x27
		0x00000000, // Register 0x28/0x29
	};
	for (int i = 0; i < _countof(register_defaults); ++i)
	{
		int addr = (i * 2) + 6;
		if (register_defaults[i] != -1) 
		{
			write(addr, register_defaults[i] & 0xffff);
			write(addr + 1, register_defaults[i] >> 16);
		}
	}

	//
	// See tables 14 & 15 of datasheet
	//
	float primary_pd = (1 + config.primary_channel.R1 / config.primary_channel.R2);
	float primary_kint = (config.primary_channel.Rogowski ? kintrc : 1.0f);
	primary_Vc = (config.primary_channel.vRef * primary_pd) / (calv * Av * (1 << 15));
	primary_Ic = config.primary_channel.vRef / (cali * config.primary_channel.Ai * (1 << 17) * config.primary_channel.ks * primary_kint);
	primary_Pc = (config.primary_channel.vRef * config.primary_channel.vRef * primary_pd) /
		(primary_kint * Av * config.primary_channel.Ai * config.primary_channel.ks * calv * cali * (1 << 28));
	primary_Ec = (config.primary_channel.vRef * config.primary_channel.vRef * primary_pd) /
		(3600 * Dclk * primary_kint * Av * config.primary_channel.Ai * config.primary_channel.ks * calv * cali * (1 << 17));


	float secondary_pd = (1 + config.secondary_channel.R1 / config.secondary_channel.R2);
	float secondary_kint = (config.secondary_channel.Rogowski ? kintrc : 1.0f);
	secondary_Vc = (config.secondary_channel.vRef * secondary_pd) / (calv * Av * (1 << 15));
	secondary_Ic = config.secondary_channel.vRef / (cali * config.secondary_channel.Ai * (1 << 17) * config.secondary_channel.ks * secondary_kint);
	secondary_Pc = (config.secondary_channel.vRef * config.secondary_channel.vRef * secondary_pd) /
		(secondary_kint * Av * config.secondary_channel.Ai * config.secondary_channel.ks * calv * cali * (1 << 28));
	secondary_Ec = (config.secondary_channel.vRef * config.secondary_channel.vRef * secondary_pd) /
		(3600 * Dclk * secondary_kint * Av * config.secondary_channel.Ai * config.secondary_channel.ks * calv * cali * (1 << 17));

	return STPM_ERROR::OK;
}


// Configure Sag/Swell
STPM_ERROR Stpm3x::configure_ss(STPM_Configuration config, STPM_SS_Config primary, STPM_SS_Config secondary)
{
	float sqrt2 = 1.414213562373095f;
	float Dsag = 1 << 10;
	float Dswell = 1 << 10;

	// See table 16 of the datasheet
	float primary_sag_reg = (primary.sag_voltage / config.primary_channel.vRef)
		* Av * sqrt2 * calv
		* (config.primary_channel.R2 / (config.primary_channel.R1 + config.primary_channel.R2))
		* Dsag;
	float primary_swell_reg = (primary.swell_voltage / config.primary_channel.vRef)
		* Av * sqrt2 * calv
		* (config.primary_channel.R2 / (config.primary_channel.R1 + config.primary_channel.R2))
		* Dsag;

	float secondary_sag_reg = (secondary.sag_voltage / config.secondary_channel.vRef)
		* Av * sqrt2 * calv
		* (config.secondary_channel.R2 / (config.secondary_channel.R1 + config.secondary_channel.R2))
		* Dsag;
	float secondary_swell_reg = (secondary.swell_voltage / config.secondary_channel.vRef)
		* Av * sqrt2 * calv
		* (config.secondary_channel.R2 / (config.secondary_channel.R1 + config.secondary_channel.R2))
		* Dsag;

	// The sag threshold timer has a period of 8us.
	float primary_sag_time_threshold = primary.sag_time_threshold / 0.008;
	float secondary_sag_time_threshold = secondary.sag_time_threshold / 0.008;



	return STPM_ERROR::OK;
}


//
// Read back data
//
STPM_ERROR Stpm3x::latch(bool primary, bool secondary)
{
	DSP_CR301bits_t reg5;
	reg5.WORD = 0;
	reg5.SW_Latch1 = primary ? 1 : 0;
	reg5.SW_Latch2 = secondary ? 1 : 0;

	return update(0x5, reg5.WORD, reg5.WORD);
}

// Read voltage and current of primary and secondary channels
STPM_ERROR Stpm3x::read_rms(float& primary_v, float& primary_i, float& secondary_v, float& secondary_i)
{
	// Latch the registers
	latch(true, true);

	// Send the read and ignore the return
	uint32_t dummy;
	auto status = exchange(0x48, 0xff, 0xffff, dummy);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// Fetch the data
	uint32_t primary;
	status = exchange(0x4a, 0xff, 0xffff, primary);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}
	uint32_t secondary;
	status = exchange(0xff, 0xff, 0xffff, secondary);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// Decode the data
	primary_v = (primary & 0x7fff) * primary_Vc;
	primary_i = (primary >> 15) * primary_Ic;

	secondary_v = (secondary & 0x7fff) * secondary_Vc;
	secondary_i = (secondary >> 15) * secondary_Ic;

	return STPM_ERROR::OK;
}

STPM_ERROR Stpm3x::read_active(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy)
{
	return read_power(1, 5, 1, primary_energy, primary_power, secondary_energy, secondary_power, total_energy);
}

STPM_ERROR Stpm3x::read_fundamental(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy)
{
	return read_power(2, 6, 2, primary_energy, primary_power, secondary_energy, secondary_power, total_energy);
}

STPM_ERROR Stpm3x::read_reactive(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy)
{
	return read_power(3, 7, 3, primary_energy, primary_power, secondary_energy, secondary_power, total_energy);
}

STPM_ERROR Stpm3x::read_apparent_rms(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy)
{
	return read_power(4, 8, 4, primary_energy, primary_power, secondary_energy, secondary_power, total_energy);
}

STPM_ERROR Stpm3x::read_apparent_vectorial(float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy)
{
	return read_power(4, 9, 4, primary_energy, primary_power, secondary_energy, secondary_power, total_energy);
}

STPM_ERROR Stpm3x::read_power(int energy_reg, int power_reg, int total_reg, float& primary_energy, float& primary_power, float& secondary_energy, float& secondary_power, float& total_energy)
{
	// The primary registers for reading data begin at 0x54
	const int primary_reg1 = 0x54;
	const int secondary_reg1 = 0x6c;
	const int total_reg1 = 0x84;


	// Latch the registers
	latch(true, true);

	// As reads are one behind the request, we must send a read first and ignore the 
	// return value
	uint32_t dummy;
	auto status = exchange(primary_reg1 + (energy_reg*2)-1, 0xff, 0xffff, dummy);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// Fetch the data
	uint32_t raw_primary_energy;
	status = exchange(primary_reg1 + (power_reg * 2) - 1, 0xff, 0xffff, raw_primary_energy);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}
	uint32_t raw_primary_power;
	status = exchange(secondary_reg1 + (energy_reg * 2) - 1, 0xff, 0xffff, raw_primary_power);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}
	uint32_t raw_secondary_energy;
	status = exchange(secondary_reg1 + (power_reg * 2) - 1, 0xff, 0xffff, raw_secondary_energy);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}
	uint32_t raw_secondary_power;
	status = exchange(total_reg1 + (total_reg * 2) - 1, 0xff, 0xffff, raw_secondary_power);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}
	uint32_t raw_total;
	status = exchange(0xff, 0xff, 0xffff, raw_total);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// Now convert
	primary_energy = raw_primary_energy * primary_Ec;
	primary_power = raw_primary_power * primary_Pc;
	secondary_energy = raw_secondary_energy * secondary_Ec;
	secondary_power = raw_secondary_power * secondary_Pc;
	total_energy = raw_total * primary_Ec;

	return STPM_ERROR::OK;
}


// Send and receive a packet from the STPM3x on the UART
// This is the only function used to communicate with the STPM3x.  All other functions
// use this one.
STPM_ERROR Stpm3x::exchange(uint8_t read_addr, uint8_t write_addr, uint16_t write_data, uint32_t& out)
{
	for (int attempts = 0; attempts < 3; ++attempts)
	{
		uint8_t data[5];
		data[0] = read_addr;
		data[1] = write_addr;
		data[2] = write_data & 0xff;
		data[3] = write_data >> 8;
		uint8_t send_crc = 0;
		for (int i = 0; i < 4; ++i)
		{
			crc_stpm3x(&send_crc, data[i]);
		}
		data[4] = bit_reverse[send_crc];
		serial.write(data, 5);

		uint8_t recv[5];
		auto bytes_read = serial.readBytes(recv, 5);

		if (bytes_read != 5) {
			// We didn't get a full packet reply from the STPM3x
			return STPM_ERROR::Timeout;
		}
		uint8_t chk_crc = 0;
		for (int i = 0; i < 4; ++i)
		{
			crc_stpm3x(&chk_crc, recv[i]);
		}
		chk_crc = bit_reverse[chk_crc];
		if (chk_crc == recv[4])
		{
			// Got back a valid CRC, so decode the data
			out = static_cast<uint32_t>(recv[0])
				| (static_cast<uint32_t>(recv[1]) << 8)
				| (static_cast<uint32_t>(recv[2]) << 16)
				| (static_cast<uint32_t>(recv[3]) << 24);
			return STPM_ERROR::OK;
		}
		
		// Invalid CRC, so flush the serial port in an attempt to recover
		// communications
		flush();
	}

	// No packet passed a CRC check
	return STPM_ERROR::CRC;
}

void Stpm3x::flush()
{

}

STPM_ERROR Stpm3x::read(uint8_t read_addr, uint32_t& out)
{
	// Send the read and ignore the return
	uint32_t dummy;
	auto status = exchange(read_addr & 0xfe, 0xff, 0xffff, dummy);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// Fetch the data
	status = exchange(0xff, 0xff, 0xffff, out);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// If the request was for an odd address, then
	// we return the second 16 bits only
	if (read_addr & 0x1)
	{
		out = out >> 16;
	}
	return STPM_ERROR::OK;
}

STPM_ERROR Stpm3x::write(uint8_t write_addr, uint16_t write_data)
{
	// Send the write and ignore the return
	uint32_t dummy;
	return exchange(0xff, write_addr, write_data, dummy);
}

STPM_ERROR Stpm3x::update(uint8_t write_addr, uint16_t write_data, uint16_t mask)
{
	// Read
	uint32_t data;
	auto status = read(write_addr, data);
	if (status != STPM_ERROR::OK)
	{
		return status;
	}

	// Update
	data = (data &~mask) | write_data;

	// Write
	return write(write_addr, static_cast<uint16_t>(data));
}


STPM_ERROR Stpm3x::sw_reset()
{
	DSP_CR301bits_t data = { 0 };
	data.SW_Reset = 1;

	return update(5, data.WORD, data.WORD);
}
