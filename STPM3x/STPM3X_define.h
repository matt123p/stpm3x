/***************************************************
  Definition of most registers of the STPM3X Power
  Monitor chip. Feel free to use the code for any
  project.

  Benjamin Völker, voelkerb@me.com
  Embedded Systems
  University of Freiburg, Institute of Informatik
 ****************************************************/

#ifndef STPM_DEFINE_h
#define STPM_DEFINE_h


#define STPM3x_FRAME_LEN 5
#define CRC_8 (0x07)


 /*------Structure definition for DSP CR1 LSB register STMP32--------------*/
 /*  Row:     0                                                            */
 /*  Address: 0x00                                                         */
 /*  Name:    DSP_CR1_LSW[15:0]                                            */
 /*  Read(R) Write(W) Latch(L): RW                                         */
 /*  Default: 0x00A0                                                       */
typedef union {
    struct {
        unsigned CLRSS_T01 : 4;
        unsigned ClearSS1 : 1;
        unsigned ENVREF1 : 1;  //  Enable internal voltage reference for primary channel:
        // 0: reference disabled – external Vref required
        // 1: reference enabled
        unsigned TC1 : 3;  //Temperature compensation coefficient selection for primary
        //channel voltage reference VREF1
        unsigned : 7;
    };
    struct {
        uint16_t WORD;
    };

} DSP_CR100bits_t;


/*------------------------------------------------------------------------*/

/*------Structure definition for DSP CR1 MSB register STMP32--------------*/
/*  Row:     1                                                            */
/*  Address: 0x01                                                         */
/*  Name:    DSP_CR1 MSW[31:16]                                           */
/*  Default: 0x0400                                                       */
typedef union {
    struct {
        unsigned : 1;
        unsigned AEM1 : 1; // Apparent energy mode for primary channel:
        // 0: use apparent RMS power
        // 1: use apparent vectorial power
        unsigned APM1 : 1; // Apparent vectorial power mode for primary channel:
        // 0: use fundamental power
        // 1: use active power
        unsigned BHPFV1 : 1; // Bypass hi-pass filter for primary voltage channel:
        // 0: HPF enabled
        // 1: HPF bypassed
        unsigned BHPFC1 : 1; // Bypass hi-pass filter for primary current channel:
        // 0: HPF enabled
        // 1: HPF bypassed
        unsigned ROC1 : 1; // Add Rogowski integrator t
        unsigned BLPFV1 : 1; // Primary voltage channel frequency content used for reactive  power calculation:
        // 0: fundamental
        // 1: wideband
        unsigned BLPFC1 : 1; // Primary current channel frequency content used for reactive power calculation:
        // 0: fundamental
        // 1: wideband
        unsigned LPW1 : 4; // LED1 speed dividing factor: 0x0 = 2^(-4), 0xF = 2^11
        // Default 0x4 = 1
        unsigned LPC1 : 2; // LED1 pulse-out power selection:LPS1 [1:0]: 00,01,10,11
        // LED1 output: active, fundamental, reactive, apparent
        unsigned LCSI : 2; // LCS1 [1:0]: 00,01,10,11LED1: primary channels, secondary channels, cumulative,
        // sigma-delta bitstream
    };
    struct {
        uint16_t WORD;
    };
} DSP_CR101bits_t;


/*------Structure definition for DSP CR2 LSB register STMP32--------------*/
/*  Row:     01                                                           */
/*  Address: 0x02                                                         */
/*  Name:    DSP_CR2_LCW[15:0]                                            */
/*  Default: 0x00A0                                                       */
typedef union {
    struct {
        unsigned CLRSS_T02 : 4;
        unsigned ClearSS2 : 1;
        unsigned ENVREF2 : 1;  //  Enable internal voltage reference for primary channel:
        // 0: reference disabled – external Vref required
        // 1: reference enabled
        unsigned TC2 : 3;  //Temperature compensation coefficient selection for primary
        //channel voltage reference VREF1
        unsigned : 7;
    };
    struct {
        uint16_t WORD;
    };
} DSP_CR200bits_t;

/*------------------------------------------------------------------------*/

