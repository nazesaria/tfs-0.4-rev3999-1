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
#include "otpch.h"
#include "tools.h"

#include <iostream>
#include <iomanip>

#include <cryptopp/sha.h>
#include <cryptopp/md5.h>
#include <cryptopp/adler32.h>
#include <cryptopp/hmac.h>

#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include <cryptopp/cryptlib.h>

#include "vocation.h"
#include "configmanager.h"

extern ConfigManager g_config;

std::string transformToMD5(std::string plainText, bool upperCase)
{
	// Crypto++ MD5 object
	CryptoPP::Weak::MD5 hash;

	// Use native byte instead of casting chars
	byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];

	// Do the actual calculation, require a byte value so we need a cast
	hash.CalculateDigest(digest, (const byte*)plainText.c_str(), plainText.length());

	// Crypto++ HexEncoder object
	CryptoPP::HexEncoder encoder;

	// Our output
	std::string output;

	// Drop internal hex encoder and use this, returns uppercase by default
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	// Make sure we want uppercase
	if(upperCase)
		return output;

	// Convert to lowercase if needed
	return asLowerCaseString(output);
}

std::string transformToSHA1(std::string plainText, bool upperCase)
{
	// Crypto++ SHA1 object
	CryptoPP::SHA1 hash;

	// Use native byte instead of casting chars
	byte digest[CryptoPP::SHA1::DIGESTSIZE];

	// Do the actual calculation, require a byte value so we need a cast
	hash.CalculateDigest(digest, (const byte*)plainText.c_str(), plainText.length());

	// Crypto++ HexEncoder object
	CryptoPP::HexEncoder encoder;

	// Our output
	std::string output;

	// Drop internal hex encoder and use this, returns uppercase by default
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	// Make sure we want uppercase
	if(upperCase)
		return output;

	// Convert to lowercase if needed
	return asLowerCaseString(output);
}

std::string transformToSHA256(std::string plainText, bool upperCase)
{
	// Crypto++ SHA256 object
	CryptoPP::SHA256 hash;

	// Use native byte instead of casting chars
	byte digest[CryptoPP::SHA256::DIGESTSIZE];

	// Do the actual calculation, require a byte value so we need a cast
	hash.CalculateDigest(digest, (const byte*)plainText.c_str(), plainText.length());

	// Crypto++ HexEncoder object
	CryptoPP::HexEncoder encoder;

	// Our output
	std::string output;

	// Drop internal hex encoder and use this, returns uppercase by default
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	// Make sure we want uppercase
	if(upperCase)
		return output;

	// Convert to lowercase if needed
	return asLowerCaseString(output);
}

std::string transformToSHA512(std::string plainText, bool upperCase)
{
	// Crypto++ SHA512 object
	CryptoPP::SHA512 hash;

	// Use native byte instead of casting chars
	byte digest[CryptoPP::SHA512::DIGESTSIZE];

	// Do the actual calculation, require a byte value so we need a cast
	hash.CalculateDigest(digest, (const byte*)plainText.c_str(), plainText.length());

	// Crypto++ HexEncoder object
	CryptoPP::HexEncoder encoder;

	// Our output
	std::string output;

	// Drop internal hex encoder and use this, returns uppercase by default
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	// Make sure we want uppercase
	if(upperCase)
		return output;

	// Convert to lowercase if needed
	return asLowerCaseString(output);
}

std::string transformToVAHash(std::string plainText, bool upperCase)
{
	std::string key = g_config.getString(ConfigManager::ENCRYPTION_KEY);
	// This is basicaly a base64 string out of a sha512 lowcase string of the HMAC of the plaintext sha256 string with a configurated key
	// Currently this removes all known weaknesses in the sha-2 implantation
	// base64(HMAC<SHA512>(key, SHA256(plainText)));

	// Get SHA256
	std::string sha256 = transformToSHA256(plainText, false);

	// This holds the HMAC
	// Use native byte instead of casting chars
	byte digest[CryptoPP::SHA512::DIGESTSIZE];

	// Do the actual calculation and setup, require a byte value so we need a cast on the key and the input
	CryptoPP::HMAC<CryptoPP::SHA512>((const byte*)key.c_str(), key.length()).CalculateDigest(
		digest, (const byte*)sha256.c_str(), CryptoPP::SHA256::DIGESTSIZE);

	// Crypto++ Base64Encoder object
	CryptoPP::Base64Encoder encoder;

	// Our output
	std::string output;

	// Encode to base64
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	// Make sure we want uppercase
	if(upperCase)
		return output;

	// Convert to lowercase if needed
	return asLowerCaseString(output);
}

void _encrypt(std::string& str, bool upperCase)
{
	switch(g_config.getNumber(ConfigManager::ENCRYPTION))
	{
		case ENCRYPTION_MD5:
			str = transformToMD5(str, upperCase);
			break;
		case ENCRYPTION_SHA1:
			str = transformToSHA1(str, upperCase);
			break;
		case ENCRYPTION_SHA256:
			str = transformToSHA256(str, upperCase);
			break;
		case ENCRYPTION_SHA512:
			str = transformToSHA512(str, upperCase);
			break;
		case ENCRYPTION_VAHASH:
			str = transformToVAHash(str, upperCase);
			break;
		default:
		{
			if(upperCase)
				std::transform(str.begin(), str.end(), str.begin(), upchar);

			break;
		}
	}
}

bool encryptTest(std::string plain, std::string& hash)
{
	std::transform(hash.begin(), hash.end(), hash.begin(), upchar);
	_encrypt(plain, true);
	return plain == hash;
}

bool replaceString(std::string& text, const std::string& key, const std::string& value)
{
	if(text.find(key) == std::string::npos)
		return false;

	std::string::size_type start = 0, pos = 0;
	while((start = text.find(key, pos)) != std::string::npos)
	{
		text.replace(start, key.size(), value);
		//text = text.substr(0, start) + value + text.substr(start + key.size());
		pos = start + value.size();
	}

	return true;
}

void trim_right(std::string& source, const std::string& t)
{
	source.erase(source.find_last_not_of(t) + 1);
}

void trim_left(std::string& source, const std::string& t)
{
	source.erase(0, source.find_first_not_of(t));
}

void toLowerCaseString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), tolower);
}

void toUpperCaseString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), upchar);
}

std::string asLowerCaseString(const std::string& source)
{
	std::string s = source;
	toLowerCaseString(s);
	return s;
}

std::string asUpperCaseString(const std::string& source)
{
	std::string s = source;
	toUpperCaseString(s);
	return s;
}

bool booleanString(std::string source)
{
	toLowerCaseString(source);
	return (source == "yes" || source == "true" || atoi(source.c_str()) > 0);
}

