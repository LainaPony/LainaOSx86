#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>

#define VGA_WIDTH  640
#define VGA_HEIGHT 480
//surely your display supports 640 by 480 by now? no? get a better system then don't complain about the lack of 80 collum on your slow ass computer
#define VGA_MEM  0xB8000 
//as the title says this is vga bullshit 
enum vga_color_bullshit {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_PURPLE = 5,
	VGA_BROWN = 6,
	VGA_LGREY = 7,
	VGA_DGREY = 8,
	VGA_LBLUE = 9,
	VGA_LGREEN = 10,
	VGA_LCYAN = 11,
	VGA_LRED = 12,
	VGA_LPURPLE = 13,
	VGA_LBROWN = 14,
	VGA_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color_bullshit fg, enum vga_color_bullshit bg) 
{
	return fg | bg << 4;
}
static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
//waaa laina you stole from the OS Dev forum partly waaa. Yes. and i will do it again because i don't personally agree with vga text mode because why why use vga text mode firstly vga is shit its a technology that was designed for CRT Monitors keep in mind but for some reason despite CRT Monitors NO LONGER EXISTING we still use VGA ports and Standards when we very well could use better standards by now, but nooo the stupid morons making this shit thought oh lets keep using vga text mode for shit because some moron at MIT couldn't understand basic concepts so we get colors done like 0x07 and etc how hard is it to force people to use the better simpler system? i'd even be happier with D standards but nooo they want to backwards compatibility our asses and force us developers to also support low ass limit color text incase some utter retard decides to use a system that is somehow 64BIT yet dosen't support anything after 1998 how genuinely retarded does one need to be? that system DOSEN'T EXIST and your all retards for supporting it just incase some fucking stupid bitch ass time travels back in time and makes it exist

//genunlinely retarded >:!( 


size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEM;

//yknow what just because you complained in about it fuck face i'm stealing the entire vga thing because i read the code and its what i would do anyway 
//just because when you copy code you bumble around and don't learn doesn't mean others do
//the difference between me and the non-human retards is that when i steal code i actually read and understand it unlike them
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_WHITE, VGA_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

//good enough don't use vga if you want better
//or learn to code and fix it yourself, don't be retarded.
