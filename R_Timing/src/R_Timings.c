#include <stdio.h>
#include <string.h>
#include "timingsoffset.h"
#include "ohgodadecode.h"

#define RD_ONLY "r"
#define WR_ONLY "w"

#define SKIP_LINE "%*s"
#define GET_VALUE "%*s = %u"
#define GET_MISC_VALUE "%*s = 0x%08X"

#ifdef STRAP_R9
	#define R_MODE "R9"
#else
	#define R_MODE "RX"
#endif

const float basedOnVersion = 1.01;
const float version = 1.03;

void decode(uint8_t *buf, char *str) {
	char hHalf, lHalf;
	// str must contains only upper case hex character
	while (*str) {
		hHalf = *str - ((*str < 'A') ? '0' : 'A' - 10);
		++str;
		lHalf = *str - ((*str < 'A') ? '0' : 'A' - 10);
		++str;
		*buf = (hHalf << 4) | (lHalf & 0x0F); // is '& 0x0F' really necessary?
		++buf;
	}
}

void encode(uint8_t *buf) {
	char str[97];
	size_t buf_index, str_index = 0;
	for (buf_index = 0; buf_index < 48; ++buf_index) { // 96 hex character = 48 bytes
		str[str_index] = buf[buf_index] >> 4;
		str[str_index] += ((str[str_index] > 9) ? 'A' - 10 : '0');
		++str_index;
		str[str_index] = buf[buf_index] & 0x0F;
		str[str_index] += ((str[str_index] > 9) ? 'A' - 10 : '0');
		++str_index;
	}
	str[96] = '\0';
	printf("%s\n", str);
}

// str must contains only upper case hex character
int isHexString(char *str) {
	char c;
	while((c = *str)) {
		if (c < '0' || c > 'Z' || (c > '9' && c < 'A')) {
			return 0;
		}
		++str;
	}
	return 1;
}

char *toUpperCase(char *str) {
	char *tmp = str;
	char c;
	while((c = *tmp)) {
		if (c >= 'a' && c <= 'z') {
			*tmp = (c - 'a') + 'A';
		}
		++tmp;
	}
	return str;
}

int isTimingStrap(char *str) {
	return (strlen(str) == 96) && isHexString(toUpperCase(str));
}

int openFile(FILE **f, const char *path, const char *mode) {
	*f = fopen(path, mode);
	if (*f == NULL) {
		printf("Error opening file!\n");
		return 0;
	}
	return 1;
}

