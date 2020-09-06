////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#ifndef __CONST__
#define __CONST__
#include "definitions.h"

enum MagicEffect_t
{
	MAGIC_EFFECT_DRAW_BLOOD	= 0x00,
	MAGIC_EFFECT_LOSE_ENERGY	= 0x01,
	MAGIC_EFFECT_POFF		= 0x02,
	MAGIC_EFFECT_BLOCKHIT		= 0x03,
	MAGIC_EFFECT_EXPLOSION_AREA	= 0x04,
	MAGIC_EFFECT_EXPLOSION_DAMAGE	= 0x05,
	MAGIC_EFFECT_FIRE_AREA		= 0x06,
	MAGIC_EFFECT_YELLOW_RINGS	= 0x07,
	MAGIC_EFFECT_POISON_RINGS	= 0x08,
	MAGIC_EFFECT_HIT_AREA		= 0x09,
	MAGIC_EFFECT_TELEPORT		= 0x0A, //10
	MAGIC_EFFECT_ENERGY_DAMAGE	= 0x0B, //11
	MAGIC_EFFECT_WRAPS_BLUE	= 0x0C, //12
	MAGIC_EFFECT_WRAPS_RED	= 0x0D, //13
	MAGIC_EFFECT_WRAPS_GREEN	= 0x0E, //14
	MAGIC_EFFECT_HITBY_FIRE	= 0x0F, //15
	MAGIC_EFFECT_POISON		= 0x10, //16
	MAGIC_EFFECT_MORT_AREA		= 0x11, //17
	MAGIC_EFFECT_SOUND_GREEN	= 0x12, //18
	MAGIC_EFFECT_SOUND_RED		= 0x13, //19
	MAGIC_EFFECT_POISON_AREA	= 0x14, //20
	MAGIC_EFFECT_SOUND_YELLOW	= 0x15, //21
	MAGIC_EFFECT_SOUND_PURPLE	= 0x16, //22
	MAGIC_EFFECT_SOUND_BLUE	= 0x17, //23
	MAGIC_EFFECT_SOUND_WHITE	= 0x18, //24
	MAGIC_EFFECT_BUBBLES		= 0x19, //25
	MAGIC_EFFECT_CRAPS		= 0x1A, //26
	MAGIC_EFFECT_GIFT_WRAPS	= 0x1B, //27
	MAGIC_EFFECT_FIREWORK_YELLOW	= 0x1C, //28
	MAGIC_EFFECT_FIREWORK_RED	= 0x1D, //29
	MAGIC_EFFECT_FIREWORK_BLUE	= 0x1E, //30
	MAGIC_EFFECT_STUN		= 0x1F, //31
	MAGIC_EFFECT_SLEEP		= 0x20, //32
	MAGIC_EFFECT_WATERCREATURE	= 0x21, //33
	MAGIC_EFFECT_GROUNDSHAKER	= 0x22, //34
	MAGIC_EFFECT_HEARTS		= 0x23, //35
	MAGIC_EFFECT_FIREATTACK	= 0x24, //36
	MAGIC_EFFECT_ENERGY_AREA	= 0x25, //37
	MAGIC_EFFECT_SMALLCLOUDS	= 0x26, //38
	MAGIC_EFFECT_HOLYDAMAGE	= 0x27, //39
	MAGIC_EFFECT_BIGCLOUDS		= 0x28, //40
	MAGIC_EFFECT_ICEAREA		= 0x29, //41
	MAGIC_EFFECT_ICETORNADO	= 0x2A, //42
	MAGIC_EFFECT_ICEATTACK		= 0x2B, //43
	MAGIC_EFFECT_STONES		= 0x2C, //44
	MAGIC_EFFECT_SMALLPLANTS	= 0x2D, //45
	MAGIC_EFFECT_CARNIPHILA	= 0x2E, //46
	MAGIC_EFFECT_PURPLEENERGY	= 0x2F, //47
	MAGIC_EFFECT_YELLOWENERGY	= 0x30, //48
	MAGIC_EFFECT_HOLYAREA		= 0x31, //49
	MAGIC_EFFECT_BIGPLANTS		= 0x32, //50
	MAGIC_EFFECT_CAKE		= 0x33, //51
	MAGIC_EFFECT_GIANTICE		= 0x34, //52
	MAGIC_EFFECT_WATERSPLASH	= 0x35, //53
	MAGIC_EFFECT_PLANTATTACK	= 0x36, //54
	MAGIC_EFFECT_TUTORIALARROW	= 0x37, //55
	MAGIC_EFFECT_TUTORIALSQUARE	= 0x38, //56
	MAGIC_EFFECT_MIRRORHORIZONTAL	= 0x39, //57
	MAGIC_EFFECT_MIRRORVERTICAL	= 0x3A, //58
	MAGIC_EFFECT_SKULLHORIZONTAL	= 0x3B, //59
	MAGIC_EFFECT_SKULLVERTICAL	= 0x3C, //60
	MAGIC_EFFECT_ASSASSIN		= 0x3D, //61
	MAGIC_EFFECT_STEPSHORIZONTAL	= 0x3E, //62
	MAGIC_EFFECT_BLOODYSTEPS	= 0x3F, //63
	MAGIC_EFFECT_STEPSVERTICAL	= 0x40, //64
	MAGIC_EFFECT_YALAHARIGHOST	= 0x41, //65
	MAGIC_EFFECT_BATS		= 0x42, //66
	MAGIC_EFFECT_SMOKE		= 0x43, //67
	MAGIC_EFFECT_INSECTS		= 0x44, //68
	MAGIC_EFFECT_DRAGONHEAD		= 0x45, //69
	MAGIC_EFFECT_70 = 0x46, //70
	MAGIC_EFFECT_71 = 0x47, //71
	MAGIC_EFFECT_72 = 0x48, //72
	MAGIC_EFFECT_73 = 0x49, //73...
	MAGIC_EFFECT_74 = 0x4A,
	MAGIC_EFFECT_75 = 0x4B,
	MAGIC_EFFECT_76 = 0x4C,
	MAGIC_EFFECT_77 = 0x4D,
	MAGIC_EFFECT_78 = 0x4E,
	MAGIC_EFFECT_79 = 0x4F,
	MAGIC_EFFECT_80 = 0x50,
	MAGIC_EFFECT_81 = 0x51,
	MAGIC_EFFECT_82 = 0x52,
	MAGIC_EFFECT_83 = 0x53,
	MAGIC_EFFECT_84 = 0x54,
	MAGIC_EFFECT_85 = 0x55,
	MAGIC_EFFECT_86 = 0x56,
	MAGIC_EFFECT_87 = 0x57,
	MAGIC_EFFECT_88 = 0x58,
	MAGIC_EFFECT_89 = 0x59,
	MAGIC_EFFECT_90 = 0x5A,
	MAGIC_EFFECT_91 = 0x5B,
	MAGIC_EFFECT_92 = 0x5C,
	MAGIC_EFFECT_93 = 0x5D,
	MAGIC_EFFECT_94 = 0x5E,
	MAGIC_EFFECT_95 = 0x5F,
	MAGIC_EFFECT_96 = 0x60,
	MAGIC_EFFECT_97 = 0x61,
	MAGIC_EFFECT_98 = 0x62,
	MAGIC_EFFECT_99 = 0x63,
	MAGIC_EFFECT_100 = 0x64,
	MAGIC_EFFECT_101 = 0x65,
	MAGIC_EFFECT_102 = 0x66,
	MAGIC_EFFECT_103 = 0x67,
	MAGIC_EFFECT_104 = 0x68,
	MAGIC_EFFECT_105 = 0x69,
	MAGIC_EFFECT_106 = 0x6A,
	MAGIC_EFFECT_107 = 0x6B,
	MAGIC_EFFECT_108 = 0x6C,
	MAGIC_EFFECT_109 = 0x6D,
	MAGIC_EFFECT_110 = 0x6E,
	MAGIC_EFFECT_111 = 0x6F,
	MAGIC_EFFECT_112 = 0x70,
	MAGIC_EFFECT_113 = 0x71,
	MAGIC_EFFECT_114 = 0x72,
	MAGIC_EFFECT_115 = 0x73,
	MAGIC_EFFECT_116 = 0x74,
	MAGIC_EFFECT_117 = 0x75,
	MAGIC_EFFECT_118 = 0x76,
	MAGIC_EFFECT_119 = 0x77,
	MAGIC_EFFECT_120 = 0x78,
	MAGIC_EFFECT_121 = 0x79,
	MAGIC_EFFECT_122 = 0x7A,
	MAGIC_EFFECT_123 = 0x7B,
	MAGIC_EFFECT_124 = 0x7C,
	MAGIC_EFFECT_125 = 0x7D,
	MAGIC_EFFECT_126 = 0x7E,
	MAGIC_EFFECT_127 = 0x7F,
	MAGIC_EFFECT_128 = 0x80,
	MAGIC_EFFECT_129 = 0x81,
	MAGIC_EFFECT_130 = 0x82,
	MAGIC_EFFECT_131 = 0x83,
	MAGIC_EFFECT_132 = 0x84,
	MAGIC_EFFECT_133 = 0x85,
	MAGIC_EFFECT_134 = 0x86,
	MAGIC_EFFECT_135 = 0x87,
	MAGIC_EFFECT_136 = 0x88,
	MAGIC_EFFECT_137 = 0x89,
	MAGIC_EFFECT_138 = 0x8A,
	MAGIC_EFFECT_139 = 0x8B,
	MAGIC_EFFECT_140 = 0x8C,
	MAGIC_EFFECT_141 = 0x8D,
	MAGIC_EFFECT_142 = 0x8E,
	MAGIC_EFFECT_143 = 0x8F,
	MAGIC_EFFECT_144 = 0x90,
	MAGIC_EFFECT_145 = 0x91,
	MAGIC_EFFECT_146 = 0x92,
	MAGIC_EFFECT_147 = 0x93,
	MAGIC_EFFECT_148 = 0x94,
	MAGIC_EFFECT_149 = 0x95,
	MAGIC_EFFECT_150 = 0x96,
	MAGIC_EFFECT_151 = 0x97,
	MAGIC_EFFECT_152 = 0x98,
	MAGIC_EFFECT_153 = 0x99,
	MAGIC_EFFECT_154 = 0x9A,
	MAGIC_EFFECT_155 = 0x9B,
	MAGIC_EFFECT_156 = 0x9C,
	MAGIC_EFFECT_157 = 0x9D,
	MAGIC_EFFECT_158 = 0x9E,
	MAGIC_EFFECT_159 = 0x9F,
	MAGIC_EFFECT_160 = 0xA0,
	MAGIC_EFFECT_161 = 0xA1,
	MAGIC_EFFECT_162 = 0xA2,
	MAGIC_EFFECT_163 = 0xA3,
	MAGIC_EFFECT_164 = 0xA4,
	MAGIC_EFFECT_165 = 0xA5,
	MAGIC_EFFECT_166 = 0xA6,
	MAGIC_EFFECT_167 = 0xA7,
	MAGIC_EFFECT_168 = 0xA8,
	MAGIC_EFFECT_169 = 0xA9,
	MAGIC_EFFECT_170 = 0xAA,
	MAGIC_EFFECT_171 = 0xAB,
	MAGIC_EFFECT_172 = 0xAC,
	MAGIC_EFFECT_173 = 0xAD,
	MAGIC_EFFECT_174 = 0xAE,
	MAGIC_EFFECT_175 = 0xAF,
	MAGIC_EFFECT_176 = 0xB0,
	MAGIC_EFFECT_177 = 0xB1,
	MAGIC_EFFECT_178 = 0xB2,
	MAGIC_EFFECT_179 = 0xB3,
	MAGIC_EFFECT_180 = 0xB4,
	MAGIC_EFFECT_181 = 0xB5,
	MAGIC_EFFECT_182 = 0xB6,
	MAGIC_EFFECT_183 = 0xB7,
	MAGIC_EFFECT_184 = 0xB8,
	MAGIC_EFFECT_185 = 0xB9,
	MAGIC_EFFECT_186 = 0xBA,
	MAGIC_EFFECT_187 = 0xBB,
	MAGIC_EFFECT_188 = 0xBC,
	MAGIC_EFFECT_189 = 0xBD,
	MAGIC_EFFECT_190 = 0xBE,
	MAGIC_EFFECT_191 = 0xBF,
	MAGIC_EFFECT_192 = 0xC0,
	MAGIC_EFFECT_193 = 0xC1,
	MAGIC_EFFECT_194 = 0xC2,
	MAGIC_EFFECT_195 = 0xC3,
	MAGIC_EFFECT_196 = 0xC4,
	MAGIC_EFFECT_197 = 0xC5,
	MAGIC_EFFECT_198 = 0xC6,
	MAGIC_EFFECT_199 = 0xC7,
	MAGIC_EFFECT_200 = 0xC8,
	MAGIC_EFFECT_201 = 0xC9,
	MAGIC_EFFECT_202 = 0xCA,
	MAGIC_EFFECT_203 = 0xCB,
	MAGIC_EFFECT_204 = 0xCC,
	MAGIC_EFFECT_205 = 0xCD,
	MAGIC_EFFECT_206 = 0xCE,
	MAGIC_EFFECT_207 = 0xCF,
	MAGIC_EFFECT_208 = 0xD0,
	MAGIC_EFFECT_209 = 0xD1,
	MAGIC_EFFECT_210 = 0xD2,
	MAGIC_EFFECT_211 = 0xD3,
	MAGIC_EFFECT_212 = 0xD4,
	MAGIC_EFFECT_213 = 0xD5,
	MAGIC_EFFECT_214 = 0xD6,
	MAGIC_EFFECT_215 = 0xD7,
	MAGIC_EFFECT_216 = 0xD8,
	MAGIC_EFFECT_217 = 0xD9,
	MAGIC_EFFECT_218 = 0xDA,
	MAGIC_EFFECT_219 = 0xDB,
	MAGIC_EFFECT_220 = 0xDC,
	MAGIC_EFFECT_221 = 0xDD,
	MAGIC_EFFECT_222 = 0xDE,
	MAGIC_EFFECT_223 = 0xDF,
	MAGIC_EFFECT_224 = 0xE0,
	MAGIC_EFFECT_225 = 0xE1,
	MAGIC_EFFECT_226 = 0xE2,
	MAGIC_EFFECT_227 = 0xE3,
	MAGIC_EFFECT_228 = 0xE4,
	MAGIC_EFFECT_229 = 0xE5,
	MAGIC_EFFECT_230 = 0xE6,
	MAGIC_EFFECT_231 = 0xE7,
	MAGIC_EFFECT_232 = 0xE8,
	MAGIC_EFFECT_233 = 0xE9,
	MAGIC_EFFECT_234 = 0xEA,
	MAGIC_EFFECT_235 = 0xEB,
	MAGIC_EFFECT_236 = 0xEC,
	MAGIC_EFFECT_237 = 0xED,
	MAGIC_EFFECT_238 = 0xEE,
	MAGIC_EFFECT_239 = 0xEF,
	MAGIC_EFFECT_240 = 0xF0,
	MAGIC_EFFECT_241 = 0xF1,
	MAGIC_EFFECT_242 = 0xF2,
	MAGIC_EFFECT_243 = 0xF3,
	MAGIC_EFFECT_244 = 0xF4,
	MAGIC_EFFECT_245 = 0xF5,
	MAGIC_EFFECT_246 = 0xF6,
	MAGIC_EFFECT_247 = 0xF7,
	MAGIC_EFFECT_248 = 0xF8,
	MAGIC_EFFECT_249 = 0xF9,
	MAGIC_EFFECT_250 = 0xFA,
	MAGIC_EFFECT_251 = 0xFB,
	MAGIC_EFFECT_252 = 0xFC,
	MAGIC_EFFECT_253 = 0xFD,
	MAGIC_EFFECT_254 = 0xFE,
	MAGIC_EFFECT_255 = 0xFF,
	MAGIC_EFFECT_SEMFIM        = 0xFFFE, //65534
	MAGIC_EFFECT_LAST		= MAGIC_EFFECT_SEMFIM,

