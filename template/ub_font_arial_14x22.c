//--------------------------------------------------------------
// File     : ub_Font_Arial_7x10.c
// Datum    : 18.02.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
//
// Font-Settings : Monospace, Max-Width=16Pixel
// Ascii-Table   : First-Char = 32, Last-Char = 126
// Data-Layout   :
//        e.G. Ascii-'R'
//       "0x78,0x44,0x44,0x44,0x78,0x48,0x48,0x44,0x00,0x00"
//
//   0x78 = ".####..."
//   0x44 = ".#...#.."
//   0x44 = ".#...#.."
//   0x44 = ".#...#.."
//   0x78 = ".####..."
//   0x48 = ".#  #..."
//   0x48 = ".#  #..."
//   0x44 = ".#...#.."
//   0x00 = "........"
//   0x00 = "........"
//
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "st7789_240_240.h"
//--------------------------------------------------------------
// Font-Daten
// erstellt von UB mit PixelFontGenerator 1.0
//--------------------------------------------------------------

uint16_t Arial_14x22_Table [] =
#if 0
	{};
#else
{
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [ ]
0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [!]
0x0CC0,0x0CC0,0x0CC0,0x0CC0,0x0CC0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = ["]
0x0660,0x0660,0x0660,0x0660,0x0660,0x3FF0,0x3FF0,0x0CC0,0x0CC0,0x0CC0,0x3FF0,0x3FF0,0x1980,0x1980,0x1980,0x1980,0x1980,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [#]
0x07C0,0x1FE0,0x3960,0x3130,0x3130,0x3100,0x1900,0x1F80,0x07E0,0x0170,0x0130,0x3130,0x3130,0x3930,0x1D60,0x0FE0,0x07C0,0x0100,0x0100,0x0000,0x0000,0x0000, // Ascii = [$]
0x1C00,0x3600,0x6308,0x6318,0x6330,0x6360,0x36C0,0x1D80,0x0300,0x06E0,0x0DB0,0x1B18,0x3318,0x2318,0x0318,0x01B0,0x00E0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [%]
0x0700,0x0F80,0x18C0,0x18C0,0x18C0,0x1980,0x0F80,0x0F00,0x1E00,0x3318,0x61B8,0x61F0,0x60F0,0x6060,0x71F0,0x3FB8,0x1F10,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [&]
0x0300,0x0300,0x0300,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [']
0x0060,0x00C0,0x0180,0x0180,0x0300,0x0300,0x0300,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0300,0x0300,0x0300,0x0180,0x0180,0x00C0,0x0060, // Ascii = [(]
0x1800,0x0C00,0x0600,0x0600,0x0300,0x0300,0x0300,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0300,0x0300,0x0300,0x0600,0x0600,0x0C00,0x1800, // Ascii = [)]
0x0300,0x0300,0x1B60,0x1FE0,0x0300,0x0480,0x0CC0,0x0480,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [*]
0x0000,0x0000,0x0000,0x0300,0x0300,0x0300,0x0300,0x0300,0x7FF8,0x7FF8,0x0300,0x0300,0x0300,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [+]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0100,0x0100,0x0200,0x0000,0x0000, // Ascii = [,]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0FC0,0x0FC0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [-]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [.]
0x0060,0x0060,0x00C0,0x00C0,0x00C0,0x0180,0x0180,0x0180,0x0380,0x0300,0x0300,0x0300,0x0600,0x0600,0x0600,0x0C00,0x0C00,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [/]
0x0780,0x0FC0,0x1CE0,0x1860,0x3030,0x3030,0x3030,0x3330,0x3330,0x3030,0x3030,0x3030,0x3030,0x1860,0x1CE0,0x0FC0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [0]
0x0180,0x0180,0x0380,0x0F80,0x1D80,0x1180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [1]
0x07C0,0x1FE0,0x1860,0x3030,0x3030,0x0030,0x0030,0x0060,0x0060,0x00C0,0x0180,0x0700,0x0C00,0x1800,0x3000,0x3FF0,0x3FF0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [2]
0x0F80,0x1FC0,0x18E0,0x3060,0x3060,0x0060,0x00C0,0x07C0,0x07C0,0x0060,0x0030,0x0030,0x3030,0x3030,0x1860,0x1FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [3]
0x00C0,0x01C0,0x01C0,0x03C0,0x03C0,0x06C0,0x0CC0,0x0CC0,0x18C0,0x18C0,0x30C0,0x3FF0,0x3FF0,0x00C0,0x00C0,0x00C0,0x00C0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [4]
0x3FE0,0x3FE0,0x3000,0x3000,0x3000,0x3780,0x3FC0,0x3860,0x3070,0x0030,0x0030,0x0030,0x3030,0x3070,0x18E0,0x1FC0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [5]
0x07C0,0x0FE0,0x1C70,0x1830,0x3800,0x3000,0x33C0,0x37E0,0x3860,0x3030,0x3030,0x3030,0x3030,0x1870,0x1860,0x0FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [6]
0x3FF0,0x3FF0,0x0030,0x0060,0x00C0,0x00C0,0x0180,0x0180,0x0300,0x0300,0x0600,0x0600,0x0600,0x0400,0x0C00,0x0C00,0x0C00,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [7]
0x0780,0x0FC0,0x1CE0,0x1860,0x1860,0x1860,0x0CC0,0x0300,0x1FC0,0x1860,0x3030,0x3030,0x3030,0x3030,0x1860,0x1FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [8]
0x0780,0x1FC0,0x1C60,0x3820,0x3030,0x3030,0x3030,0x3030,0x1870,0x1FB0,0x0F30,0x0030,0x0070,0x3060,0x38E0,0x1FC0,0x0F80,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [9]
0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [:]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0300,0x0300,0x0100,0x0100,0x0200,0x0000,0x0000, // Ascii = [;]
0x0000,0x0000,0x0000,0x0010,0x0070,0x01C0,0x0700,0x1C00,0x3000,0x1C00,0x0700,0x01C0,0x0070,0x0010,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [<]
0x0000,0x0000,0x0000,0x0000,0x0000,0x3FF0,0x3FF0,0x0000,0x0000,0x0000,0x3FF0,0x3FF0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [=]
0x0000,0x0000,0x0000,0x2000,0x3800,0x0E00,0x0380,0x00E0,0x0030,0x00E0,0x0380,0x0E00,0x3800,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [>]
0x0780,0x1FE0,0x1870,0x3030,0x3030,0x0030,0x0070,0x00E0,0x01C0,0x0180,0x0300,0x0300,0x0300,0x0000,0x0000,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [?]
0x07C0,0x0FE0,0x1C60,0x1830,0x3830,0x30F0,0x33F0,0x3630,0x3630,0x37F0,0x33B0,0x3000,0x3800,0x1800,0x1C40,0x0FC0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [@]
0x0700,0x0700,0x0D80,0x0D80,0x0D80,0x18C0,0x18C0,0x18C0,0x3060,0x3060,0x3FE0,0x3FE0,0x6030,0x6030,0x6030,0xC018,0xC018,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [A]
0x3FC0,0x3FE0,0x3070,0x3030,0x3030,0x3030,0x3060,0x3FC0,0x3FE0,0x3030,0x3018,0x3018,0x3018,0x3018,0x3030,0x3FF0,0x3FC0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [B]
0x07C0,0x1FE0,0x3830,0x3018,0x3018,0x6000,0x6000,0x6000,0x6000,0x6000,0x6000,0x6000,0x6018,0x3018,0x3830,0x1FE0,0x07C0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [C]
0x3F80,0x3FE0,0x30F0,0x3030,0x3030,0x3018,0x3018,0x3018,0x3018,0x3018,0x3018,0x3018,0x3030,0x3030,0x30E0,0x3FC0,0x3F80,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [D]
0x3FF8,0x3FF8,0x3000,0x3000,0x3000,0x3000,0x3000,0x3FF0,0x3FF0,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3FF8,0x3FF8,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [E]
0x3FF8,0x3FF8,0x3000,0x3000,0x3000,0x3000,0x3000,0x3FF0,0x3FF0,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [F]
0x07C0,0x1FF0,0x3838,0x3018,0x3000,0x6000,0x6000,0x6000,0x61F8,0x61F8,0x6018,0x6018,0x7018,0x3018,0x3838,0x1FF0,0x07C0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [G]
0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3FF0,0x3FF0,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [H]
0x1FE0,0x1FE0,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x1FE0,0x1FE0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [I]
0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x0030,0x6030,0x6070,0x3060,0x3FC0,0x0F80,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [J]
0x3018,0x3030,0x3060,0x30C0,0x3180,0x3180,0x3300,0x3600,0x3F00,0x3B00,0x3180,0x30C0,0x30C0,0x3060,0x3030,0x3030,0x3018,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [K]
0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3FF8,0x3FF8,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [L]
0x7070,0x7070,0x70F0,0x78F0,0x68B0,0x6DB0,0x6530,0x6730,0x6230,0x6230,0x6030,0x6030,0x6030,0x6030,0x6030,0x6030,0x6030,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [M]
0x3830,0x3830,0x3C30,0x3C30,0x3C30,0x3630,0x3630,0x3730,0x3330,0x33B0,0x31B0,0x31B0,0x30F0,0x30F0,0x30F0,0x3070,0x3070,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [N]
0x0FC0,0x1FE0,0x3870,0x3030,0x7038,0x6018,0x6018,0x6018,0x6018,0x6018,0x6018,0x6018,0x6030,0x3030,0x3870,0x1FE0,0x0F80,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [O]
0x3FC0,0x3FF0,0x3030,0x3018,0x3018,0x3018,0x3018,0x3030,0x3FF0,0x3FC0,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [P]
0x0FC0,0x1FE0,0x3870,0x3030,0x7038,0x6018,0x6018,0x6018,0x6018,0x6018,0x6018,0x6018,0x6130,0x31F0,0x3860,0x1FF8,0x0F90,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [Q]
0x3FC0,0x3FF0,0x3030,0x3018,0x3018,0x3018,0x3018,0x3030,0x3FF0,0x3FC0,0x3180,0x30C0,0x3060,0x3060,0x3030,0x3030,0x3018,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [R]
0x0F80,0x1FE0,0x3860,0x3030,0x3030,0x3000,0x3C00,0x1F80,0x07E0,0x0070,0x0038,0x0018,0x6018,0x6018,0x3830,0x1FF0,0x0FC0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [S]
0x7FF8,0x7FF8,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [T]
0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x1860,0x1FE0,0x0F80,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [U]
0xC018,0xC018,0x6030,0x6030,0x6030,0x3060,0x3060,0x3060,0x18C0,0x18C0,0x18C0,0x0D80,0x0D80,0x0D80,0x0700,0x0700,0x0700,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [V]
0xC018,0xC018,0xC018,0xC018,0xC018,0xE230,0x6330,0x6730,0x6730,0x6530,0x6DB0,0x6DB0,0x68A0,0x38E0,0x38E0,0x3060,0x3060,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [W]
0xC018,0x6030,0x6070,0x3060,0x18C0,0x1D80,0x0D80,0x0700,0x0700,0x0700,0x0F80,0x1DC0,0x18C0,0x3060,0x7030,0x6030,0xC018,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [X]
0x6018,0x3030,0x3030,0x1860,0x1860,0x0CC0,0x0CC0,0x0780,0x0780,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [Y]
0x3FF0,0x3FF0,0x0030,0x0060,0x00C0,0x01C0,0x0180,0x0300,0x0700,0x0600,0x0C00,0x1800,0x1800,0x3000,0x6000,0x7FF8,0x7FF8,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [Z]
0x03E0,0x03E0,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x03E0,0x03E0, // Ascii = [[]
0x1800,0x1800,0x0C00,0x0C00,0x0C00,0x0600,0x0600,0x0600,0x0700,0x0300,0x0300,0x0300,0x0180,0x0180,0x0180,0x00C0,0x00C0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [\]
0x1F00,0x1F00,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x1F00,0x1F00, // Ascii = []]
0x0300,0x0780,0x0780,0x0CC0,0x0CC0,0x1860,0x1860,0x3030,0x3030,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [^]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFFFC,0x0000,0x0000, // Ascii = [_]
0x0E00,0x0600,0x0300,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [`]
0x0000,0x0000,0x0000,0x0000,0x0FC0,0x1FE0,0x3870,0x3030,0x0030,0x03F0,0x1FF0,0x3C30,0x3030,0x3070,0x38F0,0x1FB0,0x0F18,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [a]
0x3000,0x3000,0x3000,0x3000,0x3780,0x37C0,0x3C60,0x3870,0x3030,0x3030,0x3030,0x3030,0x3030,0x3870,0x3CE0,0x3FC0,0x3780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [b]
0x0000,0x0000,0x0000,0x0000,0x07C0,0x0FE0,0x1C70,0x3830,0x3000,0x3000,0x3000,0x3000,0x3030,0x3830,0x1C60,0x0FE0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [c]
0x0030,0x0030,0x0030,0x0030,0x07B0,0x0FB0,0x1870,0x3870,0x3030,0x3030,0x3030,0x3030,0x3030,0x3870,0x1C70,0x0FF0,0x07B0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [d]
0x0000,0x0000,0x0000,0x0000,0x0780,0x0FE0,0x1860,0x3030,0x3030,0x3FF0,0x3FF0,0x3000,0x3000,0x3830,0x1C70,0x0FE0,0x07C0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [e]
0x03F0,0x07F0,0x0600,0x0600,0x3FE0,0x3FE0,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [f]
0x0000,0x0000,0x0000,0x0000,0x07B0,0x0FF0,0x18F0,0x3870,0x3030,0x3030,0x3030,0x3030,0x3030,0x3870,0x18F0,0x0FB0,0x0730,0x0030,0x3030,0x3860,0x1FE0,0x0F80, // Ascii = [g]
0x3000,0x3000,0x3000,0x3000,0x33C0,0x3FE0,0x3C70,0x3830,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [h]
0x0180,0x0180,0x0000,0x0000,0x1F80,0x1F80,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [i]
0x0180,0x0180,0x0000,0x0000,0x1F80,0x1F80,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x2180,0x3F00,0x1E00, // Ascii = [j]
0x3000,0x3000,0x3000,0x3000,0x3060,0x30C0,0x3180,0x3300,0x3600,0x3F00,0x3980,0x3180,0x30C0,0x3060,0x3060,0x3030,0x3018,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [k]
0x1F80,0x1F80,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0180,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [l]
0x0000,0x0000,0x0000,0x0000,0x6E70,0x7FF8,0x7398,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [m]
0x0000,0x0000,0x0000,0x0000,0x33C0,0x3FE0,0x3C70,0x3830,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [n]
0x0000,0x0000,0x0000,0x0000,0x0780,0x0FC0,0x1860,0x3870,0x3030,0x3030,0x3030,0x3030,0x3030,0x3870,0x1860,0x0FC0,0x0780,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [o]
0x0000,0x0000,0x0000,0x0000,0x3780,0x37E0,0x3C60,0x3870,0x3030,0x3030,0x3030,0x3030,0x3030,0x3870,0x38E0,0x3FC0,0x3780,0x3000,0x3000,0x3000,0x3000,0x3000, // Ascii = [p]
0x0000,0x0000,0x0000,0x0000,0x0730,0x1FB0,0x18F0,0x3870,0x3030,0x3030,0x3030,0x3030,0x3030,0x3870,0x1C70,0x0FB0,0x07B0,0x0030,0x0030,0x0030,0x0030,0x0030, // Ascii = [q]
0x0000,0x0000,0x0000,0x0000,0x31C0,0x1BE0,0x1C70,0x1820,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x1800,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [r]
0x0000,0x0000,0x0000,0x0000,0x0FC0,0x1FE0,0x3870,0x3030,0x3800,0x1F00,0x0FE0,0x00F0,0x0030,0x3030,0x3870,0x1FE0,0x0FC0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [s]
0x0200,0x0600,0x0600,0x0600,0x3FE0,0x3FE0,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0600,0x0700,0x03F0,0x01F0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [t]
0x0000,0x0000,0x0000,0x0000,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3030,0x3070,0x38F0,0x1FF0,0x0F30,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [u]
0x0000,0x0000,0x0000,0x0000,0x3018,0x1830,0x1830,0x1830,0x0C60,0x0C60,0x0C60,0x06C0,0x06C0,0x06C0,0x0380,0x0380,0x0380,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [v]
0x0000,0x0000,0x0000,0x0000,0xC718,0xC718,0xC718,0xC718,0x6DB0,0x6DB0,0x6DB0,0x6DB0,0x6DB0,0x7DF0,0x38E0,0x38E0,0x38E0,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [w]
0x0000,0x0000,0x0000,0x0000,0x3030,0x1860,0x1860,0x0CC0,0x0780,0x0300,0x0300,0x0300,0x0780,0x0CC0,0x1860,0x1860,0x3030,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [x]
0x0000,0x0000,0x0000,0x0000,0x3030,0x3030,0x1870,0x1860,0x1860,0x0C60,0x0CE0,0x0EC0,0x06C0,0x06C0,0x0380,0x0380,0x0380,0x0380,0x0300,0x0700,0x1E00,0x1C00, // Ascii = [y]
0x0000,0x0000,0x0000,0x0000,0x3FF8,0x3FF8,0x0018,0x0030,0x0060,0x00C0,0x0180,0x0300,0x0600,0x0C00,0x1800,0x3FF8,0x3FF8,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [z]
0x01C0,0x03C0,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0600,0x0C00,0x0C00,0x0600,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x03C0,0x01C0, // Ascii = [{]
0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300, // Ascii = [|]
0x0E00,0x0F00,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0180,0x00C0,0x00C0,0x0180,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0F00,0x0E00, // Ascii = [}]
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x1C00,0x3F10,0x23F0,0x00E0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, // Ascii = [~]
};
#endif