/*------Structure definition for DSP CR1 MSB register STMP32--------------*/
/*  Row:     01                                                           */
/*  Address: 0x03                                                         */
/*  Name:    DSP_CR2 MSW[31:16]                                           */
/*  Default: 0x0400                                                       */
typedef union {
    struct {
        unsigned : 1;
        unsigned AEM2 : 1; // Apparent energy mode for secondary channel:
        // 0: use apparent RMS power
        // 1: use apparent vectorial power
        unsigned APM2 : 1; // Apparent vectorial power mode for secondary channel:
        // 0: use fundamental power
        // 1: use active power
        unsigned BHPFV2 : 1; // Bypass hi-pass filter for secondary voltage channel:
        // 0: HPF enabled
        // 1: HPF bypassed
        unsigned BHPFC2 : 1; // Bypass hi-pass filter for secondary current channel:
        // 0: HPF enabled
        // 1: HPF bypassed
        unsigned ROC2 : 1; // Add Rogowski integrator t
        unsigned BLPFV2 : 1; // secondary voltage channel frequency content used for reactive  power calculation:
        // 0: fundamental
        // 1: wideband
        unsigned BLPFC2 : 1; // secondary current channel frequency content used for reactive power calculation:
        // 0: fundamental
        // 1: wideband
        unsigned LPW2 : 4; // LED1 speed dividing factor: 0x0 = 2^(-4), 0xF = 2^11
        // Default 0x4 = 1
        unsigned LPC2 : 2; // LED1 pulse-out power selection:LPS1 [1:0]: 00,01,10,11
        // LED1 output: active, fundamental, reactive, apparent
        unsigned LCS2 : 2; // LCS2 [1:0]: 00,01,10,11LED1: primary channels, secondary channels, cumulative,
        // sigma-delta bitstream
    };
    struct {
        uint16_t WORD;
    };
} DSP_CR201bits_t;


/*------------------------------------------------------------------------*/

/*------Structure definition for DSP CR3 LSB register STMP32--------------*/
/*  Row:     2                                                            */
/*  Address: 04                                                           */
/*  Name:    DSP_CR3 LSW[15:0]                                            */
/*  Default: 0x04e0                                                       */
typedef union {
    struct {
        unsigned SAG_TIME_THR : 14;
        unsigned ZCR_SEL : 2;        //When DSP_CR301bits.ZCR_EN=0; ZCR_SEL=00(V1),
        //                             ZCR_SEL=01(C1),
        //                             ZCR_SEL=10(V2),
        //                             ZCR_SEL=11(C1);
    };
    struct {
        uint16_t WORD;
    };
} DSP_CR300bits_t;

/*------Structure definition for DSP CR3 MSB register STMP32--------------*/
/*  Row:     2                                                            */
/*  Address: 05                                                           */
/*  Name:    DSP_CR3 MSW[31:16]                                           */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
        unsigned ZCR_EN : 1;    //ZCR/CLK pin output: 0: CLK 1: ZCR
        unsigned TMP_TOL : 2;
        unsigned TMP_EN : 1;
        unsigned SW_Reset : 1;    //SW reset brings the configuration registers to default
        //This bit is set to zero after this action automatically
        unsigned SW_Latch1 : 1;    //Primary channel measurement register latch
        //This bit is set to zero after this action automatically
        unsigned SW_Latch2 : 1;  //Secondary channel measurement register latch
        //his bit is set to zero after this action automatically
        unsigned SWAuto_Latch : 1; //Automatic measurement register latch at 7.8125 kHz
        unsigned LED_OFF1 : 1;  //LED1 pin output disable 0: LED1 output on 1: LED1 output disabled
        unsigned LED_OFF2 : 1;    //LED2 pin output disable 0: LED2 output on1: LED2 output disabled
        unsigned EN_CUM : 1;    //Cumulative energy calculation
        //0: cumulative is the sum of channel energies
        //1: total is the difference of energies
        unsigned REFFREQ : 1;  //Reference line frequency: 0: 50 Hz 1: 60 Hz
        unsigned : 4;
    };
    struct {
        uint16_t WORD;
    };
} DSP_CR301bits_t;