	//for internal use, dont send to client
	MAGIC_EFFECT_NONE		= 0xFF,
	MAGIC_EFFECT_UNKNOWN		= 0xFFFF
};

enum ShootEffect_t
{
	SHOOT_EFFECT_SPEAR		= 0x00,
	SHOOT_EFFECT_BOLT		= 0x01,
	SHOOT_EFFECT_ARROW		= 0x02,
	SHOOT_EFFECT_FIRE		= 0x03,
	SHOOT_EFFECT_ENERGY		= 0x04,
	SHOOT_EFFECT_POISONARROW	= 0x05,
	SHOOT_EFFECT_BURSTARROW	= 0x06,
	SHOOT_EFFECT_THROWINGSTAR	= 0x07,
	SHOOT_EFFECT_THROWINGKNIFE	= 0x08,
	SHOOT_EFFECT_SMALLSTONE	= 0x09,
	SHOOT_EFFECT_DEATH		= 0x0A, //10
	SHOOT_EFFECT_LARGEROCK	= 0x0B, //11
	SHOOT_EFFECT_SNOWBALL	= 0x0C, //12
	SHOOT_EFFECT_POWERBOLT	= 0x0D, //13
	SHOOT_EFFECT_POISONFIELD	= 0x0E, //14
	SHOOT_EFFECT_INFERNALBOLT	= 0x0F, //15
	SHOOT_EFFECT_HUNTINGSPEAR	= 0x10, //16
	SHOOT_EFFECT_ENCHANTEDSPEAR	= 0x11, //17
	SHOOT_EFFECT_REDSTAR	= 0x12, //18
	SHOOT_EFFECT_GREENSTAR	= 0x13, //19
	SHOOT_EFFECT_ROYALSPEAR	= 0x14, //20
	SHOOT_EFFECT_SNIPERARROW	= 0x15, //21
	SHOOT_EFFECT_ONYXARROW	= 0x16, //22
	SHOOT_EFFECT_PIERCINGBOLT	= 0x17, //23
	SHOOT_EFFECT_WHIRLWINDSWORD	= 0x18, //24
	SHOOT_EFFECT_WHIRLWINDAXE	= 0x19, //25
	SHOOT_EFFECT_WHIRLWINDCLUB	= 0x1A, //26
	SHOOT_EFFECT_ETHEREALSPEAR	= 0x1B, //27
	SHOOT_EFFECT_ICE		= 0x1C, //28
	SHOOT_EFFECT_EARTH		= 0x1D, //29
	SHOOT_EFFECT_HOLY		= 0x1E, //30
	SHOOT_EFFECT_SUDDENDEATH	= 0x1F, //31
	SHOOT_EFFECT_FLASHARROW	= 0x20, //32
	SHOOT_EFFECT_FLAMMINGARROW	= 0x21, //33
	SHOOT_EFFECT_SHIVERARROW	= 0x22, //34
	SHOOT_EFFECT_ENERGYBALL	= 0x23, //35
	SHOOT_EFFECT_SMALLICE	= 0x24, //36
	SHOOT_EFFECT_SMALLHOLY	= 0x25, //37
	SHOOT_EFFECT_SMALLEARTH	= 0x26, //38
	SHOOT_EFFECT_EARTHARROW	= 0x27, //39
	SHOOT_EFFECT_EXPLOSION	= 0x28, //40
	SHOOT_EFFECT_CAKE		= 0x29, //41
	SHOOT_EFFECT_42 = 0x2A, //42
	SHOOT_EFFECT_43 = 0x2B, //43
	SHOOT_EFFECT_44 = 0x2C, //44
	SHOOT_EFFECT_45 = 0x2D, //45
	SHOOT_EFFECT_46 = 0x2E, //46
	SHOOT_EFFECT_47 = 0x2F, //47
	SHOOT_EFFECT_48 = 0x30, //48
	SHOOT_EFFECT_49 = 0x31, //49
	SHOOT_EFFECT_50 = 0x32, //50
	SHOOT_EFFECT_51 = 0x33, //51
	SHOOT_EFFECT_52 = 0x34, //52
	SHOOT_EFFECT_53 = 0x35, //53
	SHOOT_EFFECT_54 = 0x36, //54
	SHOOT_EFFECT_55 = 0x37, //55
	SHOOT_EFFECT_56 = 0x38, //56
	SHOOT_EFFECT_57 = 0x39, //57
	SHOOT_EFFECT_58 = 0x3A, //58
	SHOOT_EFFECT_59 = 0x3B, //59
	SHOOT_EFFECT_60 = 0x3C, //60
	SHOOT_EFFECT_61	= 0x3D, //61
	SHOOT_EFFECT_62	= 0x3E, //62
	SHOOT_EFFECT_63	= 0x3F, //63
	SHOOT_EFFECT_64	= 0x40, //64
	SHOOT_EFFECT_65	= 0x41, //65
	SHOOT_EFFECT_66	= 0x42, //66
	SHOOT_EFFECT_67	= 0x43, //67
	SHOOT_EFFECT_68 = 0x44, //68
	SHOOT_EFFECT_69 = 0x45, //69
	SHOOT_EFFECT_70 = 0x46, //70
	SHOOT_EFFECT_71 = 0x47, //71
	SHOOT_EFFECT_72 = 0x48, //72
	SHOOT_EFFECT_73 = 0x49, //73...
	SHOOT_EFFECT_74 = 0x4A,
	SHOOT_EFFECT_75 = 0x4B,
	SHOOT_EFFECT_76 = 0x4C,
	SHOOT_EFFECT_77 = 0x4D,
	SHOOT_EFFECT_78 = 0x4E,
	SHOOT_EFFECT_79 = 0x4F,
	SHOOT_EFFECT_80 = 0x50,
	SHOOT_EFFECT_81 = 0x51,
	SHOOT_EFFECT_82 = 0x52,
	SHOOT_EFFECT_83 = 0x53,
	SHOOT_EFFECT_84 = 0x54,
	SHOOT_EFFECT_85 = 0x55,
	SHOOT_EFFECT_86 = 0x56,
	SHOOT_EFFECT_87 = 0x57,
	SHOOT_EFFECT_88 = 0x58,
	SHOOT_EFFECT_89 = 0x59,
	SHOOT_EFFECT_90 = 0x5A,
	SHOOT_EFFECT_91 = 0x5B,
	SHOOT_EFFECT_92 = 0x5C,
	SHOOT_EFFECT_93 = 0x5D,
	SHOOT_EFFECT_94 = 0x5E,
	SHOOT_EFFECT_95 = 0x5F,
	SHOOT_EFFECT_96 = 0x60,
	SHOOT_EFFECT_97 = 0x61,
	SHOOT_EFFECT_98 = 0x62,
	SHOOT_EFFECT_99 = 0x63,
	SHOOT_EFFECT_100 = 0x64,
	SHOOT_EFFECT_101 = 0x65,
	SHOOT_EFFECT_102 = 0x66,
	SHOOT_EFFECT_103 = 0x67,
	SHOOT_EFFECT_104 = 0x68,
	SHOOT_EFFECT_105 = 0x69,
	SHOOT_EFFECT_106 = 0x6A,
	SHOOT_EFFECT_107 = 0x6B,
	SHOOT_EFFECT_108 = 0x6C,
	SHOOT_EFFECT_109 = 0x6D,
	SHOOT_EFFECT_110 = 0x6E,
	SHOOT_EFFECT_111 = 0x6F,
	SHOOT_EFFECT_112 = 0x70,
	SHOOT_EFFECT_113 = 0x71,
	SHOOT_EFFECT_114 = 0x72,
	SHOOT_EFFECT_115 = 0x73,
	SHOOT_EFFECT_116 = 0x74,
	SHOOT_EFFECT_117 = 0x75,
	SHOOT_EFFECT_118 = 0x76,
	SHOOT_EFFECT_119 = 0x77,
	SHOOT_EFFECT_120 = 0x78,
	SHOOT_EFFECT_121 = 0x79,
	SHOOT_EFFECT_122 = 0x7A,
	SHOOT_EFFECT_123 = 0x7B,
	SHOOT_EFFECT_124 = 0x7C,
	SHOOT_EFFECT_125 = 0x7D,
	SHOOT_EFFECT_126 = 0x7E,
	SHOOT_EFFECT_127 = 0x7F,
	SHOOT_EFFECT_128 = 0x80,
	SHOOT_EFFECT_129 = 0x81,
	SHOOT_EFFECT_130 = 0x82,
	SHOOT_EFFECT_131 = 0x83,
	SHOOT_EFFECT_132 = 0x84,
	SHOOT_EFFECT_133 = 0x85,
	SHOOT_EFFECT_134 = 0x86,
	SHOOT_EFFECT_135 = 0x87,
	SHOOT_EFFECT_136 = 0x88,
	SHOOT_EFFECT_137 = 0x89,
	SHOOT_EFFECT_138 = 0x8A,
	SHOOT_EFFECT_139 = 0x8B,
	SHOOT_EFFECT_140 = 0x8C,
	SHOOT_EFFECT_141 = 0x8D,
	SHOOT_EFFECT_142 = 0x8E,
	SHOOT_EFFECT_143 = 0x8F,
	SHOOT_EFFECT_144 = 0x90,
	SHOOT_EFFECT_145 = 0x91,
	SHOOT_EFFECT_146 = 0x92,
	SHOOT_EFFECT_147 = 0x93,
	SHOOT_EFFECT_148 = 0x94,
	SHOOT_EFFECT_149 = 0x95,
	SHOOT_EFFECT_150 = 0x96,
	SHOOT_EFFECT_151 = 0x97,
	SHOOT_EFFECT_152 = 0x98,
	SHOOT_EFFECT_153 = 0x99,
	SHOOT_EFFECT_154 = 0x9A,
	SHOOT_EFFECT_155 = 0x9B,
	SHOOT_EFFECT_156 = 0x9C,
	SHOOT_EFFECT_157 = 0x9D,
	SHOOT_EFFECT_158 = 0x9E,
	SHOOT_EFFECT_159 = 0x9F,
	SHOOT_EFFECT_160 = 0xA0,
	SHOOT_EFFECT_161 = 0xA1,
	SHOOT_EFFECT_162 = 0xA2,
	SHOOT_EFFECT_163 = 0xA3,
	SHOOT_EFFECT_164 = 0xA4,
	SHOOT_EFFECT_165 = 0xA5,
	SHOOT_EFFECT_166 = 0xA6,
	SHOOT_EFFECT_167 = 0xA7,
	SHOOT_EFFECT_168 = 0xA8,
	SHOOT_EFFECT_169 = 0xA9,
	SHOOT_EFFECT_170 = 0xAA,
	SHOOT_EFFECT_171 = 0xAB,
	SHOOT_EFFECT_172 = 0xAC,
	SHOOT_EFFECT_173 = 0xAD,
	SHOOT_EFFECT_174 = 0xAE,
	SHOOT_EFFECT_175 = 0xAF,
	SHOOT_EFFECT_176 = 0xB0,
	SHOOT_EFFECT_177 = 0xB1,
	SHOOT_EFFECT_178 = 0xB2,
	SHOOT_EFFECT_179 = 0xB3,
	SHOOT_EFFECT_180 = 0xB4,
	SHOOT_EFFECT_181 = 0xB5,
	SHOOT_EFFECT_182 = 0xB6,
	SHOOT_EFFECT_183 = 0xB7,
	SHOOT_EFFECT_184 = 0xB8,
	SHOOT_EFFECT_185 = 0xB9,
	SHOOT_EFFECT_186 = 0xBA,
	SHOOT_EFFECT_187 = 0xBB,
	SHOOT_EFFECT_188 = 0xBC,
	SHOOT_EFFECT_189 = 0xBD,
	SHOOT_EFFECT_190 = 0xBE,
	SHOOT_EFFECT_191 = 0xBF,
	SHOOT_EFFECT_192 = 0xC0,
	SHOOT_EFFECT_193 = 0xC1,
	SHOOT_EFFECT_194 = 0xC2,
	SHOOT_EFFECT_195 = 0xC3,
	SHOOT_EFFECT_196 = 0xC4,
	SHOOT_EFFECT_197 = 0xC5,
	SHOOT_EFFECT_198 = 0xC6,
	SHOOT_EFFECT_199 = 0xC7,
	SHOOT_EFFECT_200 = 0xC8,
	SHOOT_EFFECT_201 = 0xC9,
	SHOOT_EFFECT_202 = 0xCA,
	SHOOT_EFFECT_203 = 0xCB,
	SHOOT_EFFECT_204 = 0xCC,
	SHOOT_EFFECT_205 = 0xCD,
	SHOOT_EFFECT_206 = 0xCE,
	SHOOT_EFFECT_207 = 0xCF,
	SHOOT_EFFECT_208 = 0xD0,
	SHOOT_EFFECT_209 = 0xD1,
	SHOOT_EFFECT_210 = 0xD2,
	SHOOT_EFFECT_211 = 0xD3,
	SHOOT_EFFECT_212 = 0xD4,
	SHOOT_EFFECT_213 = 0xD5,
	SHOOT_EFFECT_214 = 0xD6,
	SHOOT_EFFECT_215 = 0xD7,
	SHOOT_EFFECT_216 = 0xD8,
	SHOOT_EFFECT_217 = 0xD9,
	SHOOT_EFFECT_218 = 0xDA,
	SHOOT_EFFECT_219 = 0xDB,
	SHOOT_EFFECT_220 = 0xDC,
	SHOOT_EFFECT_221 = 0xDD,
	SHOOT_EFFECT_222 = 0xDE,
	SHOOT_EFFECT_223 = 0xDF,
	SHOOT_EFFECT_224 = 0xE0,
	SHOOT_EFFECT_225 = 0xE1,
	SHOOT_EFFECT_226 = 0xE2,
	SHOOT_EFFECT_227 = 0xE3,
	SHOOT_EFFECT_228 = 0xE4,
	SHOOT_EFFECT_229 = 0xE5,
	SHOOT_EFFECT_230 = 0xE6,
	SHOOT_EFFECT_231 = 0xE7,
	SHOOT_EFFECT_232 = 0xE8,
	SHOOT_EFFECT_233 = 0xE9,
	SHOOT_EFFECT_234 = 0xEA,
	SHOOT_EFFECT_235 = 0xEB,
	SHOOT_EFFECT_236 = 0xEC,
	SHOOT_EFFECT_237 = 0xED,
	SHOOT_EFFECT_238 = 0xEE,
	SHOOT_EFFECT_239 = 0xEF,
	SHOOT_EFFECT_240 = 0xF0,
	SHOOT_EFFECT_241 = 0xF1,
	SHOOT_EFFECT_242 = 0xF2,
	SHOOT_EFFECT_243 = 0xF3,
	SHOOT_EFFECT_244 = 0xF4,
	SHOOT_EFFECT_245 = 0xF5,
	SHOOT_EFFECT_246 = 0xF6,
	SHOOT_EFFECT_247 = 0xF7,
	SHOOT_EFFECT_248 = 0xF8,
	SHOOT_EFFECT_249 = 0xF9,
	SHOOT_EFFECT_250 = 0xFA,
	SHOOT_EFFECT_251 = 0xFB,
	SHOOT_EFFECT_252 = 0xFC,
	SHOOT_EFFECT_253 = 0xFD,
	SHOOT_EFFECT_254 = 0xFE,
	SHOOT_EFFECT_SEMFIM        = 0xFFFE, //65534
	SHOOT_EFFECT_LAST		= SHOOT_EFFECT_SEMFIM,

