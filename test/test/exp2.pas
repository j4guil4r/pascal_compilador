program Expr2;
var
  x: integer;
  y: longint;
  z: unsignedint;
begin
  x := 10;
  y := 20;
  z := 30;
  if (x < y) and (y <= z) or (z > 0) then begin
    writeln(1);
  end;
end.