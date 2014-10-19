/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2014 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup dataInitialisers
 *
 * @brief Global constant values
 *
 * All global constants values are, and should be, defined here.
 */


#define GLOBAL_CONSTANTS_C
#define NO_CONST_ARRAYS
#include "inc/freeEMS.h"


/* Constants */
/* &&&&&&&&&& WARNING &&&&&&&&&& These need to be changed if the timer period is changed at all!! &&&&&&&&&& WARNING &&&&&&&&&& */
/* TODO It may be better to make these actual times and calculate the number of timer units such that a change in time base of the timer doesn't affect the code. */


const unsigned char interfaceVersion[INTERFACE_VERSION_LENGTH] = { INTERFACE_VERSION };               ///< @copydoc interfaceVersion TODO change spec to not have numerics and to parse from string, maybe pull from somewhere?
const unsigned char firmwareVersion[FIRMWARE_VERSION_LENGTH] = { FIRMWARE_VERSION "-" BUILD_CONFIG }; ///< @copydoc firmwareVersion
const unsigned char buildTimeAndDate[FIRMWARE_BUILD_DATE_LENGTH] = { FIRMWARE_BUILD_DATE };           ///< @copydoc buildTimeAndDate
const unsigned char compilerVersion[COMPILER_VERSION_LENGTH] = { __VERSION__ };                       ///< @copydoc compilerVersion
const unsigned char operatingSystem[OPERATING_SYSTEM_LENGTH] = { OPERATING_SYSTEM };                  ///< @copydoc operatingSystem
const unsigned char builtByName[BUILT_BY_NAME_LENGTH] = { BUILT_BY_NAME };                            ///< @copydoc builtByName
const unsigned char supportEmail[SUPPORT_EMAIL_LENGTH] = { SUPPORT_EMAIL };                           ///< @copydoc supportEmail

/** Divisors and untunable physical constants combined into a single master fuel constant
 *
 * const unsigned short molarMassOfAir = 2897; // in grams per 100 moles, so divide by 100 to get gm/mol
 * const unsigned short msToTicks = 1250; // constant to bring ms into 0.8us chunks
 * const unsigned short universalGasConstant = 34056; // 8.314472 * 4096, so divide by 4096 to get real number
 *
 * hash define injectorFlowDivisor 1024
 * hash define injectorFlowUnitDivisor 1000 - to get it into litres/second
 * hash define injectorFlowTotalDivisor 1024000
 * hash define stoichiometricAFRDivisor 1024
 * hash define universalGasConstantDivisor 4096
 * hash define molarMassOfAirDivisor 100
 * hash define perCylinderVolumeDivisor 32768
 *
 * TODO hash define the fuel constant for different clock tick setups (msToTicks will vary)
 *
 * master = (msToTicks * molarMassOfAir * universalGasConstantDivisor * stoichiometricAFRDivisor * injectorFlowTotalDivisor) / (universalGasConstant * molarMassOfAirDivisor * perCylinderVolumeDivisor);
 * master = (1250      * 2897           * 4096                        * 1024                     * 1024000                 ) / (34056                * 100                   * 32768                   );
 * http://duckduckgo.com/?q=%28%281250+*+2897+*+4096+*+1024+*+1024000%29+%2F+%2834056+*++100+*+32768%29
 *
 * ((1250 * 2897 * 4096 * 1024 * 1024000) / (34056 *  100 * 32768) = 139371764
 */
const unsigned long masterFuelConstant = 139371764;

/** MAF fuel constant
 *
 * @todo TODO Determine what the value of MAF fuel constant should be
 */
const unsigned long MAFFuelConstant = 0;

/// @todo TODO Move these to decoder interface, and make set by each decoder where appropriate
///* ECT limits */
/* The number of timer units it takes for the switch on scheduling code to run + latencies */
const unsigned short ectSwitchOnCodeTime = 250; /* Used to set min pw in output ISR. 250 is based on worst of decoders causing latencies. */
/* The number of timer units it takes for the switch off scheduling code to run + latencies */
const unsigned short ectSwitchOffCodeTime = 250; /* Used to see if we should set self sched or not. 250 is based on worst of decoders causing latencies. */

// TODO put these where they belong, just dumped from other file for now...
/* Main injector channel bit masks and registers for use in both injection_isrs.c and engine_position_isrs.c */
/* Masks for setting mainOn flags and checking state of pin and therefore which change of state just occured */
/* Masks for clearing mainOn flags */
/* Masks for setting mainOn flags and checking state of pin and therefore which change of state just occured */
/* Masks to be used with |= to switch a channel to "turn on compare" mode */
/* Masks to be used dissable with &= to switch a channel to "turn off compare" mode */
/* Masks to be used with |= to switch a channel to "turn on on compare" mode from "turn off on compare" mode */
/* Masks to be used with &= to switch a channel to "turn off on compare" mode from "turn on on compare" mode */
/* Ignition channel bit masks for use in both PIT timer ISRs and engine_position_isrs.c */
/* Masks for setting ignition status bits and turning on the channels themselves */
/* Masks for clearing ignition status bits and turning off the channels themselves */


/* Injection masks */

// To be used with flag vars and TIE and TFLG
const unsigned char ectMainOnMasks[ECT_CHANNELS] = {BIT2,  BIT3,  BIT4,  BIT5,  BIT6,  BIT7};
const unsigned char ectMainOffMasks[ECT_CHANNELS] = {NBIT2, NBIT3, NBIT4, NBIT5, NBIT6, NBIT7};

// To be used in conjunction with injectorMainControlRegisters
const unsigned char ectMainActiveMasks[ECT_CHANNELS] = {BIT5, BIT7, BIT1, BIT3, BIT5, BIT7};      // Is this enabled for go high OR go low?
const unsigned char ectMainEnableMasks[ECT_CHANNELS] = {0x30, 0xC0, 0x03, 0x0C, 0x30, 0xC0};      // Regardless of state, mask to enable and cause to go high
const unsigned char ectMainDisableMasks[ECT_CHANNELS] = {0xCF, 0x3F, 0xFC, 0xF3, 0xCF, 0x3F};     // Regardless of state, mask to disable completely
const unsigned char ectMainGoHighMasks[ECT_CHANNELS] = {BIT4, BIT6, BIT0, BIT2, BIT4, BIT6};      // Already enabled, mask to change from go low to go high
const unsigned char ectMainGoLowMasks[ECT_CHANNELS] = {NBIT4, NBIT6, NBIT0, NBIT2, NBIT4, NBIT6}; // Already enabled, mask to change from go high to go low