	//for internal use, dont send to client
	SHOOT_EFFECT_WEAPONTYPE	= 0xFF, //255
	SHOOT_EFFECT_NONE		= 0xFF,
	SHOOT_EFFECT_UNKNOWN	= 0xFFFF
};

enum SpeakClasses
{
	SPEAK_CLASS_NONE	= 0x00,
	SPEAK_CLASS_FIRST 	= 0x01,
	SPEAK_SAY		= SPEAK_CLASS_FIRST,
	SPEAK_WHISPER		= 0x02,
	SPEAK_YELL		= 0x03,
	SPEAK_PRIVATE_PN	= 0x04,
	SPEAK_PRIVATE_NP	= 0x05,
	SPEAK_PRIVATE		= 0x06,
	SPEAK_CHANNEL_Y		= 0x07,
	SPEAK_CHANNEL_W		= 0x08,
	SPEAK_RVR_CHANNEL	= 0x09,
	SPEAK_RVR_ANSWER	= 0x0A,
	SPEAK_RVR_CONTINUE	= 0x0B,
	SPEAK_BROADCAST		= 0x0C,
	SPEAK_CHANNEL_RN	= 0x0D, //red - #c text
	SPEAK_PRIVATE_RED	= 0x0E,	//@name@text
	SPEAK_CHANNEL_O		= 0x0F,
	//SPEAK_UNKNOWN_1		= 0x10,
	SPEAK_CHANNEL_RA	= 0x11,	//red anonymous - #d text
	//SPEAK_UNKNOWN_2		= 0x12,
	SPEAK_MONSTER_SAY	= 0x13,
	SPEAK_MONSTER_YELL	= 0x14,
	SPEAK_CLASS_LAST 	= SPEAK_MONSTER_YELL
};