bool readXMLInteger(xmlNodePtr node, const char* tag, int32_t& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoi(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLInteger64(xmlNodePtr node, const char* tag, int64_t& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoll(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLFloat(xmlNodePtr node, const char* tag, float& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atof(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLString(xmlNodePtr node, const char* tag, std::string& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	if(!utf8ToLatin1(nodeValue, value))
		value = nodeValue;

	xmlFree(nodeValue);
	return true;
}

bool readXMLContentString(xmlNodePtr node, std::string& value)
{
	char* nodeValue = (char*)xmlNodeGetContent(node);
	if(!nodeValue)
		return false;

	if(!utf8ToLatin1(nodeValue, value))
		value = nodeValue;

	xmlFree(nodeValue);
	return true;
}

bool parseXMLContentString(xmlNodePtr node, std::string& value)
{
	bool result = false;
	std::string compareValue;
	while(node)
	{
		if(xmlStrcmp(node->name, (const xmlChar*)"text") && node->type != XML_CDATA_SECTION_NODE)
		{
			node = node->next;
			continue;
		}

		if(!readXMLContentString(node, compareValue))
		{
			node = node->next;
			continue;
		}

		trim_left(compareValue, "\r");
		trim_left(compareValue, "\n");
		trim_left(compareValue, " ");
		if(compareValue.length() > value.length())
		{
			value = compareValue;
			if(!result)
				result = true;
		}

		node = node->next;
	}

	return result;
}

std::string getLastXMLError()
{
	std::stringstream ss;
	xmlErrorPtr lastError = xmlGetLastError();
	if(lastError->line)
		ss << "Line: " << lastError->line << ", ";

	ss << "Info: " << lastError->message << std::endl;
	return ss.str();
}

bool utf8ToLatin1(char* intext, std::string& outtext)
{
	outtext = "";
	if(!intext)
		return false;

	int32_t inlen = strlen(intext);
	if(!inlen)
		return false;

	int32_t outlen = inlen * 2;
	uint8_t* outbuf = new uint8_t[outlen];

	int32_t res = UTF8Toisolat1(outbuf, &outlen, (uint8_t*)intext, &inlen);
	if(res < 0)
	{
		delete[] outbuf;
		return false;
	}

	outbuf[outlen] = '\0';
	outtext = (char*)outbuf;

	delete[] outbuf;
	return true;
}

StringVec explodeString(const std::string& string, const std::string& separator, bool trim/* = true*/)
{
	StringVec returnVector;
	size_t start = 0, end = 0;
	while((end = string.find(separator, start)) != std::string::npos)
	{
		std::string t = string.substr(start, end - start);
		if(trim)
			trimString(t);

		returnVector.push_back(t);
		start = end + separator.size();
	}

	returnVector.push_back(string.substr(start));
	return returnVector;
}

IntegerVec vectorAtoi(StringVec stringVector)
{
	IntegerVec returnVector;
	for(StringVec::iterator it = stringVector.begin(); it != stringVector.end(); ++it)
		returnVector.push_back(atoi((*it).c_str()));

	return returnVector;
}

bool hasBitSet(uint32_t flag, uint32_t flags)
{
	return ((flags & flag) == flag);
}

int32_t round(float v)
{
	int32_t t = (int32_t)std::floor(v);
	if((v - t) > 0.5)
		return t + 1;

	return t;
}

uint32_t rand24b()
{
	return ((rand() << 12) ^ (rand())) & (0xFFFFFF);
}

float box_muller(float m, float s)
{
	// normal random variate generator
	// mean m, standard deviation s
	float x1, x2, w, y1;
	static float y2;

	static bool useLast = false;
	if(useLast) // use value from previous call
	{
		y1 = y2;
		useLast = false;
		return (m + y1 * s);
	}

	do
	{
		double r1 = (((float)(rand()) / RAND_MAX));
		double r2 = (((float)(rand()) / RAND_MAX));

		x1 = 2.0 * r1 - 1.0;
		x2 = 2.0 * r2 - 1.0;
		w = x1 * x1 + x2 * x2;
	}
	while(w >= 1.0);
	w = sqrt((-2.0 * log(w)) / w);

	y1 = x1 * w;
	y2 = x2 * w;

	useLast = true;
	return (m + y1 * s);
}

int32_t random_range(int32_t lowestNumber, int32_t highestNumber, DistributionType_t type /*= DISTRO_UNIFORM*/)
{
	if(highestNumber == lowestNumber)
		return lowestNumber;

	if(lowestNumber > highestNumber)
		std::swap(lowestNumber, highestNumber);

	switch(type)
	{
		case DISTRO_UNIFORM:
			return (lowestNumber + ((int32_t)rand24b() % (highestNumber - lowestNumber + 1)));
		case DISTRO_NORMAL:
			return (lowestNumber + int32_t(float(highestNumber - lowestNumber) * (float)std::min((float)1, std::max((float)0, box_muller(0.5, 0.25)))));
		default:
			break;
	}

	const float randMax = 16777216;
	return (lowestNumber + int32_t(float(highestNumber - lowestNumber) * float(1.f - sqrt((1.f * rand24b()) / randMax))));
}

char upchar(char character)
{
	if((character >= 97 && character <= 122) || (character <= -1 && character >= -32))
		character -= 32;

	return character;
}

bool isNumber(char character)
{
	return (character >= 48 && character <= 57);
}

bool isLowercaseLetter(char character)
{
	return (character >= 97 && character <= 122);
}

bool isUppercaseLetter(char character)
{
	return (character >= 65 && character <= 90);
}

bool isPasswordCharacter(char character)
{
	return ((character >= 33 && character <= 47) || (character >= 58 && character <= 64) || (character >= 91 && character <= 96) || (character >= 123 && character <= 126));
}

bool isValidAccountName(std::string text)
{
	toLowerCaseString(text);

	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isLowercaseLetter(text[size]) && !isNumber(text[size]))
			return false;
	}

	return true;
}

bool isValidPassword(std::string text)
{
	toLowerCaseString(text);

	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isLowercaseLetter(text[size]) && !isNumber(text[size]) && !isPasswordCharacter(text[size]))
			return false;
	}

	return true;
}

bool isValidName(std::string text, bool forceUppercaseOnFirstLetter/* = true*/)
{
	uint32_t textLength = text.length(), lenBeforeSpace = 1, lenBeforeQuote = 1, lenBeforeDash = 1, repeatedCharacter = 0;
	char lastChar = 32;
	if(forceUppercaseOnFirstLetter)
	{
		if(!isUppercaseLetter(text[0]))
			return false;
	}
	else if(!isLowercaseLetter(text[0]) && !isUppercaseLetter(text[0]))
		return false;

	for(uint32_t size = 1; size < textLength; size++)
	{
		if(text[size] != 32)
		{
			lenBeforeSpace++;
			if(text[size] != 39)
				lenBeforeQuote++;
			else
			{
				if(lenBeforeQuote <= 1 || size == textLength - 1 || text[size + 1] == 32)
					return false;

				lenBeforeQuote = 0;
			}

			if(text[size] != 45)
				lenBeforeDash++;
			else
			{
				if(lenBeforeDash <= 1 || size == textLength - 1 || text[size + 1] == 32)
					return false;

				lenBeforeDash = 0;
			}

			if(text[size] == lastChar)
			{
				repeatedCharacter++;
				if(repeatedCharacter > 2)
					return false;
			}
			else
				repeatedCharacter = 0;

			lastChar = text[size];
		}
		else
		{
			if(lenBeforeSpace <= 1 || size == textLength - 1 || text[size + 1] == 32)
				return false;

			lenBeforeSpace = lenBeforeQuote = lenBeforeDash = 0;
		}

		if(!(isLowercaseLetter(text[size]) || text[size] == 32 || text[size] == 39 || text[size] == 45
			|| (isUppercaseLetter(text[size]) && text[size - 1] == 32)))
			return false;
	}

	return true;
}

bool isNumbers(std::string text)
{
	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isNumber(text[size]))
			return false;
	}

	return true;
}

bool checkText(std::string text, std::string str)
{
	trimString(text);
	return asLowerCaseString(text) == str;
}

std::string generateRecoveryKey(int32_t fieldCount, int32_t fieldLenght, bool mixCase/* = false*/)
{
	std::stringstream key;
	int32_t i = 0, j = 0, lastNumber = 99, number = 0;

	char character = 0, lastCharacter = 0;
	bool madeNumber = false, madeCharacter = false;
	do
	{
		do
		{
			madeNumber = madeCharacter = false;
			if((mixCase && !random_range(0, 2)) || (!mixCase && (bool)random_range(0, 1)))
			{
				number = random_range(2, 9);
				if(number != lastNumber)
				{
					key << number;
					lastNumber = number;
					madeNumber = true;
				}
			}
			else
			{
				if(mixCase && (bool)random_range(0,1) )
					character = (char)random_range(97, 122);
				else
					character = (char)random_range(65, 90);

				if(character != lastCharacter)
				{
					key << character;
					lastCharacter = character;
					madeCharacter = true;
				}
			}
		}
		while((!madeCharacter && !madeNumber) ? true : (++j && j < fieldLenght));
		lastCharacter = character = number = j = 0;

		lastNumber = 99;
		if(i < fieldCount - 1)
			key << "-";
	}
	while(++i && i < fieldCount);
	return key.str();
}

std::string trimString(std::string& str)
{
	str.erase(str.find_last_not_of(" ") + 1);
	return str.erase(0, str.find_first_not_of(" "));
}

std::string parseParams(tokenizer::iterator &it, tokenizer::iterator end)
{
	if(it == end)
		return "";

	std::string tmp = (*it);
	++it;
	if(tmp[0] == '"')
	{
		tmp.erase(0, 1);
		while(it != end && tmp[tmp.length() - 1] != '"')
		{
			tmp += " " + (*it);
			++it;
		}

		if(tmp.length() > 0 && tmp[tmp.length() - 1] == '"')
			tmp.erase(tmp.length() - 1);
	}

	return tmp;
}

std::string formatDate(time_t _time/* = 0*/)
{
	if(!_time)
		_time = time(NULL);

	const tm* tms = localtime(&_time);
	std::stringstream s;
	if(tms)
		s << tms->tm_mday << "/" << (tms->tm_mon + 1) << "/" << (tms->tm_year + 1900) << " " << tms->tm_hour << ":" << tms->tm_min << ":" << tms->tm_sec;
	else
		s << "UNIX Time: " << (int32_t)_time;

	return s.str();
}

std::string formatDateEx(time_t _time/* = 0*/, std::string format/* = "%d %b %Y, %H:%M:%S"*/)
{
	if(!_time)
		_time = time(NULL);

	const tm* tms = localtime(&_time);
	char buffer[100];
	if(tms)
		strftime(buffer, 25, format.c_str(), tms);
	else
		sprintf(buffer, "UNIX Time: %d", (int32_t)_time);

	return buffer;
}

std::string formatTime(time_t _time/* = 0*/, bool ms/* = false*/)
{
	if(!_time)
		_time = time(NULL);
	else if(ms)
		ms = false;

	const tm* tms = localtime(&_time);
	std::stringstream s;
	if(tms)
	{
		s << tms->tm_hour << ":" << tms->tm_min << ":";
		if(tms->tm_sec < 10)
			s << "0";

		s << tms->tm_sec;
		if(ms)
		{
			timeb t;
			ftime(&t);

			s << "."; // make it format zzz
			if(t.millitm < 10)
				s << "0";

			if(t.millitm < 100)
				s << "0";

			s << t.millitm;
		}
	}
	else
		s << "UNIX Time: " << (int32_t)_time;

	return s.str();
}

