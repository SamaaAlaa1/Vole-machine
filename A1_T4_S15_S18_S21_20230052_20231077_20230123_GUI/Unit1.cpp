//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop
#include <System.SysUtils.hpp>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)

TForm1 *Form1;
//---------------------------------------------------------------------------
int hexToDecimal(const String& hexStr) {
	try {
		return StrToInt("$" + hexStr);
	} catch (const Exception &e) {
		ShowMessage("Invalid hex string: " + hexStr);
		return 0; // Default to 0 in case of error
	}
}

String decToHex(int decimal_number)
{
	String hex_str = IntToHex(decimal_number, 2);
	hex_str = hex_str.UpperCase();
	return hex_str;
}
String decToHex_(int decimal_number)
{
	String hex_str = IntToHex(decimal_number, 1);
	hex_str = hex_str.UpperCase();
	return hex_str;
}

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

 for (int i = 0; i < 16; i++) {
		TListBoxItem *item = new TListBoxItem(reg);
		item->Text = "00";
		reg->AddObject(item);
	}
for (int i = 0; i < 256; i++) {
	   TListBoxItem *item = new TListBoxItem(memory);
		item->Text = "00";
		memory->AddObject(item);
	}
for (int i = 0; i < 16; i++) {
	TListBoxItem *item = new TListBoxItem(R);
	item->Text = "R" + IntToHex(i, 1);
	R->AddObject(item);
}

}

//---------------------------------------------------------------------------
int pc = 10;
int index = 10;
const int maxInstructions = 1000;
int instructionCount = 0;
String out = "";
void __fastcall TForm1::StoreClick(TObject *Sender)
{

	UnicodeString instruction = load->Text;
	if (instruction.Length() == 4) {
		memory->Items->Strings[index] = instruction.SubString(1, 2);
		index++;
		memory->Items->Strings[index] = instruction.SubString(3, 2);
		index++;
		load->Text = "";
	} else {
		ShowMessage("Instruction must be 4 characters long.");
	}
}

//---------------------------------------------------------------------------

float hexToFloat(const String& hex_value)
{
	int int_value = hexToDecimal(hex_value);
	int exponent = ((int_value >> 4) & 7) - 8;
	float mantissa = (int_value & 15);
	return mantissa * pow(2.0, exponent);
}
String floatToHex(float value)
{
	const float max = hexToFloat("FF");
	const float min = hexToFloat("00");
	if (value > max) return "FF";
	if (value < min) return "00";
	int integer = int(value * 16);
	int exponent = 0;
	while (integer > 15) {
		integer >>= 1;
		exponent++;
	}
	int hex_val = (exponent << 4) | integer;
	return decToHex(hex_val);
}

