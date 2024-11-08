//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TListBox *reg;
	TEdit *load;
	TButton *Store;
	TButton *Run;
	TButton *Button1;
	TButton *Button2;
	TBrushObject *Brush1;
	TListBox *memory;
	TButton *Button3;
	TOpenDialog *OpenDialog1;
	TEdit *output;
	TListBox *R;
	TLabel *cpu;
	TColorKeyAnimation *ColorKeyAnimation1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	void __fastcall StoreClick(TObject *Sender);
	void __fastcall RunClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