std::string convertIPAddress(uint32_t ip)
{
	char buffer[17];
	sprintf(buffer, "%d.%d.%d.%d", ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24));
	return buffer;
}

Skulls_t getSkulls(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "black" || tmpStrValue == "5")
		return SKULL_BLACK;

	if(tmpStrValue == "red" || tmpStrValue == "4")
		return SKULL_RED;

	if(tmpStrValue == "white" || tmpStrValue == "3")
		return SKULL_WHITE;

	if(tmpStrValue == "green" || tmpStrValue == "2")
		return SKULL_GREEN;

	if(tmpStrValue == "yellow" || tmpStrValue == "1")
		return SKULL_YELLOW;

	return SKULL_NONE;
}

PartyShields_t getShields(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "whitenoshareoff" || tmpStrValue == "10")
		return SHIELD_YELLOW_NOSHAREDEXP;

	if(tmpStrValue == "blueshareoff" || tmpStrValue == "9")
		return SHIELD_BLUE_NOSHAREDEXP;

	if(tmpStrValue == "yellowshareblink" || tmpStrValue == "8")
		return SHIELD_YELLOW_NOSHAREDEXP_BLINK;

	if(tmpStrValue == "blueshareblink" || tmpStrValue == "7")
		return SHIELD_BLUE_NOSHAREDEXP_BLINK;

	if(tmpStrValue == "yellowshareon" || tmpStrValue == "6")
		return SHIELD_YELLOW_SHAREDEXP;

	if(tmpStrValue == "blueshareon" || tmpStrValue == "5")
		return SHIELD_BLUE_SHAREDEXP;

	if(tmpStrValue == "yellow" || tmpStrValue == "4")
		return SHIELD_YELLOW;

	if(tmpStrValue == "blue" || tmpStrValue == "3")
		return SHIELD_BLUE;

	if(tmpStrValue == "whiteyellow" || tmpStrValue == "2")
		return SHIELD_WHITEYELLOW;

	if(tmpStrValue == "whiteblue" || tmpStrValue == "1")
		return SHIELD_WHITEBLUE;

	return SHIELD_NONE;
}

GuildEmblems_t getEmblems(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "blue" || tmpStrValue == "3")
		return EMBLEM_BLUE;

	if(tmpStrValue == "red" || tmpStrValue == "2")
		return EMBLEM_RED;

	if(tmpStrValue == "green" || tmpStrValue == "1")
		return EMBLEM_GREEN;

	return EMBLEM_NONE;
}

Direction getDirection(std::string string)
{
	if(string == "north" || string == "n" || string == "0")
		return NORTH;

	if(string == "east" || string == "e" || string == "1")
		return EAST;

	if(string == "south" || string == "s" || string == "2")
		return SOUTH;

	if(string == "west" || string == "w" || string == "3")
		return WEST;

	if(string == "southwest" || string == "south west" || string == "south-west" || string == "sw" || string == "4")
		return SOUTHWEST;

	if(string == "southeast" || string == "south east" || string == "south-east" || string == "se" || string == "5")
		return SOUTHEAST;

	if(string == "northwest" || string == "north west" || string == "north-west" || string == "nw" || string == "6")
		return NORTHWEST;

	if(string == "northeast" || string == "north east" || string == "north-east" || string == "ne" || string == "7")
		return NORTHEAST;

	return SOUTH;
}

Direction getDirectionTo(Position pos1, Position pos2, bool extended/* = true*/)
{
	Direction direction = NORTH;
	if(pos1.x > pos2.x)
	{
		direction = WEST;
		if(extended)
		{
			if(pos1.y > pos2.y)
				direction = NORTHWEST;
			else if(pos1.y < pos2.y)
				direction = SOUTHWEST;
		}
	}
	else if(pos1.x < pos2.x)
	{
		direction = EAST;
		if(extended)
		{
			if(pos1.y > pos2.y)
				direction = NORTHEAST;
			else if(pos1.y < pos2.y)
				direction = SOUTHEAST;
		}
	}
	else
	{
		if(pos1.y > pos2.y)
			direction = NORTH;
		else if(pos1.y < pos2.y)
			direction = SOUTH;
	}

	return direction;
}

Direction getReverseDirection(Direction dir)
{
	switch(dir)
	{
		case NORTH:
			return SOUTH;
		case SOUTH:
			return NORTH;
		case WEST:
			return EAST;
		case EAST:
			return WEST;
		case SOUTHWEST:
			return NORTHEAST;
		case NORTHWEST:
			return SOUTHEAST;
		case NORTHEAST:
			return SOUTHWEST;
		case SOUTHEAST:
			return NORTHWEST;
	}

	return SOUTH;
}

Position getNextPosition(Direction direction, Position pos)
{
	switch(direction)
	{
		case NORTH:
			pos.y--;
			break;
		case SOUTH:
			pos.y++;
			break;
		case WEST:
			pos.x--;
			break;
		case EAST:
			pos.x++;
			break;
		case SOUTHWEST:
			pos.x--;
			pos.y++;
			break;
		case NORTHWEST:
			pos.x--;
			pos.y--;
			break;
		case SOUTHEAST:
			pos.x++;
			pos.y++;
			break;
		case NORTHEAST:
			pos.x++;
			pos.y--;
			break;
	}

	return pos;
}

struct AmmoTypeNames
{
	const char* name;
	Ammo_t ammoType;
};

struct MagicEffectNames
{
	const char* name;
	MagicEffect_t magicEffect;
};

struct ShootTypeNames
{
	const char* name;
	ShootEffect_t shootType;
};

struct CombatTypeNames
{
	const char* name;
	CombatType_t combatType;
};

struct AmmoActionNames
{
	const char* name;
	AmmoAction_t ammoAction;
};

struct FluidTypeNames
{
	const char* name;
	FluidTypes_t fluidType;
};

struct SkillIdNames
{
	const char* name;
	skills_t skillId;
};