enum MessageClasses
{
	MSG_CLASS_FIRST			= 0x12,
	MSG_STATUS_CONSOLE_RED		= MSG_CLASS_FIRST, /*Red message in the console*/
	MSG_EVENT_ORANGE		= 0x13, /*Orange message in the console*/
	MSG_STATUS_CONSOLE_ORANGE	= 0x14, /*Orange message in the console*/
	MSG_STATUS_WARNING		= 0x15, /*Red message in game window and in the console*/
	MSG_EVENT_ADVANCE		= 0x16, /*White message in game window and in the console*/
	MSG_EVENT_DEFAULT		= 0x17, /*White message at the bottom of the game window and in the console*/
	MSG_STATUS_DEFAULT		= 0x18, /*White message at the bottom of the game window and in the console*/
	MSG_INFO_DESCR			= 0x19, /*Green message in game window and in the console*/
	MSG_STATUS_SMALL		= 0x1A, /*White message at the bottom of the game window"*/
	MSG_STATUS_CONSOLE_BLUE		= 0x1B, /*Blue message in the console*/
	MSG_CLASS_LAST			= MSG_STATUS_CONSOLE_BLUE
};

enum MapMarks_t
{
	MAPMARK_TICK		= 0x00,
	MAPMARK_QUESTION	= 0x01,
	MAPMARK_EXCLAMATION	= 0x02,
	MAPMARK_STAR		= 0x03,
	MAPMARK_CROSS		= 0x04,
	MAPMARK_TEMPLE		= 0x05,
	MAPMARK_KISS		= 0x06,
	MAPMARK_SHOVEL		= 0x07,
	MAPMARK_SWORD		= 0x08,
	MAPMARK_FLAG		= 0x09,
	MAPMARK_LOCK		= 0x0A,
	MAPMARK_BAG		= 0x0B,
	MAPMARK_SKULL		= 0x0C,
	MAPMARK_DOLLAR		= 0x0D,
	MAPMARK_REDNORTH	= 0x0E,
	MAPMARK_REDSOUTH	= 0x0F,
	MAPMARK_REDEAST		= 0x10,
	MAPMARK_REDWEST		= 0x11,
	MAPMARK_GREENNORTH	= 0x12,
	MAPMARK_GREENSOUTH	= 0x13
};

