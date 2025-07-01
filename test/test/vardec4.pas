program VarDeclTester;
var
  a, b, c: integer;
  x, y, z: longint;
  u, v, w: unsignedint;
  flag1, flag2: boolean;
  num1, num2: integer;
  big1, big2: longint;
  uns1, uns2: unsignedint;
  check: boolean;

begin
  a := 10;
  b := -20;
  c := a + b;

  x := 1000000000;
  y := -2000000000;
  z := x * 2;

  u := 42;
  v := 100;
  w := v - u;

  flag1 := true;
  flag2 := false;
  check := flag1 and flag2;

  num1 := 50;
  num2 := -30;
  big1 := 3000000000;
  big2 := -big1;
  uns1 := 65535;
  uns2 := uns1 div 2;

  writeln(a, b, c);
  writeln(x, y, z);
  writeln(u, v, w);
  writeln(flag1, flag2, check);
  writeln(num1, num2);
  writeln(big1, big2);
  writeln(uns1, uns2);
end.