MagicEffectNames magicEffectNames[] =
{
	{"redspark",		MAGIC_EFFECT_DRAW_BLOOD},
	{"bluebubble",		MAGIC_EFFECT_LOSE_ENERGY},
	{"poff",		MAGIC_EFFECT_POFF},
	{"yellowspark",		MAGIC_EFFECT_BLOCKHIT},
	{"explosionarea",	MAGIC_EFFECT_EXPLOSION_AREA},
	{"explosion",		MAGIC_EFFECT_EXPLOSION_DAMAGE},
	{"firearea",		MAGIC_EFFECT_FIRE_AREA},
	{"yellowbubble",	MAGIC_EFFECT_YELLOW_RINGS},
	{"greenbubble",		MAGIC_EFFECT_POISON_RINGS},
	{"blackspark",		MAGIC_EFFECT_HIT_AREA},
	{"teleport",		MAGIC_EFFECT_TELEPORT},
	{"energy",		MAGIC_EFFECT_ENERGY_DAMAGE},
	{"blueshimmer",		MAGIC_EFFECT_WRAPS_BLUE},
	{"redshimmer",		MAGIC_EFFECT_WRAPS_RED},
	{"greenshimmer",	MAGIC_EFFECT_WRAPS_GREEN},
	{"fire",		MAGIC_EFFECT_HITBY_FIRE},
	{"greenspark",		MAGIC_EFFECT_POISON},
	{"mortarea",		MAGIC_EFFECT_MORT_AREA},
	{"greennote",		MAGIC_EFFECT_SOUND_GREEN},
	{"rednote",		MAGIC_EFFECT_SOUND_RED},
	{"poison",		MAGIC_EFFECT_POISON_AREA},
	{"yellownote",		MAGIC_EFFECT_SOUND_YELLOW},
	{"purplenote",		MAGIC_EFFECT_SOUND_PURPLE},
	{"bluenote",		MAGIC_EFFECT_SOUND_BLUE},
	{"whitenote",		MAGIC_EFFECT_SOUND_WHITE},
	{"bubbles",		MAGIC_EFFECT_BUBBLES},
	{"dice",		MAGIC_EFFECT_CRAPS},
	{"giftwraps",		MAGIC_EFFECT_GIFT_WRAPS},
	{"yellowfirework",	MAGIC_EFFECT_FIREWORK_YELLOW},
	{"redfirework",		MAGIC_EFFECT_FIREWORK_RED},
	{"bluefirework",	MAGIC_EFFECT_FIREWORK_BLUE},
	{"stun",		MAGIC_EFFECT_STUN},
	{"sleep",		MAGIC_EFFECT_SLEEP},
	{"watercreature",	MAGIC_EFFECT_WATERCREATURE},
	{"groundshaker",	MAGIC_EFFECT_GROUNDSHAKER},
	{"hearts",		MAGIC_EFFECT_HEARTS},
	{"fireattack",		MAGIC_EFFECT_FIREATTACK},
	{"energyarea",		MAGIC_EFFECT_ENERGY_AREA},
	{"smallclouds",		MAGIC_EFFECT_SMALLCLOUDS},
	{"holydamage",		MAGIC_EFFECT_HOLYDAMAGE},
	{"bigclouds",		MAGIC_EFFECT_BIGCLOUDS},
	{"icearea",		MAGIC_EFFECT_ICEAREA},
	{"icetornado",		MAGIC_EFFECT_ICETORNADO},
	{"iceattack",		MAGIC_EFFECT_ICEATTACK},
	{"stones",		MAGIC_EFFECT_STONES},
	{"smallplants",		MAGIC_EFFECT_SMALLPLANTS},
	{"carniphila",		MAGIC_EFFECT_CARNIPHILA},
	{"purpleenergy",	MAGIC_EFFECT_PURPLEENERGY},
	{"yellowenergy",	MAGIC_EFFECT_YELLOWENERGY},
	{"holyarea",		MAGIC_EFFECT_HOLYAREA},
	{"bigplants",		MAGIC_EFFECT_BIGPLANTS},
	{"cake",		MAGIC_EFFECT_CAKE},
	{"giantice",		MAGIC_EFFECT_GIANTICE},
	{"watersplash",		MAGIC_EFFECT_WATERSPLASH},
	{"plantattack",		MAGIC_EFFECT_PLANTATTACK},
	{"tutorialarrow",	MAGIC_EFFECT_TUTORIALARROW},
	{"tutorialsquare",	MAGIC_EFFECT_TUTORIALSQUARE},
	{"mirrorhorizontal",	MAGIC_EFFECT_MIRRORHORIZONTAL},
	{"mirrorvertical",	MAGIC_EFFECT_MIRRORVERTICAL},
	{"skullhorizontal",	MAGIC_EFFECT_SKULLHORIZONTAL},
	{"skullvertical",	MAGIC_EFFECT_SKULLVERTICAL},
	{"assassin",		MAGIC_EFFECT_ASSASSIN},
	{"stepshorizontal",	MAGIC_EFFECT_STEPSHORIZONTAL},
	{"bloodysteps",		MAGIC_EFFECT_BLOODYSTEPS},
	{"stepsvertical",	MAGIC_EFFECT_STEPSVERTICAL},
	{"yalaharighost",	MAGIC_EFFECT_YALAHARIGHOST},
	{"bats",		MAGIC_EFFECT_BATS},
	{"smoke",		MAGIC_EFFECT_SMOKE},
	{"insects",		MAGIC_EFFECT_INSECTS},
	{"dragonhead",	MAGIC_EFFECT_DRAGONHEAD},
	{"efeito70",	MAGIC_EFFECT_70},
	{"efeito71",	MAGIC_EFFECT_71},
	{"efeito72",	MAGIC_EFFECT_72},
	{"efeito73",	MAGIC_EFFECT_73},
	{"efeito74",	MAGIC_EFFECT_74},
	{"efeito75",	MAGIC_EFFECT_75},
	{"efeito76",	MAGIC_EFFECT_76},
	{"efeito77",	MAGIC_EFFECT_77},
	{"efeito78",	MAGIC_EFFECT_78},
	{"efeito79",	MAGIC_EFFECT_79},
	{"efeito80",	MAGIC_EFFECT_80},
	{"efeito81",	MAGIC_EFFECT_81},
	{"efeito82",	MAGIC_EFFECT_82},
	{"efeito83",	MAGIC_EFFECT_83},
	{"efeito84",	MAGIC_EFFECT_84},
	{"efeito85",	MAGIC_EFFECT_85},
	{"efeito86",	MAGIC_EFFECT_86},
	{"efeito87",	MAGIC_EFFECT_87},
	{"efeito88",	MAGIC_EFFECT_88},
	{"efeito89",	MAGIC_EFFECT_89},
	{"efeito90",	MAGIC_EFFECT_90},
	{"efeito91",	MAGIC_EFFECT_91},
	{"efeito92",	MAGIC_EFFECT_92},
	{"efeito93",	MAGIC_EFFECT_93},
	{"efeito94",	MAGIC_EFFECT_94},
	{"efeito95",	MAGIC_EFFECT_95},
	{"efeito96",	MAGIC_EFFECT_96},
	{"efeito97",	MAGIC_EFFECT_97},
	{"efeito98",	MAGIC_EFFECT_98},
	{"efeito99",	MAGIC_EFFECT_99},
	{"efeito100",	MAGIC_EFFECT_100},
	{"efeito101",	MAGIC_EFFECT_101},
	{"efeito102",	MAGIC_EFFECT_102},
	{"efeito103",	MAGIC_EFFECT_103},
	{"efeito104",	MAGIC_EFFECT_104},
	{"efeito105",	MAGIC_EFFECT_105},
	{"efeito106",	MAGIC_EFFECT_106},
	{"efeito107",	MAGIC_EFFECT_107},
	{"efeito108",	MAGIC_EFFECT_108},
	{"efeito109",	MAGIC_EFFECT_109},
	{"efeito110",	MAGIC_EFFECT_110},
	{"efeito111",	MAGIC_EFFECT_111},
	{"efeito112",	MAGIC_EFFECT_112},
	{"efeito113",	MAGIC_EFFECT_113},
	{"efeito114",	MAGIC_EFFECT_114},
	{"efeito115",	MAGIC_EFFECT_115},
	{"efeito116",	MAGIC_EFFECT_116},
	{"efeito117",	MAGIC_EFFECT_117},
	{"efeito118",	MAGIC_EFFECT_118},
	{"efeito119",	MAGIC_EFFECT_119},
	{"efeito120",	MAGIC_EFFECT_120},
	{"efeito121",	MAGIC_EFFECT_121},
	{"efeito122",	MAGIC_EFFECT_122},
	{"efeito123",	MAGIC_EFFECT_123},
	{"efeito124",	MAGIC_EFFECT_124},
	{"efeito125",	MAGIC_EFFECT_125},
	{"efeito126",	MAGIC_EFFECT_126},
	{"efeito127",	MAGIC_EFFECT_127},
	{"efeito128",	MAGIC_EFFECT_128},
	{"efeito129",	MAGIC_EFFECT_129},
	{"efeito130",	MAGIC_EFFECT_130},
	{"efeito131",	MAGIC_EFFECT_131},
	{"efeito132",	MAGIC_EFFECT_132},
	{"efeito133",	MAGIC_EFFECT_133},
	{"efeito134",	MAGIC_EFFECT_134},
	{"efeito135",	MAGIC_EFFECT_135},
	{"efeito136",	MAGIC_EFFECT_136},
	{"efeito137",	MAGIC_EFFECT_137},
	{"efeito138",	MAGIC_EFFECT_138},
	{"efeito139",	MAGIC_EFFECT_139},
	{"efeito140",	MAGIC_EFFECT_140},
	{"efeito141",	MAGIC_EFFECT_141},
	{"efeito142",	MAGIC_EFFECT_142},
	{"efeito143",	MAGIC_EFFECT_143},
	{"efeito144",	MAGIC_EFFECT_144},
	{"efeito145",	MAGIC_EFFECT_145},
	{"efeito146",	MAGIC_EFFECT_146},
	{"efeito147",	MAGIC_EFFECT_147},
	{"efeito148",	MAGIC_EFFECT_148},
	{"efeito149",	MAGIC_EFFECT_149},
	{"efeito150",	MAGIC_EFFECT_150},
	{"efeito151",	MAGIC_EFFECT_151},
	{"efeito152",	MAGIC_EFFECT_152},
	{"efeito153",	MAGIC_EFFECT_153},
	{"efeito154",	MAGIC_EFFECT_154},
	{"efeito155",	MAGIC_EFFECT_155},
	{"efeito156",	MAGIC_EFFECT_156},
	{"efeito157",	MAGIC_EFFECT_157},
	{"efeito158",	MAGIC_EFFECT_158},
	{"efeito159",	MAGIC_EFFECT_159},
	{"efeito160",	MAGIC_EFFECT_160},
	{"efeito161",	MAGIC_EFFECT_161},
	{"efeito162",	MAGIC_EFFECT_162},
	{"efeito163",	MAGIC_EFFECT_163},
	{"efeito164",	MAGIC_EFFECT_164},
	{"efeito165",	MAGIC_EFFECT_165},
	{"efeito166",	MAGIC_EFFECT_166},
	{"efeito167",	MAGIC_EFFECT_167},
	{"efeito168",	MAGIC_EFFECT_168},
	{"efeito169",	MAGIC_EFFECT_169},
	{"efeito170",	MAGIC_EFFECT_170},
	{"efeito171",	MAGIC_EFFECT_171},
	{"efeito172",	MAGIC_EFFECT_172},
	{"efeito173",	MAGIC_EFFECT_173},
	{"efeito174",	MAGIC_EFFECT_174},
	{"efeito175",	MAGIC_EFFECT_175},
	{"efeito176",	MAGIC_EFFECT_176},
	{"efeito177",	MAGIC_EFFECT_177},
	{"efeito178",	MAGIC_EFFECT_178},
	{"efeito179",	MAGIC_EFFECT_179},
	{"efeito180",	MAGIC_EFFECT_180},
	{"efeito181",	MAGIC_EFFECT_181},
	{"efeito182",	MAGIC_EFFECT_182},
	{"efeito183",	MAGIC_EFFECT_183},
	{"efeito184",	MAGIC_EFFECT_184},
	{"efeito185",	MAGIC_EFFECT_185},
	{"efeito186",	MAGIC_EFFECT_186},
	{"efeito187",	MAGIC_EFFECT_187},
	{"efeito188",	MAGIC_EFFECT_188},
	{"efeito189",	MAGIC_EFFECT_189},
	{"efeito190",	MAGIC_EFFECT_190},
	{"efeito191",	MAGIC_EFFECT_191},
	{"efeito192",	MAGIC_EFFECT_192},
	{"efeito193",	MAGIC_EFFECT_193},
	{"efeito194",	MAGIC_EFFECT_194},
	{"efeito195",	MAGIC_EFFECT_195},
	{"efeito196",	MAGIC_EFFECT_196},
	{"efeito197",	MAGIC_EFFECT_197},
	{"efeito198",	MAGIC_EFFECT_198},
	{"efeito199",	MAGIC_EFFECT_199},
	{"efeito200",	MAGIC_EFFECT_200},
	{"efeito201",	MAGIC_EFFECT_201},
	{"efeito202",	MAGIC_EFFECT_202},
	{"efeito203",	MAGIC_EFFECT_203},
	{"efeito204",	MAGIC_EFFECT_204},
	{"efeito205",	MAGIC_EFFECT_205},
	{"efeito206",	MAGIC_EFFECT_206},
	{"efeito207",	MAGIC_EFFECT_207},
	{"efeito208",	MAGIC_EFFECT_208},
	{"efeito209",	MAGIC_EFFECT_209},
	{"efeito210",	MAGIC_EFFECT_210},
	{"efeito211",	MAGIC_EFFECT_211},
	{"efeito212",	MAGIC_EFFECT_212},
	{"efeito213",	MAGIC_EFFECT_213},
	{"efeito214",	MAGIC_EFFECT_214},
	{"efeito215",	MAGIC_EFFECT_215},
	{"efeito216",	MAGIC_EFFECT_216},
	{"efeito217",	MAGIC_EFFECT_217},
	{"efeito218",	MAGIC_EFFECT_218},
	{"efeito219",	MAGIC_EFFECT_219},
	{"efeito220",	MAGIC_EFFECT_220},
	{"efeito221",	MAGIC_EFFECT_221},
	{"efeito222",	MAGIC_EFFECT_222},
	{"efeito223",	MAGIC_EFFECT_223},
	{"efeito224",	MAGIC_EFFECT_224},
	{"efeito225",	MAGIC_EFFECT_225},
	{"efeito226",	MAGIC_EFFECT_226},
	{"efeito227",	MAGIC_EFFECT_227},
	{"efeito228",	MAGIC_EFFECT_228},
	{"efeito229",	MAGIC_EFFECT_229},
	{"efeito230",	MAGIC_EFFECT_230},
	{"efeito231",	MAGIC_EFFECT_231},
	{"efeito232",	MAGIC_EFFECT_232},
	{"efeito233",	MAGIC_EFFECT_233},
	{"efeito234",	MAGIC_EFFECT_234},
	{"efeito235",	MAGIC_EFFECT_235},
	{"efeito236",	MAGIC_EFFECT_236},
	{"efeito237",	MAGIC_EFFECT_237},
	{"efeito238",	MAGIC_EFFECT_238},
	{"efeito239",	MAGIC_EFFECT_239},
	{"efeito240",	MAGIC_EFFECT_240},
	{"efeito241",	MAGIC_EFFECT_241},
	{"efeito242",	MAGIC_EFFECT_242},
	{"efeito243",	MAGIC_EFFECT_243},
	{"efeito244",	MAGIC_EFFECT_244},
	{"efeito245",	MAGIC_EFFECT_245},
	{"efeito246",	MAGIC_EFFECT_246},
	{"efeito247",	MAGIC_EFFECT_247},
	{"efeito248",	MAGIC_EFFECT_248},
	{"efeito249",	MAGIC_EFFECT_249},
	{"efeito250",	MAGIC_EFFECT_250},
	{"efeito251",	MAGIC_EFFECT_251},
	{"efeito252",	MAGIC_EFFECT_252},
	{"efeito253",	MAGIC_EFFECT_253},
	{"efeito254",	MAGIC_EFFECT_254},
	{"efeito255",	MAGIC_EFFECT_255},
	{"semfim",        MAGIC_EFFECT_SEMFIM}
};