enum FluidColors_t
{
	FLUID_EMPTY	= 0x00,
	FLUID_BLUE	= 0x01,
	FLUID_RED	= 0x02,
	FLUID_BROWN	= 0x03,
	FLUID_GREEN	= 0x04,
	FLUID_YELLOW	= 0x05,
	FLUID_WHITE	= 0x06,
	FLUID_PURPLE	= 0x07
};

enum FluidTypes_t
{
	FLUID_NONE		= FLUID_EMPTY,
	FLUID_WATER		= FLUID_BLUE,
	FLUID_BLOOD		= FLUID_RED,
	FLUID_BEER		= FLUID_BROWN,
	FLUID_SLIME		= FLUID_GREEN,
	FLUID_LEMONADE		= FLUID_YELLOW,
	FLUID_MILK		= FLUID_WHITE,
	FLUID_MANA		= FLUID_PURPLE,

	FLUID_LIFE		= FLUID_RED + 8,
	FLUID_OIL		= FLUID_BROWN + 8,
	FLUID_URINE		= FLUID_YELLOW + 8,
	FLUID_COCONUTMILK	= FLUID_WHITE + 8,
	FLUID_WINE		= FLUID_PURPLE + 8,

	FLUID_MUD		= FLUID_BROWN + 16,
	FLUID_FRUITJUICE	= FLUID_YELLOW + 16,

