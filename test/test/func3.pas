program Func3;

function max(a: integer; b: integer; c: integer): integer;
begin
  if (a >= b) and (a >= c) then begin
    max := a;
  end
  else begin
    if b >= c then begin
        max := b;
    end
    else begin
        max := c;
    end;
  end;
end;

begin
  writeln(max(10, 20, 15));
end.