ShootTypeNames shootTypeNames[] =
{
	{"spear",		SHOOT_EFFECT_SPEAR},
	{"bolt",		SHOOT_EFFECT_BOLT},
	{"arrow",		SHOOT_EFFECT_ARROW},
	{"fire",		SHOOT_EFFECT_FIRE},
	{"energy",		SHOOT_EFFECT_ENERGY},
	{"poisonarrow",		SHOOT_EFFECT_POISONARROW},
	{"burstarrow",		SHOOT_EFFECT_BURSTARROW},
	{"throwingstar",	SHOOT_EFFECT_THROWINGSTAR},
	{"throwingknife",	SHOOT_EFFECT_THROWINGKNIFE},
	{"smallstone",		SHOOT_EFFECT_SMALLSTONE},
	{"death",		SHOOT_EFFECT_DEATH},
	{"largerock",		SHOOT_EFFECT_LARGEROCK},
	{"snowball",		SHOOT_EFFECT_SNOWBALL},
	{"powerbolt",		SHOOT_EFFECT_POWERBOLT},
	{"poison",		SHOOT_EFFECT_POISONFIELD},
	{"infernalbolt",	SHOOT_EFFECT_INFERNALBOLT},
	{"huntingspear",	SHOOT_EFFECT_HUNTINGSPEAR},
	{"enchantedspear",	SHOOT_EFFECT_ENCHANTEDSPEAR},
	{"redstar",		SHOOT_EFFECT_REDSTAR},
	{"greenstar",		SHOOT_EFFECT_GREENSTAR},
	{"royalspear",		SHOOT_EFFECT_ROYALSPEAR},
	{"sniperarrow",		SHOOT_EFFECT_SNIPERARROW},
	{"onyxarrow",		SHOOT_EFFECT_ONYXARROW},
	{"piercingbolt",	SHOOT_EFFECT_PIERCINGBOLT},
	{"whirlwindsword",	SHOOT_EFFECT_WHIRLWINDSWORD},
	{"whirlwindaxe",	SHOOT_EFFECT_WHIRLWINDAXE},
	{"whirlwindclub",	SHOOT_EFFECT_WHIRLWINDCLUB},
	{"etherealspear",	SHOOT_EFFECT_ETHEREALSPEAR},
	{"ice",			SHOOT_EFFECT_ICE},
	{"earth",		SHOOT_EFFECT_EARTH},
	{"holy",		SHOOT_EFFECT_HOLY},
	{"suddendeath",		SHOOT_EFFECT_SUDDENDEATH},
	{"flasharrow",		SHOOT_EFFECT_FLASHARROW},
	{"flammingarrow",	SHOOT_EFFECT_FLAMMINGARROW},
	{"flamingarrow",	SHOOT_EFFECT_FLAMMINGARROW},
	{"shiverarrow",		SHOOT_EFFECT_SHIVERARROW},
	{"energyball",		SHOOT_EFFECT_ENERGYBALL},
	{"smallice",		SHOOT_EFFECT_SMALLICE},
	{"smallholy",		SHOOT_EFFECT_SMALLHOLY},
	{"smallearth",		SHOOT_EFFECT_SMALLEARTH},
	{"eartharrow",		SHOOT_EFFECT_EARTHARROW},
	{"explosion",		SHOOT_EFFECT_EXPLOSION},
	{"cake",		SHOOT_EFFECT_CAKE},
	{"missile42",		SHOOT_EFFECT_42},
	{"missile43",		SHOOT_EFFECT_43},
	{"missile44",		SHOOT_EFFECT_44},
	{"missile45",		SHOOT_EFFECT_45},
	{"missile46",		SHOOT_EFFECT_46},
	{"missile47",		SHOOT_EFFECT_47},
	{"missile48",		SHOOT_EFFECT_48},
	{"missile49",		SHOOT_EFFECT_49},
	{"missile50",		SHOOT_EFFECT_50},
	{"missile51",		SHOOT_EFFECT_51},
	{"missile52",		SHOOT_EFFECT_52},
	{"missile53",		SHOOT_EFFECT_53},
	{"missile54",		SHOOT_EFFECT_54},
	{"missile55",		SHOOT_EFFECT_55},
	{"missile56",		SHOOT_EFFECT_56},
	{"missile57",		SHOOT_EFFECT_57},
	{"missile58",		SHOOT_EFFECT_58},
	{"missile59",		SHOOT_EFFECT_59},
	{"missile60",		SHOOT_EFFECT_60},
	{"missile61",		SHOOT_EFFECT_61},
	{"missile62",		SHOOT_EFFECT_62},
	{"missile63",		SHOOT_EFFECT_63},
	{"missile64",		SHOOT_EFFECT_64},
	{"missile65",		SHOOT_EFFECT_65},
	{"missile66",		SHOOT_EFFECT_66},
	{"missile67",		SHOOT_EFFECT_67},
	{"missile68",		SHOOT_EFFECT_68},
	{"missile69",		SHOOT_EFFECT_69},
	{"missile70",		SHOOT_EFFECT_70},
	{"missile71",		SHOOT_EFFECT_71},
	{"missile72",		SHOOT_EFFECT_72},
	{"missile73",		SHOOT_EFFECT_73},
	{"missile74",		SHOOT_EFFECT_74},
	{"missile75",		SHOOT_EFFECT_75},
	{"missile76",		SHOOT_EFFECT_76},
	{"missile77",		SHOOT_EFFECT_77},
	{"missile78",		SHOOT_EFFECT_78},
	{"missile79",		SHOOT_EFFECT_79},
	{"missile80",		SHOOT_EFFECT_80},
	{"missile81",		SHOOT_EFFECT_81},
	{"missile82",		SHOOT_EFFECT_82},
	{"missile83",		SHOOT_EFFECT_83},
	{"missile84",		SHOOT_EFFECT_84},
	{"missile85",		SHOOT_EFFECT_85},
	{"missile86",		SHOOT_EFFECT_86},
	{"missile87",		SHOOT_EFFECT_87},
	{"missile88",		SHOOT_EFFECT_88},
	{"missile89",		SHOOT_EFFECT_89},
	{"missile90",		SHOOT_EFFECT_90},
	{"missile91",		SHOOT_EFFECT_91},
	{"missile92",		SHOOT_EFFECT_92},
	{"missile93",		SHOOT_EFFECT_93},
	{"missile94",		SHOOT_EFFECT_94},
	{"missile95",		SHOOT_EFFECT_95},
	{"missile96",		SHOOT_EFFECT_96},
	{"missile97",		SHOOT_EFFECT_97},
	{"missile98",		SHOOT_EFFECT_98},
	{"missile99",		SHOOT_EFFECT_99},
	{"missile100",		SHOOT_EFFECT_100},
	{"missile101",		SHOOT_EFFECT_101},
	{"missile102",		SHOOT_EFFECT_102},
	{"missile103",		SHOOT_EFFECT_103},
	{"missile104",		SHOOT_EFFECT_104},
	{"missile105",		SHOOT_EFFECT_105},
	{"missile106",		SHOOT_EFFECT_106},
	{"missile107",		SHOOT_EFFECT_107},
	{"missile108",		SHOOT_EFFECT_108},
	{"missile109",		SHOOT_EFFECT_109},
	{"missile110",		SHOOT_EFFECT_110},
	{"missile111",		SHOOT_EFFECT_111},
	{"missile112",		SHOOT_EFFECT_112},
	{"missile113",		SHOOT_EFFECT_113},
	{"missile114",		SHOOT_EFFECT_114},
	{"missile115",		SHOOT_EFFECT_115},
	{"missile116",		SHOOT_EFFECT_116},
	{"missile117",		SHOOT_EFFECT_117},
	{"missile118",		SHOOT_EFFECT_118},
	{"missile119",		SHOOT_EFFECT_119},
	{"missile120",		SHOOT_EFFECT_120},
	{"missile121",		SHOOT_EFFECT_121},
	{"missile122",		SHOOT_EFFECT_122},
	{"missile123",		SHOOT_EFFECT_123},
	{"missile124",		SHOOT_EFFECT_124},
	{"missile125",		SHOOT_EFFECT_125},
	{"missile126",		SHOOT_EFFECT_126},
	{"missile127",		SHOOT_EFFECT_127},
	{"missile128",		SHOOT_EFFECT_128},
	{"missile129",		SHOOT_EFFECT_129},
	{"missile130",		SHOOT_EFFECT_130},
	{"missile131",		SHOOT_EFFECT_131},
	{"missile132",		SHOOT_EFFECT_132},
	{"missile133",		SHOOT_EFFECT_133},
	{"missile134",		SHOOT_EFFECT_134},
	{"missile135",		SHOOT_EFFECT_135},
	{"missile136",		SHOOT_EFFECT_136},
	{"missile137",		SHOOT_EFFECT_137},
	{"missile138",		SHOOT_EFFECT_138},
	{"missile139",		SHOOT_EFFECT_139},
	{"missile140",		SHOOT_EFFECT_140},
	{"missile141",		SHOOT_EFFECT_141},
	{"missile142",		SHOOT_EFFECT_142},
	{"missile143",		SHOOT_EFFECT_143},
	{"missile144",		SHOOT_EFFECT_144},
	{"missile145",		SHOOT_EFFECT_145},
	{"missile146",		SHOOT_EFFECT_146},
	{"missile147",		SHOOT_EFFECT_147},
	{"missile148",		SHOOT_EFFECT_148},
	{"missile149",		SHOOT_EFFECT_149},
	{"missile150",		SHOOT_EFFECT_150},
	{"missile151",		SHOOT_EFFECT_151},
	{"missile152",		SHOOT_EFFECT_152},
	{"missile153",		SHOOT_EFFECT_153},
	{"missile154",		SHOOT_EFFECT_154},
	{"missile155",		SHOOT_EFFECT_155},
	{"missile156",		SHOOT_EFFECT_156},
	{"missile157",		SHOOT_EFFECT_157},
	{"missile158",		SHOOT_EFFECT_158},
	{"missile159",		SHOOT_EFFECT_159},
	{"missile160",		SHOOT_EFFECT_160},
	{"missile161",		SHOOT_EFFECT_161},
	{"missile162",		SHOOT_EFFECT_162},
	{"missile163",		SHOOT_EFFECT_163},
	{"missile164",		SHOOT_EFFECT_164},
	{"missile165",		SHOOT_EFFECT_165},
	{"missile166",		SHOOT_EFFECT_166},
	{"missile167",		SHOOT_EFFECT_167},
	{"missile168",		SHOOT_EFFECT_168},
	{"missile169",		SHOOT_EFFECT_169},
	{"missile170",		SHOOT_EFFECT_170},
	{"missile171",		SHOOT_EFFECT_171},
	{"missile172",		SHOOT_EFFECT_172},
	{"missile173",		SHOOT_EFFECT_173},
	{"missile174",		SHOOT_EFFECT_174},
	{"missile175",		SHOOT_EFFECT_175},
	{"missile176",		SHOOT_EFFECT_176},
	{"missile177",		SHOOT_EFFECT_177},
	{"missile178",		SHOOT_EFFECT_178},
	{"missile179",		SHOOT_EFFECT_179},
	{"missile180",		SHOOT_EFFECT_180},
	{"missile181",		SHOOT_EFFECT_181},
	{"missile182",		SHOOT_EFFECT_182},
	{"missile183",		SHOOT_EFFECT_183},
	{"missile184",		SHOOT_EFFECT_184},
	{"missile185",		SHOOT_EFFECT_185},
	{"missile186",		SHOOT_EFFECT_186},
	{"missile187",		SHOOT_EFFECT_187},
	{"missile188",		SHOOT_EFFECT_188},
	{"missile189",		SHOOT_EFFECT_189},
	{"missile190",		SHOOT_EFFECT_190},
	{"missile191",		SHOOT_EFFECT_191},
	{"missile192",		SHOOT_EFFECT_192},
	{"missile193",		SHOOT_EFFECT_193},
	{"missile194",		SHOOT_EFFECT_194},
	{"missile195",		SHOOT_EFFECT_195},
	{"missile196",		SHOOT_EFFECT_196},
	{"missile197",		SHOOT_EFFECT_197},
	{"missile198",		SHOOT_EFFECT_198},
	{"missile199",		SHOOT_EFFECT_199},
	{"missile200",		SHOOT_EFFECT_200},
	{"missile201",		SHOOT_EFFECT_201},
	{"missile202",		SHOOT_EFFECT_202},
	{"missile203",		SHOOT_EFFECT_203},
	{"missile204",		SHOOT_EFFECT_204},
	{"missile205",		SHOOT_EFFECT_205},
	{"missile206",		SHOOT_EFFECT_206},
	{"missile207",		SHOOT_EFFECT_207},
	{"missile208",		SHOOT_EFFECT_208},
	{"missile209",		SHOOT_EFFECT_209},
	{"missile210",		SHOOT_EFFECT_210},
	{"missile211",		SHOOT_EFFECT_211},
	{"missile212",		SHOOT_EFFECT_212},
	{"missile213",		SHOOT_EFFECT_213},
	{"missile214",		SHOOT_EFFECT_214},
	{"missile215",		SHOOT_EFFECT_215},
	{"missile216",		SHOOT_EFFECT_216},
	{"missile217",		SHOOT_EFFECT_217},
	{"missile218",		SHOOT_EFFECT_218},
	{"missile219",		SHOOT_EFFECT_219},
	{"missile220",		SHOOT_EFFECT_220},
	{"missile221",		SHOOT_EFFECT_221},
	{"missile222",		SHOOT_EFFECT_222},
	{"missile223",		SHOOT_EFFECT_223},
	{"missile224",		SHOOT_EFFECT_224},
	{"missile225",		SHOOT_EFFECT_225},
	{"missile226",		SHOOT_EFFECT_226},
	{"missile227",		SHOOT_EFFECT_227},
	{"missile228",		SHOOT_EFFECT_228},
	{"missile229",		SHOOT_EFFECT_229},
	{"missile230",		SHOOT_EFFECT_230},
	{"missile231",		SHOOT_EFFECT_231},
	{"missile232",		SHOOT_EFFECT_232},
	{"missile233",		SHOOT_EFFECT_233},
	{"missile234",		SHOOT_EFFECT_234},
	{"missile235",		SHOOT_EFFECT_235},
	{"missile236",		SHOOT_EFFECT_236},
	{"missile237",		SHOOT_EFFECT_237},
	{"missile238",		SHOOT_EFFECT_238},
	{"missile239",		SHOOT_EFFECT_239},
	{"missile240",		SHOOT_EFFECT_240},
	{"missile241",		SHOOT_EFFECT_241},
	{"missile242",		SHOOT_EFFECT_242},
	{"missile243",		SHOOT_EFFECT_243},
	{"missile244",		SHOOT_EFFECT_244},
	{"missile245",		SHOOT_EFFECT_245},
	{"missile246",		SHOOT_EFFECT_246},
	{"missile247",		SHOOT_EFFECT_247},
	{"missile248",		SHOOT_EFFECT_248},
	{"missile249",		SHOOT_EFFECT_249},
	{"missile250",		SHOOT_EFFECT_250},
	{"missile251",		SHOOT_EFFECT_251},
	{"missile252",		SHOOT_EFFECT_252},
	{"missile253",		SHOOT_EFFECT_253},
	{"missile254",		SHOOT_EFFECT_254},
	{"missile255",		SHOOT_EFFECT_254},
	{"semfim",		SHOOT_EFFECT_SEMFIM}
};