	FLUID_LAVA		= FLUID_RED + 24,
	FLUID_RUM		= FLUID_BROWN + 24,
	FLUID_SWAMP		= FLUID_GREEN + 24,

	FLUID_TEA               = FLUID_BROWN + 32,
	FLUID_MEAD              = FLUID_BROWN + 40
};

const uint8_t reverseFluidMap[] =
{
	FLUID_EMPTY,
	FLUID_WATER,
	FLUID_MANA,
	FLUID_BEER,
	FLUID_EMPTY,
	FLUID_BLOOD,
	FLUID_SLIME,
	FLUID_EMPTY,
	FLUID_LEMONADE,
	FLUID_MILK
};

enum ClientFluidTypes_t
{
	CLIENTFLUID_EMPTY	= 0x00,
	CLIENTFLUID_BLUE	= 0x01,
	CLIENTFLUID_PURPLE	= 0x02,
	CLIENTFLUID_BROWN_1	= 0x03,
	CLIENTFLUID_BROWN_2	= 0x04,
	CLIENTFLUID_RED		= 0x05,
	CLIENTFLUID_GREEN	= 0x06,
	CLIENTFLUID_BROWN	= 0x07,
	CLIENTFLUID_YELLOW	= 0x08,
	CLIENTFLUID_WHITE	= 0x09
};

