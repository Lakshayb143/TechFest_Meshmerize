String checkReplacement(String temp)
{
  // Serial.println();
  // Serial.println("In checkReplacement");
  // Serial.println("Paramter String: " +  temp);
  // Serial.println();
  String ret = temp;
  if (temp.equalsIgnoreCase("LUR"))
    ret = "U";
  if (temp.equalsIgnoreCase("LUS"))
    ret = "R";
  if (temp.equalsIgnoreCase("RUL"))
    ret = "U";
  if (temp.equalsIgnoreCase("SUL"))
    ret = "R";
  if (temp.equalsIgnoreCase("SUS"))
    ret = "U";
  if (temp.equalsIgnoreCase("LUL"))
    ret = "S";

  return ret;
}


void endOfMaze()
{

  digitalWrite(RIN1, LOW);
  digitalWrite(RIN2, LOW);
  digitalWrite(LIN1, LOW);
  digitalWrite(LIN2, LOW);

  digitalWrite(LEDPIN, HIGH);

  run_ID = 1;

  path_ID = 0;

  path.trim();

  optimizePath(path);
  delay(10000);
}


void turn(char dir)
{
  switch (dir)
  {
  case 'R':
    digitalWrite(RIN1, LOW);
    digitalWrite(RIN2, LOW);
    digitalWrite(LIN1, HIGH);
    digitalWrite(LIN2, LOW);
    break;
  case 'L':
    digitalWrite(RIN1, HIGH);
    digitalWrite(RIN2, LOW);
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, LOW);
    break;
  case 'S':
    digitalWrite(RIN1, LOW);
    digitalWrite(RIN2, HIGH);
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, HIGH);
    break;
  case 'U':
    digitalWrite(RIN1, HIGH);
    digitalWrite(RIN2, LOW);
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, HIGH);
    break;

  default:
    Serial.println("Oh Boy!");
  }
}