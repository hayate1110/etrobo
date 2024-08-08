#include "Tracer.h" // <1>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2) { // <2>
}

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  msg_f("running...", 1);
  
  float turn = calc_pop_value();
  int pwm_l = pwm - turn;
  int pwm_r = pwm + turn;

  leftWheel.setPWM(pwm_l); 
  rightWheel.setPWM(pwm_r); 
}

float Tracer::calc_pop_value() {
  printf("%d\n", colorSensor.getBrightness());
  const float Kp = 1;
  const int target = 20;
  const int bias = -25;
  int diff = colorSensor.getBrightness() - target;
  return Kp*diff+bias;
}