void writeTimings(FILE *f, VBIOS_STRAP *Timings) {
	// yes... yes... this looks bad... but who cares?
	fprintf(f, "####SEQ_WR_CTL_D1####\n");
	fprintf(f, "DAT_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.DAT_DLY);
	fprintf(f, "DQS_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.DQS_DLY);
	fprintf(f, "DQS_XTR = %u\n", Timings -> SEQ_WR_CTL_D1.DQS_XTR);
	fprintf(f, "DAT_2Y_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.DAT_2Y_DLY);
	fprintf(f, "ADR_2Y_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.ADR_2Y_DLY);
	fprintf(f, "CMD_2Y_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.CMD_2Y_DLY);
	fprintf(f, "OEN_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.OEN_DLY);
	fprintf(f, "OEN_EXT = %u\n", Timings -> SEQ_WR_CTL_D1.OEN_EXT);
	fprintf(f, "OEN_SEL = %u\n", Timings -> SEQ_WR_CTL_D1.OEN_SEL);
	fprintf(f, "ODT_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.ODT_DLY);
	fprintf(f, "ODT_EXT = %u\n", Timings -> SEQ_WR_CTL_D1.ODT_EXT);
	fprintf(f, "ADR_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.ADR_DLY);
	fprintf(f, "CMD_DLY = %u\n", Timings -> SEQ_WR_CTL_D1.CMD_DLY);
	fprintf(f, "####SEQ_WR_CTL_2####\n");
	fprintf(f, "DAT_DLY_H_D0 = %u\n", Timings -> SEQ_WR_CTL_2.DAT_DLY_H_D0);
	fprintf(f, "DQS_DLY_H_D0 = %u\n", Timings -> SEQ_WR_CTL_2.DQS_DLY_H_D0);
	fprintf(f, "OEN_DLY_H_D0 = %u\n", Timings -> SEQ_WR_CTL_2.OEN_DLY_H_D0);
	fprintf(f, "DAT_DLY_H_D1 = %u\n", Timings -> SEQ_WR_CTL_2.DAT_DLY_H_D1);
	fprintf(f, "DQS_DLY_H_D1 = %u\n", Timings -> SEQ_WR_CTL_2.DQS_DLY_H_D1);
	fprintf(f, "OEN_DLY_H_D1 = %u\n", Timings -> SEQ_WR_CTL_2.OEN_DLY_H_D1);
	fprintf(f, "WCDR_EN = %u\n", Timings -> SEQ_WR_CTL_2.WCDR_EN);
	fprintf(f, "####SEQ_PMG_TIMING####\n");
	fprintf(f, "TCKSRE = %u\n", Timings -> SEQ_PMG_TIMING.TCKSRE);
	fprintf(f, "TCKSRX = %u\n", Timings -> SEQ_PMG_TIMING.TCKSRX);
	fprintf(f, "TCKE_PULSE = %u\n", Timings -> SEQ_PMG_TIMING.TCKE_PULSE);
	fprintf(f, "TCKE = %u\n", Timings -> SEQ_PMG_TIMING.TCKE);
	fprintf(f, "SEQ_IDLE = %u\n", Timings -> SEQ_PMG_TIMING.SEQ_IDLE);
	fprintf(f, "TCKE_PULSE_MSB = %u\n", Timings -> SEQ_PMG_TIMING.TCKE_PULSE_MSB);
	fprintf(f, "SEQ_IDLE_SS = %u\n", Timings -> SEQ_PMG_TIMING.SEQ_IDLE_SS);
	fprintf(f, "####SEQ_RAS_TIMING####\n");
	fprintf(f, "TRCDW = %u\n", Timings -> SEQ_RAS_TIMING.TRCDW);
	fprintf(f, "TRCDWA = %u\n", Timings -> SEQ_RAS_TIMING.TRCDWA);
	fprintf(f, "TRCDR = %u\n", Timings -> SEQ_RAS_TIMING.TRCDR);
	fprintf(f, "TRCDRA = %u\n", Timings -> SEQ_RAS_TIMING.TRCDRA);
	fprintf(f, "TRRD = %u\n", Timings -> SEQ_RAS_TIMING.TRRD);
	fprintf(f, "TRC = %u\n", Timings -> SEQ_RAS_TIMING.TRC);
	fprintf(f, "####SEQ_CAS_TIMING####\n");
	fprintf(f, "TNOPW = %u\n", Timings -> SEQ_CAS_TIMING.TNOPW);
	fprintf(f, "TNOPR = %u\n", Timings -> SEQ_CAS_TIMING.TNOPR);
	fprintf(f, "TR2W = %u\n", Timings -> SEQ_CAS_TIMING.TR2W);
	fprintf(f, "TCCDL = %u\n", Timings -> SEQ_CAS_TIMING.TCCDL);
	fprintf(f, "TCCDS = %u\n", Timings -> SEQ_CAS_TIMING.TCCDS);
	fprintf(f, "TW2R = %u\n", Timings -> SEQ_CAS_TIMING.TW2R);
	fprintf(f, "TCL = %u\n", Timings -> SEQ_CAS_TIMING.TCL);
	fprintf(f, "####SEQ_MISC_TIMING####\n");
	fprintf(f, "TRP_WRA = %u\n", Timings -> SEQ_MISC_TIMING.TRP_WRA);
	fprintf(f, "TRP_RDA = %u\n", Timings -> SEQ_MISC_TIMING.TRP_RDA);
	fprintf(f, "TRP = %u\n", Timings -> SEQ_MISC_TIMING.TRP);
	fprintf(f, "TRFC = %u\n", Timings -> SEQ_MISC_TIMING.TRFC);
	fprintf(f, "####SEQ_MISC_TIMING2####\n");
	fprintf(f, "PA2RDATA = %u\n", Timings -> SEQ_MISC_TIMING2.PA2RDATA);
	fprintf(f, "PA2WDATA = %u\n", Timings -> SEQ_MISC_TIMING2.PA2WDATA);
	fprintf(f, "TFAW = %u\n", Timings -> SEQ_MISC_TIMING2.TFAW);
	fprintf(f, "TCRCRL = %u\n", Timings -> SEQ_MISC_TIMING2.TCRCRL);
	fprintf(f, "TCRCWL = %u\n", Timings -> SEQ_MISC_TIMING2.TCRCWL);
	fprintf(f, "T32AW = %u\n", Timings -> SEQ_MISC_TIMING2.T32AW);
	fprintf(f, "TWDATATR = %u\n", Timings -> SEQ_MISC_TIMING2.TWDATATR);
	fprintf(f, "####ARB_DRAM_TIMING####\n");
	fprintf(f, "ACTRD = %u\n", Timings -> ARB_DRAM_TIMING.ACTRD);
	fprintf(f, "ACTWR = %u\n", Timings -> ARB_DRAM_TIMING.ACTWR);
	fprintf(f, "RASMACTRD = %u\n", Timings -> ARB_DRAM_TIMING.RASMACTRD);
	fprintf(f, "RASMACTWR = %u\n", Timings -> ARB_DRAM_TIMING.RASMACTWR);
	fprintf(f, "####ARB_DRAM_TIMING2####\n");
	fprintf(f, "RAS2RAS = %u\n", Timings -> ARB_DRAM_TIMING2.RAS2RAS);
	fprintf(f, "RP = %u\n", Timings -> ARB_DRAM_TIMING2.RP);
	fprintf(f, "WRPLUSRP = %u\n", Timings -> ARB_DRAM_TIMING2.WRPLUSRP);
	fprintf(f, "BUS_TURN = %u\n", Timings -> ARB_DRAM_TIMING2.BUS_TURN);
	fprintf(f, "####MC_SEQ_MISC####\n");
	fprintf(f, "MC_SEQ_MISC1 = 0x%08X\n", Timings -> SEQ_MISC1);
	fprintf(f, "MC_SEQ_MISC3 = 0x%08X\n", Timings -> SEQ_MISC3);
	fprintf(f, "MC_SEQ_MISC8 = 0x%08X", Timings -> SEQ_MISC8);
}

void readValue(FILE *f, uint32_t *buf, const char *format_str, size_t buf_index, size_t shift) {
	unsigned int current;
	fscanf(f, format_str, &current);
	buf[buf_index] |= (current << (32U - shift));
}

void readTimings(FILE *f, uint32_t *buf) {
	// yes... yes... this also looks bad...
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, DAT_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, DQS_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, DQS_XTR_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, DAT_2Y_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, ADR_2Y_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, CMD_2Y_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, OEN_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, OEN_EXT_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, OEN_SEL_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, ODT_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, ODT_EXT_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, ADR_DLY_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_D1_OFFSET, CMD_DLY_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, DAT_DLY_H_D0_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, DQS_DLY_H_D0_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, OEN_DLY_H_D0_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, DAT_DLY_H_D1_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, DQS_DLY_H_D1_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, OEN_DLY_H_D1_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_WR_CTL_2_OFFSET, WCDR_EN_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, TCKSRE_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, TCKSRX_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, TCKE_PULSE_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, TCKE_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, SEQ_IDLE_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, TCKE_PULSE_MSB_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_PMG_TIMING_OFFSET, SEQ_IDLE_SS_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_RAS_TIMING_OFFSET, TRCDW_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_RAS_TIMING_OFFSET, TRCDWA_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_RAS_TIMING_OFFSET, TRCDR_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_RAS_TIMING_OFFSET, TRCDRA_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_RAS_TIMING_OFFSET, TRRD_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_RAS_TIMING_OFFSET, TRC_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TNOPW_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TNOPR_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TR2W_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TCCDL_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TCCDS_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TW2R_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_CAS_TIMING_OFFSET, TCL_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING_OFFSET, TRP_WRA_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING_OFFSET, TRP_RDA_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING_OFFSET, TRP_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING_OFFSET, TRFC_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, PA2RDATA_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, PA2WDATA_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, TFAW_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, TCRCRL_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, TCRCWL_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, T32AW_OFFSET);
	readValue(f, buf, GET_VALUE, SEQ_MISC_TIMING2_OFFSET, TWDATATR_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING_OFFSET, ACTRD_OFFSET);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING_OFFSET, ACTWR_OFFSET);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING_OFFSET, RASMACTRD_OFFSET);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING_OFFSET, RASMACTWR_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING2_OFFSET, RAS2RAS_OFFSET);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING2_OFFSET, RP_OFFSET);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING2_OFFSET, WRPLUSRP_OFFSET);
	readValue(f, buf, GET_VALUE, ARB_DRAM_TIMING2_OFFSET, BUS_TURN_OFFSET);
	fscanf(f, SKIP_LINE);
	readValue(f, buf, GET_MISC_VALUE, SEQ_MISC1_OFFSET, 32U);
	readValue(f, buf, GET_MISC_VALUE, SEQ_MISC3_OFFSET, 32U);
	readValue(f, buf, GET_MISC_VALUE, SEQ_MISC8_OFFSET, 32U);
}

int main(int argc, char **argv) {
	
	FILE *f;
	uint32_t buf[12] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
	VBIOS_STRAP *Timings = (VBIOS_STRAP *) buf;
	
	if (argc == 3 && isTimingStrap(argv[1]) && openFile(&f, argv[2], WR_ONLY) ) {
		// argv[0] <96-char hex string> <output file>
		decode((uint8_t *) buf, argv[1]);
		writeTimings(f, Timings);
	} else if (argc == 2 && openFile(&f, argv[1], RD_ONLY) ) {
		// argv[0] <input file>
		readTimings(f, buf);
		encode((uint8_t *) buf);
	} else {
		printf("\nR_Timings v%.02f by Vento - [%s Timings Mode]\n", version, R_MODE);
		printf("Based on OhGodADecode v%.02f by OhGodACompany - OhGodAGirl & OhGodAPet\n", basedOnVersion);
		printf("Decode with: %s <96-char hex string> <output file>\n", argv[0]);
		printf("Encode with: %s <input file>\n", argv[0]);
		return 1;
	}
	
	fclose(f);
	
	return 0;
}
