program Control6;
var
  i, j: integer;
begin
  i := 1;

  while i <= 3 do
  begin
    j := 1;
    while j <= 3 do
    begin
      writeln(j);
      j := j + 1;
    end;
    i := i + 1;
  end;
end.