CombatTypeNames combatTypeNames[] =
{
	{"physical",		COMBAT_PHYSICALDAMAGE},
	{"energy",		COMBAT_ENERGYDAMAGE},
	{"earth",		COMBAT_EARTHDAMAGE},
	{"fire",		COMBAT_FIREDAMAGE},
	{"undefined",		COMBAT_UNDEFINEDDAMAGE},
	{"lifedrain",		COMBAT_LIFEDRAIN},
	{"life drain",		COMBAT_LIFEDRAIN},
	{"manadrain",		COMBAT_MANADRAIN},
	{"mana drain",		COMBAT_MANADRAIN},
	{"healing",		COMBAT_HEALING},
	{"drown",		COMBAT_DROWNDAMAGE},
	{"ice",			COMBAT_ICEDAMAGE},
	{"holy",		COMBAT_HOLYDAMAGE},
	{"death",		COMBAT_DEATHDAMAGE}
};

AmmoTypeNames ammoTypeNames[] =
{
	{"spear",		AMMO_SPEAR},
	{"arrow",		AMMO_ARROW},
	{"poisonarrow",		AMMO_ARROW},
	{"burstarrow",		AMMO_ARROW},
	{"bolt",		AMMO_BOLT},
	{"powerbolt",		AMMO_BOLT},
	{"smallstone",		AMMO_STONE},
	{"largerock",		AMMO_STONE},
	{"throwingstar",	AMMO_THROWINGSTAR},
	{"throwingknife",	AMMO_THROWINGKNIFE},
	{"snowball",		AMMO_SNOWBALL},
	{"huntingspear",	AMMO_SPEAR},
	{"royalspear",		AMMO_SPEAR},
	{"enchantedspear",	AMMO_SPEAR},
	{"sniperarrow",		AMMO_ARROW},
	{"onyxarrow",		AMMO_ARROW},
	{"piercingbolt",	AMMO_BOLT},
	{"infernalbolt",	AMMO_BOLT},
	{"flasharrow",		AMMO_ARROW},
	{"flammingarrow",	AMMO_ARROW},
	{"flamingarrow",	AMMO_ARROW},
	{"shiverarrow",		AMMO_ARROW},
	{"eartharrow",		AMMO_ARROW},
	{"etherealspear",	AMMO_SPEAR}
};

