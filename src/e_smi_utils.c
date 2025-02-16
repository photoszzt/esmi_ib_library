/*
 * University of Illinois/NCSA Open Source License
 *
 * Copyright (c) 2020-22, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Developed by:
 *
 *                 AMD Research and AMD Software Development
 *
 *                 Advanced Micro Devices, Inc.
 *
 *                 www.amd.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimers.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimers in
 *    the documentation and/or other materials provided with the distribution.
 *  - Neither the names of <Name of Development Group, Name of Institution>,
 *    nor the names of its contributors may be used to endorse or promote
 *    products derived from this Software without specific prior written
 *    permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 *
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <e_smi/e_smi_utils.h>

int readsys_u32(char *filepath, uint32_t *pval)
{
	FILE *fptr;

	if (!(filepath && pval)) {
		return EFAULT;
	}
	fptr = fopen(filepath, "r");
	if (fptr == NULL) {
		return errno;
	}
	if (fscanf(fptr, "%u", pval) < 0) {
		fclose(fptr);
		return errno;
	}
	fclose(fptr);
	return 0;
}

int writesys_s32(char *filepath, int32_t val)
{
	FILE *fptr;

	if (NULL == filepath) {
		return EFAULT;
	}
	fptr = fopen(filepath, "w");
	if (fptr == NULL) {
		return errno;
	}
	if (fprintf(fptr, "%d", val) < 0) {
		fclose(fptr);
		return errno;
	}
	fclose(fptr);
	return 0;
}

int writesys_u32(char *filepath, uint32_t val)
{
	FILE *fptr;

	if (NULL == filepath) {
		return EFAULT;
	}
	fptr = fopen(filepath, "w");
	if (fptr == NULL) {
		return errno;
	}
	if (fprintf(fptr, "%u", val) < 0) {
		fclose(fptr);
		return errno;
	}
	fclose(fptr);
	return 0;
}

int readsys_u64(char *filepath, uint64_t *pval)
{
	FILE *fptr;

	if (!(filepath && pval)) {
		return EFAULT;
	}
	fptr = fopen(filepath, "r");
	if (fptr == NULL) {
		return errno;
	}
	if (fscanf(fptr, "%lu", pval) < 0) {
		fclose(fptr);
		return errno;
	}
	fclose(fptr);
	return 0;
}

int readsys_str(char *filepath, char *pval, uint32_t len)
{
	FILE *fptr;

	if (!(filepath && pval)) {
		return EFAULT;
	}
	fptr = fopen(filepath, "r");
	if (fptr == NULL) {
		return errno;
	}
	if (!fgets(pval, len, fptr)) {
		fclose(fptr);
		return errno;
	}
	fclose(fptr);
	return 0;
}

int readmsr_u64(char *filepath, uint64_t *pval, uint64_t reg)
{
	int fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return errno;

	if (pread(fd, pval, sizeof(uint64_t), reg) < 0) {
		close(fd);
		return errno;
	}
	close(fd);

	return 0;
}
