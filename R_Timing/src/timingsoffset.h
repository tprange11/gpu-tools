#ifndef __TIMINGS_OFFSET_H
#define __TIMINGS_OFFSET_H

#define SEQ_WR_CTL_D1_OFFSET 0U
//typedef struct _SEQ_WR_CTL_D1_FORMAT {
#define DAT_DLY_OFFSET 32U // : 4;
#define DQS_DLY_OFFSET 28U // : 4;
#define DQS_XTR_OFFSET 24U // : 1;
#define DAT_2Y_DLY_OFFSET 23U // : 1;
#define ADR_2Y_DLY_OFFSET 22U // : 1;
#define CMD_2Y_DLY_OFFSET 21U // : 1;
#define OEN_DLY_OFFSET 20U // : 4;
#define OEN_EXT_OFFSET 16U // : 4;
#define OEN_SEL_OFFSET 12U // : 2;
//#define Pad0_OFFSET 10U // : 2;
#define ODT_DLY_OFFSET 8U // : 4;
#define ODT_EXT_OFFSET 4U // : 1;
#define ADR_DLY_OFFSET 3U // : 1;
#define CMD_DLY_OFFSET 2U // : 1;
//#define Pad1_OFFSET 1U // : 1;
//} SEQ_WR_CTL_D1_FORMAT; // 4 bytes 

#define SEQ_WR_CTL_2_OFFSET 1U
//typedef struct _SEQ_WR_CTL_2_FORMAT {
#define DAT_DLY_H_D0_OFFSET 32U // : 1;
#define DQS_DLY_H_D0_OFFSET 31U // : 1;
#define OEN_DLY_H_D0_OFFSET 30U // : 1;
#define DAT_DLY_H_D1_OFFSET 29U // : 1;
#define DQS_DLY_H_D1_OFFSET 28U // : 1;
#define OEN_DLY_H_D1_OFFSET 27U // : 1;
#define WCDR_EN_OFFSET 26U // : 1;
//#define Pad0_OFFSET 25U // : 25;
//} SEQ_WR_CTL_2_FORMAT;  // 4 bytes

#define SEQ_PMG_TIMING_OFFSET_RX 2U
#define SEQ_PMG_TIMING_OFFSET_R9 6U
//typedef struct _SEQ_PMG_TIMING_FORMAT {
#define TCKSRE_OFFSET 32U // : 3;
//#define Pad0_OFFSET 29U // : 1;
#define TCKSRX_OFFSET 28U // : 3;
//#define Pad1_OFFSET 25U // : 1;
#define TCKE_PULSE_OFFSET 24U // : 4;
#define TCKE_OFFSET 20U // : 6;
#define SEQ_IDLE_OFFSET 14U // : 3;
//#define Pad2_OFFSET 11U // : 2;
#define TCKE_PULSE_MSB_OFFSET 9U // : 1;
#define SEQ_IDLE_SS_OFFSET 8U // : 8;
//} SEQ_PMG_TIMING_FORMAT; // 4 bytes

#define SEQ_RAS_TIMING_OFFSET_RX 3U
#define SEQ_RAS_TIMING_OFFSET_R9 2U
//typedef struct _SEQ_RAS_TIMING_FORMAT {
#define TRCDW_OFFSET 32U // : 5;
#define TRCDWA_OFFSET 27U // : 5;
#define TRCDR_OFFSET 22U // : 5;
#define TRCDRA_OFFSET 17U // : 5;
#define TRRD_OFFSET 12U // : 4;
#define TRC_OFFSET 8U // : 7;
//#define Pad0_OFFSET 1U // : 1;
//} SEQ_RAS_TIMING_FORMAT;  // 4 bytes

#define SEQ_CAS_TIMING_OFFSET_RX 4U
#define SEQ_CAS_TIMING_OFFSET_R9 3U
//typedef struct _SEQ_CAS_TIMING_FORMAT {
#define TNOPW_OFFSET 32U // : 2;
#define TNOPR_OFFSET 30U // : 2;
#define TR2W_OFFSET 28U // : 5;
#define TCCDL_OFFSET 23U // : 3;
#define TCCDS_OFFSET 20U // : 4;
#define TW2R_OFFSET 16U // : 5;
//#define Pad0_OFFSET 11U // : 3;
#define TCL_OFFSET 8U // : 5;
//#define Pad1_OFFSET 3U // : 3;
//} SEQ_CAS_TIMING_FORMAT; // 4 bytes