AmmoActionNames ammoActionNames[] =
{
	{"move",		AMMOACTION_MOVE},
	{"moveback",		AMMOACTION_MOVEBACK},
	{"move back",		AMMOACTION_MOVEBACK},
	{"removecharge",	AMMOACTION_REMOVECHARGE},
	{"remove charge",	AMMOACTION_REMOVECHARGE},
	{"removecount",		AMMOACTION_REMOVECOUNT},
	{"remove count",	AMMOACTION_REMOVECOUNT}
};

FluidTypeNames fluidTypeNames[] =
{
	{"none",		FLUID_NONE},
	{"water",		FLUID_WATER},
	{"blood",		FLUID_BLOOD},
	{"beer",		FLUID_BEER},
	{"slime",		FLUID_SLIME},
	{"lemonade",		FLUID_LEMONADE},
	{"milk",		FLUID_MILK},
	{"mana",		FLUID_MANA},
	{"life",		FLUID_LIFE},
	{"oil",			FLUID_OIL},
	{"urine",		FLUID_URINE},
	{"coconutmilk",		FLUID_COCONUTMILK},
	{"coconut milk",	FLUID_COCONUTMILK},
	{"wine",		FLUID_WINE},
	{"mud",			FLUID_MUD},
	{"fruitjuice",		FLUID_FRUITJUICE},
	{"fruit juice",		FLUID_FRUITJUICE},
	{"lava",		FLUID_LAVA},
	{"rum",			FLUID_RUM},
	{"swamp",		FLUID_SWAMP},
	{"tea",			FLUID_TEA},
	{"mead",		FLUID_MEAD}
};

SkillIdNames skillIdNames[] =
{
	{"fist",		SKILL_FIST},
	{"club",		SKILL_CLUB},
	{"sword",		SKILL_SWORD},
	{"axe",			SKILL_AXE},
	{"distance",		SKILL_DIST},
	{"dist",		SKILL_DIST},
	{"shielding",		SKILL_SHIELD},
	{"shield",		SKILL_SHIELD},
	{"fishing",		SKILL_FISH},
	{"fish",		SKILL_FISH},
	{"level",		SKILL__LEVEL},
	{"magiclevel",		SKILL__MAGLEVEL},
	{"magic level",		SKILL__MAGLEVEL}
};

MagicEffect_t getMagicEffect(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(magicEffectNames) / sizeof(MagicEffectNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), magicEffectNames[i].name))
			return magicEffectNames[i].magicEffect;
	}

	return MAGIC_EFFECT_UNKNOWN;
}

ShootEffect_t getShootType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(shootTypeNames) / sizeof(ShootTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), shootTypeNames[i].name))
			return shootTypeNames[i].shootType;
	}

	return SHOOT_EFFECT_UNKNOWN;
}

CombatType_t getCombatType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(combatTypeNames) / sizeof(CombatTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), combatTypeNames[i].name))
			return combatTypeNames[i].combatType;
	}

	return COMBAT_NONE;
}

Ammo_t getAmmoType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(ammoTypeNames) / sizeof(AmmoTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), ammoTypeNames[i].name))
			return ammoTypeNames[i].ammoType;
	}

	return AMMO_NONE;
}

AmmoAction_t getAmmoAction(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(ammoActionNames) / sizeof(AmmoActionNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), ammoActionNames[i].name))
			return ammoActionNames[i].ammoAction;
	}

	return AMMOACTION_NONE;
}

FluidTypes_t getFluidType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(fluidTypeNames) / sizeof(FluidTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), fluidTypeNames[i].name))
			return fluidTypeNames[i].fluidType;
	}

	return FLUID_NONE;
}

skills_t getSkillId(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(skillIdNames) / sizeof(SkillIdNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), skillIdNames[i].name))
			return skillIdNames[i].skillId;
	}

	return SKILL_FIST;
}