void __fastcall TForm1::RunClick(TObject *Sender)
{
   output->Text = "";
   while (true) {
   if (instructionCount++ > maxInstructions) {
	   ShowMessage("Exceeded maximum instruction count. Possible infinite loop detected.");
	   break;
   }
   if (pc < 0 || pc >= memory->Items->Count) {
	   ShowMessage("Program counter out of bounds.");
	   break;
   }
   UnicodeString ig = memory->Items->Strings[pc] + memory->Items->Strings[pc + 1];
   pc+=2;
   UnicodeString opcode = ig.SubString(1, 1);
   UnicodeString operand1 = ig.SubString(2, 1);
   UnicodeString operand2 = ig.SubString(3, 1);
   UnicodeString operand3 = ig.SubString(4, 1);
   //ShowMessage("opcode: "+ opcode +"Op1: " + operand1 + ", Op2: " + operand2 + ", Op3: " + operand3);
   if(opcode == "1"){
	  int xy =  hexToDecimal((operand2+operand3));
	  int idg =   hexToDecimal(operand1);
	  reg->Items->Strings[idg] = memory->Items->Strings[xy];
   }
   else if(opcode == "2"){
	   int idg =  hexToDecimal(operand1);
	   reg->Items->Strings[idg] = (operand2 + operand3);
   }
   else if(opcode == "3"){
	if (operand3 == "0" && operand2 == "0") {
		int idg = hexToDecimal(operand1);
		memory->Items->Strings[0] = reg->Items->Strings[idg];
		int hex = hexToDecimal(memory->Items->Strings[0]);
		//ShowMessage(hex);
		if(hex == 32) out+=" ";
		else out+= String(hex % 16);
//		ShowMessage("Operand1: " + operand1 + ", Operand2: " + operand2 + ", Operand3: " + operand3);
//		ShowMessage("Hex Value from Memory[0]: " + memory->Items->Strings[0] + " (IDG: " + IntToStr(idg) + ")");
		output->Text = out;
	}
	else {
		int xy = hexToDecimal(operand2 + operand3);
		int idg = hexToDecimal(operand1);
		if (xy < memory->Items->Count && idg < reg->Items->Count) {
			memory->Items->Strings[xy] = reg->Items->Strings[idg];
		} else {
			ShowMessage("Invalid memory or register index.");
		}
	}
}
   else if(opcode == "4"){
	   int idg1 = hexToDecimal(operand2);
	   int idg2 = hexToDecimal(operand3);
	   reg->Items->Strings[idg2] = reg->Items->Strings[idg1];
   }
   else if(opcode == "5"){
	  int s = hexToDecimal(operand2);
	  int t = hexToDecimal(operand3);
	  int r =  hexToDecimal(operand1);
	  int a = hexToDecimal(reg->Items->Strings[s]);
	  int b = hexToDecimal(reg->Items->Strings[t]);
	  int res = (a+b)%16;
	  reg->Items->Strings[r] = decToHex(res);
   }
   else if(opcode == "6"){
	  int s = hexToFloat(operand2);
	  int t = hexToFloat(operand3);
	  int r = hexToFloat(operand1);
	  float a = hexToFloat(reg->Items->Strings[s]);
	  float b = hexToFloat(reg->Items->Strings[t]);
	  float res = a+b;
	  reg->Items->Strings[r] = floatToHex(res);
   }
   else if(opcode == "7"){
	  int s = hexToDecimal(operand2);
	  int t = hexToDecimal(operand3);
	  int r = hexToDecimal(operand1);
	  int a = hexToDecimal(reg->Items->Strings[s]);
	  int b = hexToDecimal(reg->Items->Strings[t]);
	  int res = a|b;
	  String hexValue;
	  if (res == 0) {
		hexValue = "00";
	  }
	  else {
		 hexValue = decToHex(res);
	  }
	  reg->Items->Strings[r] = hexValue;
   }
   else if(opcode == "8"){
	  int s = hexToDecimal(operand2);
	  int t = hexToDecimal(operand3);
	  int r = hexToDecimal(operand1);
	  int a = hexToDecimal(reg->Items->Strings[s]);
	  int b = hexToDecimal(reg->Items->Strings[t]);
	  int res = a&b;
	  reg->Items->Strings[r] = decToHex(res);
   }
   else if(opcode == "9"){
	  int s = hexToDecimal(operand2);
	  int t = hexToDecimal(operand3);
	  int r =  hexToDecimal(operand1);
	  int a = hexToDecimal(reg->Items->Strings[s]);
	  int b = hexToDecimal(reg->Items->Strings[t]);
	  int res = a^b;
	  reg->Items->Strings[r] = decToHex(res);
   }
   else if(opcode == "A"){
	 int r = hexToDecimal(operand1);
	 int x =  hexToDecimal(operand3);
	 int a = hexToDecimal(reg->Items->Strings[r]);
	 x = x % 16;
	 int rotatedValue = (a << x) | (a >> (16 - x));
	 rotatedValue &= 0xFFFF;
	 reg->Items->Strings[r] = decToHex(rotatedValue);
   }
   else if(opcode == "B") {
	int xy = hexToDecimal(operand2 + operand3); // Jump target address
	int idg = hexToDecimal(operand1);           // Register index for comparison

	// Convert register contents to decimal for proper comparison
	int regVal = hexToDecimal(reg->Items->Strings[idg]);
	int compVal = hexToDecimal(reg->Items->Strings[0]);
	if (regVal == compVal) {  // Conditional jump if values match
		pc = xy;
	}
}


   else if(opcode == "C"&& operand1 == "0" && operand2 == "0" && operand3 == "0"){
		pc = 10;
		break;
   }
   else if(opcode == "D"){
	 int xy =  hexToDecimal(operand2+operand3);
	 int idg =  hexToDecimal(operand1);
	 if(reg->Items->Strings[idg] > reg->Items->Strings[0]){
	  pc = xy;
	 }
   }

   }
   }


//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   for (int i = 0; i < 256; i++) {
		memory->Items->Strings[i] = "00";
	}
	pc = 10;
	index = 10;
	output->Text = "";
	out = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	 for (int i = 0; i < 16; i++) {
		reg->Items->Strings[i] = "00";
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if (OpenDialog1->Execute()) {
		// Clear memory before loading new instructions
		for (int i = 0; i < 256; i++) {
			memory->Items->Strings[i] = "00";
		}

		String filename = OpenDialog1->FileName;
		TStringList *lineList = nullptr;
		try {
			lineList = new TStringList();
			lineList->LoadFromFile(filename);

			int index_ = 10; // Start loading from index 10
			for (int i = 0; i < lineList->Count && index_ < 256; i++) {
				String line = lineList->Strings[i];
				if (line.Length() == 4) {
					memory->Items->Strings[index_++] = line.SubString(1, 2);
					memory->Items->Strings[index_++] = line.SubString(3, 2);
				}
			}
		} catch (const Exception &e) {
			ShowMessage("Error reading file: " + e.Message);
		}
		delete lineList;
	}
}



//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