/*------------------------------------------------------------------------*/
/*================================================*/
/*------Definition structure for DSP CR4 register STMP32------------------*/
/*  Row:     3                                                            */
/*  Address: 0x06                                                         */
/*  Name:    DSP_CR400                                                    */
/*  Structures:PHC2[9:0];PHV2[1:0]; PHC1[9:0]; PHV1[1:0]                  */
typedef union {
    struct {
        unsigned PHC2 : 10;         //PHC2[9:0]
        unsigned PHV2 : 2;          //PHV2[1:0]
        unsigned PHC1 : 10;         //PHC1[9:0]
        unsigned PHV1 : 2;          //PHV2[1:0]
        unsigned : 8;
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_CR400bits_t;

/*------Definition structure for DSP CR5 register STMP32------------------*/
/*  Row:     4                                                            */
/*  Address: 0x08                                                         */
/*  Name:    DSP_CR500                                                    */
/*  Structures:SAG_THR1[9:0];SWV_THR1[9:0]; PHC1[9:0]; CHV1[11:0]         */
typedef union {
    struct {
        unsigned CHV1 : 12;          //CHV1[11:0]]
        unsigned SWV_THR1 : 10;          //SWV_THR1[9:0]
        unsigned SAG_THR1 : 10;          //SAG_THR1[9:1]
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_CR500bits_t;

/*------Definition structure for DSP CR6 register STMP32------------------*/
/*  Row:     5                                                            */
/*  Address: 0x0A                                                         */
/*  Name:    DSP_CR600                                                    */
/*  Structures:;SWC_THR1[9:0]; CHC1[11:0]                                 */
typedef union {
    struct {
        unsigned CHC1 : 12;          //CHV1[11:0]]
        unsigned SWV_THR1 : 10;          //SWV_THR1[9:0]
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 6;
    };
} DSP_CR600bits_t;

/*------Definition structure for DSP CR7 register STMP32------------------*/
/*  Row:     6                                                            */
/*  Address: 0x0C                                                         */
/*  Name:    DSP_CR700                                                    */
/*  Structures:;SWC_THR1[9:0]; CHC1[11:0]                                 */
typedef union {
    struct {
        unsigned CHV2 : 12;                 //CHV1[11:0]]
        unsigned SWV_THR2 : 10;             //SWV_THR1[9:0]
        unsigned SAG_THR2 : 10;             //SAG_THR1[9:1]
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
} DSP_CR700bits_t;

/*------Definition structure for DSP CR8 register STMP32------------------*/
/*  Row:     7                                                            */
/*  Address: 0x0E                                                         */
/*  Name:    DSP_CR800                                                    */
/*  Structures:SAG_THR2[9:0];SWV_THR2[9:0]; PHC1[9:0]; CHV2[11:0]         */
typedef union {
    struct {
        unsigned CHV2 : 12;                 //CHV1[11:0]]
        unsigned SWV_THR2 : 10;             //SWV_THR1[9:0]
        unsigned SAG_THR2 : 10;             //SAG_THR1[9:1]
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
} DSP_CR800bits_t;

/*------Definition structure for DSP CR9 register STMP32------------------*/
/*  Row:     8                                                            */
/*  Address: 0x10                                                         */
/*  Name:    DSP_CR900                                                    */
/*  Structures:OFAF1[9:0];OFA1[9:0]; AH_UP1[11:0]                         */
typedef union {

    struct {
        unsigned AH_UP1 : 12;
        unsigned OFA1 : 10;
        unsigned OFAF1 : 10;
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
} DSP_CR900bits_t;

/*------Definition structure for DSP CR10 register STMP32-----------------*/
/*  Row:     9                                                            */
/*  Address: 0x12                                                         */
/*  Name:    DSP_CR1000                                                   */
/*  Structures:OFAS1[9:0];OFR1[9:0]; AH_DOWN1[11:0]                       */
typedef union {
    struct {
        unsigned AH_DOWN1 : 12;
        unsigned OFR1 : 10;
        unsigned OFAS1 : 10;
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
} DSP_CR1000bits_t;

/*------Definition structure for DSP CR11 register STMP32-----------------*/
/*  Row:     10                                                           */
/*  Address: 0x14                                                         */
/*  Name:    DSP_CR1100                                                   */
/*  Structures:OFAF2[9:0];OFA2[9:0]; AH_UP2[11:0]                         */
typedef union {
    struct {
        unsigned AH_UP2 : 12;
        unsigned OFA2 : 10;
        unsigned OFAF2 : 10;
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
} DSP_CR1100bits_t;

/*------Definition structure for DSP CR12 register STMP32-----------------*/
/*  Row:     11                                                           */
/*  Address: 0x16                                                         */
/*  Name:    DSP_CR1200                                                   */
/*  Structures:OFAS2[9:0];OFR2[9:0]; AH_DOWN2[11:0]                       */
typedef union {
    struct {
        unsigned AH_DOWN2 : 12;
        unsigned OFR2 : 10;
        unsigned OFAS2 : 10;
    };
    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    };
} DSP_CR1200bits_t;

/*------Structure definition for DFE CR1 register STMP32------------------*/
/*  Row:     12                                                           */
/*  Address: 18                                                           */
/*  Name:    DFE_CR1 LSB[15:0]                                            */
/*  Default: 0x0327                                                       */
typedef union {
    struct {
        unsigned ENV1 : 1;
        unsigned : 15;
    };
    struct {
        uint16_t WORD;
    };
} DFE_CR100bits_t;


/*------Structure definition for DFE CR1 register STMP32------------------*/
/*  Row:     12                                                           */
/*  Address: 19                                                           */
/*  Name:    DFE_CR1 MSW[31:16]                                           */
/*  Default: 0x3270327                                                    */

typedef union {
    struct {
        unsigned ENC1 : 1;
        unsigned : 9;
        unsigned GAIN1 : 2;
        unsigned : 4;
    };
    struct {
        uint16_t WORD;
    };
} DFE_CR101bits_t;


/*------Structure definition for DFE CR2 register STMP32------------------*/
/*  Row:     13                                                           */
/*  Address: 1B                                                           */
/*  Name:    DFE_CR2 LSB[15:0]                                           */
/*  Default: 0x3270327                                                    */
typedef union {
    struct {
        unsigned ENV2 : 1;
        unsigned : 15;
    };
    struct {
        uint16_t WORD;
    };
} DFE_CR200bits_t;


/*------Structure definition for DFE CR2 register STMP32------------------*/
/*  Row:     13                                                           */
/*  Address: 1B                                                           */
/*  Name:    DFE_CR2 MSW[31:16]                                           */
/*  Default: 0x3270327                                                    */
typedef union {
    struct {
        unsigned ENC2 : 1;
        unsigned : 9;
        unsigned GAIN2 : 2;
        unsigned : 4;
    };
    struct {
        uint16_t WORD;
    };
} DFE_CR201bits_t;


/*------Structure definition for DSP_SR1 register STMP32------------------*/
/*  Row:     16                                                           */
/*  Address: 0x22                                                         */
/*  Name:    DSP_SR1                                                      */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
                                                                    // == PH1+PH2 status ==
        unsigned signTotalActivePower : 1;							// Sign total active power
        unsigned signTotalReactivePower : 1;						// Sign total reactive power
        unsigned overflowTotalActiveEnergy : 1;						// Overflow total active energy
        unsigned overflowTotalReactiveEnergy : 1;					// Overflow total reactive energy

                                                                    // == PH2 IRQ status ==
        unsigned signSecondaryChannelActivePower : 1;				// Sign secondary channel active power
        unsigned signSecondaryChannelActiveFundamentalPower : 1;	// Sign secondary channel active fundamental power
        unsigned signSecondaryChannelReactivePower : 1;				// Sign secondary channel reactive power
        unsigned signSecondaryChannelApparentPower : 1;				// Sign secondary channel apparent power
        unsigned overflowSecondaryChannelActiveEnergy : 1;			// Overflow secondary channel active energy
        unsigned overflowSecondaryChannelActiveFundamentalEnergy: 1;// Overflow secondary channel active fundamental energy
        unsigned overflowSecondaryChannelReactiveEnergy : 1;		// Overflow secondary channel reactive energy
        unsigned overflowSecondaryChannelApparentEnergy : 1;		// Overflow secondary channel apparent energy

                                                                    // == PH1 IRQ status ==
        unsigned signPrimaryChannelActivePower : 1;					// Sign primary channel active power
        unsigned signPrimaryChannelActiveFundamentalPower : 1;		// Sign primary channel active fundamental power
        unsigned signPrimaryChannelReactivePower : 1;				// Sign primary channel reactive power
        unsigned signPrimaryChannelApparentPower : 1;				// Sign primary channel apparent power
        unsigned overflowPrimaryChannelActiveEnergy : 1;			// Overflow primary channel active energy
        unsigned overflowPrimaryChannelActiveFundamentalEnergy : 1;	// Overflow primary channel active fundamental energy
        unsigned overflowPrimaryChannelReactiveEnergy : 1;			// Overflow primary channel reactive energy
        unsigned overflowPrimaryChannelApparentEnergy : 1;			// Overflow primary channel apparent energy

                                                                    // == C1 IRQ status ==
        unsigned primaryCurrentSigmaDeltaBitstreamStuck : 1;		// Primary current sigma - delta bitstream stuck
        unsigned ah1AccumulationOfPrimaryChannelCurrent : 1;		// AH1 - accumulation of primary channel current
        unsigned primaryCurrentSwellDetected : 1;					// Primary current swell detected
        unsigned primaryCurrentSwellEnd : 1;						// Primary current swell end

                                                                    // == V1 IRQ status ==
        unsigned primaryVoltageSigmaDeltaBitstreamStuck : 1;		// Primary voltage sigma - delta bitstream stuck
        unsigned primaryVoltagePeriodError : 1;						// Primary voltage period error
        unsigned primaryVoltageSagDetected : 1;						// Primary voltage sag detected
        unsigned primaryVoltageSagEnd : 1;							// Primary voltage sag end
        unsigned primaryVoltageSwellDetected : 1;					// Primary voltage swell detected
        unsigned primaryVoltageSwellEnd : 1;						// Primary voltage swell end

                                                                    // == Tamper ==
        unsigned tamperOnPrimary : 1;								// Tamper on primary
        unsigned tamperOrWrongConnection : 1;						// Tamper or wrong connection
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_SR1bits_t;

/*------Structure definition for DSP_SR2 register STMP32------------------*/
/*  Row:     18                                                           */
/*  Address: 0x24                                                         */
/*  Name:    DSP_SR2                                                      */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
                                                                    // == PH1+PH2 status ==
        unsigned signTotalActivePower : 1;							// Sign total active power
        unsigned signTotalReactivePower : 1;						// Sign total reactive power
        unsigned overflowTotalActiveEnergy : 1;						// Overflow total active energy
        unsigned overflowTotalReactiveEnergy : 1;					// Overflow total reactive energy

                                                                    // == PH2 status ==
        unsigned signSecondaryChannelActivePower : 1;				// Sign secondary channel active power
        unsigned signSecondaryChannelActiveFundamentalPower : 1;	// Sign secondary channel active fundamental power
        unsigned signSecondaryChannelReactivePower : 1;				// Sign secondary channel reactive power
        unsigned signSecondaryChannelApparentPower : 1;				// Sign secondary channel apparent power
        unsigned overflowSecondaryChannelActiveEnergy : 1;			// Overflow secondary channel active energy
        unsigned overflowSecondaryChannelActiveFundamentalEnergy : 1;// Overflow secondary channel active fundamental energy
        unsigned overflowSecondaryChannelReactiveEnergy : 1;		// Overflow secondary channel reactive energy
        unsigned overflowSecondaryChannelApparentEnergy : 1;		// Overflow secondary channel apparent energy

                                                                    // == PH1 status ==
        unsigned signPrimaryChannelActivePower : 1;					// Sign primary channel active power
        unsigned signPrimaryChannelActiveFundamentalPower : 1;		// Sign primary channel active fundamental power
        unsigned signPrimaryChannelReactivePower : 1;				// Sign primary channel reactive power
        unsigned signPrimaryChannelApparentPower : 1;				// Sign primary channel apparent power
        unsigned overflowPrimaryChannelActiveEnergy : 1;			// Overflow primary channel active energy
        unsigned overflowPrimaryChannelActiveFundamentalEnergy : 1;	// Overflow primary channel active fundamental energy
        unsigned overflowPrimaryChannelReactiveEnergy : 1;			// Overflow primary channel reactive energy
        unsigned overflowPrimaryChannelApparentEnergy : 1;			// Overflow primary channel apparent energy

                                                                    // == C2 status ==
        unsigned secondaryCurrentSigmaDeltaBitstreamStuck : 1;		// Secondary current sigma - delta bitstream stuck
        unsigned ah1AccumulationOfSecondaryChannelCurrent : 1;		// AH1 - accumulation of secondary channel current
        unsigned secondaryCurrentSwellDetected : 1;					// Secondary current swell detected
        unsigned secondaryCurrentSwellEnd : 1;						// Secondary current swell end

                                                                    // == V2 status ==
        unsigned secondaryVoltageSigmaDeltaBitstreamStuck : 1;		// Secondary voltage sigma - delta bitstream stuck
        unsigned secondaryVoltagePeriodError : 1;					// Secondary voltage period error
        unsigned secondaryVoltageSagDetected : 1;					// Secondary voltage sag detected
        unsigned secondaryVoltageSagEnd : 1;						// Secondary voltage sag end
        unsigned secondaryVoltageSwellDetected : 1;					// Secondary voltage swell detected
        unsigned secondaryVoltageSwellEnd : 1;						// Secondary voltage swell end

                                                                    // == Tamper ==
        unsigned tamperOnSecondary : 1;								// Tamper on secondary
        unsigned tamperOrWrongConnection : 1;						// Tamper or wrong connection
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_SR2bits_t;


/*------Structure definition for DSP_EV1 register STMP32------------------*/
/*  Row:     21                                                           */
/*  Address: 0x??                                                         */
/*  Name:    DSP_EV1                                                      */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
                                                                    // == PH1+PH2 events ==
        unsigned signTotalActivePower : 1;							// Sign total active power
        unsigned signTotalReactivePower : 1;						// Sign total reactive power
        unsigned overflowTotalActiveEnergy : 1;						// Overflow total active energy
        unsigned overflowTotalReactiveEnergy : 1;					// Overflow total reactive energy

                                                                    // == PH1 events ==
        unsigned signPrimaryChannelActivePower : 1;					// Sign primary channel active power
        unsigned signPrimaryChannelActiveFundamentalPower : 1;		// Sign primary channel active fundamental power
        unsigned signPrimaryChannelReactivePower : 1;				// Sign primary channel reactive power
        unsigned signPrimaryChannelApparentPower : 1;				// Sign primary channel apparent power
        unsigned overflowPrimaryChannelActiveEnergy : 1;			// Overflow primary channel active energy
        unsigned overflowPrimaryChannelActiveFundamentalEnergy : 1;	// Overflow primary channel active fundamental energy
        unsigned overflowPrimaryChannelReactiveEnergy : 1;			// Overflow primary channel reactive energy
        unsigned overflowPrimaryChannelApparentEnergy : 1;			// Overflow primary channel apparent energy

                                                                    // == C1 events ==
        unsigned primaryCurrentZeroCrossing : 1;					// Primary current zero-crossing
        unsigned primaryCurrentSigmaDeltaBitstreamStuck : 1;		// Primary current sigma-delta bitstream stuck
        unsigned primaryCurrentAhAccumulation : 1;					// Primary current AH accumulation
        unsigned primaryCurrentSwellEventHistory : 1;				// Primary current swell event history

                                                                    // == V1 events ==
        unsigned primaryVoltageZeroCrossing : 1;					// Primary voltage zero-crossing
        unsigned primaryVoltageSigmaDeltaBitstreamStuck : 1;		// Primary voltage sigma-delta bitstream stuck
        unsigned primaryVoltagePeriodErrorOutOfRange : 1;			// Primary voltage period error (out of range)

        unsigned primaryVoltageSwellEventHistory : 4;				// Primary voltage swell event history
        unsigned primaryVoltageSagEventHistory : 4;					// Primary voltage sag event history
        unsigned reserved : 2;										// Reserved
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_EV1bits_t;

/*------Structure definition for DSP_EV2 register STMP32------------------*/
/*  Row:     22                                                           */
/*  Address: 0x??                                                         */
/*  Name:    DSP_EV2                                                      */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
                                                                        // == PH1+PH2 events ==
        unsigned signTotalActivePower : 1;								// Sign total active power
        unsigned signTotalReactivePower : 1;							// Sign total reactive power
        unsigned overflowTotalActiveEnergy : 1;							// Overflow total active energy
        unsigned overflowTotalReactiveEnergy : 1;						// Overflow total reactive energy

                                                                        // == PH2 events ==
        unsigned signSecondaryChannelActivePower : 1;					// Sign secondary channel active power
        unsigned signSecondaryChannelActiveFundamentalPower : 1;		// Sign secondary channel active fundamental power
        unsigned signSecondaryChannelReactivePower : 1;					// Sign secondary channel reactive power
        unsigned signSecondaryChannelApparentPower : 1;					// Sign secondary channel apparent power
        unsigned overflowSecondaryChannelActiveEnergy : 1;				// Overflow secondary channel active energy
        unsigned overflowSecondaryChannelActiveFundamentalEnergy : 1;	// Overflow secondary channel active fundamental energy
        unsigned overflowSecondaryChannelReactiveEnergy : 1;			// Overflow secondary channel reactive energy
        unsigned overflowSecondaryChannelApparentEnergy : 1;			// Overflow secondary channel apparent energy

                                                                        // == C2 events ==
        unsigned secondaryCurrentZeroCrossing : 1;						// Secondary current zero-crossing
        unsigned secondaryCurrentSigmaDeltaBitstreamStuck : 1;			// Secondary current sigma-delta bitstream stuck
        unsigned secondaryCurrentAhAccumulation : 1;					// Secondary current AH accumulation
        unsigned secondaryCurrentSwellEventHistory : 1;					// Secondary current swell event history

                                                                        // == V2 events ==
        unsigned secondaryVoltageZeroCrossing : 1;						// Secondary voltage zero-crossing
        unsigned secondaryVoltageSigmaDeltaBitstreamStuck : 1;			// Secondary voltage sigma-delta bitstream stuck
        unsigned secondaryVoltagePeriodErrorOutOfRange : 1;				// Secondary voltage period error (out of range)

        unsigned secondaryVoltageSwellEventHistory : 4;					// Secondary voltage swell event history
        unsigned secondaryVoltageSagEventHistory : 4;					// Secondary voltage sag event history
        unsigned reserved : 2;											// Reserved
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_EV2bits_t;


/*------Structure definition for US1 REG1 LSW register STMP32-------------*/
/*  Row:     18                                                           */
/*  Address: 0x24                                                         */
/*  Name:    US1_REG1_LSW[15:0]                                           */
/*  Default: 0x4007                                                       */
typedef union {
    struct {
        unsigned CRC_Pol : 8;
        unsigned Noise_EN : 1;
        unsigned BRK_ERR : 1;
        unsigned : 4;
        unsigned CRC_EN : 1;
        unsigned ISB_FIRST : 1;
    };
    struct {
        uint16_t WORD;
    };
} US1_REG100bits_t;

/*------Structure definition for U1 REG1 MSW register STMP32--------------*/
/*  Row:     18                                                           */
/*  Address: 0x25                                                         */
/*  Name:    US1_REG1_MSW[31:16]                                          */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
        unsigned TIME_OUT : 8;
    };
    struct {
        uint16_t WORD;
    };
} US1_REG101bits_t;


/*------Structure definition for DSP_REG16 register STMP32------------------*/
/*  Row:     38                                                           */
/*  Address: 0x4c                                                         */
/*  Name:    DSP_REG16                                                      */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
        unsigned swv1_time : 15;
        unsigned : 1;
        unsigned sag1_time : 15;
        unsigned : 1;
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_Reg16bits_t;

/*------Structure definition for DSP_REG17 register STMP32------------------*/
/*  Row:     39                                                           */
/*  Address: 0x4e                                                         */
/*  Name:    DSP_REG17                                                      */
/*  Default: 0x0000                                                       */
typedef union {
    struct {
        unsigned swc1_time : 15;
        unsigned : 1;
        unsigned c1_pha : 12;
        unsigned : 4;
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_Reg16bits_t;

/*------Structure definition for DSP_REG18 register STMP32------------------*/
/*  Row:     40                                                             */
/*  Address: 0x50                                                           */
/*  Name:    DSP_REG18                                                      */
/*  Default: 0x0000                                                         */
typedef union {
    struct {
        unsigned swv2_time : 15;
        unsigned : 1;
        unsigned sag2_time : 15;
        unsigned : 1;
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_Reg16bits_t;

/*------Structure definition for DSP_REG19 register STMP32------------------*/
/*  Row:     41                                                             */
/*  Address: 0x52                                                           */
/*  Name:    DSP_REG19                                                      */
/*  Default: 0x0000                                                         */
typedef union {
    struct {
        unsigned swc2_time : 15;
        unsigned : 1;
        unsigned c2_pha : 12;
        unsigned : 4;
    };
    struct {
        uint16_t LWORD;
        uint16_t HWORD;
    };
    struct {
        uint32_t DWORD;
    };
} DSP_Reg16bits_t;



#endif