std::string getCombatName(CombatType_t combatType)
{
	switch(combatType)
	{
		case COMBAT_PHYSICALDAMAGE:
			return "physical";
		case COMBAT_ENERGYDAMAGE:
			return "energy";
		case COMBAT_EARTHDAMAGE:
			return "earth";
		case COMBAT_FIREDAMAGE:
			return "fire";
		case COMBAT_UNDEFINEDDAMAGE:
			return "undefined";
		case COMBAT_LIFEDRAIN:
			return "life drain";
		case COMBAT_MANADRAIN:
			return "mana drain";
		case COMBAT_HEALING:
			return "healing";
		case COMBAT_DROWNDAMAGE:
			return "drown";
		case COMBAT_ICEDAMAGE:
			return "ice";
		case COMBAT_HOLYDAMAGE:
			return "holy";
		case COMBAT_DEATHDAMAGE:
			return "death";
		default:
			break;
	}

	return "unknown";
}

std::string getSkillName(uint16_t skillId, bool suffix/* = true*/)
{
	switch(skillId)
	{
		case SKILL_FIST:
		{
			std::string tmp = "fist";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_CLUB:
		{
			std::string tmp = "club";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_SWORD:
		{
			std::string tmp = "sword";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_AXE:
		{
			std::string tmp = "axe";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_DIST:
		{
			std::string tmp = "distance";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_SHIELD:
			return "shielding";
		case SKILL_FISH:
			return "fishing";
		case SKILL__MAGLEVEL:
			return "magic level";
		case SKILL__LEVEL:
			return "level";
		default:
			break;
	}

	return "unknown";
}

std::string getReason(int32_t reasonId)
{
	switch(reasonId)
	{
		case 0:
			return "Offensive Name";
		case 1:
			return "Invalid Name Format";
		case 2:
			return "Unsuitable Name";
		case 3:
			return "Name Inciting Rule Violation";
		case 4:
			return "Offensive Statement";
		case 5:
			return "Spamming";
		case 6:
			return "Illegal Advertising";
		case 7:
			return "Off-Topic Public Statement";
		case 8:
			return "Non-English Public Statement";
		case 9:
			return "Inciting Rule Violation";
		case 10:
			return "Bug Abuse";
		case 11:
			return "Game Weakness Abuse";
		case 12:
			return "Using Unofficial Software to Play";
		case 13:
			return "Hacking";
		case 14:
			return "Multi-Clienting";
		case 15:
			return "Account Trading or Sharing";
		case 16:
			return "Threatening Gamemaster";
		case 17:
			return "Pretending to Have Influence on Rule Enforcement";
		case 18:
			return "False Report to Gamemaster";
		case 19:
			return "Destructive Behaviour";
		case 20:
			return "Excessive Unjustified Player Killing";
		default:
			break;
	}

	return "Unknown Reason";
}

std::string getAction(ViolationAction_t actionId, bool ipBanishment)
{
	std::string action = "Unknown";
	switch(actionId)
	{
		case ACTION_NOTATION:
			action = "Notation";
			break;
		case ACTION_NAMEREPORT:
			action = "Name Report";
			break;
		case ACTION_BANISHMENT:
			action = "Banishment";
			break;
		case ACTION_BANREPORT:
			action = "Name Report + Banishment";
			break;
		case ACTION_BANFINAL:
			action = "Banishment + Final Warning";
			break;
		case ACTION_BANREPORTFINAL:
			action = "Name Report + Banishment + Final Warning";
			break;
		case ACTION_STATEMENT:
			action = "Statement Report";
			break;
		//internal use
		case ACTION_DELETION:
			action = "Deletion";
			break;
		case ACTION_NAMELOCK:
			action = "Name Lock";
			break;
		case ACTION_BANLOCK:
			action = "Name Lock + Banishment";
			break;
		case ACTION_BANLOCKFINAL:
			action = "Name Lock + Banishment + Final Warning";
			break;
		default:
			break;
	}

	if(ipBanishment)
		action += " + IP Banishment";

	return action;
}

std::string parseVocationString(StringVec vocStringVec)
{
	std::string str = "";
	if(!vocStringVec.empty())
	{
		for(StringVec::iterator it = vocStringVec.begin(); it != vocStringVec.end(); ++it)
		{
			if((*it) != vocStringVec.front())
			{
				if((*it) != vocStringVec.back())
					str += ", ";
				else
					str += " and ";
			}

			str += (*it);
			str += "s";
		}
	}

	return str;
}

bool parseVocationNode(xmlNodePtr vocationNode, VocationMap& vocationMap, StringVec& vocStringVec, std::string& errorStr)
{
	if(xmlStrcmp(vocationNode->name,(const xmlChar*)"vocation"))
		return true;

	int32_t vocationId = -1;
	std::string strValue, tmpStrValue;
	if(readXMLString(vocationNode, "name", strValue))
	{
		vocationId = Vocations::getInstance()->getVocationId(strValue);
		if(vocationId != -1)
		{
			vocationMap[vocationId] = true;
			int32_t promotedVocation = Vocations::getInstance()->getPromotedVocation(vocationId);
			if(promotedVocation != -1)
				vocationMap[promotedVocation] = true;
		}
		else
		{
			errorStr = "Wrong vocation name: " + strValue;
			return false;
		}
	}
	else if(readXMLString(vocationNode, "id", strValue))
	{
		IntegerVec intVector;
		if(!parseIntegerVec(strValue, intVector))
		{
			errorStr = "Invalid vocation id - '" + strValue + "'";
			return false;
		}

		size_t size = intVector.size();
		for(size_t i = 0; i < size; ++i)
		{
			Vocation* vocation = Vocations::getInstance()->getVocation(intVector[i]);
			if(vocation && vocation->getName() != "")
			{
				vocationId = vocation->getId();
				strValue = vocation->getName();

				vocationMap[vocationId] = true;
				int32_t promotedVocation = Vocations::getInstance()->getPromotedVocation(vocationId);
				if(promotedVocation != -1)
					vocationMap[promotedVocation] = true;
			}
			else
			{
				std::stringstream ss;
				ss << "Wrong vocation id: " << intVector[i];

				errorStr = ss.str();
				return false;
			}
		}
	}

	if(vocationId != -1 && (!readXMLString(vocationNode, "showInDescription", tmpStrValue) || booleanString(tmpStrValue)))
		vocStringVec.push_back(asLowerCaseString(strValue));

	return true;
}

bool parseIntegerVec(std::string str, IntegerVec& intVector)
{
	StringVec strVector = explodeString(str, ";");
	IntegerVec tmpIntVector;
	for(StringVec::iterator it = strVector.begin(); it != strVector.end(); ++it)
	{
		tmpIntVector = vectorAtoi(explodeString((*it), "-"));
		if(!tmpIntVector[0] && it->substr(0, 1) != "0")
			continue;

		intVector.push_back(tmpIntVector[0]);
		if(tmpIntVector.size() > 1)
		{
			while(tmpIntVector[0] < tmpIntVector[1])
				intVector.push_back(++tmpIntVector[0]);
		}
	}

	return true;
}

bool fileExists(const char* filename)
{
	FILE* f = fopen(filename, "rb");
	if(!f)
		return false;

	fclose(f);
	return true;
}

uint32_t adlerChecksum(uint8_t* data, size_t length)
{
	// Keep this check, rarely used I think
	if(length > NETWORK_MAX_SIZE || !length)
		return 0;

	// Crypto++ object
	CryptoPP::Adler32 adler;
	// Digest cash object, cast later
	byte digest[CryptoPP::Adler32::DIGESTSIZE];

	// Do the calculation now
	adler.CalculateDigest(digest, (const byte*)data, length);
	// return uint32_t cast type
	return (uint32_t)(((uint16_t)digest[0] << 8 | digest[1]) << 16) | ((uint16_t)digest[2] << 8 | digest[3]);
}

std::string getFilePath(FileType_t type, std::string name/* = ""*/)
{
	#ifdef __FILESYSTEM_HIERARCHY_STANDARD__
	std::string path = "/var/lib/tfs/";
	#endif
	std::string path = g_config.getString(ConfigManager::DATA_DIRECTORY);
	switch(type)
	{
		case FILE_TYPE_OTHER:
			path += name;
			break;
		case FILE_TYPE_XML:
			path += "XML/" + name;
			break;
		case FILE_TYPE_LOG:
			#ifndef __FILESYSTEM_HIERARCHY_STANDARD__
			path = g_config.getString(ConfigManager::LOGS_DIRECTORY) + name;
			#else
			path = "/var/log/tfs/" + name;
			#endif
			break;
		case FILE_TYPE_MOD:
		{
			#ifndef __FILESYSTEM_HIERARCHY_STANDARD__
			path = "mods/" + name;
			#else
			path = "/usr/share/tfs/" + name;
			#endif
			break;
		}
		case FILE_TYPE_CONFIG:
		{
			#if defined(__HOMEDIR_CONF__)
			if(fileExists("~/.tfs/" + name))
				path = "~/.tfs/" + name;
			else
			#endif
			#if defined(__FILESYSTEM_HIERARCHY_STANDARD__)
				path = "/etc/tfs/" + name;
			#else
				path = name;
			#endif
			break;
		}
		default:
			std::clog << "> ERROR: Wrong file type!" << std::endl;
			break;
	}
	return path;
}
