program Long5;

function square(l: longint): longint;
begin
  square := l * l;
end;

begin
  writeln(square(123456789));
end.