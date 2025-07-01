program Control5;
var
  i, j, k: integer;
  counter: longint;
  flag: boolean;
begin
  i := 1;
  counter := 0;
  flag := true;

  while i <= 3 do
  begin
    for j := 1 to 4 do
    begin
      k := 5;
      while k >= 1 do
      begin
        if (i mod 2 = 0) and flag then
        begin
          counter := counter + (i * j * k);
          writeln(counter);
        end
        else
        begin
          counter := counter + 1;
          writeln(counter);
        end;
        k := k - 1;
      end;
      flag := not flag;
    end;
    i := i + 1;
  end;

  for i := 3 downto 1 do
  begin
    j := i;
    while j > 0 do
    begin
      writeln(i * j);
      j := j - 1;
    end;
  end;
end.