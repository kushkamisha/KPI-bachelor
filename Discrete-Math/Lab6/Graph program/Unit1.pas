unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, Menus;

const
  Nmax = 15;
type
  Tcoords = array[1..Nmax,1..2] of Integer;
  Tmatrix = array[1..Nmax,1..Nmax] of Integer;
  TForm1 = class(TForm)
    mm1: TMainMenu;
    N11: TMenuItem;
    N21: TMenuItem;
    N31: TMenuItem;
    pb1: TPaintBox;
    procedure FormCreate(Sender: TObject);
    procedure pb1Click(Sender: TObject);
    procedure N21Click(Sender: TObject);
    procedure N11Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  number,cclick,cnumber,cnumber1,cnumber2,rebro: Byte;
  coords: Tcoords;
  matrix: Tmatrix;
  visited: array[1..nmax] of Boolean;
  componenta: Byte;

implementation

{$R *.dfm}

function hit(a,b,n:integer;g:Tcoords):byte;
  var
    i,res: Byte;
  begin
    res := 0;
    for i:=1 to n do
     if (Abs(a-g[i,1])<20) and (Abs(b-g[i,2])<20) then
       res := i;
    hit := res;
  end;

procedure TForm1.FormCreate(Sender: TObject);
  var
    i,j: Byte;
  begin
    number := 0;
    for i:=1 to Nmax do
      for j:=1 to Nmax do
        matrix[i,j] := 0;
    cclick := 0;
    cnumber := 0;
    cnumber1 := 0;
    cnumber2 := 0;
    rebro := 0;
  end;

procedure TForm1.pb1Click(Sender: TObject);
  var
    x,y,cx,cy,x_rebro,y_rebro: Integer;
  begin
    if number < Nmax then
    begin
      inc(number);
      x := Mouse.CursorPos.X - Form1.Left - 15;
      y := Mouse.CursorPos.Y - Form1.Top - 60;
      if hit(x,y,number,coords) = 0 then
      begin
        coords[number,1] := x;
        coords[number,2] := y;
        pb1.Canvas.Ellipse(x-10,y-10,x+10,y+10);
        if number < 10 then
          pb1.Canvas.TextOut(x-3,y-7,IntToStr(number))
        else
          pb1.Canvas.TextOut(x-6,y-7,IntToStr(number));
      end else
        begin
          Dec(number);
          inc(cclick);
          if (cclick mod 2) = 0 then
          begin
            matrix[cnumber,hit(x,y,number,coords)] := 1;
            matrix[hit(x,y,number,coords),cnumber] := 1;
            //cnumber - 1-ая вершина
            //hit(x,y,number,coords) - 2-ая вершина
            pb1.Canvas.MoveTo(coords[cnumber,1],coords[cnumber,2]);
            pb1.Canvas.LineTo(coords[hit(x,y,number,coords),1],coords[hit(x,y,number,coords),2]);
            x_rebro := (coords[cnumber,1] + coords[hit(x,y,number,coords),1]) div 2;
            y_rebro := (coords[cnumber,2] + coords[hit(x,y,number,coords),2]) div 2;
            pb1.Canvas.TextOut(x_rebro - 2, y_rebro - 3, '1');

            //Перерисовываем 1 вершину
            cnumber1 := hit(x,y,number,coords);
            cx := coords[hit(x,y,cnumber1,coords),1];
            cy := coords[hit(x,y,cnumber1,coords),2];
            pb1.Canvas.Ellipse(cx-10, cy-10, cx+10, cy+10);
            if cnumber1 < 10 then
              pb1.Canvas.TextOut(cx-3, cy-7, IntToStr(cnumber1))
            else
              pb1.Canvas.TextOut(cx-6, cy-7, IntToStr(cnumber1));

            //Перерисовываем 2 вершину
            cx := coords[cnumber,1];
            cy := coords[cnumber,2];
            pb1.Canvas.Ellipse(cx-10, cy-10, cx+10, cy+10);
            if cnumber < 10 then
              pb1.Canvas.TextOut(cx-3, cy-7, IntToStr(cnumber))
            else
              pb1.Canvas.TextOut(cx-6, cy-7, IntToStr(cnumber));

            cclick := 0;
            inc(rebro);
          end;
          cnumber := hit(x,y,number,coords);
        end;
    end;
  end;

procedure TForm1.N21Click(Sender: TObject);
  var
    visited: array[1..Nmax,1..Nmax] of Byte;
    previous: array[1..Nmax] of Integer;
    summa: array[1..Nmax] of Byte;
    i,j,k,ndeep,nulls,container: Byte;
  begin
    for i:=1 to number do
      previous[i] := 0;
    for i:=1 to number do
      for j:=1 to number do
        visited[i,j] := 0;
    previous[1] := 1;
    for ndeep:=1 to number do
    begin
      i := ndeep;
      //flag := True;
      //ShowMessage('ndeep-> '+IntToStr(ndeep));
      j := 1;
      k := 2;
      while True do
      begin
        while ((matrix[i,j]=0) or (visited[ndeep,j]=1)) and (j<=number) do
          Inc(j);
        if j=number+1 then
        begin
          if previous[k-2] <= Nmax then
          begin
            i := previous[k-2];//Aica?ao e i?aauaouae oi?ea aey auoiaa ec ooieea
            //ShowMessage(IntToStr(i)); //- Iieacuaaao aecoaeuii iiene a aeoaeio
            dec(k);
          end else
            Break;//flag := False;
        end else
        begin
          visited[ndeep,j] := 1;
          //ShowMessage(IntToStr(j));
          previous[k] := j;
          inc(k);
          i := j;
          j := 1;
        end;
        j := 1;
        {for i:=1 to k do
          ShowMessage(IntToStr(previous[i]));}
      end;
      {for i:=1 to number do
        ShowMessage(IntToStr(ndeep)+ '->'+intToStr(i)+' '+IntToStr(visited[ndeep,i]));}
    end;
    for i:=1 to number do
      summa[i] := 0;
    for i:=1 to number do
      for j:=1 to number do
        summa[i] := summa[i] + visited[j,i];

    {for i:=1 to number do
      ShowMessage('summa '+IntToStr(summa[i]));}
    container := 0;
    nulls := 0;
    componenta := 0;
    for i:=1 to number do
      if summa[i] = 0 then inc(nulls);
    componenta := nulls;
    //ShowMessage('nulls '+inttostr(componenta));

    {for i:=1 to number do
      ShowMessage(IntToStr(summa[i])); }

    for i:=1 to number do
    begin
      if summa[i]<>0 then
        container := summa[i] - 1;
      for j:=1 to number do
        if (summa[i] = summa[j]) and ((container>0) and (i<>j)) then
        begin
          summa[j] := 0;
          Dec(container);
        end;
      {for j:=1 to number do
        ShowMessage(IntToStr(i)+' '+IntToStr(summa[j]));}
    end;

    {for i:=1 to number do
      ShowMessage(IntToStr(summa[i]));}
    for i:=1 to number do
      if summa[i]<>0 then Inc(componenta);
    ShowMessage('Компонента зв''язності -> '+IntToStr(componenta));
  end;

procedure TForm1.N11Click(Sender: TObject);
  begin
    if componenta=1 then
      ShowMessage('Граф зв''язний')
    else
      ShowMessage('Граф не зв''язний');
  end;

end.