const uint8_t fluidMap[] =
{
	CLIENTFLUID_EMPTY,
	CLIENTFLUID_BLUE,
	CLIENTFLUID_RED,
	CLIENTFLUID_BROWN_1,
	CLIENTFLUID_GREEN,
	CLIENTFLUID_YELLOW,
	CLIENTFLUID_WHITE,
	CLIENTFLUID_PURPLE
};

enum Color_t
{
	COLOR_BLACK		= 0,
	COLOR_BLUE		= 5,
	COLOR_GREEN		= 18,
	COLOR_LIGHTGREEN	= 66,
	COLOR_DARKBROWN		= 78,
	COLOR_LIGHTBLUE		= 89,
	COLOR_DARKRED		= 108,
	COLOR_DARKPURPLE	= 112,
	COLOR_BROWN		= 120,
	COLOR_GREY		= 129,
	COLOR_TEAL		= 143,
	COLOR_DARKPINK		= 152,
	COLOR_PURPLE		= 154,
	COLOR_DARKORANGE	= 156,
	COLOR_RED		= 180,
	COLOR_PINK		= 190,
	COLOR_ORANGE		= 192,
	COLOR_DARKYELLOW	= 205,
	COLOR_YELLOW		= 210,
	COLOR_WHITE		= 215,

	COLOR_NONE		= 255,
	COLOR_UNKNOWN		= 256
};

enum Icons_t
{
	ICON_NONE = 0,
	ICON_POISON = 1 << 0,
	ICON_BURN = 1 << 1,
	ICON_ENERGY = 1 << 2,
	ICON_DRUNK = 1 << 3,
	ICON_MANASHIELD = 1 << 4,
	ICON_PARALYZE = 1 << 5,
	ICON_HASTE = 1 << 6,
	ICON_SWORDS = 1 << 7,
	ICON_DROWNING = 1 << 8,
	ICON_FREEZING = 1 << 9,
	ICON_DAZZLED = 1 << 10,
	ICON_CURSED = 1 << 11,
	ICON_BUFF = 1 << 12,
	ICON_PZ = 1 << 13,
	ICON_PROTECTIONZONE = 1 << 14
};

enum WeaponType_t
{
	WEAPON_NONE = 0,
	WEAPON_SWORD,
	WEAPON_CLUB,
	WEAPON_AXE,
	WEAPON_DIST,
	WEAPON_SHIELD,
	WEAPON_FIST,
	WEAPON_WAND,
	WEAPON_AMMO
};

enum Ammo_t
{
	AMMO_NONE = 0,
	AMMO_BOLT,
	AMMO_ARROW,
	AMMO_SPEAR,
	AMMO_THROWINGSTAR,
	AMMO_THROWINGKNIFE,
	AMMO_STONE,
	AMMO_SNOWBALL
};

enum AmmoAction_t
{
	AMMOACTION_NONE = 0,
	AMMOACTION_REMOVECOUNT,
	AMMOACTION_REMOVECHARGE,
	AMMOACTION_MOVE,
	AMMOACTION_MOVEBACK
};

enum WieldInfo_t
{
	WIELDINFO_LEVEL = 1,
	WIELDINFO_MAGLV = 2,
	WIELDINFO_VOCREQ = 4,
	WIELDINFO_PREMIUM = 8
};

enum Skulls_t
{
	SKULL_NONE = 0,
	SKULL_YELLOW,
	SKULL_GREEN,
	SKULL_WHITE,
	SKULL_RED,
	SKULL_BLACK,
	SKULL_LAST = SKULL_BLACK
};

enum PartyShields_t
{
	SHIELD_NONE = 0,
	SHIELD_WHITEYELLOW,
	SHIELD_WHITEBLUE,
	SHIELD_BLUE,
	SHIELD_YELLOW,
	SHIELD_BLUE_SHAREDEXP,
	SHIELD_YELLOW_SHAREDEXP,
	SHIELD_BLUE_NOSHAREDEXP_BLINK,
	SHIELD_YELLOW_NOSHAREDEXP_BLINK,
	SHIELD_BLUE_NOSHAREDEXP,
	SHIELD_YELLOW_NOSHAREDEXP,
	SHIELD_LAST = SHIELD_YELLOW_NOSHAREDEXP
};

enum GuildEmblems_t
{
	EMBLEM_NONE = 0,
	EMBLEM_GREEN,
	EMBLEM_RED,
	EMBLEM_BLUE
};

enum item_t
{
	ITEM_FIREFIELD		= 1492,
	ITEM_FIREFIELD_SAFE	= 1500,

	ITEM_POISONFIELD	= 1496,
	ITEM_POISONFIELD_SAFE	= 1503,

	ITEM_ENERGYFIELD	= 1495,
	ITEM_ENERGYFIELD_SAFE	= 1504,

	ITEM_MAGICWALL		= 1497,
	ITEM_MAGICWALL_SAFE	= 11098,

	ITEM_WILDGROWTH		= 1499,
	ITEM_WILDGROWTH_SAFE	= 11099,

	ITEM_DEPOT		= 2594,
	ITEM_LOCKER		= 2589,

	ITEM_MALE_CORPSE	= 3058,
	ITEM_FEMALE_CORPSE	= 3065,

	ITEM_FULLSPLASH		= 2016,
	ITEM_SMALLSPLASH	= 2019,

	ITEM_PARCEL		= 2595,
	ITEM_PARCEL_STAMPED	= 2596,
	ITEM_LETTER		= 2597,
	ITEM_LETTER_STAMPED	= 2598,
	ITEM_LABEL		= 2599,

	ITEM_WATERBALL_SPLASH	= 7711,
	ITEM_WATERBALL		= 7956,

	ITEM_HOUSE_TRANSFER	= 1968 //read-only
};

