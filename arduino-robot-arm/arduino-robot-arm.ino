#include <Servo.h>          // 서보 모터 제어에 필요한 라이브러리를 불러옵니다.
#include <SoftwareSerial.h> // 블루투스 통신에 필요한 라이브러리를 불러옵니다.

Servo servo1; Servo servo2; Servo servo3; Servo servo4; Servo servo5; Servo servo6; Servo servo7; // 서보 모터 제어를 위한 객체를 선언합니다.
// 시계·반시계 방향 회전 축
// 제1축
// 제2축
// 제3축
// 제4축
// 좌측 집게
// 우측 집게

SoftwareSerial bt(2, 3); // 블루투스 통신을 위한 객체를 선언합니다.

String myString=""; // 블루투스 통신으로 받은 문자열을 저장할 변수를 선언합니다.
int first; int second; int third; int fourth; int fifth; int sixth; // 블루투스 통신으로 받은 문자열의 구분자 인덱스를 저장할 변수를 선언합니다.
String str1; String str2; String str3; String str4; String str5; String str6; // 블루투스 통신으로 받은 문자열을 구분자로 구분 지어 저장할 변수를 선언합니다.
int angle1; int angle2; int angle3; int angle4; int angle5; int angle6; int angle7; // 블루투스 통신으로 문자열을 받은 후 서보 모터 제어 각도를 정수로 저장할 변수를 선언합니다.

void setup() {
  servo1.attach(12); servo2.attach(11); servo3.attach(10); servo4.attach(9);  servo5.attach(8); // 서보 모터의 핀 번호를 지정하고 PWM 신호를 보냅니다.
  // 왼쪽 180 | 오른쪽 0
  // 펼침 65  | 굽힘 150
  // 펼침 100 | 굽힘 10
  // 펼침 90  | 굽힘 180
  // 펼침 100 | 굽힘 10
  
  servo6.attach(7); servo7.attach(6); // 서보 모터의 핀 번호를 지정하고 PWM 신호를 보냅니다.
  // (좌측 집게) 놓음 170 | 잡음 75
  // (우측 집게) 놓음 0   | 잡음 95
  
  bt.begin(9600);     // 블루투스 통신을 시작합니다.
  Serial.begin(9600); // 모니터링을 위해 시리얼 통신을 시작합니다.

  servo1.write(90); servo2.write(65); servo3.write(100); servo4.write(90); servo5.write(10); servo6.write(75); servo7.write(95); // 서보 모터를 초기 각도로 설정합니다.
}

void loop() {
  /* 블루투스 통신으로 받은 문자열을 합칩니다. */
  while(bt.available()) {
    char myChar=(char)bt.read();
    myString+=myChar;
    delay(5);
  }

  /* 블루투스 통신으로 받은 문자열이 있다면 */
  if(!myString.equals("")) {
    /* 블루투스 통신으로 받은 문자열의 구분자의 인덱스를 변수에 저장합니다. */
    first=myString.indexOf(","); second=myString.indexOf(",", first+1); third=myString.indexOf(",", second+1); fourth=myString.indexOf(",", third+1); fifth=myString.indexOf(",", fourth+1); sixth=myString.indexOf(",", fifth+1); len=myString.length();
    /* 블루투스 통신으로 받은 문자열을 구분자로 구분 지어 변수에 저장합니다. */
    str1=myString.substring(0, first); str2=myString.substring(first+1, second); str3=myString.substring(second+1, third); str4=myString.substring(third+1, fourth); str5=myString.substring(fourth+1, fifth); str6=myString.substring(fifth+1, len);
    /* 블루투스 통신으로 받아 구분자로 구분 지은 문자열을 정수로 변환하여 변수에 저장합니다. */
    angle1=map(str1.toInt(), 0, 100, 180, 0); angle2=map(str2.toInt(), 0, 100, 65, 150); angle3=map(str3.toInt(), 0, 100, 100, 0); angle4=map(str4.toInt(), 0, 100, 90, 180); angle5=map(str5.toInt(), 0, 100, 100, 10); angle6=map(str6.toInt(), 0, 100, 170, 75); angle7=map(str6.toInt(), 0, 100, 0, 95);
    /* 블루투스 통신으로 받은 값대로 서보 모터를 제어합니다. */
    servo1.write(angle1); servo2.write(angle2); servo3.write(angle3); servo4.write(angle4); servo5.write(angle5); servo6.write(angle6); servo7.write(angle7);
    
    myString=""; // 문자열 변수를 초기화합니다.
  }
}
