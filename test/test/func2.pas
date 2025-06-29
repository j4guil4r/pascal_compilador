program Func2;

function factorial(n: integer): longint;
begin
  if n <= 1 then begin
    factorial := 1;
  end
  else begin
    factorial := n * factorial(n - 1);
  end;
end;

begin
  writeln(factorial(20));
end.