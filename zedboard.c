#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>

#include "zedboard.h"
#include "eval.h"
#include "token.h"

const unsigned gpio_address = 0x400d0000;
const unsigned gpio_size = 0xff;

const int gpio_led0_offset = 0x12C;
const int gpio_led1_offset = 0x130;
const int gpio_led2_offset = 0x134;
const int gpio_led3_offset = 0x138;
const int gpio_led4_offset = 0x13C;
const int gpio_led5_offset = 0x140;
const int gpio_led6_offset = 0x144;
const int gpio_led7_offset = 0x148;

const int gpio_sw0_offset = 0x14C;
const int gpio_sw1_offset = 0x150;
const int gpio_sw2_offset = 0x154;
const int gpio_sw3_offset = 0x158;
const int gpio_sw4_offset = 0x15C;
const int gpio_sw5_offset = 0x160;
const int gpio_sw6_offset = 0x164;
const int gpio_sw7_offset = 0x168;

static
void
writeLED(char *pBase, int value)
{
    assert(value == 0 || value == 1);
    *(int*)(pBase + gpio_led0_offset) = value;
}

static
int
readSwitch(char* pBase, int nn)
{
    assert(nn >= 0 && nn <= 7);
    int val = *(int*)(pBase + 0x14C + (4 * nn));
    assert(val == 0 || val == 1);
    return val;
}

static
char*
readInput(char* pBase)
{
    char buf[8];
    for (int ii = 0; ii < 8; ii++) {
        buf[ii] = readSwitch(pBase, ii) + '0';
    }
    printf("%s\n", buf);
    return &buf;
}

void
zedboard(sexp_ast* ast)
{
    int fd = open("/dev/mem", O_RDWR);
    char* pBase = (char*)mmap(0, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    assert(pBase != MAP_FAILED);

    while(1) {
        char* input = readInput(pBase);
        int ans = evaluate(ast, input);
        writeLED(pBase, ans);
    }

    munmap(pBase, gpio_size);
    close(fd);
}