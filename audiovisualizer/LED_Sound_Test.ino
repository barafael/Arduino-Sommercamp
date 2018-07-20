#define NOISE_LEVEL_0 500
#define BENCHMARK_PIN 3
void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(BENCHMARK_PIN, OUTPUT);
}

int brightness = 0;
int Amp = 0;

void loop() {
  //Serial.println(analogRead(A5));
  digitalWrite(BENCHMARK_PIN, HIGH);

  int Volt = analogRead(A5);
  digitalWrite(BENCHMARK_PIN, LOW);
  float next = MAF_next(Volt);
  Serial.println(next);

  if (Volt >= NOISE_LEVEL_0) {
    Amp = Volt - NOISE_LEVEL_0;
  }
  else if (Volt < NOISE_LEVEL_0) {
    Amp = NOISE_LEVEL_0 - Volt;
  }


  //brightness = (Amp / NOISE_LEVEL_0) * 255;
  //analogWrite(6, brightness);
  //delay(1);
}

int marker = 0;
const int MAF_N = 32;
float values[MAF_N];
float MAF_next(float value) {
  marker = (marker + 1) % MAF_N;
  values[marker] = value;
  float sum = 0;
  for (size_t index = 0; index < MAF_N; index++) {
    sum += values[index];
  }
  return sum / MAF_N;
}
