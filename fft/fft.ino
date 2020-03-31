#include "arduinoFFT.h"
#include "pitches.h"


#define SAMPLES 64
#define SAMPLING_F 2048

arduinoFFT FFT = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

double p;
double seq[6];
char chords[7];
char prevChord;
int seqLength = 6;

void setup() {
  Serial.begin(115200);
  samplingPeriod = round(1000000*(1.0/SAMPLING_F));
  chords[6] = NULL;
}


void loop() {
  delay(300);
  playSariasSong();
  
  p = fft();
  Serial.println(p);
  nextSequence(p);
  seqToChords();
  
  String strchords(chords);
  Serial.println(strchords);
  
  if(strchords.equals("ADFADF")){
    Serial.println("SONG OF TIME");
    playSecret();
    delay(1000);
    playSongOfTime();
    delay(5000);
  } else if (strchords.equals("DFdDFd")){
    Serial.println("SONG OF STORMS");
    playSecret();
    delay(1000);
    playSongOfStorms();
    delay(5000);
  }

}

double fft(){
  // put your main code here, to run repeatedly:
  for(int i=0; i<SAMPLES; i++){
    microSeconds = micros();
    vReal[i] = analogRead(0);
    vImag[i] = 0;

    while(micros() < (microSeconds + samplingPeriod)){
      //do nothing    
    }
  }

  //perform fft
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  //find peak frequency
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_F);
  //Serial.println(peak);

  return(peak);
}


void nextSequence(double last){
  if(prevChord == hzToChord(last)){
    return;
  }
  
  for(int i=1; i<seqLength; i++){
    seq[i-1] = seq[i];
  }
  seq[seqLength-1] = last;
  prevChord = hzToChord(last);
}

char hzToChord(double hz){
  if(860 < hz && hz < 910){
      return 'A';
    }
    else if(570 < hz && hz < 630){
      return 'D';
    }
    else if(690 < hz && hz < 740){
      return 'F';
    }
    else if(950 < hz && hz < 980){
      return 'd';
    } else {
      return prevChord;
    }
  
}

void seqToChords(){
  for(int i=0; i<seqLength; i++){
    double hz = seq[i];
    chords[i] = hzToChord(hz);
  }
}

void playSecret(){
  int melody[] = {
  NOTE_G5, NOTE_FS5, NOTE_DS5, NOTE_A4, NOTE_GS4, NOTE_E5, NOTE_GS5, NOTE_C6
  };

  int songLength = sizeof(melody)/sizeof(melody[0]);

  for (int note = 0; note < songLength; note++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    tone(8, melody[note], 1000);
    // pause between notes
    int pause =  1.3*100;
    delay(pause);
    // stop the tone
    noTone(8);
  } 
}

void playSongOfTime(){
  int melody[] = {
  NOTE_A5, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_D5, NOTE_F5, 
  NOTE_A5, NOTE_B5, NOTE_AS5, NOTE_FS5, NOTE_F5, NOTE_FS5,
  NOTE_A5, NOTE_D5, NOTE_CS5, NOTE_DS5, NOTE_D5
  };

  // The note duration, 8 = 8th note, 4 = quarter note, etc.
  int durations[] = {
    4, 2, 4, 4, 2, 4, 
    8, 8, 4, 4, 8, 8, 
    4, 4, 8, 8, 2
  };
  int songLength = sizeof(melody)/sizeof(melody[0]);

  for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(8, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 2;
    delay(pause);
    // stop the tone
    noTone(8);
  }
}

void playSongOfStorms(){
  int melody[] = {
  NOTE_D5, NOTE_F5, NOTE_D6, NOTE_D5, NOTE_F5, NOTE_D6, 
  NOTE_E6, NOTE_F6, NOTE_E6, NOTE_F6, NOTE_E6, NOTE_C6,
  NOTE_A5, NOTE_A5, NOTE_D5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_A5, NOTE_D5, NOTE_F5, NOTE_G5, NOTE_E5,
  };

  // The note duration, 8 = 8th note, 4 = quarter note, etc.
  int durations[] = {
    6, 6, 2, 6, 6, 2, 
    3, 6, 6, 6, 6, 6, 
    2, 3, 3, 6, 6, 1,
    3, 3, 6, 6, 1
  };
  int songLength = sizeof(melody)/sizeof(melody[0]);

  for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(8, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.5;
    delay(pause);
    // stop the tone
    noTone(8);
  }
}

void playSariasSong(){
  int melody[] = {
  NOTE_F5, NOTE_G5, NOTE_GS5, NOTE_F5, NOTE_G5, NOTE_GS5, 
  NOTE_F5, NOTE_FS5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_GS5,
  NOTE_FS5, NOTE_A5, NOTE_D5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_A5, NOTE_D5
  };

  // The note duration, 8 = 8th note, 4 = quarter note, etc.
  int durations[] = {
    8, 8, 4, 8, 8, 4, 
    8, 8, 8, 8, 4, 8, 
    8, 8, 8, 4, 4, 4,
    8, 8, 2, 6, 1
  };
  int songLength = sizeof(melody)/sizeof(melody[0]);

  for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(8, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.5;
    delay(pause);
    // stop the tone
    noTone(8);
  }
}
