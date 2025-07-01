program mega_test;
var
  x, y, z, i, counter: integer;
  flag: boolean;

function max(a, b: integer): integer;
begin
  if a > b then begin
    max := a;
  end
  else begin
    max := b;
  end;
end;

procedure print_result(val: integer);
begin
  writeln(val);
end;

begin
  x := 10;
  y := 3;
  z := x div y;
  print_result(z);
  z := x mod y;
  print_result(z);
  z := -x mod y;
  print_result(z);
  z := x * y + 5;
  print_result(z);


  flag := (x > y) and (z <> 0);
  if flag then begin
    writeln(1);
  end
  else begin
    writeln(0);
  end;


  counter := 0;
  for i := 1 to 5 do
  begin
    while counter < i do
    begin
      counter := counter + 1;
    end;
  end;
  writeln(5, counter);


  z := max(x, y);
  print_result(z);
  print_result(max(z, 100));

  if x > 0 then
  begin
    if y < 5 then begin
      writeln(6666);
    end
    else begin
      writeln(555555);
    end;
  end
  else begin
    writeln(222222);
  end;

  writeln(333333333);
  for i := -10 to 10 do
  begin
    if i mod 2 = 0 then begin
      writeln(i, 0);
    end
    else begin
      writeln(i, 1);
    end;
  end;
end.