enum PlayerFlags
{
	PlayerFlag_CannotUseCombat = 0,			//2^0 = 1
	PlayerFlag_CannotAttackPlayer,			//2^1 = 2
	PlayerFlag_CannotAttackMonster,			//2^2 = 4
	PlayerFlag_CannotBeAttacked,			//2^3 = 8
	PlayerFlag_CanConvinceAll,			//2^4 = 16
	PlayerFlag_CanSummonAll,			//2^5 = 32
	PlayerFlag_CanIllusionAll,			//2^6 = 64
	PlayerFlag_CanSenseInvisibility,		//2^7 = 128
	PlayerFlag_IgnoredByMonsters,			//2^8 = 256
	PlayerFlag_NotGainInFight,			//2^9 = 512
	PlayerFlag_HasInfiniteMana,			//2^10 = 1024
	PlayerFlag_HasInfiniteSoul,			//2^11 = 2048
	PlayerFlag_HasNoExhaustion,			//2^12 = 4096
	PlayerFlag_CannotUseSpells,			//2^13 = 8192
	PlayerFlag_CannotPickupItem,			//2^14 = 16384
	PlayerFlag_CanAlwaysLogin,			//2^15 = 32768
	PlayerFlag_CanBroadcast,			//2^16 = 65536
	PlayerFlag_CanEditHouses,			//2^17 = 131072
	PlayerFlag_CannotBeBanned,			//2^18 = 262144
	PlayerFlag_CannotBePushed,			//2^19 = 524288
	PlayerFlag_HasInfiniteCapacity,			//2^20 = 1048576
	PlayerFlag_CanPushAllCreatures,			//2^21 = 2097152
	PlayerFlag_CanTalkRedPrivate,			//2^22 = 4194304
	PlayerFlag_CanTalkRedChannel,			//2^23 = 8388608
	PlayerFlag_TalkOrangeHelpChannel,		//2^24 = 16777216
	PlayerFlag_NotGainExperience,			//2^25 = 33554432
	PlayerFlag_NotGainMana,				//2^26 = 67108864
	PlayerFlag_NotGainHealth,			//2^27 = 134217728
	PlayerFlag_NotGainSkill,			//2^28 = 268435456
	PlayerFlag_SetMaxSpeed,				//2^29 = 536870912
	PlayerFlag_SpecialVIP,				//2^30 = 1073741824
	PlayerFlag_NotGenerateLoot,			//2^31 = 2147483648
	PlayerFlag_CanTalkRedChannelAnonymous,		//2^32 = 4294967296
	PlayerFlag_IgnoreProtectionZone,		//2^33 = 8589934592
	PlayerFlag_IgnoreSpellCheck,			//2^34 = 17179869184
	PlayerFlag_IgnoreEquipCheck,			//2^35 = 34359738368
	PlayerFlag_CannotBeMuted,			//2^36 = 68719476736
	PlayerFlag_IsAlwaysPremium,			//2^37 = 137438953472
	PlayerFlag_CanAnswerRuleViolations,		//2^38 = 274877906944
	PlayerFlag_39,	//ignore			//2^39 = 549755813888 //not used by us
	PlayerFlag_ShowGroupNameInsteadOfVocation,	//2^40 = 1099511627776
	PlayerFlag_HasInfiniteStamina,			//2^41 = 2199023255552
	PlayerFlag_CannotMoveItems,			//2^42 = 4398046511104
	PlayerFlag_CannotMoveCreatures,			//2^43 = 8796093022208
	PlayerFlag_CanReportBugs,			//2^44 = 17592186044416
	PlayerFlag_45,	//ignore			//2^45 = 35184372088832 //not used by us
	PlayerFlag_CannotBeSeen,			//2^46 = 70368744177664
	PlayerFlag_HideHealth,				//2^47 = 140737488355328

	PlayerFlag_LastFlag
};

enum PlayerCustomFlags
{
	PlayerCustomFlag_AllowIdle = 0,				//2^0 = 1
	PlayerCustomFlag_CanSeePosition,			//2^1 = 2
	PlayerCustomFlag_CanSeeItemDetails,			//2^2 = 4
	PlayerCustomFlag_CanSeeCreatureDetails,			//2^3 = 8
	PlayerCustomFlag_NotSearchable,				//2^4 = 16
	PlayerCustomFlag_GamemasterPrivileges,			//2^5 = 32
	PlayerCustomFlag_CanThrowAnywhere,			//2^6 = 64
	PlayerCustomFlag_CanPushAllItems,			//2^7 = 128
	PlayerCustomFlag_CanMoveAnywhere,			//2^8 = 256
	PlayerCustomFlag_CanMoveFromFar,			//2^9 = 512
	PlayerCustomFlag_CanLoginMultipleCharacters,		//2^10 = 1024 (account flag)
	PlayerCustomFlag_HasFullLight,				//2^11 = 2048
	PlayerCustomFlag_CanLogoutAnytime,			//2^12 = 4096 (account flag)
	PlayerCustomFlag_HideLevel,				//2^13 = 8192
	PlayerCustomFlag_IsProtected,				//2^14 = 16384
	PlayerCustomFlag_IsImmune,				//2^15 = 32768
	PlayerCustomFlag_NotGainSkull,				//2^16 = 65536
	PlayerCustomFlag_NotGainUnjustified,			//2^17 = 131072
	PlayerCustomFlag_IgnorePacification,			//2^18 = 262144
	PlayerCustomFlag_IgnoreLoginDelay,			//2^19 = 524288
	PlayerCustomFlag_CanStairhop,				//2^20 = 1048576
	PlayerCustomFlag_CanTurnhop,				//2^21 = 2097152
	PlayerCustomFlag_IgnoreHouseRent,			//2^22 = 4194304
	PlayerCustomFlag_CanWearAllAddons,			//2^23 = 8388608
	PlayerCustomFlag_IsWalkable,				//2^24 = 16777216
	PlayerCustomFlag_CanWalkthrough,			//2^25 = 33554432

	PlayerCustomFlag_LastFlag
};

//Reserved player storage key ranges
//[10000000 - 20000000]
#define PSTRG_RESERVED_RANGE_START	10000000
#define PSTRG_RESERVED_RANGE_SIZE	10000000

//[1000 - 1500]
#define PSTRG_OUTFITS_RANGE_START	(PSTRG_RESERVED_RANGE_START + 1000)
#define PSTRG_OUTFITS_RANGE_SIZE	500

//[1500 - 2000]
#define PSTRG_OUTFITSID_RANGE_START	(PSTRG_RESERVED_RANGE_START + 1500)
#define PSTRG_OUTFITSID_RANGE_SIZE	500

#define NETWORK_CRYPTOHEADER_SIZE 8
#define NETWORK_RETRY_TIMEOUT 5000
#define NETWORK_DEFAULT_SIZE 4096
#define NETWORK_HEADER_SIZE 2
#define NETWORK_MAX_SIZE 15360

#define IPBAN_FLAG 128
#define LOCALHOST 2130706433

#define IS_IN_KEYRANGE(key, range) (key >= PSTRG_##range##_START && ((key - PSTRG_##range##_START) < PSTRG_##range##_SIZE))
#endif