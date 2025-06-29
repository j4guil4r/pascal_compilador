program Expr3;
var
  flag1, flag2: integer;
begin
  flag1 := 1;
  flag2 := 0;
  if (flag1 = 1) and not (flag2 = 1) then begin
    writeln(1);
  end;
end.