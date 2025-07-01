program Unsigned5;

function double(u: unsignedint): unsignedint;
begin
  double := u * 2;
end;

begin
  writeln(double(30000));
end.