#define SEQ_MISC_TIMING_OFFSET_RX 5U
//typedef struct _SEQ_MISC_TIMING_FORMAT {
#define TRP_WRA_OFFSET 32U // : 7;
#define TRP_RDA_OFFSET_RX 25U // : 7;
#define TRP_OFFSET_RX 18U // : 6;
#define TRFC_OFFSET 12U // : 9;
//#define Pad0_OFFSET 3U // : 3;
//} SEQ_MISC_TIMING_FORMAT; // 4 bytes

#define SEQ_MISC_TIMING_OFFSET_R9 4U
//typedef struct _SEQ_MISC_TIMING_FORMAT_R9 {
//#define TRP_WRA_OFFSET 32U // : 8;
#define TRP_RDA_OFFSET_R9 24U // : 7;
#define TRP_OFFSET_R9 17U // : 5;
//#define TRFC_OFFSET 12U // : 9;
//#define Pad0_OFFSET 3U // : 3;
//} SEQ_MISC_TIMING_FORMAT_R9;

#define SEQ_MISC_TIMING2_OFFSET_RX 6U
#define SEQ_MISC_TIMING2_OFFSET_R9 5U
//typedef struct _SEQ_MISC_TIMING2_FORMAT {
#define PA2RDATA_OFFSET 32U // : 3;
//#define Pad0_OFFSET 29U // : 1;
#define PA2WDATA_OFFSET 28U // : 3;
//#define Pad1_OFFSET 25U // : 1;
#define TFAW_OFFSET 24U // : 5;
#define TCRCRL_OFFSET 19U // : 3;
#define TCRCWL_OFFSET 16U // : 5;
#define T32AW_OFFSET 11U // : 4;
//#define Pad2_OFFSET 7U // : 3;
#define TWDATATR_OFFSET 4U // : 4;
//} SEQ_MISC_TIMING2_FORMAT; // 4 bytes

#define SEQ_MISC1_OFFSET 7U
#define SEQ_MISC3_OFFSET 8U
#define SEQ_MISC8_OFFSET 9U

#define ARB_DRAM_TIMING_OFFSET 10U
//typedef struct _ARB_DRAM_TIMING_FORMAT {
#define ACTRD_OFFSET 32U // : 8;
#define ACTWR_OFFSET 24U // : 8;
#define RASMACTRD_OFFSET 16U // : 8;
#define RASMACTWR_OFFSET 8U // : 8;
//} ARB_DRAM_TIMING_FORMAT; // 4 bytes

#define ARB_DRAM_TIMING2_OFFSET 11U
//typedef struct _ARB_DRAM_TIMING2_FORMAT {
#define RAS2RAS_OFFSET 32U // : 8;
#define RP_OFFSET 24U // : 8;
#define WRPLUSRP_OFFSET 16U // : 8;
#define BUS_TURN_OFFSET 8U // : 8;
//} ARB_DRAM_TIMING2_FORMAT; // 4 bytes

#ifdef STRAP_R9
	#define SEQ_PMG_TIMING_OFFSET SEQ_PMG_TIMING_OFFSET_R9
	#define SEQ_RAS_TIMING_OFFSET SEQ_RAS_TIMING_OFFSET_R9
	#define SEQ_CAS_TIMING_OFFSET SEQ_CAS_TIMING_OFFSET_R9
	#define SEQ_MISC_TIMING_OFFSET SEQ_MISC_TIMING_OFFSET_R9
	#define TRP_RDA_OFFSET TRP_RDA_OFFSET_R9
	#define TRP_OFFSET TRP_OFFSET_R9
	#define SEQ_MISC_TIMING2_OFFSET SEQ_MISC_TIMING2_OFFSET_R9
#else
	#define SEQ_PMG_TIMING_OFFSET SEQ_PMG_TIMING_OFFSET_RX
	#define SEQ_RAS_TIMING_OFFSET SEQ_RAS_TIMING_OFFSET_RX
	#define SEQ_CAS_TIMING_OFFSET SEQ_CAS_TIMING_OFFSET_RX
	#define SEQ_MISC_TIMING_OFFSET SEQ_MISC_TIMING_OFFSET_RX
	#define TRP_RDA_OFFSET TRP_RDA_OFFSET_RX
	#define TRP_OFFSET TRP_OFFSET_RX
	#define SEQ_MISC_TIMING2_OFFSET SEQ_MISC_TIMING2_OFFSET_RX
#endif

#endif
